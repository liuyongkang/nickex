/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  内核入口
 *
 *        Version:  1.0
 *        Created:  2013年10月12日 16时42分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "multiboot.h"
#include "monitor.h"
#include "gdt.h"
#include "idt.h"

int nx_main(struct multiboot *mboot)
{
	init_gdt();
	init_idt();
	monitor_clear();
	monitor_write_str("Hello world!\n");
	asm volatile("int $0x3");
	asm volatile("int $0x4");

	return 0;
}

