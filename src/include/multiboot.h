/*
 * =====================================================================================
 *
 *       Filename:  multiboot.h
 *
 *    Description:  mboot结构体的定义
 *
 *        Version:  1.0
 *        Created:  2013年10月12日 17时38分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_

#include "common.h"

struct multiboot {
	u_int32 flags;
	u_int32 mem_lower;
	u_int32 mem_upper;
	u_int32 boot_device;
	u_int32 cmdline;
	u_int32 mods_count;
	u_int32 mods_addr;
	u_int32 num;
	u_int32 size;
	u_int32 addr;
	u_int32 shndx;
	u_int32 mmap_length;
	u_int32 mmap_addr;
	u_int32 drives_length;
	u_int32 drives_addr;
	u_int32 config_table;
	u_int32 boot_loader_name;
	u_int32 apm_table;
	u_int32 vbe_control_info;
	u_int32 vbe_mode_info;
	u_int32 vbe_mode;
	u_int32 vbe_interface_seg;
	u_int32 vbe_interface_off;
	u_int32 vbe_interface_len;
};

#endif // MULTIBOOT_H_

