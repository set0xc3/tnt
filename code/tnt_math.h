/*
 - [ ] vec2
 - [ ] vec3
 - [ ] vec4
 - [ ] mat2
 - [ ] mat3
 - [ ] mat4
 - [ ] quat
 - [ ] euler
 - [ ] color
 - [ ] aabb
*/

#if !defined(TNT_MATH_H)
#define TNT_MATH_H

#include "tnt_types.h"

typedef f32 Mat2[2][2];
typedef f32 Mat3[3][3];
typedef f32 Mat4[4][4];

typedef union Vec2F32 Vec2F32;
union Vec2F32
{
  struct
  {
    f32 x, y;
  };
  f32 v[2];
};

typedef union Vec3F32 Vec3F32;
union Vec3F32
{
  struct
  {
    f32 x, y, z;
  };
  f32 v[3];
};

typedef union Vec4F32 Vec4F32;
union Vec4F32
{
  struct
  {
    f32 x, y, z, w;
  };
  f32 v[4];
};

#define v2f32(x, y) \
  (Vec2F32)         \
  {                 \
    {               \
      x, y          \
    }               \
  }
#define v3f32(x, y, z) \
  (Vec3F32)            \
  {                    \
    {                  \
      x, y, z          \
    }                  \
  }
#define v4f32(x, y, z, w) \
  (Vec4F32)               \
  {                       \
    {                     \
      x, y, z, w          \
    }                     \
  }

#define v2f32_add(a, b)    \
  (Vec2F32)                \
  {                        \
    {                      \
      a.x + b.x, a.y + b.y \
    }                      \
  }
#define v2f32_sub(a, b)    \
  (Vec2F32)                \
  {                        \
    {                      \
      a.x - b.x, a.y - b.y \
    }                      \
  }
#define v2f32_mult(a, b) \
  (Vec2F32)              \
  {                      \
    {                    \
      a.x *b.x, a.y *b.y \
    }                    \
  }
#define v2f32_div(a, b)    \
  (Vec2F32)                \
  {                        \
    {                      \
      a.x / b.x, a.y / b.y \
    }                      \
  }

#define v3f32_add(a, b)               \
  (Vec3F32)                           \
  {                                   \
    {                                 \
      a.x + b.x, a.y + b.y, a.z + b.z \
    }                                 \
  }
#define v3f32_sub(a, b)               \
  (Vec3F32)                           \
  {                                   \
    {                                 \
      a.x - b.x, a.y - b.y, a.z - b.z \
    }                                 \
  }
#define v3f32_mult(a, b)           \
  (Vec3F32)                        \
  {                                \
    {                              \
      a.x *b.x, a.y *b.y, a.z *b.z \
    }                              \
  }
#define v3f32_div(a, b)               \
  (Vec3F32)                           \
  {                                   \
    {                                 \
      a.x / b.x, a.y / b.y, a.z / b.z \
    }                                 \
  }

#define v4f32_add(a, b)                          \
  (Vec4F32)                                      \
  {                                              \
    {                                            \
      a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w \
    }                                            \
  }
#define v4f32_sub(a, b)                          \
  (Vec4F32)                                      \
  {                                              \
    {                                            \
      a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w \
    }                                            \
  }
#define v4f32_mult(a, b)                     \
  (Vec4F32)                                  \
  {                                          \
    {                                        \
      a.x *b.x, a.y *b.y, a.z *b.z, a.w *b.w \
    }                                        \
  }
#define v4f32_div(a, b)                          \
  (Vec4F32)                                      \
  {                                              \
    {                                            \
      a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w \
    }                                            \
  }

#endif // TNT_MATH_H
