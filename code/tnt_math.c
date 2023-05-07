#include "tnt_math.h"
#include <math.h>

Vec2 v2(f32 x, f32 y)
{
	Vec2 v = {0};
	v.x = x;
	v.y = y;
	return v;
}

Vec3 v3(f32 x, f32 y, f32 z)
{
	Vec3 v = {0};
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

Vec4 v4(f32 x, f32 y, f32 z, f32 w)
{
	Vec4 v = {0};
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return v;
}

Vec2 v2_add(Vec2 a, Vec2 b)
{
	Vec2 v = {0};
	v.x = a.x+b.x;
	v.y = a.y+b.y;
	return v;
}

Vec3 v3_add(Vec3 a, Vec3 b)
{
	Vec3 v = {0};
	v.x = a.x+b.x;
	v.y = a.y+b.y;
	v.z = a.z+b.z;
	return v;
}

Vec4 v4_add(Vec4 a, Vec4 b)
{
	Vec4 v = {0};
	v.x = a.x+b.x;
	v.y = a.y+b.y;
	v.z = a.z+b.z;
	v.w = a.w+b.w;
	return v;
}

Vec2 v2_sub(Vec2 a, Vec2 b)
{
	Vec2 v = {0};
	v.x = a.x-b.x;
	v.y = a.y-b.y;
	return v;
}

Vec3 v3_sub(Vec3 a, Vec3 b)
{
	Vec3 v = {0};
	v.x = a.x-b.x;
	v.y = a.y-b.y;
	v.z = a.z-b.z;
	return v;
}

Vec4 v4_sub(Vec4 a, Vec4 b)
{
	Vec4 v = {0};
	v.x = a.x-b.x;
	v.y = a.y-b.y;
	v.z = a.z-b.z;
	v.w = a.w-b.w;
	return v;
}

Vec2 v2_mul(Vec2 a, Vec2 b)
{
	Vec2 v = {0};
	v.x = a.x*b.x;
	v.y = a.y*b.y;
	return v;
}

Vec3 v3_mul(Vec3 a, Vec3 b)
{
	Vec3 v = {0};
	v.x = a.x*b.x;
	v.y = a.y*b.y;
	v.z = a.z*b.z;
	return v;
}

Vec4 v4_mul(Vec4 a, Vec4 b)
{
	Vec4 v = {0};
	v.x = a.x*b.x;
	v.y = a.y*b.y;
	v.z = a.z*b.z;
	v.w = a.w*b.w;
	return v;
}

Vec2 v2_div(Vec2 a, Vec2 b)
{
	Vec2 v = {0};
	v.x = a.x/b.x;
	v.y = a.y/b.y;
	return v;
}

Vec3 v3_div(Vec3 a, Vec3 b)
{
	Vec3 v = {0};
	v.x = a.x/b.x;
	v.y = a.y/b.y;
	v.z = a.z/b.z;
	return v;
}

Vec4 v4_div(Vec4 a, Vec4 b)
{
	Vec4 v = {0};
	v.x = a.x/b.x;
	v.y = a.y/b.y;
	v.z = a.z/b.z;
	v.w = a.w/b.w;
	return v;
}

Vec2 v2_normalize(Vec2 v)
{
	f32 magnitude = sqrt(v.x * v.x + v.y * v.y);
	v.x /= magnitude;
  v.y /= magnitude;
	return v;
}

Vec3 v3_normalize(Vec3 v)
{
	f32 magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= magnitude;
  v.y /= magnitude;
  v.z /= magnitude;
	return v;
}

Vec4 v4_normalize(Vec4 v)
{
	f32 magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	v.x /= magnitude;
  v.y /= magnitude;
  v.z /= magnitude;
  v.w /= magnitude;
	return v;
}

Vec2i v2i(i32 x, i32 y)
{
	Vec2i v = {0};
	v.x = x;
	v.y = y;
	return v;
}

Vec3i v3i(i32 x, i32 y, i32 z)
{
	Vec3i v = {0};
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

Vec2i v2i_add(Vec2i a, Vec2i b)
{
	Vec2i v = {0};
	v.x = a.x+b.x;
	v.y = a.y+b.y;
	return v;
}

Vec3i v3i_add(Vec3i a, Vec3i b)
{
	Vec3i v = {0};
	v.x = a.x+b.x;
	v.y = a.y+b.y;
	v.z = a.z+b.z;
	return v;
}

Vec2i v2i_sub(Vec2i a, Vec2i b)
{
	Vec2i v = {0};
	v.x = a.x-b.x;
	v.y = a.y-b.y;
	return v;
}

Vec3i v3i_sub(Vec3i a, Vec3i b)
{
	Vec3i v = {0};
	v.x = a.x-b.x;
	v.y = a.y-b.y;
	v.z = a.z-b.z;
	return v;
}

Vec2i v2i_mul(Vec2i a, Vec2i b)
{
	Vec2i v = {0};
	v.x = a.x*b.x;
	v.y = a.y*b.y;
	return v;
}

Vec3i v3i_mul(Vec3i a, Vec3i b)
{
	Vec3i v = {0};
	v.x = a.x*b.x;
	v.y = a.y*b.y;
	v.z = a.z*b.z;
	return v;
}

Vec2i v2i_div(Vec2i a, Vec2i b)
{
	Vec2i v = {0};
	v.x = a.x/b.x;
	v.y = a.y/b.y;
	return v;
}

Vec3i v3i_div(Vec3i a, Vec3i b)
{
	Vec3i v = {0};
	v.x = a.x/b.x;
	v.y = a.y/b.y;
	v.z = a.z/b.z;
	return v;
}

Mat4 m4(f32 x, f32 y, f32 z, f32 w)
{
	Mat4 result = mat4_identity();
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;
	return result;
}

Mat4 mat4_identity()
{
	Mat4 result = {0};
	result.m[0][0] = 1.0f;
 	result.m[1][1] = 1.0f;
 	result.m[2][2] = 1.0f;
	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
 	result.m[3][3] = 1.0f;
	return result;
}

Mat4 mat4_mul_mat4(Mat4 a, Mat4 b)
{
	Mat4 result = {0};
  for (u32 i = 0; i < 4; i += 1) 
	{
  	for (u32 j = 0; j < 4; j += 1) 
		{
    	for (u32 k = 0; k < 4; k += 1) 
			{
      	result.m[i][j] += a.m[i][k] * b.m[k][j];
      }
    }
	}
  return result;
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v)
{
	Vec4 result = {0};
  for (u32 i = 0; i < 4; i += 1) 
	{
  	for (u32 j = 0; j < 4; j += 1) 
		{
    	result.v[i] += m.m[i][j] * v.v[j];
    }
  }
	return result;
}

Mat4 mat4_translate(Vec3 pos)
{
	Mat4 result = mat4_identity();
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][0] = pos.x;
	result.m[3][1] = pos.y;
	result.m[3][2] = pos.z;
	result.m[3][3] = 1.0f;
	return result;
}

Mat4 mat4_scale(Vec3 scale)
{
	Mat4 result = mat4_identity();
	result.m[0][0] = scale.x;
 	result.m[1][1] = scale.y;
 	result.m[2][2] = scale.z;
 	result.m[3][3] = 1.0f;
	return result;
}

Mat4 mat4_rotate(f32 angle, Vec3 axis)
{
	f32 c = cos(angle);
  f32 s = sin(angle);
  f32 x = axis.x;
  f32 y = axis.y;
  f32 z = axis.z;

  Mat4 result = mat4_identity();
  result.m[0][0] = x * x * (1 - c) + c;
  result.m[0][1] = x * y * (1 - c) - z * s;
  result.m[0][2] = x * z * (1 - c) + y * s;
  result.m[0][3] = 0.0f;
  result.m[1][0] = y * x * (1 - c) + z * s;
  result.m[1][1] = y * y * (1 - c) + c;
  result.m[1][2] = y * z * (1 - c) - x * s;
  result.m[1][3] = 0.0f;
  result.m[2][0] = z * x * (1 - c) - y * s;
  result.m[2][1] = z * y * (1 - c) + x * s;
  result.m[2][2] = z * z * (1 - c) + c;
  result.m[2][3] = 0.0f;
  result.m[3][0] = 0.0f;
  result.m[3][1] = 0.0f;
  result.m[3][2] = 0.0f;
  result.m[3][3] = 1.0f;

  return result;
}

Mat4 mat4_perspective(f32 fov, f32 aspect, f32 near, f32 far)
{
	f32 scale = 1.0f / tan(fov * 0.5f * (M_PI / 180.0f));
	f32 frustum_length = far - near;

	Mat4 result = mat4_identity();
	result.m[0][0] = scale * aspect;
	result.m[1][1] = scale;
	result.m[2][2] = -(far + near) / frustum_length;
	result.m[2][3] = -1;
	result.m[3][2] = -(far * near) / frustum_length;
	result.m[3][3] = 0;
	return result;
}

Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up)
{
	Vec3 f = v3(center.x - eye.x, center.y - eye.y, center.z - eye.z);
	f = v3_normalize(f);

  Vec3 s = v3(f.y * up.z - f.z * up.y, f.z * up.x - f.x * up.z, f.x * up.y - f.y * up.x);
	s = v3_normalize(s);

  Vec3 u = v3(s.y * f.z - s.z * f.y, s.z * f.x - s.x * f.z, s.x * f.y - s.y * f.x);

  Mat4 result = mat4_identity();
  result.m[0][0] = s.x;
  result.m[1][0] = s.y;
  result.m[2][0] = s.z;
  result.m[0][1] = u.x;
  result.m[1][1] = u.y;
  result.m[2][1] = u.z;
  result.m[0][2] = -f.x;
  result.m[1][2] = -f.y;
  result.m[2][2] = -f.z;
  result.m[3][0] = -(s.x * eye.x + s.y * eye.y + s.z * eye.z);
  result.m[3][1] = -(u.x * eye.x + u.y * eye.y + u.z * eye.z);
  result.m[3][2] = (f.x * eye.x + f.y * eye.y + f.z * eye.z);
  return result;
}

Mat4 mat4_inverse(Mat4 m)
{
	Mat4 result = mat4_identity();
	Mat4 inv = {0};

  inv.m[0][0] =
      m.m[1][1] * m.m[2][2] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2] -
      m.m[2][1] * m.m[1][2] * m.m[3][3] + m.m[2][1] * m.m[1][3] * m.m[3][2] +
      m.m[3][1] * m.m[1][2] * m.m[2][3] - m.m[3][1] * m.m[1][3] * m.m[2][2];

  inv.m[1][0] =
      -m.m[1][0] * m.m[2][2] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2] +
      m.m[2][0] * m.m[1][2] * m.m[3][3] - m.m[2][0] * m.m[1][3] * m.m[3][2] -
      m.m[3][0] * m.m[1][2] * m.m[2][3] + m.m[3][0] * m.m[1][3] * m.m[2][2];

  inv.m[2][0] =
      m.m[1][0] * m.m[2][1] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1] -
      m.m[2][0] * m.m[1][1] * m.m[3][3] + m.m[2][0] * m.m[1][3] * m.m[3][1] +
      m.m[3][0] * m.m[1][1] * m.m[2][3] - m.m[3][0] * m.m[1][3] * m.m[2][1];

  inv.m[3][0] =
      -m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1] +
      m.m[2][0] * m.m[1][1] * m.m[3][2] - m.m[2][0] * m.m[1][2] * m.m[3][1] -
      m.m[3][0] * m.m[1][1] * m.m[2][2] + m.m[3][0] * m.m[1][2] * m.m[2][1];

  inv.m[0][1] =
      -m.m[0][1] * m.m[2][2] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2] +
      m.m[2][1] * m.m[0][2] * m.m[3][3] - m.m[2][1] * m.m[0][3] * m.m[3][2] -
      m.m[3][1] * m.m[0][2] * m.m[2][3] + m.m[3][1] * m.m[0][3] * m.m[2][2];

  inv.m[1][1] =
      m.m[0][0] * m.m[2][2] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2] -
      m.m[2][0] * m.m[0][2] * m.m[3][3] + m.m[2][0] * m.m[0][3] * m.m[3][2] +
      m.m[3][0] * m.m[0][2] * m.m[2][3] - m.m[3][0] * m.m[0][3] * m.m[2][2];

  inv.m[2][1] =
      -m.m[0][0] * m.m[2][1] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1] +
      m.m[2][0] * m.m[0][1] * m.m[3][3] - m.m[2][0] * m.m[0][3] * m.m[3][1] -
      m.m[3][0] * m.m[0][1] * m.m[2][3] + m.m[3][0] * m.m[0][3] * m.m[2][1];

  inv.m[3][1] =
      m.m[0][0] * m.m[2][1] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1] -
      m.m[2][0] * m.m[0][1] * m.m[3][2] + m.m[2][0] * m.m[0][2] * m.m[3][1] +
      m.m[3][0] * m.m[0][1] * m.m[2][2] - m.m[3][0] * m.m[0][2] * m.m[2][1];

  inv.m[0][2] =
      m.m[0][1] * m.m[1][2] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2] -
      m.m[1][1] * m.m[0][2] * m.m[3][3] + m.m[1][1] * m.m[0][3] * m.m[3][2] +
      m.m[3][1] * m.m[0][2] * m.m[1][3] - m.m[3][1] * m.m[0][3] * m.m[1][2];

  inv.m[1][2] =
      -m.m[0][0] * m.m[1][2] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2] +
      m.m[1][0] * m.m[0][2] * m.m[3][3] - m.m[1][0] * m.m[0][3] * m.m[3][2] -
      m.m[3][0] * m.m[0][2] * m.m[1][3] + m.m[3][0] * m.m[0][3] * m.m[1][2];

  inv.m[2][2] =
      m.m[0][0] * m.m[1][1] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1] -
      m.m[1][0] * m.m[0][1] * m.m[3][3] + m.m[1][0] * m.m[0][3] * m.m[3][1] +
      m.m[3][0] * m.m[0][1] * m.m[1][3] - m.m[3][0] * m.m[0][3] * m.m[1][1];

  inv.m[3][2] =
      -m.m[0][0] * m.m[1][1] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1] +
      m.m[1][0] * m.m[0][1] * m.m[3][2] - m.m[1][0] * m.m[0][2] * m.m[3][1] -
      m.m[3][0] * m.m[0][1] * m.m[1][2] + m.m[3][0] * m.m[0][2] * m.m[1][1];

  inv.m[0][3] =
      -m.m[0][1] * m.m[1][2] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2] +
      m.m[1][1] * m.m[0][2] * m.m[2][3] - m.m[1][1] * m.m[0][3] * m.m[2][2] -
      m.m[2][1] * m.m[0][2] * m.m[1][3] + m.m[2][1] * m.m[0][3] * m.m[1][2];

  inv.m[1][3] =
      m.m[0][0] * m.m[1][2] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2] -
      m.m[1][0] * m.m[0][2] * m.m[2][3] + m.m[1][0] * m.m[0][3] * m.m[2][2] +
      m.m[2][0] * m.m[0][2] * m.m[1][3] - m.m[2][0] * m.m[0][3] * m.m[1][2];

  inv.m[2][3] =
      -m.m[0][0] * m.m[1][1] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1] +
      m.m[1][0] * m.m[0][1] * m.m[2][3] - m.m[1][0] * m.m[0][3] * m.m[2][1] -
      m.m[2][0] * m.m[0][1] * m.m[1][3] + m.m[2][0] * m.m[0][3] * m.m[1][1];

  inv.m[3][3] =
      m.m[0][0] * m.m[1][1] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1] -
      m.m[1][0] * m.m[0][1] * m.m[2][2] + m.m[1][0] * m.m[0][2] * m.m[2][1] +
      m.m[2][0] * m.m[0][1] * m.m[1][2] - m.m[2][0] * m.m[0][2] * m.m[1][1];

  f64 det = m.m[0][0] * inv.m[0][0] + m.m[0][1] * inv.m[1][0] +
            m.m[0][2] * inv.m[2][0] + m.m[0][3] * inv.m[3][0];

	if (det == 0)
	{
    return result;
	}

	det = 1.0 / det;

  for (u32 i = 0; i < 4; i += 1) 
	{
  	for (u32 j = 0; j < 4; j += 1) 
		{
    	result.m[i][j] = inv.m[i][j] * det;
    }
	}

	return result;
}

Vec3 mat4_world_to_screen(Mat4 m, Vec3 point)
{
	Vec3 result = {0};

	Vec4 clip = {0};
	clip.x = point.x * m.m[0][0] + point.y * m.m[1][0] + point.z * m.m[2][0] + m.m[3][0]; 
  clip.y = point.x * m.m[0][1] + point.y * m.m[1][1] + point.z * m.m[2][1] + m.m[3][1]; 
  clip.z = point.x * m.m[0][2] + point.y * m.m[1][2] + point.z * m.m[2][2] + m.m[3][2]; 
  clip.w = point.x * m.m[0][3] + point.y * m.m[1][3] + point.z * m.m[2][3] + m.m[3][3]; 
  if (clip.w < 1.0f) 
	{
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

Vec3 mat4_screen_to_world(Vec2 screen_coord, Mat4 projection_matrix, Mat4 view_matrix, i32 screen_width, i32 screen_height)
{
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

void mat4_print(Mat4 m)
{
	for (u32 i = 0; i < 4; i++)
  {
  	for (u32 j = 0; j < 4; j++)
    {
    	printf("%f ", m.m[i][j]);
    }
    printf("\n");
  }
}

