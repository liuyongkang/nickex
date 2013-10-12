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

int nx_main(struct multiboot *mboot)
{
	monitor_clear();
	monitor_write_str("Hello world!\n");

	return 0;
}

