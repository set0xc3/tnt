#if !defined(TNT_RENDER_TYPES_H)
#define TNT_RENDER_TYPES_H

#include "tnt_vector.h"

typedef struct R_VertexData R_VertexData;
struct R_VertexData {
  V3F32 position; // 12 bytes
  V4F32 color;    // 16 bytes
  V2F32 uv;       // 8  bytes
};                // 36 bytes

typedef struct R_Mesh R_Mesh;
struct R_Mesh {
	R_VertexData *vertices;
	u64 vertex_count;
};

typedef void* R_Window;
typedef void* R_Context;

#endif // TNT_RENDER_TYPES_H
