/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年10月28日 16时22分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "common.h"
#include "timer.h"
#include "idt.h"
#include "monitor.h"

u_int32 tick = 0;

void timer_callback(struct registers_struct *regs)
{
	tick++;
	monitor_write_str("Tick: ");
	monitor_write_dec(tick);
	monitor_write_str("\n");
}

void init_timer(u_int32 frequency)
{
	register_interrupt_handler(IRQ0, timer_callback);

	u_int32 divisor = 1193180 / frequency;

	outb(0x43, 0x36);

	u_int8 l = (u_int8)(divisor & 0xFF);
	u_int8 h = (u_int8)((divisor>>8) & 0xFF);

	outb(0x40, l);
	outb(0x40, h);
}

