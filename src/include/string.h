/*
 * =====================================================================================
 *
 *       Filename:  string.h
 *
 *    Description:  一些字符串处理函数的声明
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 21时27分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef STRING_H_
#define STRING_H_

#include "common.h"

// 将一块数据拷贝到另一个地方
extern void *memcpy(void *dest, const void *src, u_int32 count);

// 给一块内存空间按字节赋值
extern void *memset(void *dest, s_int8 val, u_int32 count);

// 给一块内存空间按字赋值
extern void *memsetw(void *dest, s_int16 val, u_int32 count);

// 字符串长度
extern u_int32 strlen(const s_int8 *str);

// 字符串比较
extern u_int32 strcmp(const s_int8 *s1, const s_int8 *s2);

// 字符串拷贝
extern s_int8 *strcpy(s_int8 *dest, const s_int8 *src);


#endif // STRING_H_

