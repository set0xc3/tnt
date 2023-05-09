#include "tnt_math.h"

#include <math.h>

Vec2 v2(f32 x, f32 y) {
  Vec2 v = {0};
  v.x = x;
  v.y = y;
  return v;
}

Vec3 v3(f32 x, f32 y, f32 z) {
  Vec3 v = {0};
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

Vec4 v4(f32 x, f32 y, f32 z, f32 w) {
  Vec4 v = {0};
  v.x = x;
  v.y = y;
  v.z = z;
  v.w = w;
  return v;
}

Vec2 v2_add(Vec2 a, Vec2 b) {
  Vec2 v = {0};
  v.x = a.x + b.x;
  v.y = a.y + b.y;
  return v;
}

Vec3 v3_add(Vec3 a, Vec3 b) {
  Vec3 v = {0};
  v.x = a.x + b.x;
  v.y = a.y + b.y;
  v.z = a.z + b.z;
  return v;
}

Vec4 v4_add(Vec4 a, Vec4 b) {
  Vec4 v = {0};
  v.x = a.x + b.x;
  v.y = a.y + b.y;
  v.z = a.z + b.z;
  v.w = a.w + b.w;
  return v;
}

Vec2 v2_sub(Vec2 a, Vec2 b) {
  Vec2 v = {0};
  v.x = a.x - b.x;
  v.y = a.y - b.y;
  return v;
}

Vec3 v3_sub(Vec3 a, Vec3 b) {
  Vec3 v = {0};
  v.x = a.x - b.x;
  v.y = a.y - b.y;
  v.z = a.z - b.z;
  return v;
}

Vec4 v4_sub(Vec4 a, Vec4 b) {
  Vec4 v = {0};
  v.x = a.x - b.x;
  v.y = a.y - b.y;
  v.z = a.z - b.z;
  v.w = a.w - b.w;
  return v;
}

Vec2 v2_mul(Vec2 a, Vec2 b) {
  Vec2 v = {0};
  v.x = a.x * b.x;
  v.y = a.y * b.y;
  return v;
}

Vec3 v3_mul(Vec3 a, Vec3 b) {
  Vec3 v = {0};
  v.x = a.x * b.x;
  v.y = a.y * b.y;
  v.z = a.z * b.z;
  return v;
}

Vec4 v4_mul(Vec4 a, Vec4 b) {
  Vec4 v = {0};
  v.x = a.x * b.x;
  v.y = a.y * b.y;
  v.z = a.z * b.z;
  v.w = a.w * b.w;
  return v;
}

Vec2 v2_div(Vec2 a, Vec2 b) {
  Vec2 v = {0};
  v.x = a.x / b.x;
  v.y = a.y / b.y;
  return v;
}

Vec3 v3_div(Vec3 a, Vec3 b) {
  Vec3 v = {0};
  v.x = a.x / b.x;
  v.y = a.y / b.y;
  v.z = a.z / b.z;
  return v;
}

Vec4 v4_div(Vec4 a, Vec4 b) {
  Vec4 v = {0};
  v.x = a.x / b.x;
  v.y = a.y / b.y;
  v.z = a.z / b.z;
  v.w = a.w / b.w;
  return v;
}

Vec2 v2_normalize(Vec2 v) {
  f32 magnitude = sqrtf(v.x * v.x + v.y * v.y);
  v.x /= magnitude;
  v.y /= magnitude;
  return v;
}

Vec3 v3_normalize(Vec3 v) {
  f32 magnitude = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  v.x /= magnitude;
  v.y /= magnitude;
  v.z /= magnitude;
  return v;
}

Vec4 v4_normalize(Vec4 v) {
  f32 magnitude = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
  v.x /= magnitude;
  v.y /= magnitude;
  v.z /= magnitude;
  v.w /= magnitude;
  return v;
}

f32 v2_dot(Vec2 left, Vec2 right) {
  return (left.x * right.x) + (left.y * right.y);
}

f32 v3_dot(Vec3 left, Vec3 right) {
  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

f32 v4_dot(Vec4 left, Vec4 right) {
  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) +
         (left.w * right.w);
}

Vec3 v3_cross(Vec3 left, Vec3 right) {
  Vec3 result = {0};
  result.x = (left.y * right.z) - (left.z * right.y);
  result.y = (left.x * right.x) - (left.x * right.z);
  result.z = (left.x * right.y) - (left.y * right.x);
  return result;
}

Vec2i v2i(i32 x, i32 y) {
  Vec2i v = {0};
  v.x = x;
  v.y = y;
  return v;
}

Vec3i v3i(i32 x, i32 y, i32 z) {
  Vec3i v = {0};
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

Vec2i v2i_add(Vec2i a, Vec2i b) {
  Vec2i v = {0};
  v.x = a.x + b.x;
  v.y = a.y + b.y;
  return v;
}

Vec3i v3i_add(Vec3i a, Vec3i b) {
  Vec3i v = {0};
  v.x = a.x + b.x;
  v.y = a.y + b.y;
  v.z = a.z + b.z;
  return v;
}

Vec2i v2i_sub(Vec2i a, Vec2i b) {
  Vec2i v = {0};
  v.x = a.x - b.x;
  v.y = a.y - b.y;
  return v;
}

Vec3i v3i_sub(Vec3i a, Vec3i b) {
  Vec3i v = {0};
  v.x = a.x - b.x;
  v.y = a.y - b.y;
  v.z = a.z - b.z;
  return v;
}

Vec2i v2i_mul(Vec2i a, Vec2i b) {
  Vec2i v = {0};
  v.x = a.x * b.x;
  v.y = a.y * b.y;
  return v;
}

Vec3i v3i_mul(Vec3i a, Vec3i b) {
  Vec3i v = {0};
  v.x = a.x * b.x;
  v.y = a.y * b.y;
  v.z = a.z * b.z;
  return v;
}

Vec2i v2i_div(Vec2i a, Vec2i b) {
  Vec2i v = {0};
  v.x = a.x / b.x;
  v.y = a.y / b.y;
  return v;
}

Vec3i v3i_div(Vec3i a, Vec3i b) {
  Vec3i v = {0};
  v.x = a.x / b.x;
  v.y = a.y / b.y;
  v.z = a.z / b.z;
  return v;
}

Mat4 m4(f32 x, f32 y, f32 z, f32 w) {
  Mat4 result = mat4_identity();
  result.x = x;
  result.y = y;
  result.z = z;
  result.w = w;
  return result;
}

Mat4 mat4_identity(void) {
  Mat4 result = {0};
  result.e[0][0] = 1.0f;
  result.e[1][1] = 1.0f;
  result.e[2][2] = 1.0f;
  result.e[3][0] = 0.0f;
  result.e[3][1] = 0.0f;
  result.e[3][3] = 1.0f;
  return result;
}

Mat4 mat4_mul_mat4(Mat4 left, Mat4 right) {
  Mat4 result = {0};
  for (u32 i = 0; i < 4; i += 1) {
    for (u32 j = 0; j < 4; j += 1) {
      for (u32 k = 0; k < 4; k += 1) {
        result.e[i][j] += left.e[i][k] * right.e[k][j];
      }
    }
  }
  return result;
}

Vec4 mat4_mul_vec4(Mat4 left, Vec4 right) {
  Vec4 result = {0};
  for (u32 i = 0; i < 4; i += 1) {
    for (u32 j = 0; j < 4; j += 1) {
      result.e[i] += left.e[i][j] * right.e[j];
    }
  }
  return result;
}

Mat4 mat4_translate(Vec3 translation) {
  Mat4 result = mat4_identity();
  result.e[3][0] = translation.x;
  result.e[3][1] = translation.y;
  result.e[3][2] = translation.z;
  return result;
}

Mat4 mat4_scale(Vec3 scale) {
  Mat4 result = mat4_identity();
  result.e[0][0] = scale.x;
  result.e[1][1] = scale.y;
  result.e[2][2] = scale.z;
  result.e[3][3] = 1.0f;
  return result;
}

Mat4 mat4_rotate(f32 angle, Vec3 axis) {
  f32 c = cos(angle);
  f32 s = sin(angle);
  axis = v3_normalize(axis);

  Mat4 result = mat4_identity();
  result.e[0][0] = axis.x * axis.x * (1 - c) + c;
  result.e[0][1] = axis.x * axis.y * (1 - c) - axis.z * s;
  result.e[0][2] = axis.x * axis.z * (1 - c) + axis.y * s;
  result.e[0][3] = 0.0f;
  result.e[1][0] = axis.y * axis.x * (1 - c) + axis.z * s;
  result.e[1][1] = axis.y * axis.y * (1 - c) + c;
  result.e[1][2] = axis.y * axis.z * (1 - c) - axis.x * s;
  result.e[1][3] = 0.0f;
  result.e[2][0] = axis.z * axis.x * (1 - c) - axis.y * s;
  result.e[2][1] = axis.z * axis.y * (1 - c) + axis.x * s;
  result.e[2][2] = axis.z * axis.z * (1 - c) + c;
  result.e[2][3] = 0.0f;
  result.e[3][0] = 0.0f;
  result.e[3][1] = 0.0f;
  result.e[3][2] = 0.0f;
  result.e[3][3] = 1.0f;

  return result;
}

Mat4 mat4_perspective(f32 fov, f32 aspect, f32 near, f32 far) {
  f32 cotangent = 1.0f / tanf(fov / 2.0f);

  Mat4 result = {0};
  result.e[0][0] = cotangent / aspect;
  result.e[1][1] = cotangent;
  result.e[2][3] = -1.0f;

  result.e[2][2] = (far + near) / (near - far);
  result.e[3][2] = (2.0f * far * near) / (near - far);
  return result;
}

Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up) {
  Vec3 f = v3_normalize(v3_sub(center, eye));
  Vec3 s = v3_normalize(v3_cross(f, up));
  Vec3 u = v3_cross(s, f);

  Mat4 result = {0};
  result.e[0][0] = s.x;
  result.e[0][1] = u.x;
  result.e[0][2] = -f.x;
  result.e[0][3] = 0.0f;

  result.e[1][0] = s.y;
  result.e[1][1] = u.y;
  result.e[1][2] = -f.y;
  result.e[1][3] = 0.0f;

  result.e[2][0] = s.z;
  result.e[2][1] = u.z;
  result.e[2][2] = -f.z;
  result.e[2][3] = 0.0f;

  result.e[3][0] = -v3_dot(s, eye);
  result.e[3][1] = -v3_dot(u, eye);
  result.e[3][2] = v3_dot(f, eye);
  result.e[3][3] = 1.0f;

  return result;
}

Mat4 mat4_inverse(Mat4 m) {
  Mat4 result = mat4_identity();
  Mat4 inv = {0};

  inv.e[0][0] =
      m.e[1][1] * m.e[2][2] * m.e[3][3] - m.e[1][1] * m.e[2][3] * m.e[3][2] -
      m.e[2][1] * m.e[1][2] * m.e[3][3] + m.e[2][1] * m.e[1][3] * m.e[3][2] +
      m.e[3][1] * m.e[1][2] * m.e[2][3] - m.e[3][1] * m.e[1][3] * m.e[2][2];

  inv.e[1][0] =
      -m.e[1][0] * m.e[2][2] * m.e[3][3] + m.e[1][0] * m.e[2][3] * m.e[3][2] +
      m.e[2][0] * m.e[1][2] * m.e[3][3] - m.e[2][0] * m.e[1][3] * m.e[3][2] -
      m.e[3][0] * m.e[1][2] * m.e[2][3] + m.e[3][0] * m.e[1][3] * m.e[2][2];

  inv.e[2][0] =
      m.e[1][0] * m.e[2][1] * m.e[3][3] - m.e[1][0] * m.e[2][3] * m.e[3][1] -
      m.e[2][0] * m.e[1][1] * m.e[3][3] + m.e[2][0] * m.e[1][3] * m.e[3][1] +
      m.e[3][0] * m.e[1][1] * m.e[2][3] - m.e[3][0] * m.e[1][3] * m.e[2][1];

  inv.e[3][0] =
      -m.e[1][0] * m.e[2][1] * m.e[3][2] + m.e[1][0] * m.e[2][2] * m.e[3][1] +
      m.e[2][0] * m.e[1][1] * m.e[3][2] - m.e[2][0] * m.e[1][2] * m.e[3][1] -
      m.e[3][0] * m.e[1][1] * m.e[2][2] + m.e[3][0] * m.e[1][2] * m.e[2][1];

  inv.e[0][1] =
      -m.e[0][1] * m.e[2][2] * m.e[3][3] + m.e[0][1] * m.e[2][3] * m.e[3][2] +
      m.e[2][1] * m.e[0][2] * m.e[3][3] - m.e[2][1] * m.e[0][3] * m.e[3][2] -
      m.e[3][1] * m.e[0][2] * m.e[2][3] + m.e[3][1] * m.e[0][3] * m.e[2][2];

  inv.e[1][1] =
      m.e[0][0] * m.e[2][2] * m.e[3][3] - m.e[0][0] * m.e[2][3] * m.e[3][2] -
      m.e[2][0] * m.e[0][2] * m.e[3][3] + m.e[2][0] * m.e[0][3] * m.e[3][2] +
      m.e[3][0] * m.e[0][2] * m.e[2][3] - m.e[3][0] * m.e[0][3] * m.e[2][2];

  inv.e[2][1] =
      -m.e[0][0] * m.e[2][1] * m.e[3][3] + m.e[0][0] * m.e[2][3] * m.e[3][1] +
      m.e[2][0] * m.e[0][1] * m.e[3][3] - m.e[2][0] * m.e[0][3] * m.e[3][1] -
      m.e[3][0] * m.e[0][1] * m.e[2][3] + m.e[3][0] * m.e[0][3] * m.e[2][1];

  inv.e[3][1] =
      m.e[0][0] * m.e[2][1] * m.e[3][2] - m.e[0][0] * m.e[2][2] * m.e[3][1] -
      m.e[2][0] * m.e[0][1] * m.e[3][2] + m.e[2][0] * m.e[0][2] * m.e[3][1] +
      m.e[3][0] * m.e[0][1] * m.e[2][2] - m.e[3][0] * m.e[0][2] * m.e[2][1];

  inv.e[0][2] =
      m.e[0][1] * m.e[1][2] * m.e[3][3] - m.e[0][1] * m.e[1][3] * m.e[3][2] -
      m.e[1][1] * m.e[0][2] * m.e[3][3] + m.e[1][1] * m.e[0][3] * m.e[3][2] +
      m.e[3][1] * m.e[0][2] * m.e[1][3] - m.e[3][1] * m.e[0][3] * m.e[1][2];

  inv.e[1][2] =
      -m.e[0][0] * m.e[1][2] * m.e[3][3] + m.e[0][0] * m.e[1][3] * m.e[3][2] +
      m.e[1][0] * m.e[0][2] * m.e[3][3] - m.e[1][0] * m.e[0][3] * m.e[3][2] -
      m.e[3][0] * m.e[0][2] * m.e[1][3] + m.e[3][0] * m.e[0][3] * m.e[1][2];

  inv.e[2][2] =
      m.e[0][0] * m.e[1][1] * m.e[3][3] - m.e[0][0] * m.e[1][3] * m.e[3][1] -
      m.e[1][0] * m.e[0][1] * m.e[3][3] + m.e[1][0] * m.e[0][3] * m.e[3][1] +
      m.e[3][0] * m.e[0][1] * m.e[1][3] - m.e[3][0] * m.e[0][3] * m.e[1][1];

  inv.e[3][2] =
      -m.e[0][0] * m.e[1][1] * m.e[3][2] + m.e[0][0] * m.e[1][2] * m.e[3][1] +
      m.e[1][0] * m.e[0][1] * m.e[3][2] - m.e[1][0] * m.e[0][2] * m.e[3][1] -
      m.e[3][0] * m.e[0][1] * m.e[1][2] + m.e[3][0] * m.e[0][2] * m.e[1][1];

  inv.e[0][3] =
      -m.e[0][1] * m.e[1][2] * m.e[2][3] + m.e[0][1] * m.e[1][3] * m.e[2][2] +
      m.e[1][1] * m.e[0][2] * m.e[2][3] - m.e[1][1] * m.e[0][3] * m.e[2][2] -
      m.e[2][1] * m.e[0][2] * m.e[1][3] + m.e[2][1] * m.e[0][3] * m.e[1][2];

  inv.e[1][3] =
      m.e[0][0] * m.e[1][2] * m.e[2][3] - m.e[0][0] * m.e[1][3] * m.e[2][2] -
      m.e[1][0] * m.e[0][2] * m.e[2][3] + m.e[1][0] * m.e[0][3] * m.e[2][2] +
      m.e[2][0] * m.e[0][2] * m.e[1][3] - m.e[2][0] * m.e[0][3] * m.e[1][2];

  inv.e[2][3] =
      -m.e[0][0] * m.e[1][1] * m.e[2][3] + m.e[0][0] * m.e[1][3] * m.e[2][1] +
      m.e[1][0] * m.e[0][1] * m.e[2][3] - m.e[1][0] * m.e[0][3] * m.e[2][1] -
      m.e[2][0] * m.e[0][1] * m.e[1][3] + m.e[2][0] * m.e[0][3] * m.e[1][1];

  inv.e[3][3] =
      m.e[0][0] * m.e[1][1] * m.e[2][2] - m.e[0][0] * m.e[1][2] * m.e[2][1] -
      m.e[1][0] * m.e[0][1] * m.e[2][2] + m.e[1][0] * m.e[0][2] * m.e[2][1] +
      m.e[2][0] * m.e[0][1] * m.e[1][2] - m.e[2][0] * m.e[0][2] * m.e[1][1];

  f64 det = m.e[0][0] * inv.e[0][0] + m.e[0][1] * inv.e[1][0] +
            m.e[0][2] * inv.e[2][0] + m.e[0][3] * inv.e[3][0];

  if (det == 0) {
    return result;
  }

  det = 1.0 / det;

  for (u32 i = 0; i < 4; i += 1) {
    for (u32 j = 0; j < 4; j += 1) {
      result.e[i][j] = inv.e[i][j] * det;
    }
  }

  return result;
}

Vec3 mat4_world_to_screen(Mat4 m, Vec3 point) {
  Vec3 result = {0};

  Vec4 clip = {0};
  clip.x = point.x * m.e[0][0] + point.y * m.e[1][0] + point.z * m.e[2][0] +
           m.e[3][0];
  clip.y = point.x * m.e[0][1] + point.y * m.e[1][1] + point.z * m.e[2][1] +
           m.e[3][1];
  clip.z = point.x * m.e[0][2] + point.y * m.e[1][2] + point.z * m.e[2][2] +
           m.e[3][2];
  clip.w = point.x * m.e[0][3] + point.y * m.e[1][3] + point.z * m.e[2][3] +
           m.e[3][3];
  if (clip.w < 1.0f) {
    return result;
  }

  Vec3 ndc = {0};
  ndc.x = clip.x / clip.w;
  ndc.y = clip.y / clip.w;
  ndc.z = clip.z / clip.w;

  result.x = ndc.x;
  result.y = ndc.y;
  result.z = ndc.z;

  return result;
}

Vec3 mat4_screen_to_world(Vec2 screen_coord, Mat4 projection_matrix,
                          Mat4 view_matrix, i32 screen_width,
                          i32 screen_height) {
  // Преобразование в нормализованные координаты устройства
  Vec2 ndc = {0};
  ndc.x = (2.0f * screen_coord.x) / screen_width - 1.0f;
  ndc.y = 1.0f - (2.0f * screen_coord.y) / screen_height;

  // Обратная проекция в пространство камеры
  Vec4 clip_coord = v4(ndc.x, ndc.y, -1.0f, 1.0f);
  Mat4 inv_projection = mat4_inverse(projection_matrix);
  Vec4 eye_coord = mat4_mul_vec4(inv_projection, clip_coord);
  eye_coord.z = -1.0f;
  eye_coord.w = 0.0f;

  // Преобразование в мировое пространство
  Mat4 inv_view = mat4_inverse(view_matrix);
  Vec4 world_coord = mat4_mul_vec4(inv_view, eye_coord);
  world_coord = v4_normalize(world_coord);

  return v3(world_coord.x, world_coord.y, world_coord.z);
}

void mat4_print(Mat4 m) {
  for (u32 i = 0; i < 4; i++) {
    for (u32 j = 0; j < 4; j++) {
      printf("%f ", m.e[i][j]);
    }
    printf("\n");
  }
}

f32 to_radiansf(f32 degree) { return degree * (M_PI / 180.0f); }

f32 to_degreesf(f32 radian) { return radian * (180.0f / M_PI); }

f64 to_radians(f64 degree) { return degree * (M_PI / 180.0f); }

f64 to_degrees(f64 radian) { return radian * (180.0f / M_PI); }
