#if !defined(TNT_MATH_H)
#define TNT_MATH_H

#include "tnt_types.h"

typedef union Vec2 Vec2;
union Vec2
{
  struct
  {
    f32 x, y;
  };
  f32 v[2];
};

typedef union Vec3 Vec3;
union Vec3
{
  struct
  {
    f32 x, y, z;
  };
  f32 v[3];
};

typedef union Vec4 Vec4;
union Vec4
{
  struct
  {
    f32 x, y, z, w;
  };
  f32 v[4];
};

typedef union Vec2i Vec2i;
union Vec2i
{
  struct
  {
    i32 x, y;
  };
  i32 v[2];
};

typedef union Vec3i Vec3i;
union Vec3i
{
  struct
  {
    i32 x, y, z;
  };
  i32 v[3];
};

typedef union Mat2 Mat2;
union Mat2
{
  struct
  {
    f32 x, y;
  };
  f32 m[2][2];
};

typedef union Mat3 Mat3;
union Mat3
{
  struct
  {
    f32 x, y, z;
  };
  f32 m[3][3];
};

typedef union Mat4 Mat4;
union Mat4
{
  struct
  {
    f32 x, y, z, w;
  };
  f32 m[4][4];
};

// float 32-bit

Vec2 v2(f32 x, f32 y);
Vec3 v3(f32 x, f32 y, f32 z);
Vec4 v4(f32 x, f32 y, f32 z, f32 w);

Vec2 v2_add(Vec2 a, Vec2 b);
Vec3 v3_add(Vec3 a, Vec3 b);
Vec4 v4_add(Vec4 a, Vec4 b);

Vec2 v2_sub(Vec2 a, Vec2 b);
Vec3 v3_sub(Vec3 a, Vec3 b);
Vec4 v4_sub(Vec4 a, Vec4 b);

Vec2 v2_mul(Vec2 a, Vec2 b);
Vec3 v3_mul(Vec3 a, Vec3 b);
Vec4 v4_mul(Vec4 a, Vec4 b);

Vec2 v2_div(Vec2 a, Vec2 b);
Vec3 v3_div(Vec3 a, Vec3 b);
Vec4 v4_div(Vec4 a, Vec4 b);

// int 32-bit

Vec2i v2i(i32 x, i32 y);
Vec3i v3i(i32 x, i32 y, i32 z);

Vec2i v2i_add(Vec2i a, Vec2i b);
Vec3i v3i_add(Vec3i a, Vec3i b);

Vec2i v2i_sub(Vec2i a, Vec2i b);
Vec3i v3i_sub(Vec3i a, Vec3i b);

Vec2i v2i_mul(Vec2i a, Vec2i b);
Vec3i v3i_mul(Vec3i a, Vec3i b);

Vec2i v2i_div(Vec2i a, Vec2i b);
Vec3i v3i_div(Vec3i a, Vec3i b);

// matrix

Mat4 m4(f32 x, f32 y, f32 z, f32 w);

Mat4 mat4_identity();
Mat4 mat4_mul(Mat4 *a, Mat4 *b);
Mat4 mat4_translate(Mat4 mat, Vec3 pos);
Mat4 mat4_scale(Vec3 scale);
Mat4 mat4_perspective(f32 fov, f32 aspect, f32 near, f32 far);
Vec3 mat4_world_to_screen(Mat4 *mat, Vec3 point);
void mat4_print(Mat4 *mat);

#endif // TNT_MATH_H
