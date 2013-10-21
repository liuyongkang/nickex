/*
 * =====================================================================================
 *
 *       Filename:  gdt.h
 *
 *    Description:  GDB 定义
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 20时01分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef GDT_H_
#define GDT_H_

#include "common.h"

// 全局描述符类型
struct gdt_entry_struct {
	u_int16 limit_low; 	// 段界限 15～0
	u_int16 base_low; 	// 段基地址 15～0
	u_int8 base_middle; 	// 段基地址 23～16
	u_int8 access; 		// 段存在位，描述符特权级，描述符类型，描述符子类别
	u_int8 granularity; 	// 粒度，默认的操作数大小，64为代码段标志，软件可使用的位，段界限
	u_int8 base_high; 	// 段基地址 31～24
} __attribute__((packed));

// GDT指针
struct gdt_ptr_struct {
	u_int16 limit; 		// GDT的边界，数值上等于表的大小减一
	u_int32 base; 		// GDT的起始地址
} __attribute__((packed));

// 将GDT指针写到GDTR
extern void gdt_flush(u_int32);

// 初始化GDT
extern void init_gdt();


#endif // GDT_H_

