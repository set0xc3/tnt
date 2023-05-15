#if !defined(TNT_RENDER_TYPES_H)
#define TNT_RENDER_TYPES_H

#include "tnt_math.h"
#include "tnt_string.h"

typedef enum R_DrawingMode {
  DRAWING_MODE_POINTS,
  DRAWING_MODE_LINES,
  DRAWING_MODE_TRIANGLES,
} R_DrawingMode;

typedef enum R_DataType {
  R_FLOAT,
  R_INT,
} R_DataType;

typedef enum R_ModelStatic {
  MODEL_STATIC_QUAD,
  MODEL_STATIC_CUBE,
} R_ModelStatic;

typedef struct R_VertexAttribs {
  u64 size;
  R_DataType data_type;
  u64 stride;
  u64 pointer;
} R_VertexAttribs;

typedef struct R_Vertex2D {
  Vec2 position;
  Vec4 color;
} R_Vertex2D;

typedef struct R_Vertex3D {
  Vec3 position;
  Vec4 color;
} R_Vertex3D;

typedef struct R_Texture {
  u32 id;
  String8 type;
  String8 path;
} R_Texture;

typedef struct R_Mesh {
  R_Vertex3D *vertices;
  u64 vertices_count;

  u64 *indices;
  u64 indices_count;

  R_Texture *textures;
  u64 textures_count;
} R_Mesh;

typedef struct R_Model {
  u32 vbo, vao, ebo;
  R_Mesh *meshes;
  u64 meshes_count;
} R_Model;

typedef struct R_Sprite {
  R_Texture *texture;
} R_Sprite;

typedef void R_WindowHandle;
typedef void R_ContextHandle;
typedef u32 R_ShaderHandle;

#endif  // TNT_RENDER_TYPES_H
