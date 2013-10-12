/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  一些字符串处理函数的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 16时30分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "string.h"


/*
 * 将一块数据拷贝到另一个地方
 * dest 指向拷贝到的位置
 * src 指向需要拷贝的数据
 * count 为拷贝的字节数
 * 返回值为dest
 */
void *memcpy(void *dest, const void *src, u_int32 count)
{
	s_int8 *d = (s_int8 *)dest;
	const s_int8 *s = (s_int8 *)src;

	while (count--) {
		*d++ = *s++;
	}

	return dest;
}

/* 
 * 给一块内存空间按字节赋值
 * dest 指向要赋值的内存块
 * val 为赋值的内容
 * count 为赋值的字节数
 * 返回值为dest
 */
void *memset(void *dest, s_int8 val, u_int32 count)
{
	s_int8 *d = (s_int8 *)dest;
	s_int8 v = (s_int8)val;

	while (count--) {
		*d++ = v;
	}

	return dest;
}

/*
 * 给一块内存空间按字赋值
 * dest 指向要赋值的内存块
 * val 为赋值的内容
 * count 为赋值的字数
 * 返回值为dest
 */
void *memsetw(void *dest, s_int16 val, u_int32 count)
{
	s_int16 *d = (s_int16 *)dest;
	s_int16 v = (s_int16)val;

	while (count--) {
		*d++ = v;
	}

	return dest;
}

/*
 * 字符串长度
 * str 指向将要测量的字符串
 * 返回值为字符串的长度
 */
u_int32 strlen(const s_int8 *str)
{
	const s_int8 *cur = str;

	while (*cur++)
	      ;
	--cur;

	return cur - str;
}

/*
 * 字符串比较
 * s1和s2 为要比较的两个字符串
 * 返回值为正代表两个字符串中第一个不相同的字符s1串比s2串大，负则代表小，0则代表相等
 */
u_int32 strcmp(const s_int8 *s1, const s_int8 *s2)
{
	while (*s1 && (*s1++ == *s2++)) 
	      ;

	return *s1 - *s2;
}

/*
 * 字符串拷贝
 * dest 指向要拷贝到的位置
 * src 指向要拷贝的字符串
 * 返回值为dest
 */
s_int8 *strcpy(s_int8 *dest, const s_int8 *src)
{
	s_int8 *s = dest;

	while (*src && (*s++ = *src++))
	      ;
	*s = '\0';

	return dest;
}

