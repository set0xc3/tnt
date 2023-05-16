#if !defined(TNT_MATH_H)
#define TNT_MATH_H

#include "tnt_base_types.h"

#define TNT_PI 3.14159265358979323846
#define TNT_PI32 3.14159265359f

typedef union Vec2 {
  struct {
    f32 x, y;
  };

  struct {
    f32 u, v;
  };

  struct {
    f32 left, right;
  };

  struct {
    f32 width, height;
  };

  f32 elements[2];
} Vec2;

typedef union Vec3 {
  struct {
    f32 x, y, z;
  };

  struct {
    f32 u, v, w;
  };

  struct {
    f32 r, g, b;
  };

  struct {
    Vec2 xy;
    f32 _ignored0;
  };

  struct {
    f32 _ignored1;
    Vec2 yz;
  };

  struct {
    Vec2 uv;
    f32 _ignored2;
  };

  struct {
    f32 _ignored3;
    Vec2 vw;
  };

  f32 elements[3];
} Vec3;

typedef union Vec4 {
  struct {
    union {
      Vec3 xyz;
      struct {
        f32 x, y, z;
      };
    };

    f32 w;
  };

  struct {
    union {
      Vec3 rgb;
      struct {
        f32 r, g, b;
      };
    };

    f32 a;
  };

  struct {
    Vec2 xy;
    f32 _ignored0;
    f32 _ignored1;
  };

  struct {
    f32 _ignored2;
    Vec2 yz;
    f32 _ignored3;
  };

  struct {
    f32 _ignored4;
    f32 _ignored5;
    Vec2 zw;
  };

  struct {
    f32 left, right, top, botton;
  };

  f32 elements[4];
} Vec4;

typedef union Mat2 {
  struct {
    f32 x, y;
  };
  f32 elements[2][2];
  Vec2 columns[2];
} Mat2;

typedef union Mat3 {
  struct {
    f32 x, y, z;
  };
  f32 elements[3][3];
  Vec3 columns[3];
} Mat3;

typedef union Mat4 {
  struct {
    f32 x, y, z, w;
  };
  f32 elements[4][4];
  Vec4 columns[4];
} Mat4;

#define COLOR_RED v4(1.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_RED_DARK v4(0.5f, 0.0f, 0.0f, 1.0f)
#define COLOR_GREEN v4(0.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_GREEN_DARK v4(0.0f, 0.5f, 0.0f, 1.0f)
#define COLOR_BLUE v4(0.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_BLUE_DARK v4(0.0f, 0.0f, 0.5f, 1.0f)
#define COLOR_PINK v4(1.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_PINK_DARK v4(0.5f, 0.0f, 0.5f, 1.0f)
#define COLOR_YELLOW v4(1.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_YELLOW_DARK v4(0.5f, 0.5f, 0.0f, 1.0f)
#define COLOR_CYAN v4(0.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_CYAN_DARK v4(0.0f, 0.5f, 0.5f, 1.0f)
#define COLOR_WHITE v4(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_BLACK v4(0.0f, 0.0f, 0.0f, 1.0f)

// vector

Vec2 v2(f32 x, f32 y);
Vec3 v3(f32 x, f32 y, f32 z);
Vec4 v4(f32 x, f32 y, f32 z, f32 w);

Vec4 v4v(Vec3 vector, f32 w);

Vec2 add_v2(Vec2 left, Vec2 right);
Vec3 add_v3(Vec3 left, Vec3 right);
Vec4 add_v4(Vec4 left, Vec4 right);

Vec2 sub_v2(Vec2 left, Vec2 right);
Vec3 sub_v3(Vec3 left, Vec3 right);
Vec4 sub_v4(Vec4 left, Vec4 right);

Vec2 mul_v2(Vec2 left, Vec2 right);
Vec3 mul_v3(Vec3 left, Vec3 right);
Vec4 mul_v4(Vec4 left, Vec4 right);

Vec2 mul_v2f(Vec2 left, f32 right);
Vec3 mul_v3f(Vec3 left, f32 right);
Vec4 mul_v4f(Vec4 left, f32 right);

Vec2 div_v2(Vec2 left, Vec2 right);
Vec3 div_v3(Vec3 left, Vec3 right);
Vec4 div_v4(Vec4 left, Vec4 right);

Vec2 div_v2f(Vec2 left, f32 right);
Vec3 div_v3f(Vec3 left, f32 right);
Vec4 div_v4f(Vec4 left, f32 right);

b32 is_equal_v2(Vec2 left, Vec2 right);
b32 is_equal_v3(Vec3 left, Vec3 right);
b32 is_equal_v4(Vec4 left, Vec4 right);

Vec2 norm_v2(Vec2 v);
Vec3 norm_v3(Vec3 v);
Vec4 norm_v4(Vec4 v);

f32 dot_v2(Vec2 left, Vec2 right);
f32 dot_v3(Vec3 left, Vec3 right);
f32 dot_v4(Vec4 left, Vec4 right);

Vec3 cross(Vec3 left, Vec3 right);

f32 len_sqrt_v2(Vec2 v);
f32 len_sqrt_v3(Vec3 v);
f32 len_sqrt_v4(Vec4 v);

f32 len_v2(Vec2 v);
f32 len_v3(Vec3 v);
f32 len_v4(Vec4 v);

Vec2 lerp_v2(Vec2 left, Vec2 right, f32 time);
Vec3 lerp_v3(Vec3 left, Vec3 right, f32 time);
Vec4 lerp_v4(Vec4 left, Vec4 right, f32 time);

// matrix

Mat3 m_identity_m3(f32 diagonal);
Mat3 m_transpose_m3(Mat3 matrix);

Mat4 m_identity_m4(f32 diagonal);
Mat4 m_transpose_m4(Mat4 matrix);
Mat4 m_mul_m4(Mat4 left, Mat4 right);
Vec4 m_mul_m4_v4(Mat4 matrix, Vec4 vector);
Mat4 m_mul_m4f(Mat4 matrix, f32 scalar);
Mat4 m_inv_general_m4(Mat4 Matrix);
Mat4 m_translate(Vec3 translation);
Mat4 m_inv_translate(Mat4 matrix);
Mat4 m_scale(Vec3 scale);
Mat4 m_inverse_scale(Mat4 matrix);
Mat4 m_rotate_rh(f32 angle, Vec3 axis);
Mat4 m_rotate_lh(f32 angle, Vec3 axis);
Mat4 m_inverse_rotate(Mat4 matrix);
Mat4 m_orthographic_rh_no(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far);
Mat4 m_orthographic_rh_zo(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far);
Mat4 m_orthographic_lh_no(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far);
Mat4 m_orthographic_lh_zo(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far);
Mat4 m_inverse_orthographic(Mat4 matrix);
Mat4 m_perspective_rh_no(f32 fov, f32 aspect, f32 near, f32 far);
Mat4 m_perspective_rh_zo(f32 fov, f32 aspect, f32 near, f32 far);
Mat4 m_perspective_lh_no(f32 fov, f32 aspect, f32 near, f32 far);
Mat4 ma_perspective_lh_zo(f32 fov, f32 aspect, f32 near, f32 far);
Mat4 m_inv_perspective_rh(Mat4 matrix);
Mat4 m_inv_perspective_lh(Mat4 matrix);
Mat4 _ma_look_at(Vec3 f, Vec3 s, Vec3 u, Vec3 eye);
Mat4 m_look_at_rh(Vec3 eye, Vec3 center, Vec3 up);
Mat4 m_look_at_lh(Vec3 eye, Vec3 center, Vec3 up);
Mat4 m_inverse_look_at(Mat4 matrix);
Vec4 m_linear_combine_v4_m4(Vec4 left, Mat4 right);
Vec3 m_world_to_screen(
    Mat4 m, Vec3 point);  // вычисляет координаты точки в пространстве NDC
Vec3 m_screen_to_world(
    Vec2 screen_coord, Mat4 projection_matrix, Mat4 view_matrix,
    i32 screen_width,
    i32 screen_height);  // преобразует координаты точки на экране в координаты
                         // точки в мировом пространстве
void m_print_m4(Mat4 m);

f32 m_to_radiansf(f32 degree);
f32 m_to_degreesf(f32 radian);
f64 m_to_radians(f64 degree);
f64 m_to_degrees(f64 radian);

#endif  // TNT_MATH_H
