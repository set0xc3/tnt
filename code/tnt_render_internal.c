#include <SDL2/SDL_video.h>
#include <glad/glad.h>
#include <stdio.h>

#include "tnt_base_types.h"
#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_render.h"
#include "tnt_render_types.h"
#include "tnt_string.h"

internal void gl_init(R_WindowHandle *window);
internal void gl_destroy(R_WindowHandle *window);
internal void gl_begin(R_WindowHandle *window, R_ContextHandle *context,
                       Vec4 viewport);
internal void gl_flush(R_DrawingMode drawing_mode, u64 vertices_count,
                       u64 indices_count);
internal void gl_end(R_WindowHandle *window);
internal void gl_window_select(R_WindowHandle *window, R_ContextHandle *ctx);
internal u32 gl_shader_load(String8 vs_path, String8 fs_path, String8 gs_path);
internal void gl_shader_bind(u32 id);
internal u32 gl_index_buffer_create(void *buffer, u64 size);
internal void gl_index_buffer_bind(u32 id);
internal u32 gl_vertex_buffer_create(void *buffer, u64 size);
internal void gl_vertex_buffer_bind(u32 id);
internal void gl_vertex_buffer_update(void *buffer, u64 size);
internal u32 gl_frame_buffer_create(void *buffer, u64 size);
internal void gl_frame_buffer_bind(u32 id);
internal u32 gl_render_buffer_create(u32 width, u32 height);
internal void gl_render_buffer_bind(u32 id);
internal u32 gl_vertex_array_create(u32 vbo, u32 ebo, R_VertexAttribs *attribs,
                                    u32 size);
internal void gl_vertex_array_bind(u32 id);
internal void gl_uniform_mat4_set(u32 id, String8 name, f32 *mat);
internal void gl_set_depth_state(b32 enabled);

internal void push_quad(RenderContext *render, Vec2 position, Vec2 size,
                        Vec4 color);

internal void gl_init(R_WindowHandle *window) {
  if (gladLoadGL() == 0) {
    LOG_ERROR("Failed load glad");
    ASSERT(true);
    exit(1);
  }
}

internal void gl_destroy(R_WindowHandle *window) {
  SDL_GL_DeleteContext(window);
}

internal void gl_begin(R_WindowHandle *window, R_ContextHandle *context,
                       Vec4 viewport) {
  gl_window_select(window, context);

  glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

internal void gl_flush(R_DrawingMode drawing_mode, u64 vertices_count,
                       u64 indices_count) {
  u32 mode = 0;
  switch (drawing_mode) {
    case DRAWING_MODE_POINTS:
      mode = GL_POINTS;
      break;
    case DRAWING_MODE_LINES:
      mode = GL_LINES;
      break;
    case DRAWING_MODE_TRIANGLES:
      mode = GL_TRIANGLES;
      break;
  }

  if (indices_count == 0) {
    glDrawArrays(mode, 0, vertices_count);
  } else {
    glDrawElements(mode, indices_count, GL_UNSIGNED_INT, 0);
  }
}

internal void gl_end(R_WindowHandle *window) {
  SDL_GL_SwapWindow((SDL_Window *)window);
}

internal void gl_window_select(R_WindowHandle *window,
                               R_ContextHandle *context) {
  SDL_GL_MakeCurrent((SDL_Window *)window, (SDL_GLContext)context);
}

internal u32 gl_shader_load(String8 vs_path, String8 fs_path, String8 gs_path) {
  u32 result = 0;
  i32 success = 0;
  char buffer_log[4096] = {0};

  String8 vs_source = os_file_read(vs_path);
  String8 fs_source = os_file_read(fs_path);
  String8 gs_source = os_file_read(gs_path);

  // Create and compile vertex shader
  u32 vs_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs_id, 1, (const GLchar **)&vs_source.data,
                 (GLint *)&vs_source.size);
  glCompileShader(vs_id);
  glGetShaderiv(vs_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs_id, 4096, 0, buffer_log);
    LOG_ERROR("Shader vertex compilation failed: %s", buffer_log);
  }

  // Create and compile fragment shader
  u32 fs_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs_id, 1, (const GLchar **)&fs_source.data,
                 (GLint *)&fs_source.size);
  glCompileShader(fs_id);
  glGetShaderiv(fs_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fs_id, 4096, 0, buffer_log);
    LOG_ERROR("Shader fragment compilation failed: %s", buffer_log);
  }

  u32 gs_id = 0;
  if (str_len(gs_source)) {
    // Create and compile fragment shader
    gs_id = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gs_id, 1, (const GLchar **)&gs_source.data,
                   (GLint *)&gs_source.size);
    glCompileShader(gs_id);
    glGetShaderiv(gs_id, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(gs_id, 4096, 0, buffer_log);
      LOG_ERROR("Shader geometry compilation failed: %s", buffer_log);
    }
  }

  // Create program, attach shaders to it, and link it
  result = glCreateProgram();
  glAttachShader(result, vs_id);
  glAttachShader(result, fs_id);
  if (str_len(gs_source)) {
    glAttachShader(result, gs_id);
  }
  glLinkProgram(result);

  // Clear
  glDeleteShader(vs_id);
  glDeleteShader(fs_id);
  if (str_len(gs_source)) {
    glDeleteShader(gs_id);
  }

  return result;
}

internal void gl_shader_bind(u32 id) { glUseProgram(id); }

internal u32 gl_index_buffer_create(void *buffer, u64 size) {
  u32 id = 0;
  glCreateBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer,
               buffer ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
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
  glBufferData(GL_ARRAY_BUFFER, size, buffer,
               buffer ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
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
  glBufferData(GL_FRAMEBUFFER, size, buffer,
               buffer ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
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

internal u32 gl_vertex_array_create(u32 vbo, u32 ebo, R_VertexAttribs *attribs,
                                    u32 size) {
  u32 attrib_type = 0;
  if (attribs->data_type == R_FLOAT) {
    attrib_type = GL_FLOAT;
  } else if (attribs->data_type == R_INT) {
    attrib_type = GL_INT;
  }

  u32 id = 0;
  glCreateVertexArrays(1, &id);
  glBindVertexArray(id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  for (u64 i = 0; i < size; i += 1) {
    R_VertexAttribs *attrib = &attribs[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attrib->size, attrib_type, GL_FALSE,
                          attrib->stride, (void *)attrib->pointer);
  }
  return id;
}

internal void gl_vertex_array_bind(u32 id) { glBindVertexArray(id); }

internal void gl_uniform_mat4_set(u32 id, String8 name, f32 *mat) {
  i32 uniform_location = glGetUniformLocation(id, str8_to_char(name));
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, mat);
}

internal void gl_set_depth_state(b32 enabled) {
  if (enabled) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

internal void push_quad(RenderContext *render, Vec2 position, Vec2 size,
                        Vec4 color) {
  if (render->quad_buffer_idx == QUAD_MAX) {
    LOG_WARNING("QUAD MAX!");
    return;
  }

  f32 x = position.x;
  f32 y = position.y;
  f32 w = size.x;
  f32 h = size.y;

  R_Vertex2D vertices[] = {
      {v2(x, y), color},         {v2(x + w, y), color},
      {v2(x + w, y + h), color},

      {v2(x + w, y + h), color}, {v2(x, y + h), color},
      {v2(x, y), color},
  };

  u64 offset = render->quad_buffer_idx * 6;
  render->quad_vertices[offset + 0] = vertices[0];
  render->quad_vertices[offset + 1] = vertices[1];
  render->quad_vertices[offset + 2] = vertices[2];
  render->quad_vertices[offset + 3] = vertices[3];
  render->quad_vertices[offset + 4] = vertices[4];
  render->quad_vertices[offset + 5] = vertices[5];
  render->quad_buffer_idx += 1;
}
