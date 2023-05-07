#if !defined(TNT_RENDER_TYPES_H)
#define TNT_RENDER_TYPES_H

#include "tnt_string.h"
#include "tnt_math.h"

enum R_DrawingMode {
  DRAWING_MODE_POINTS,
  DRAWING_MODE_LINES,
  DRAWING_MODE_TRIANGLES,
};

typedef struct R_VertexAttribs {
  u64 size;
  u64 type;
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
	R_Mesh *meshes;
	u64 meshes_count;
} R_Model;

typedef void R_Window;
typedef void R_Context;
typedef u32 R_Shader;

#endif // TNT_RENDER_TYPES_H
