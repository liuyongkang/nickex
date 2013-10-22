/*
 * =====================================================================================
 *
 *       Filename:  idt.h
 *
 *    Description:  IDT的定义
 *
 *        Version:  1.0
 *        Created:  2013年10月16日 19时45分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef IDT_H_
#define IDT_H_

#include "common.h"

// 中断描述符
struct idt_entry_struct {
	u_int16 base_lo; 	// 中断处理过程在目标代码段内的偏移量 15～0
	u_int16 sel; 		// 段描述符选择子
	u_int8 always0; 	// 7～5为0, 4～0不使用
	u_int8 flags; 		// 一些标志位
	u_int16 base_hi; 	// 终端处理过程在目标代码段内的偏移量
} __attribute__((packed));

// IDT指针
struct idt_ptr_struct {
	u_int16 limit; 		// IDT的边界，数值上等于表的大小减一
	u_int32 base; 		// IDT的起始地址
} __attribute__((packed));

// 寄存器
struct registers_struct {
	u_int32 ds;
	u_int32 edi;
	u_int32 esi;
	u_int32 ebp;
	u_int32 esp;
	u_int32 ebx;
	u_int32 edx;
	u_int32 ecx;
	u_int32 eax;
	u_int32 int_no;
	u_int32 err_code;
	u_int32 eip;
	u_int32 cs;
	u_int32 eflags;
	u_int32 useresp;
	u_int32 ss;
};

// 初始化IDT
extern void init_idt();

// 将IDT写到IDTR
extern void idt_flush(u_int32);

#endif // IDT_H_

