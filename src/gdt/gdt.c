/*
 * =====================================================================================
 *
 *       Filename:  gdt.c
 *
 *    Description:  GDT相关函数的定义
 *
 *        Version:  1.0
 *        Created:  2013年10月15日 20时57分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "gdt.h"

static struct gdt_entry_struct gdt_entries[5]; 		// GDT
static struct gdt_ptr_struct gdt_ptr; 			// GDT指针


/*
 * 设置GDT入口的值
 */
static void gdt_set_gate(s_int32 num, u_int32 base, u_int32 limit, u_int8 access, u_int8 gran)
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;
	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access = access;
}

/*
 * 初始化GDT
 */
void init_gdt()
{
	// 设置GDT指针
	gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 5) - 1;
	gdt_ptr.base = (u_int32)&gdt_entries;

	// 设置全局描述符
	gdt_set_gate(0, 0, 0, 0, 0); 			// 第一个为全0
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 	// 代码段
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 	// 数据段
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 	// 用户模式代码段
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 	// 用户模式数据段

	// 将GDT写到GDTR
	gdt_flush((u_int32)&gdt_ptr);
}

