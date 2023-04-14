#include "tnt_render.h"
#include "tnt_os.h"

b8 render_load(TNT_Render *ctx, String8 path) {
  ctx->handle = os_library_load(path);
  if (!ctx->handle) {
    return false;
  }
  ctx->api = os_library_load_symbol(ctx->handle, str8("api"));
  return true;
}

void render_unload(TNT_Render *ctx) { 
	os_library_unload(ctx->handle); 
}
