#if defined(TNT_MATH_H)
#define TNT_MATH_H

typedef union Mat3 Mat3;
union Mat3 {
  f32 m[3][3];
};

typedef union Mat4 Mat4;
union Mat4 {
  f32 m[4][4];
};

#endif // TNT_MATH_H
