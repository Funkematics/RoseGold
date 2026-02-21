#ifndef RG_TYPES_H
#define RG_TYPES_H

#include <stdint.h>
#include <stddef.h>

/* Following NASA/JPL guidelines on types, this ensures portability/predictabiliy */
typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;
typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;
typedef float     f32;
typedef double    f64;

/* Even the bools and null */
typedef u8 bool8;
#define RG_TRUE   ((bool8)1)
#define RG_FALSE  ((bool8)0)
#define RG_NULL   ((void*)0)

#endif /* RG_TYPES_H */


