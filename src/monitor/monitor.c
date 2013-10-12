/*
 * =====================================================================================
 *
 *       Filename:  monitor.c
 *
 *    Description:  一些屏幕显示函数的实现
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 17时59分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "monitor.h"

static u_int16 *video_memory = (u_int16 *)0xB8000;

static u_int8 cursor_x = 0;
static u_int8 cursor_y = 0;

static const u_int8 cursor_max_x = 80;
static const u_int8 cursor_max_y = 25;

/*
 * 移动光标
 */
static void move_cursor()
{
	u_int16 cursor_location = cursor_y * cursor_max_x + cursor_x; 	// 要移动到的位置

	// 设置光标的高字节
	outb(0x3D4, 14);
	outb(0x3D5, cursor_location >> 8);

	// 设置光标的低字节
	outb(0x3D4, 15);
	outb(0x3D5, cursor_location);
}

/*
 * 屏幕向下滚动一行
 */
static void scroll()
{
	u_int8 attribute_byte = (0 << 4) | (15 & 0x0F); 	// 属性为黑底白字
	u_int16 blank = 0x20 | (attribute_byte << 8); 		// 字符为空白

	// y坐标超过屏幕，进行滚动
	if (cursor_y >= cursor_max_x) {
		int i;
		// 整体上移一行
		for (i = 0 * cursor_max_x; i < (cursor_max_y - 1) * cursor_max_x; i++) {
			video_memory[i] = video_memory[i + cursor_max_y];
		}

		// 最下面一行为空白
		for (i = (cursor_max_y - 1) * cursor_max_x; i < cursor_max_y * cursor_max_x; i++) {
			video_memory[i] = blank;
		}
		
		// y坐标设为最下一行
		cursor_y = cursor_max_x - 1;
	}
}

/*
 * 向屏幕上写一特定颜色的字符
 * c 为要显示的字符
 * back 为背景色
 * fore 为景前色
 */
void monitor_put_color(s_int8 c, enum color back, enum color fore)
{
	u_int8 attribute_byte = ((u_int8)back << 4) | ((u_int8)fore & 0x0F);
	u_int16 *location;

	if (c == 0x08 && cursor_x) { 		// 退格键
		cursor_x--;
	} else if (c == 0x09) { 		// tab
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	} else if (c == '\r') {
		cursor_x = 0;
	} else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else if (c >= ' ') { 			// 其余可打印字符
		location = video_memory + (cursor_y * cursor_max_x + cursor_x);
		*location = (attribute_byte << 8) | c;
		cursor_x++;
	}

	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y++;
	}

	// 如需，则滚动屏幕
	scroll();

	// 移动光标
	move_cursor();
}

/*
 * 向屏幕上写一个字符（白底黑字）
 * d 为要显示的字符
 */
void monitor_put(s_int8 c)
{
	monitor_put_color(c, black, white);
}

/*
 * 清空屏幕
 */
void monitor_clear()
{
	u_int8 attribute_byte = (0 << 4) | (15 & 0x0F); 	// 黑底白字
	u_int16 blank = 0x20 | (attribute_byte << 8); 		// 空白字符
	
	int i;

	// 屏幕都写为空白
	for (i = 0 * cursor_max_x; i < (cursor_max_x * cursor_max_y); i++) {
		video_memory[i] = blank;
	}

	// 调整位置
	cursor_x = 0;
	cursor_y = 0;

	// 移动光标
	move_cursor();
}

/*
 * 向屏幕山写一个特定颜色的字符串
 * s 指向要显示的字符串
 * back 为背景色
 * fore 为景前色
 */
void monitor_write_str_color(s_int8 *s, enum color back, enum color fore)
{
	while (*s) {
		monitor_put_color(*s++, back, fore);
	}
}

/*
 * 向屏幕上写一个字符串（黑底白字）
 * s 指向要显示的字符串
 */
void monitor_write_str(s_int8 *s)
{
	monitor_write_str_color(s, black, white);
}

/*
 * 以16进制向屏幕上写一个有特定颜色的u_int32类型的值
 * n 为要显示的数值
 * back 为背景色
 * fore 为景前色
 */
void monitor_write_hex_color(u_int32 n, enum color back, enum color fore)
{
	int i;
	s_int8 cur_digit;

	for (i = 0; i < 8; ++i) { // 8位16进制数
		// 取出一位16进制数
		cur_digit = (n >> (32 - (i + 1) * 4)) & 0x0F;
		
		if (cur_digit < 0x0A) {
			cur_digit += '0';
		} else {
			cur_digit += 'A' - 0x0A;
		}

		// 写到屏幕
		monitor_put_color(cur_digit, back, fore);
	}
}

/*
 * 以16进制向屏幕上写一个u_int32类型的值（白底黑字）
 * n 为要显示的数值
 */
void monitor_write_hex(u_int32 n)
{
	monitor_write_hex_color(n, black, white);
}

/*
 * 以10进制向屏幕上写一个有特定颜色的u_int32类型的值
 * n 为要显示的数值
 * back 为背景色
 * fore 为景前色
 */
void monitor_write_dec_color(u_int32 n, enum color back, enum color fore)
{
	u_int8 digit[10]; 		// 不超过十位
	int index = 9; 			// 先指到最后一位
	int i;

	if (n) { 	// 若为0，则输出0
		monitor_put_color((u_int8)0, back, fore);
	}

	// 分离每一位
	while (n) {
		digit[index--] = n % 10 + '0';
		n /= 10;
	}

	// 显示
	for (i = index + 1; i < 10; i++) {
		monitor_put_color(digit[i], back, fore);
	}
}

/*
 * 以10进制向屏幕上写一个u_int32类型的值（白底黑字）
 * n 为要显示的数值
 */
void monitor_write_dec(u_int32 n)
{
	monitor_write_dec_color(n, black, white);
}

