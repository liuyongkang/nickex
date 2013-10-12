/*
 * =====================================================================================
 *
 *       Filename:  common.c
 *
 *    Description:  几个读写端口函数的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 21时05分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "common.h"


/* 
 * 写一个字节到特定端口
 * port 为特定端口
 * value 为将要写入的值
 */
void outb(u_int16 port, u_int8 value)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (value));
}

/*
 * 从特定端口读一个字节
 * port 为特定端口
 * 返回值 为读到的内容
 */
u_int8 inb(u_int16 port)
{
	u_int8 ret;

	__asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "dN" (port));

	return ret;
}

/*
 * 从特定端口读一个字
 * port 为特定端口
 * 返回值 为读到的内容
 */
u_int16 inw(u_int16 port)
{
	u_int16 ret;

	__asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (port));

	return ret;
}

