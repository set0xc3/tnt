#if !defined(TNT_RENDER_TYPES_H)
#define TNT_RENDER_TYPES_H

#include "tnt_math.h"

enum R_DrawingMode
{
	DRAWING_MODE_POINTS,
	DRAWING_MODE_LINES,
	DRAWING_MODE_TRIANGLES,
};

typedef struct R_VertexAttribs R_VertexAttribs;
struct R_VertexAttribs
{
	u64 size;
	u64 type;
	u64 stride;
	u64 pointer;
};

typedef struct R_Vertex2D R_Vertex2D;
struct R_Vertex2D
{
	Vec2 position;
	Vec4 color;
};

typedef struct R_Vertex3D R_Vertex3D;
struct R_Vertex3D
{
	Vec3 position;
	Vec4 color;
};

typedef struct R_Mesh R_Mesh;
struct R_Mesh
{
	R_Vertex3D *vertices;
	u64 vertex_count;
	u64 *indices;
	u64 indices_count;
};

typedef void R_Window;
typedef void R_Context;
typedef u32 R_Shader;

#endif // TNT_RENDER_TYPES_H
