#if !defined(TNT_RENDER_TYPES_H)
#define TNT_RENDER_TYPES_H

#include "tnt_math.h"
#include "tnt_string.h"

typedef u32 R_DrawingMode;
enum R_DrawingMode {
  DRAWING_MODE_POINTS,
  DRAWING_MODE_LINES,
  DRAWING_MODE_TRIANGLES,
};

typedef u32 R_AttribDataType;
enum R_AttribDataType {
  ATTRIB_DATA_TYPE_FLOAT,
  ATTRIB_DATA_TYPE_INT,
};

typedef u32 R_ModelStatic;
enum R_ModelStatic {
  MODEL_STATIC_QUAD,
  MODEL_STATIC_CUBE,
};

typedef struct R_VertexAttribs R_VertexAttribs;
struct R_VertexAttribs {
  u64 size;
  R_AttribDataType data_type;
  u64 stride;
  u64 pointer;
};

typedef struct R_Vertex2D R_Vertex2D;
struct R_Vertex2D {
  Vec2 position;
  Vec4 color;
};

typedef struct R_Vertex3D R_Vertex3D;
struct R_Vertex3D {
  Vec3 position;
  Vec4 color;
};

typedef struct R_Texture R_Texture;
struct R_Texture {
  u32 id;
  String8 type;
  String8 path;
};

typedef struct R_Mesh R_Mesh;
struct R_Mesh {
  u32 vbo, vao, ebo;

  R_Vertex3D *vertices;
  u64 vertices_count;

  u64 *indices;
  u64 indices_count;

  R_Texture *textures;
  u64 textures_count;
};

typedef struct R_Model R_Model;
struct R_Model {
  R_Mesh *meshes;
  u64 meshes_count;
};

typedef struct R_Sprite R_Sprite;
struct R_Sprite {
  R_Texture *texture;
};

typedef struct GameObject GameObject;
struct GameObject {
  u64 uuid;
  Transform transform;
  R_Sprite sprite;
  R_Model model;
};

typedef void R_WindowHandle;
typedef void R_ContextHandle;
typedef u32 R_ShaderHandle;

#endif  // TNT_RENDER_TYPES_H
