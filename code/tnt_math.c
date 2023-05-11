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

Vec4 v4v(Vec3 vector, f32 w) {
  Vec4 result;
  result.xyz = vector;
  result.w = w;

  return result;
}

Vec2 add_v2(Vec2 left, Vec2 right) {
  Vec2 v = {0};
  v.x = left.x + right.x;
  v.y = left.y + right.y;
  return v;
}

Vec3 add_v3(Vec3 left, Vec3 right) {
  Vec3 v = {0};
  v.x = left.x + right.x;
  v.y = left.y + right.y;
  v.z = left.z + right.z;
  return v;
}

Vec4 add_v4(Vec4 left, Vec4 right) {
  Vec4 v = {0};
  v.x = left.x + right.x;
  v.y = left.y + right.y;
  v.z = left.z + right.z;
  v.w = left.w + right.w;
  return v;
}

Vec2 sub_v2(Vec2 left, Vec2 right) {
  Vec2 v = {0};
  v.x = left.x - right.x;
  v.y = left.y - right.y;
  return v;
}

Vec3 sub_v3(Vec3 left, Vec3 right) {
  Vec3 v = {0};
  v.x = left.x - right.x;
  v.y = left.y - right.y;
  v.z = left.z - right.z;
  return v;
}

Vec4 sub_v4(Vec4 left, Vec4 right) {
  Vec4 v = {0};
  v.x = left.x - right.x;
  v.y = left.y - right.y;
  v.z = left.z - right.z;
  v.w = left.w - right.w;
  return v;
}

Vec2 mul_v2(Vec2 left, Vec2 right) {
  Vec2 v = {0};
  v.x = left.x * right.x;
  v.y = left.y * right.y;
  return v;
}

Vec3 mul_v3(Vec3 left, Vec3 right) {
  Vec3 v = {0};
  v.x = left.x * right.x;
  v.y = left.y * right.y;
  v.z = left.z * right.z;
  return v;
}

Vec4 mul_v4(Vec4 left, Vec4 right) {
  Vec4 v = {0};
  v.x = left.x * right.x;
  v.y = left.y * right.y;
  v.z = left.z * right.z;
  v.w = left.w * right.w;
  return v;
}

Vec2 mul_v2f(Vec2 left, f32 right) {
  Vec2 v = {0};
  v.x = left.x * right;
  v.y = left.y * right;
  return v;
}

Vec3 mul_v3f(Vec3 left, f32 right) {
  Vec3 v = {0};
  v.x = left.x * right;
  v.y = left.y * right;
  v.z = left.z * right;
  return v;
}

Vec4 mul_v4f(Vec4 left, f32 right) {
  Vec4 v = {0};
  v.x = left.x * right;
  v.y = left.y * right;
  v.z = left.z * right;
  v.w = left.w * right;
  return v;
}

Vec2 div_v2(Vec2 left, Vec2 right) {
  Vec2 v = {0};
  v.x = left.x / right.x;
  v.y = left.y / right.y;
  return v;
}

Vec3 div_v3(Vec3 left, Vec3 right) {
  Vec3 v = {0};
  v.x = left.x / right.x;
  v.y = left.y / right.y;
  v.z = left.z / right.z;
  return v;
}

Vec4 div_v4(Vec4 left, Vec4 right) {
  Vec4 v = {0};
  v.x = left.x / right.x;
  v.y = left.y / right.y;
  v.z = left.z / right.z;
  v.w = left.w / right.w;
  return v;
}

Vec2 div_v2f(Vec2 left, f32 right) {
  Vec2 v = {0};
  v.x = left.x / right;
  v.y = left.y / right;
  return v;
}

Vec3 div_v3f(Vec3 left, f32 right) {
  Vec3 v = {0};
  v.x = left.x / right;
  v.y = left.y / right;
  v.z = left.z / right;
  return v;
}

Vec4 div_v4f(Vec4 left, f32 right) {
  Vec4 v = {0};
  v.x = left.x / right;
  v.y = left.y / right;
  v.z = left.z / right;
  v.w = left.w / right;
  return v;
}

b32 eq_v2(Vec2 left, Vec2 right) {
  return left.x == right.x && left.y == right.y;
}

b32 eq_v3(Vec3 left, Vec3 right) {
  return left.x == right.x && left.y == right.y && left.z == right.z;
}

b32 eq_v4(Vec4 left, Vec4 right) {
  return left.x == right.x && left.y == right.y && left.z == right.z &&
         left.w == right.w;
}

Vec2 norm_v2(Vec2 v) { return mul_v2f(v, 1.0f / sqrtf(dot_v2(v, v))); }

Vec3 norm_v3(Vec3 v) { return mul_v3f(v, 1.0f / sqrtf(dot_v3(v, v))); }

Vec4 norm_v4(Vec4 v) { return mul_v4f(v, 1.0f / sqrtf(dot_v4(v, v))); }

f32 dot_v2(Vec2 left, Vec2 right) {
  return (left.x * right.x) + (left.y * right.y);
}

f32 dot_v3(Vec3 left, Vec3 right) {
  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

f32 dot_v4(Vec4 left, Vec4 right) {
  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) +
         (left.w * right.w);
}

Vec3 cross(Vec3 left, Vec3 right) {
  Vec3 result = {0};
  result.x = (left.y * right.z) - (left.z * right.y);
  result.y = (left.x * right.x) - (left.x * right.z);
  result.z = (left.x * right.y) - (left.y * right.x);
  return result;
}

f32 len_sqrt_v2(Vec2 v) { return dot_v2(v, v); }

f32 len_sqrt_v3(Vec3 v) { return dot_v3(v, v); }

f32 len_sqrt_v4(Vec4 v) { return dot_v4(v, v); }

f32 len_v2(Vec2 v) { return sqrtf(len_sqrt_v2(v)); }

f32 len_v3(Vec3 v) { return sqrtf(len_sqrt_v3(v)); }

f32 len_v4(Vec4 v) { return sqrtf(len_sqrt_v4(v)); }

Vec2 lerp_v2(Vec2 left, Vec2 right, f32 time) {
  return add_v2(mul_v2f(left, 1.0f - time), mul_v2f(right, time));
}

Vec3 lerp_v3(Vec3 left, Vec3 right, f32 time) {
  return add_v3(mul_v3f(left, 1.0f - time), mul_v3f(right, time));
}

Vec4 lerp_v4(Vec4 left, Vec4 right, f32 time) {
  return add_v4(mul_v4f(left, 1.0f - time), mul_v4f(right, time));
}

Mat3 m_identity_m3(f32 diagonal) {
  Mat3 result = {0};
  result.elements[0][0] = diagonal;
  result.elements[1][1] = diagonal;
  result.elements[2][2] = diagonal;

  return result;
}

Mat3 m_transpose_m3(Mat3 matrix) {
  Mat3 result = matrix;
  result.elements[0][1] = matrix.elements[1][0];
  result.elements[0][2] = matrix.elements[2][0];
  result.elements[1][0] = matrix.elements[0][1];
  result.elements[1][2] = matrix.elements[2][1];
  result.elements[2][1] = matrix.elements[1][2];
  result.elements[2][0] = matrix.elements[0][2];

  return result;
}

Mat4 m_identity_m4(f32 diagonal) {
  Mat4 result = {0};
  result.elements[0][0] = diagonal;
  result.elements[1][1] = diagonal;
  result.elements[2][2] = diagonal;
  result.elements[3][3] = diagonal;
  return result;
}

Mat4 m_transpose_m4(Mat4 matrix) {
  Mat4 result = matrix;
  result.elements[0][1] = matrix.elements[1][0];
  result.elements[0][2] = matrix.elements[2][0];
  result.elements[0][3] = matrix.elements[3][0];
  result.elements[1][0] = matrix.elements[0][1];
  result.elements[1][2] = matrix.elements[2][1];
  result.elements[1][3] = matrix.elements[3][1];
  result.elements[2][1] = matrix.elements[1][2];
  result.elements[2][0] = matrix.elements[0][2];
  result.elements[2][3] = matrix.elements[3][2];
  result.elements[3][1] = matrix.elements[1][3];
  result.elements[3][2] = matrix.elements[2][3];
  result.elements[3][0] = matrix.elements[0][3];

  return result;
}

Mat4 m_mul_m4(Mat4 left, Mat4 right) {
  Mat4 result;
  result.columns[0] = m_linear_combine_v4_m4(right.columns[0], left);
  result.columns[1] = m_linear_combine_v4_m4(right.columns[1], left);
  result.columns[2] = m_linear_combine_v4_m4(right.columns[2], left);
  result.columns[3] = m_linear_combine_v4_m4(right.columns[3], left);

  return result;
}

Vec4 m_mul_m4_v4(Mat4 matrix, Vec4 vecotr) {
  return m_linear_combine_v4_m4(vecotr, matrix);
}

Mat4 m_mul_m4f(Mat4 matrix, f32 scalar) {
  Mat4 result;
  result.elements[0][0] = matrix.elements[0][0] * scalar;
  result.elements[0][1] = matrix.elements[0][1] * scalar;
  result.elements[0][2] = matrix.elements[0][2] * scalar;
  result.elements[0][3] = matrix.elements[0][3] * scalar;
  result.elements[1][0] = matrix.elements[1][0] * scalar;
  result.elements[1][1] = matrix.elements[1][1] * scalar;
  result.elements[1][2] = matrix.elements[1][2] * scalar;
  result.elements[1][3] = matrix.elements[1][3] * scalar;
  result.elements[2][0] = matrix.elements[2][0] * scalar;
  result.elements[2][1] = matrix.elements[2][1] * scalar;
  result.elements[2][2] = matrix.elements[2][2] * scalar;
  result.elements[2][3] = matrix.elements[2][3] * scalar;
  result.elements[3][0] = matrix.elements[3][0] * scalar;
  result.elements[3][1] = matrix.elements[3][1] * scalar;
  result.elements[3][2] = matrix.elements[3][2] * scalar;
  result.elements[3][3] = matrix.elements[3][3] * scalar;

  return result;
}

Mat4 m_inv_general_m4(Mat4 matrix) {
  Vec3 C01 = cross(matrix.columns[0].xyz, matrix.columns[1].xyz);
  Vec3 C23 = cross(matrix.columns[2].xyz, matrix.columns[3].xyz);
  Vec3 B10 = sub_v3(mul_v3f(matrix.columns[0].xyz, matrix.columns[1].w),
                    mul_v3f(matrix.columns[1].xyz, matrix.columns[0].w));
  Vec3 B32 = sub_v3(mul_v3f(matrix.columns[2].xyz, matrix.columns[3].w),
                    mul_v3f(matrix.columns[3].xyz, matrix.columns[2].w));

  float inv_determinant = 1.0f / (dot_v3(C01, B32) + dot_v3(C23, B10));
  C01 = mul_v3f(C01, inv_determinant);
  C23 = mul_v3f(C23, inv_determinant);
  B10 = mul_v3f(B10, inv_determinant);
  B32 = mul_v3f(B32, inv_determinant);

  Mat4 result;
  result.columns[0] = v4v(add_v3(cross(matrix.columns[1].xyz, B32),
                                 mul_v3f(C23, matrix.columns[1].w)),
                          -dot_v3(matrix.columns[1].xyz, C23));
  result.columns[1] = v4v(sub_v3(cross(B32, matrix.columns[0].xyz),
                                 mul_v3f(C23, matrix.columns[0].w)),
                          +dot_v3(matrix.columns[0].xyz, C23));
  result.columns[2] = v4v(add_v3(cross(matrix.columns[3].xyz, B10),
                                 mul_v3f(C01, matrix.columns[3].w)),
                          -dot_v3(matrix.columns[3].xyz, C01));
  result.columns[3] = v4v(sub_v3(cross(B10, matrix.columns[2].xyz),
                                 mul_v3f(C01, matrix.columns[2].w)),
                          +dot_v3(matrix.columns[2].xyz, C01));

  return m_transpose_m4(result);
}

Mat4 m_translate(Vec3 translation) {
  Mat4 result = m_identity_m4(1.0f);
  result.elements[3][0] = translation.x;
  result.elements[3][1] = translation.y;
  result.elements[3][2] = translation.z;

  return result;
}

Mat4 m_inv_translate(Mat4 matrix) {
  Mat4 result = matrix;
  result.elements[3][0] = -matrix.elements[3][0];
  result.elements[3][1] = -matrix.elements[3][1];
  result.elements[3][2] = -matrix.elements[3][2];

  return result;
}

Mat4 m_scale(Vec3 scale) {
  Mat4 result = m_identity_m4(1.0f);
  result.elements[0][0] = scale.x;
  result.elements[1][1] = scale.y;
  result.elements[2][2] = scale.z;
  result.elements[3][3] = 1.0f;

  return result;
}

Mat4 m_inverse_scale(Mat4 matrix) {
  Mat4 result = matrix;
  result.elements[0][0] = 1.0f / result.elements[0][0];
  result.elements[1][1] = 1.0f / result.elements[1][1];
  result.elements[2][2] = 1.0f / result.elements[2][2];

  return result;
}

Mat4 m_rotate_rh(f32 angle, Vec3 axis) {
  f32 sin_theta = sinf(angle);
  f32 cos_theta = cosf(angle);
  f32 cos_value = 1.0f - cos_theta;

  axis = norm_v3(axis);

  Mat4 result = m_identity_m4(1.0f);
  result.elements[0][0] = (axis.x * axis.x * cos_value) + cos_theta;
  result.elements[0][1] = (axis.x * axis.y * cos_value) + (axis.z * sin_theta);
  result.elements[0][2] = (axis.x * axis.z * cos_value) - (axis.y * sin_theta);

  result.elements[1][0] = (axis.y * axis.x * cos_value) - (axis.z * sin_theta);
  result.elements[1][1] = (axis.y * axis.y * cos_value) + cos_theta;
  result.elements[1][2] = (axis.y * axis.z * cos_value) + (axis.x * sin_theta);

  result.elements[2][0] = (axis.z * axis.x * cos_value) + (axis.y * sin_theta);
  result.elements[2][1] = (axis.z * axis.y * cos_value) - (axis.x * sin_theta);
  result.elements[2][2] = (axis.z * axis.z * cos_value) + cos_theta;

  return result;
}

Mat4 m_rotate_lh(f32 angle, Vec3 axis) { return m_rotate_rh(-angle, axis); }

Mat4 m_inverse_rotate(Mat4 matrix) { return m_transpose_m4(matrix); }

Mat4 m_orthographic_rh_no(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far) {
  Mat4 result = {0};
  result.elements[0][0] = 2.0f / (right - left);
  result.elements[1][1] = 2.0f / (top - bottom);
  result.elements[2][2] = 2.0f / (near - far);
  result.elements[3][3] = 1.0f;

  result.elements[3][0] = (left + right) / (left - right);
  result.elements[3][1] = (bottom + top) / (bottom - top);
  result.elements[3][2] = (near + far) / (near - far);

  return result;
}

Mat4 m_orthographic_rh_zo(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far) {
  Mat4 result = {0};
  result.elements[0][0] = 2.0f / (right - left);
  result.elements[1][1] = 2.0f / (top - bottom);
  result.elements[2][2] = 1.0f / (near - far);
  result.elements[3][3] = 1.0f;

  result.elements[3][0] = (left + right) / (left - right);
  result.elements[3][1] = (bottom + top) / (bottom - top);
  result.elements[3][2] = near / (near - far);

  return result;
}

Mat4 m_orthographic_lh_no(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far) {
  Mat4 result = m_orthographic_rh_no(left, right, bottom, top, near, far);
  result.elements[2][2] = -result.elements[2][2];

  return result;
}

Mat4 m_orthographic_lh_zo(f32 left, f32 right, f32 bottom, f32 top, f32 near,
                          f32 far) {
  Mat4 result = m_orthographic_rh_zo(left, right, bottom, top, near, far);
  result.elements[2][2] = -result.elements[2][2];

  return result;
}

Mat4 m_inverse_orthographic(Mat4 matrix) {
  Mat4 result = {0};
  result.elements[0][0] = 1.0f / matrix.elements[0][0];
  result.elements[1][1] = 1.0f / matrix.elements[1][1];
  result.elements[2][2] = 1.0f / matrix.elements[2][2];
  result.elements[3][3] = 1.0f;

  result.elements[3][0] = -matrix.elements[3][0] * result.elements[0][0];
  result.elements[3][1] = -matrix.elements[3][1] * result.elements[1][1];
  result.elements[3][2] = -matrix.elements[3][2] * result.elements[2][2];

  return result;
}

Mat4 m_perspective_rh_no(f32 fov, f32 aspect, f32 near, f32 far) {
  f32 cotangent = 1.0f / tanf(fov / 2.0f);

  Mat4 result = {0};
  result.elements[0][0] = cotangent / aspect;
  result.elements[1][1] = cotangent;
  result.elements[2][2] = (near + far) / (near - far);
  result.elements[2][3] = -1.0f;
  result.elements[3][2] = (2.0f * near * far) / (near - far);

  return result;
}

Mat4 m_perspective_rh_zo(f32 fov, f32 aspect, f32 near, f32 far) {
  f32 cotangent = 1.0f / tanf(fov / 2.0f);

  Mat4 result = {0};
  result.elements[0][0] = cotangent / aspect;
  result.elements[1][1] = cotangent;
  result.elements[2][2] = far / (near - far);
  result.elements[2][3] = -1.0f;
  result.elements[3][2] = (near * far) / (near - far);

  return result;
}

Mat4 m_perspective_lh_no(f32 fov, f32 aspect, f32 near, f32 far) {
  Mat4 result = m_perspective_rh_no(fov, aspect, near, far);
  result.elements[2][2] = -result.elements[2][2];
  result.elements[2][3] = -result.elements[2][3];

  return result;
}

Mat4 ma_perspective_lh_zo(f32 fov, f32 aspect, f32 near, f32 far) {
  Mat4 result = m_perspective_rh_zo(fov, aspect, near, far);
  result.elements[2][2] = -result.elements[2][2];
  result.elements[2][3] = -result.elements[2][3];

  return result;
}

Mat4 m_inv_perspective_rh(Mat4 matrix) {
  Mat4 result = {0};
  result.elements[0][0] = 1.0f / matrix.elements[0][0];
  result.elements[1][1] = 1.0f / matrix.elements[1][1];
  result.elements[2][2] = 0.0f;

  result.elements[2][3] = 1.0f / matrix.elements[3][2];
  result.elements[3][2] = matrix.elements[2][3];
  result.elements[3][3] = matrix.elements[2][2] * result.elements[2][3];

  return result;
}

Mat4 m_inv_perspective_lh(Mat4 matrix) {
  Mat4 result = {0};
  result.elements[0][0] = 1.0f / matrix.elements[0][0];
  result.elements[1][1] = 1.0f / matrix.elements[1][1];
  result.elements[2][2] = 0.0f;

  result.elements[2][3] = 1.0f / matrix.elements[3][2];
  result.elements[3][2] = matrix.elements[2][3];
  result.elements[3][3] = matrix.elements[2][2] * -result.elements[2][3];

  return result;
}

Mat4 _ma_look_at(Vec3 f, Vec3 s, Vec3 u, Vec3 eye) {
  Mat4 result = {0};
  result.elements[0][0] = s.x;
  result.elements[0][1] = u.x;
  result.elements[0][2] = -f.x;
  result.elements[0][3] = 0.0f;

  result.elements[1][0] = s.y;
  result.elements[1][1] = u.y;
  result.elements[1][2] = -f.y;
  result.elements[1][3] = 0.0f;

  result.elements[2][0] = s.z;
  result.elements[2][1] = u.z;
  result.elements[2][2] = -f.z;
  result.elements[2][3] = 0.0f;

  result.elements[3][0] = -dot_v3(s, eye);
  result.elements[3][1] = -dot_v3(u, eye);
  result.elements[3][2] = dot_v3(f, eye);
  result.elements[3][3] = 1.0f;

  return result;
}

Mat4 m_look_at_rh(Vec3 eye, Vec3 center, Vec3 up) {
  Vec3 f = norm_v3(sub_v3(center, eye));
  Vec3 s = norm_v3(cross(f, up));
  Vec3 u = cross(s, f);

  return _ma_look_at(f, s, u, eye);
}

Mat4 m_look_at_lh(Vec3 eye, Vec3 center, Vec3 up) {
  Vec3 f = norm_v3(sub_v3(eye, center));
  Vec3 s = norm_v3(cross(f, up));
  Vec3 u = cross(s, f);

  return _ma_look_at(f, s, u, eye);
}

Mat4 m_inverse_look_at(Mat4 matrix) {
  Mat4 result = {0};

  Mat3 rotation = {0};
  rotation.columns[0] = matrix.columns[0].xyz;
  rotation.columns[1] = matrix.columns[1].xyz;
  rotation.columns[2] = matrix.columns[2].xyz;
  rotation = m_transpose_m3(rotation);

  result.columns[0] = v4v(rotation.columns[0], 0.0f);
  result.columns[1] = v4v(rotation.columns[1], 0.0f);
  result.columns[2] = v4v(rotation.columns[2], 0.0f);
  result.columns[3] = mul_v4f(matrix.columns[3], -1.0f);
  result.elements[3][0] = -1.0f * matrix.elements[3][0] /
                          (rotation.elements[0][0] + rotation.elements[0][1] +
                           rotation.elements[0][2]);
  result.elements[3][1] = -1.0f * matrix.elements[3][1] /
                          (rotation.elements[1][0] + rotation.elements[1][1] +
                           rotation.elements[1][2]);
  result.elements[3][2] = -1.0f * matrix.elements[3][2] /
                          (rotation.elements[2][0] + rotation.elements[2][1] +
                           rotation.elements[2][2]);
  result.elements[3][3] = 1.0f;

  return result;
}

Vec4 m_linear_combine_v4_m4(Vec4 left, Mat4 right) {
  Vec4 result;
  result.x = left.elements[0] * right.columns[0].x;
  result.y = left.elements[0] * right.columns[0].y;
  result.z = left.elements[0] * right.columns[0].z;
  result.w = left.elements[0] * right.columns[0].w;

  result.x += left.elements[1] * right.columns[1].x;
  result.y += left.elements[1] * right.columns[1].y;
  result.z += left.elements[1] * right.columns[1].z;
  result.w += left.elements[1] * right.columns[1].w;

  result.x += left.elements[2] * right.columns[2].x;
  result.y += left.elements[2] * right.columns[2].y;
  result.z += left.elements[2] * right.columns[2].z;
  result.w += left.elements[2] * right.columns[2].w;

  result.x += left.elements[3] * right.columns[3].x;
  result.y += left.elements[3] * right.columns[3].y;
  result.z += left.elements[3] * right.columns[3].z;
  result.w += left.elements[3] * right.columns[3].w;

  return result;
}

Vec3 m_world_to_screen(Mat4 m, Vec3 point) {
  Vec3 result = {0};

  Vec4 clip = {0};
  clip.x = point.x * m.elements[0][0] + point.y * m.elements[1][0] +
           point.z * m.elements[2][0] + m.elements[3][0];
  clip.y = point.x * m.elements[0][1] + point.y * m.elements[1][1] +
           point.z * m.elements[2][1] + m.elements[3][1];
  clip.z = point.x * m.elements[0][2] + point.y * m.elements[1][2] +
           point.z * m.elements[2][2] + m.elements[3][2];
  clip.w = point.x * m.elements[0][3] + point.y * m.elements[1][3] +
           point.z * m.elements[2][3] + m.elements[3][3];
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

Vec3 m_screen_to_world(Vec2 screen_coord, Mat4 projection_matrix,
                       Mat4 view_matrix, i32 screen_width, i32 screen_height) {
  // Преобразование в нормализованные координаты устройства
  Vec2 ndc = {0};
  ndc.x = (2.0f * screen_coord.x) / screen_width - 1.0f;
  ndc.y = 1.0f - (2.0f * screen_coord.y) / screen_height;

  // Обратная проекция в пространство камеры
  Vec4 clip_coord = v4(ndc.x, ndc.y, -1.0f, 1.0f);
  Mat4 inv_projection = m_inv_general_m4(projection_matrix);
  Vec4 eye_coord = m_mul_m4_v4(inv_projection, clip_coord);
  eye_coord.z = -1.0f;
  eye_coord.w = 0.0f;

  // Преобразование в мировое пространство
  Mat4 inv_view = m_inv_general_m4(view_matrix);
  Vec4 world_coord = m_mul_m4_v4(inv_view, eye_coord);
  world_coord = norm_v4(world_coord);

  return v3(world_coord.x, world_coord.y, world_coord.z);
}

void m_print_m4(Mat4 m) {
  for (u32 i = 0; i < 4; i++) {
    for (u32 j = 0; j < 4; j++) {
      printf("%f ", m.elements[i][j]);
    }
    printf("\n");
  }
}

f32 m_to_radiansf(f32 degree) { return degree * (M_PI / 180.0f); }

f32 m_to_degreesf(f32 radian) { return radian * (180.0f / M_PI); }

f64 m_to_radians(f64 degree) { return degree * (M_PI / 180.0f); }

f64 m_to_degrees(f64 radian) { return radian * (180.0f / M_PI); }
