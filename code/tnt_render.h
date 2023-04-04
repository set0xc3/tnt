#if !defined(TNT_RENDER_H)
#define TNT_RENDER_H

#include "tnt_types.h"
#include "tnt_string.h"
#include "tnt_vector.h"
#include "tnt_render_types.h"

typedef struct RenderAPI RenderAPI;
struct RenderAPI {
  char *version;
  void (*init)(R_Window *window);
  void (*destroy)(R_Window *window);
  void (*begin)(R_Window *window, R_Context *context, V4F32 viewport);
  void (*flush)(R_Window *window);
  void (*end)(R_Window *window);
  u32  (*shader_load)(String8 vs_path, String8 fs_path);
};

typedef struct Render Render;
struct Render {
  void *handle;
  RenderAPI *api;
};

b8   render_load(Render *ctx, String8 path);
void render_unload(Render *ctx);

#endif // TNT_RENDER_H
