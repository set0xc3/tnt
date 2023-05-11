#include "tnt_render.h"

#include "tnt_base_types.h"
#include "tnt_camera.h"
#include "tnt_logger.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_internal.c"
#include "tnt_render_types.h"

void render_init(RenderState* render, OS_Window* window) {
  gl_init(window->handle);

  render->shader_2d =
      gl_shader_load(str8("./assets/shaders/2d_vs.glsl"),
                     str8("./assets/shaders/2d_fs.glsl"), str8(""));

  render->shader_3d =
      gl_shader_load(str8("./assets/shaders/3d_vs.glsl"),
                     str8("./assets/shaders/3d_fs.glsl"), str8(""));

  render->shader_grid =
      gl_shader_load(str8("./assets/shaders/grid_vs.glsl"),
                     str8("./assets/shaders/grid_fs.glsl"), str8(""));

  R_VertexAttribs attribs[] = {{2, ATTRIB_DATA_TYPE_FLOAT, sizeof(R_Vertex2D),
                                GetMember(R_Vertex2D, position)},
                               {4, ATTRIB_DATA_TYPE_FLOAT, sizeof(R_Vertex2D),
                                GetMember(R_Vertex2D, color)}};
  render->quad_vbo = gl_vertex_buffer_create(NULL, sizeof(render->quad_buffer));
  render->quad_vao =
      gl_vertex_array_create(render->quad_vbo, 0, attribs, ArrayCount(attribs));
}

void render_begin(RenderState* render, OS_Window* window) {
  gl_begin(window->handle, window->render,
           v4(0.0f, 0.0f, window->width, window->height));
}

void render_end(RenderState* render, OS_Window* window) {
  render->quad_buffer_idx = 0;

  gl_end(window->handle);
}

void render_create_model(RenderState* render, R_ModelStatic enum_model,
                         R_Model* out_model) {
  switch (enum_model) {
    case MODEL_STATIC_QUAD: {
      R_VertexAttribs attribs[] = {
          {3, ATTRIB_DATA_TYPE_FLOAT, sizeof(R_Vertex3D),
           GetMember(R_Vertex3D, position)},
          {4, ATTRIB_DATA_TYPE_FLOAT, sizeof(R_Vertex3D),
           GetMember(R_Vertex3D, color)}};
      R_Vertex3D vertices[] = {
          // positions         // colors
          {v3(0.5f, 0.5f, 0.0f), v4(1.0f, 0.0f, 0.0f, 1.0f)},
          {v3(0.5f, -0.5f, 0.0f), v4(0.0f, 1.0f, 0.0f, 1.0f)},
          {v3(-0.5f, -0.5f, 0.0f), v4(0.0f, 0.0f, 1.0f, 1.0f)},
          {v3(-0.5f, 0.5f, 0.0f), v4(1.0f, 1.0f, 0.0f, 1.0f)}};
      u32 indices[] = {
          0, 1, 3,  // first triangle
          1, 2, 3   // second triangle
      };
      out_model->meshes = os_memory_alloc(0, sizeof(R_Mesh));
      out_model->meshes->indices = os_memory_alloc(0, sizeof(indices));
      out_model->vbo = gl_vertex_buffer_create(vertices, sizeof(vertices));
      out_model->ebo = gl_index_buffer_create(indices, sizeof(indices));
      out_model->vao = gl_vertex_array_create(out_model->vbo, out_model->ebo,
                                              attribs, ArrayCount(attribs));
      out_model->meshes->vertices = vertices;
      out_model->meshes->vertices_count = ArrayCount(vertices);
      out_model->meshes->indices = (u64*)indices;
      out_model->meshes->indices_count = ArrayCount(indices);
      out_model->meshes_count = 1;
    } break;
    case MODEL_STATIC_CUBE: {
      R_VertexAttribs attribs[] = {
          {3, ATTRIB_DATA_TYPE_FLOAT, sizeof(R_Vertex3D),
           GetMember(R_Vertex3D, position)},
          {4, ATTRIB_DATA_TYPE_FLOAT, sizeof(R_Vertex3D),
           GetMember(R_Vertex3D, color)}};
      R_Vertex3D vertices[] = {{v3(-1.0f, -1.0f, -1.0f), COLOR_RED},
                               {v3(1.0f, -1.0f, -1.0f), COLOR_GREEN},
                               {v3(1.0f, 1.0f, -1.0f), COLOR_BLUE},
                               {v3(1.0f, 1.0f, -1.0f), COLOR_BLUE},
                               {v3(-1.0f, 1.0f, -1.0f), COLOR_GREEN},
                               {v3(-1.0f, -1.0f, -1.0f), COLOR_RED},

                               {v3(-1.0f, -1.0f, 1.0f), COLOR_RED},
                               {v3(1.0f, -1.0f, 1.0f), COLOR_GREEN},
                               {v3(1.0f, 1.0f, 1.0f), COLOR_BLUE},
                               {v3(1.0f, 1.0f, 1.0f), COLOR_BLUE},
                               {v3(-1.0f, 1.0f, 1.0f), COLOR_GREEN},
                               {v3(-1.0f, -1.0f, 1.0f), COLOR_RED},

                               {v3(-1.0f, 1.0f, 1.0f), COLOR_RED},
                               {v3(-1.0f, 1.0f, -1.0f), COLOR_GREEN},
                               {v3(-1.0f, -1.0f, -1.0f), COLOR_BLUE},
                               {v3(-1.0f, -1.0f, -1.0f), COLOR_BLUE},
                               {v3(-1.0f, -1.0f, 1.0f), COLOR_GREEN},
                               {v3(-1.0f, 1.0f, 1.0f), COLOR_RED},

                               {v3(1.0f, 1.0f, 1.0f), COLOR_RED},
                               {v3(1.0f, 1.0f, -1.0f), COLOR_GREEN},
                               {v3(1.0f, -1.0f, -1.0f), COLOR_BLUE},
                               {v3(1.0f, -1.0f, -1.0f), COLOR_BLUE},
                               {v3(1.0f, -1.0f, 1.0f), COLOR_GREEN},
                               {v3(1.0f, 1.0f, 1.0f), COLOR_RED},

                               {v3(-1.0f, -1.0f, -1.0f), COLOR_RED},
                               {v3(1.0f, -1.0f, -1.0f), COLOR_GREEN},
                               {v3(1.0f, -1.0f, 1.0f), COLOR_BLUE},
                               {v3(1.0f, -1.0f, 1.0f), COLOR_BLUE},
                               {v3(-1.0f, -1.0f, 1.0f), COLOR_GREEN},
                               {v3(-1.0f, -1.0f, -1.0f), COLOR_RED},

                               {v3(-1.0f, 1.0f, -1.0f), COLOR_RED},
                               {v3(1.0f, 1.0f, -1.0f), COLOR_GREEN},
                               {v3(1.0f, 1.0f, 1.0f), COLOR_BLUE},
                               {v3(1.0f, 1.0f, 1.0f), COLOR_BLUE},
                               {v3(-1.0f, 1.0f, 1.0f), COLOR_GREEN},
                               {v3(-1.0f, 1.0f, -1.0f), COLOR_RED}};

      out_model->meshes = os_memory_alloc(0, sizeof(R_Mesh));
      out_model->vbo = gl_vertex_buffer_create(vertices, sizeof(vertices));
      out_model->vao = gl_vertex_array_create(out_model->vbo, out_model->ebo,
                                              attribs, ArrayCount(attribs));
      out_model->meshes->vertices = vertices;
      out_model->meshes->vertices_count = ArrayCount(vertices);
      out_model->meshes_count = 1;
    } break;
    default:
      LOG_WARNING("Модель не найдена!");
      break;
  }
}

void render_draw_line(RenderState* render, Vec2 point1, Vec2 point2,
                      Vec4 color) {
  R_Vertex2D vertices[] = {
      {point1, color},
      {point2, color},
  };

  Mat4 model_matrix = m_identity_m4(1.0f);
  model_matrix =
      m_mul_m4(model_matrix, m_translate(v3(point1.x, point1.y, 0.0f)));

  // gl_uniform_mat4_set(render->shader_3d, str8("model"), *model_matrix.m);
  // gl_shader_bind(render->shader_2d);
  // gl_vertex_buffer_bind(render->vbo_2d);
  // gl_vertex_buffer_update(vertices, sizeof(vertices));
  // gl_vertex_array_bind(render->vao_2d);
  // gl_flush(DRAWING_MODE_LINES, ArrayCount(vertices));
}

void render_draw_rect(RenderState* render, Vec4 rect, Vec4 color) {
  push_quad(render, rect, color);
}
