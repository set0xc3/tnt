#if !defined(TNT_VECTOR_H)
#define TNT_VECTOR_H

#include "tnt_types.h"

typedef union V2F32 V2F32;
union V2F32 {
	struct {
  	f32 x,y;
  }; 
  f32 v[2];
};

typedef union V3F32 V3F32;
union V3F32 {
	struct {
  	f32 x,y,z;
  }; 
  f32 v[3];
};

typedef union V4F32 V4F32;
union V4F32 {
	struct {
    f32 x,y,z,w;
  };
  f32 v[4];
};

#define v2(t,x,y)     (t){{x,y}}
#define v3(t,x,y,z)   (t){{x,y,z}}
#define v4(t,x,y,z,w) (t){{x,y,z,w}}

#define v2_add(t,a,b) (t){a.x+b.x, a.y+b.y}
#define v3_add(t,a,b) (t){a.x+b.x, a.y+b.y, a.z+b.z}
#define v4_add(t,a,b) (t){a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w}

#endif // TNT_VECTOR_H
