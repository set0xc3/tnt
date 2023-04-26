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
	Mat4 m = {0};
	m.x = x;
	m.y = y;
	m.z = z;
	m.w = w;
	return m;
}

Mat4 mat4_identity()
{
	Mat4 result = {0};
	result.m[0][0] = 1.0f;
 	result.m[1][1] = 1.0f;
 	result.m[2][2] = 1.0f;
 	result.m[3][3] = 1.0f;
	return result;
}

Mat4 mat4_mul(Mat4 *a, Mat4 *b)
{
	Mat4 result = {0};
	for (u32 i = 0; i < 4; ++i)
	{
    for (u32 j = 0; j < 4; ++j) 
		{
    	result.m[i][j] = 0;
    	for (u32 k = 0; k < 4; ++k)
			{
    		result.m[i][j] += a->m[i][k] * b->m[k][j];
    	}
		}
	}
	return result;
}

Mat4 mat4_translate(Mat4 mat, Vec3 pos)
{
	mat.m[0][0] = 1.0f;
	mat.m[1][1] = 1.0f;
	mat.m[2][2] = 1.0f;
	mat.m[3][0] = pos.x;
	mat.m[3][1] = pos.y;
	mat.m[3][2] = pos.z;
	mat.m[3][3] = 1.0f;
	return mat;
}

Mat4 mat4_scale(Vec3 scale)
{
	Mat4 result = {0};
	result.m[0][0] = scale.x;
 	result.m[1][1] = scale.y;
 	result.m[2][2] = scale.z;
 	result.m[3][3] = 1.0f;
	return result;
}

Mat4 mat4_perspective(f32 fov, f32 aspect, f32 near, f32 far)
{
	f32 tan_half_fov = tanf(fov * 0.5f * (M_PI / 180.0f));

	Mat4 result = {0};
	result.m[0][0] = 1.0f / (aspect * tan_half_fov); // aspect * fov
	result.m[1][1] = 1.0f / tan_half_fov;
	result.m[2][2] = far / (far - near);
	result.m[3][2] = (-far * near) / (far - near);
	result.m[2][3] = 1;
	result.m[3][3] = 0;
	return result;
}

Vec3 mat4_world_to_screen(Mat4 *mat, Vec3 point)
{
	Vec3 result = {0};

	Vec4 clip = {0};
	clip.x = point.x * mat->m[0][0] + point.y * mat->m[1][0] + point.z * mat->m[2][0] + mat->m[3][0]; 
  clip.y = point.x * mat->m[0][1] + point.y * mat->m[1][1] + point.z * mat->m[2][1] + mat->m[3][1]; 
  clip.z = point.x * mat->m[0][2] + point.y * mat->m[1][2] + point.z * mat->m[2][2] + mat->m[3][2]; 
  clip.w = point.x * mat->m[0][3] + point.y * mat->m[1][3] + point.z * mat->m[2][3] + mat->m[3][3]; 
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

void mat4_print(Mat4 *mat)
{
	for (u32 i = 0; i < 4; i++)
  {
  	for (u32 j = 0; j < 4; j++)
    {
    	printf("%f ", mat->m[i][j]);
    }
    printf("\n");
  }
}

