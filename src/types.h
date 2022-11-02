
#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef s32 size_t;

#define NULL ((void *)0)

#define INT_MAX ((int)0x7fffffff)
#define UINT_MAX ((unsigned int)0xffffffff)

#define LONG_MAX INT_MAX
#define ULONG_MAX UINT_MAX

#define LLONG_MAX ((long long)0x7fffffffffffffff)
#define ULLONG_MAX ((unsigned long long)0xffffffffffffffff)

#endif
