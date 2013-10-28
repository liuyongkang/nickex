/*
 * =====================================================================================
 *
 *       Filename:  idt.c
 *
 *    Description:  中断相关函数的定义
 *
 *        Version:  1.0
 *        Created:  2013年10月16日 20时20分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nick (LiuYongkang), liuyongkanglinux@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include "idt.h"
#include "monitor.h"
#include "string.h"

static struct idt_entry_struct idt_entries[256]; 	// IDT
static struct idt_ptr_struct idt_ptr; 			// IDTR
interrupt_handler_t interrupt_handlers[256];

// 给一个中断描述符赋值
static void idt_set_gate(u_int8 num, u_int32 base, u_int16 sel, u_int8 flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;
	idt_entries[num].sel = sel;
	idt_entries[num].always0 = 0;
	idt_entries[num].flags = flags;
}

// 初始化IDT
void init_idt()
{
	// 重新映射IRQ表
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	memset(&interrupt_handlers, 0, sizeof(interrupt_handlers));

	// 设置IDTR
	idt_ptr.limit = sizeof(struct idt_ptr_struct) * 256 - 1;
	idt_ptr.base = (u_int32)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entries));

	idt_set_gate(0, (u_int32)isr0, 0x08, 0x8E);
	idt_set_gate(1, (u_int32)isr1, 0x08, 0x8E);
	idt_set_gate(2, (u_int32)isr2, 0x08, 0x8E);
	idt_set_gate(3, (u_int32)isr3, 0x08, 0x8E);
	idt_set_gate(4, (u_int32)isr4, 0x08, 0x8E);
	idt_set_gate(5, (u_int32)isr5, 0x08, 0x8E);
	idt_set_gate(6, (u_int32)isr6, 0x08, 0x8E);
	idt_set_gate(7, (u_int32)isr7, 0x08, 0x8E);
	idt_set_gate(8, (u_int32)isr8, 0x08, 0x8E);
	idt_set_gate(9, (u_int32)isr9, 0x08, 0x8E);
	idt_set_gate(10, (u_int32)isr10, 0x08, 0x8E);
	idt_set_gate(11, (u_int32)isr11, 0x08, 0x8E);
	idt_set_gate(12, (u_int32)isr12, 0x08, 0x8E);
	idt_set_gate(13, (u_int32)isr13, 0x08, 0x8E);
	idt_set_gate(14, (u_int32)isr14, 0x08, 0x8E);
	idt_set_gate(15, (u_int32)isr15, 0x08, 0x8E);
	idt_set_gate(16, (u_int32)isr16, 0x08, 0x8E);
	idt_set_gate(17, (u_int32)isr17, 0x08, 0x8E);
	idt_set_gate(18, (u_int32)isr18, 0x08, 0x8E);
	idt_set_gate(19, (u_int32)isr19, 0x08, 0x8E);
	idt_set_gate(20, (u_int32)isr20, 0x08, 0x8E);
	idt_set_gate(21, (u_int32)isr21, 0x08, 0x8E);
	idt_set_gate(22, (u_int32)isr22, 0x08, 0x8E);
	idt_set_gate(23, (u_int32)isr23, 0x08, 0x8E);
	idt_set_gate(24, (u_int32)isr24, 0x08, 0x8E);
	idt_set_gate(25, (u_int32)isr25, 0x08, 0x8E);
	idt_set_gate(26, (u_int32)isr26, 0x08, 0x8E);
	idt_set_gate(27, (u_int32)isr27, 0x08, 0x8E);
	idt_set_gate(28, (u_int32)isr28, 0x08, 0x8E);
	idt_set_gate(29, (u_int32)isr29, 0x08, 0x8E);
	idt_set_gate(30, (u_int32)isr30, 0x08, 0x8E);
	idt_set_gate(31, (u_int32)isr31, 0x08, 0x8E);

	idt_set_gate(32, (u_int32)irq0, 0x08, 0x8E);
	idt_set_gate(33, (u_int32)irq1, 0x08, 0x8E);
	idt_set_gate(34, (u_int32)irq2, 0x08, 0x8E);
	idt_set_gate(35, (u_int32)irq3, 0x08, 0x8E);
	idt_set_gate(36, (u_int32)irq4, 0x08, 0x8E);
	idt_set_gate(37, (u_int32)irq5, 0x08, 0x8E);
	idt_set_gate(38, (u_int32)irq6, 0x08, 0x8E);
	idt_set_gate(39, (u_int32)irq7, 0x08, 0x8E);
	idt_set_gate(40, (u_int32)irq8, 0x08, 0x8E);
	idt_set_gate(41, (u_int32)irq9, 0x08, 0x8E);
	idt_set_gate(42, (u_int32)irq10, 0x08, 0x8E);
	idt_set_gate(43, (u_int32)irq11, 0x08, 0x8E);
	idt_set_gate(44, (u_int32)irq12, 0x08, 0x8E);
	idt_set_gate(45, (u_int32)irq13, 0x08, 0x8E);
	idt_set_gate(46, (u_int32)irq14, 0x08, 0x8E);
	idt_set_gate(47, (u_int32)irq15, 0x08, 0x8E);

	// 将IDT写到IDTR
	idt_flush((u_int32)&idt_ptr);
}

// 调用中断处理
void idt_handler(struct registers_struct *regs)
{
	if (interrupt_handlers[regs->int_no]) {
		interrupt_handlers[regs->int_no](regs);
	} else {
		monitor_write_str("unhandled interrupt: ");
		monitor_write_dec(regs->int_no);
		monitor_write_str("\n");
	}
}

// 中断处理函数
void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

// 注册一个中断处理函数
void register_interrupt_handler(u_int8 n, interrupt_handler_t h)
{
	interrupt_handlers[n] = h;
}

void irq_handler(struct registers_struct *regs)
{
	if (regs->int_no >= 40) {
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);

	if (interrupt_handlers[regs->int_no]) {
		interrupt_handlers[regs->int_no](regs);
	}
}

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

