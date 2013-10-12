/*
 * =====================================================================================
 *
 *       Filename:  monitor.h
 *
 *    Description:  一些屏幕显示函数的声明
 *
 *        Version:  1.0
 *        Created:  2013年10月11日 17时52分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include "common.h"

enum color {
	black = 0,
	blue = 1,
	green = 2,
	cyan = 3,
	red = 4,
	magenta = 5,
	brown = 6,
	light_grey = 7,
	dark_grey = 8,
	light_blue = 9,
	light_green = 10,
	light_cyan = 11,
	light_red = 12,
	light_magenta = 13,
	light_brown = 14,
	white = 15
};

// 向屏幕上写一特定颜色的字符
extern void monitor_put_color(s_int8 c, enum color back, enum color fore);

// 向屏幕上写一个字符（白底黑字）
extern void monitor_put(s_int8 c);

// 清空屏幕
extern void monitor_clear();

// 向屏幕山写一个特定颜色的字符串
extern void monitor_write_str_color(s_int8 *s, enum color back, enum color fore);

// 向屏幕上写一个字符串（白底黑字）
extern void monitor_write_str(s_int8 *s);

// 以16进制向屏幕上写一个有特定颜色的u_int32类型的值
extern void monitor_write_hex_color(u_int32 n, enum color back, enum color fore);

// 以16进制向屏幕上写一个u_int32类型的值（白底黑字）
extern void monitor_write_hex(u_int32 n);

// 以10进制向屏幕上写一个有特定颜色的u_int32类型的值
extern void monitor_write_dec_color(u_int32 n, enum color back, enum color fore);

// 以10进制向屏幕上写一个u_int32类型的值（白底黑字）
extern void monitor_write_dec(u_int32 n);

#endif // MONITOR_H_

