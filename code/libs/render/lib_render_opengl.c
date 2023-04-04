#include "lib_render_opengl.h"
#include "tnt_render.h"
#include "tnt_platform.h"
#include "tnt_logger.h"
#include "tnt_string.h"
#include "tnt_os.h"

#include <stdio.h>

#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>

#define MAX_QUAD_COUNT 1000
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

u32 gl_shader_id = 0;
u32 gl_quad_va, gl_quad_vb, gl_quad_eb = 0;

R_VertexData quad_vertices[MAX_VERTEX_COUNT] = {0};
u32 quad_count = 0;

EXPORT RenderAPI api = {
	"1.0.0",
	gl_init,
	gl_destroy,
	gl_begin,
	gl_flush,
	gl_end,
	gl_shader_load
};

internal void gl_init(R_Window *window) {
	if (gladLoadGL() == 0) {
		LOG_ERROR("Failed load glad");
		ASSERT(true);
		exit(1);
  }
  gl_shader_id = gl_shader_load(
	str8("./assets/shaders/base_vs.glsl"), 
    str8("./assets/shaders/base_fs.glsl"));

	u32 vao, vbo, ebo = 0;
	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(R_VertexData) * MAX_VERTEX_COUNT, 0, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(R_VertexData), (void *)offsetof(R_VertexData, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(R_VertexData), (void *)offsetof(R_VertexData, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(R_VertexData), (void *)offsetof(R_VertexData, uv));

	/* update index buffer */
	u32 indices_buffer[MAX_INDEX_COUNT] = {0};
	u32 offset = 0;
	for (u64 i = 0; i < MAX_INDEX_COUNT; i += 6) {
		indices_buffer[i + 0] = 0 + offset;
		indices_buffer[i + 1] = 1 + offset;
		indices_buffer[i + 2] = 2 + offset;
		indices_buffer[i + 3] = 2 + offset;
		indices_buffer[i + 4] = 3 + offset;
		indices_buffer[i + 5] = 0 + offset;
		offset += 4;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_buffer), indices_buffer, GL_STATIC_DRAW);

	gl_quad_va = vao;
	gl_quad_vb = vbo;
	gl_quad_eb = ebo;
}

internal void gl_destroy(R_Window *window) {
	SDL_GL_DeleteContext(window);
}

internal void gl_begin(R_Window *window, R_Context *context, V4F32 viewport) {
  gl_window_select(window, context);

  glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

internal void gl_flush(R_Window *window) {
	if (quad_count == 0) {
		return;
	}
	glUseProgram(gl_shader_id);
	glBindVertexArray(gl_quad_va);
	glBindBuffer(GL_ARRAY_BUFFER, gl_quad_vb);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(R_VertexData) * MAX_VERTEX_COUNT, quad_vertices);
	glDrawElements(GL_TRIANGLES, quad_count * 6, GL_UNSIGNED_INT, 0);
	quad_count = 0;
}

internal void gl_end(R_Window *window) {
	SDL_GL_SwapWindow((SDL_Window *)window);
}

internal void gl_window_select(R_Window *window, R_Context *context) {
  SDL_GL_MakeCurrent((SDL_Window *)window, (SDL_GLContext)context);
}

internal u32 gl_shader_load(String8 vs_path, String8 fs_path) { 
u32 result = 0;
  i32 success = 0;
  char buffer_log[1024] = {0};

  String8 vs_code = os_file_read(vs_path);
  String8 fs_code = os_file_read(fs_path);

  // Create and compile vertex shader
  u32 vs_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs_id, 1, (const GLchar**)&vs_code.data, 0);
  glCompileShader(vs_id);
  glGetShaderiv(vs_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs_id, 4096, 0, buffer_log);
    LOG_ERROR("Shader vertex compilation failed: %s", buffer_log);
  }

  // Create and compile fragment shader
  u32 fs_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs_id, 1, (const GLchar**)&fs_code.data, 0);
  glCompileShader(fs_id);
  glGetShaderiv(vs_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fs_id, 4096, 0, buffer_log);
    LOG_ERROR("Shader fragment compilation failed: %s", buffer_log);
  }

  // Create program, attach shaders to it, and link it
  result = glCreateProgram();
  glAttachShader(result, vs_id);
  glAttachShader(result, fs_id);
  glLinkProgram(result);

  // Clear
  glDeleteShader(vs_id);
  glDeleteShader(fs_id);

  return result;
}
