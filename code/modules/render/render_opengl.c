#include "render_opengl.h"
#include "tnt_render.h"
#include "tnt_types.h"
#include "tnt_types_platform.h"
#include "tnt_logger.h"
#include "tnt_string.h"
#include "tnt_os.h"

#include <stdio.h>

#include <glad/glad.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>

EXPORT TNT_RenderAPI api = {
	"1.0.0",
	gl_init,
	gl_destroy,
	gl_begin,
	gl_flush,
	gl_end,
	gl_shader_load,
	gl_shader_bind,
	gl_index_buffer_create,
	gl_index_buffer_bind,
	gl_vertex_buffer_create,
	gl_vertex_buffer_bind,
	gl_vertex_buffer_update,
	gl_frame_buffer_create,
	gl_frame_buffer_bind,
	gl_render_buffer_create,
	gl_render_buffer_bind,
	gl_vertex_array_create,
	gl_vertex_array_bind,
};

internal void gl_init(R_Window *window) {
	if (gladLoadGL() == 0) {
		LOG_ERROR("Failed load glad");
		ASSERT(true);
		exit(1);
  }
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

internal void gl_flush(R_Window *window, R_Mesh *mesh) {
	glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
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

internal void gl_shader_bind(u32 id) {
	glUseProgram(id);
}

internal u32 gl_index_buffer_create(void *buffer, u64 size) {
	u32 id = 0;
	glCreateBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, buffer ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return id;
}

internal void gl_index_buffer_bind(u32 id) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

internal u32 gl_vertex_buffer_create(void *buffer, u64 size) {
	u32 id = 0;
	glCreateBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, buffer ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return id;
}

internal void gl_vertex_buffer_bind(u32 id) {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

internal void gl_vertex_buffer_update(void *buffer, u64 size) {
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, buffer);
}

internal u32 gl_frame_buffer_create(void *buffer, u64 size) {
	u32 id = 0;
	glCreateFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glBufferData(GL_FRAMEBUFFER, size, buffer, buffer ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	glBindBuffer(GL_FRAMEBUFFER, 0);
	return id;
}

internal void gl_frame_buffer_bind(u32 id) {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

internal u32 gl_render_buffer_create(u32 width, u32 height) {
	u32 id = 0;
	glCreateRenderbuffers(1, &id);
	glBindRenderbuffer(GL_RENDERBUFFER, id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	return id;
}

internal void gl_render_buffer_bind(u32 id) {
	glBindRenderbuffer(GL_RENDERBUFFER, id);
}

internal u32 gl_vertex_array_create(u32 vbo_id, void *buffer, u64 size) {
	u32 id = 0;
	glCreateVertexArrays(1, &id);
	glBindVertexArray(id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(R_VertexData), (void *)offsetof(R_VertexData, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(R_VertexData), (void *)offsetof(R_VertexData, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(R_VertexData), (void *)offsetof(R_VertexData, uv));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return id;
}

internal void gl_vertex_array_bind(u32 id) {
	glBindVertexArray(id);
}

