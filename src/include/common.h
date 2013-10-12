/*
 * =====================================================================================
 *
 *       Filename:  comman.h
 *
 *    Description:  一些类型和函数的声明
 *
 *        Version:  1.0
 *        Created:  2013年10月10日 20时50分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef COMMON_H_
#define COMMON_H_

// 一些类型，为标准化大小
typedef char 			s_int8;
typedef unsigned char 		u_int8;
typedef short 			s_int16;
typedef unsigned short 		u_int16;
typedef int 			s_int32;
typedef unsigned int 		u_int32;


// 写一个字节到特定端口
extern void outb(u_int16 port, u_int8 value);

// 从特定端口读一个字节
extern u_int8 inb(u_int16 port);

// 从特定端口读一个字
extern u_int16 inw(u_int16 port);

#endif // COMMON_H_
