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

// 指向一个中断处理函数的函数指针
typedef void (*interrupt_handler_t)(struct registers_struct *);

// 注册一个中断处理函数
extern void register_interrupt_handler(u_int8 n, interrupt_handler_t h);

// 初始化IDT
extern void init_idt();

// 将IDT写到IDTR
extern void idt_flush(u_int32);

// 中断处理函数
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// 定义IRQ
#define  IRQ0     32 	// 电脑系统计时器
#define  IRQ1     33 	// 键盘
#define  IRQ2     34 	// 与 IRQ9 相接，MPU-401 MD 使用
#define  IRQ3     35 	// 串口设备
#define  IRQ4     36 	// 串口设备
#define  IRQ5     37 	// 建议声卡使用
#define  IRQ6     38 	// 软驱传输控制使用
#define  IRQ7     39 	// 打印机传输控制使用
#define  IRQ8     40 	// 即时时钟
#define  IRQ9     41 	// 与 IRQ2 相接，可设定给其他硬件
#define  IRQ10    42 	// 建议网卡使用
#define  IRQ11    43 	// 建议 AGP 显卡使用
#define  IRQ12    44 	// 接 PS/2 鼠标，也可设定给其他硬件
#define  IRQ13    45 	// 协处理器使用
#define  IRQ14    46 	// IDE0 传输控制使用
#define  IRQ15    47 	// IDE1 传输控制使用

// 声明 IRQ 函数
extern void irq0();		// 电脑系统计时器
extern void irq1(); 		// 键盘
extern void irq2(); 		// 与 IRQ9 相接，MPU-401 MD 使用
extern void irq3(); 		// 串口设备
extern void irq4(); 		// 串口设备
extern void irq5(); 		// 建议声卡使用
extern void irq6(); 		// 软驱传输控制使用
extern void irq7(); 		// 打印机传输控制使用
extern void irq8(); 		// 即时时钟
extern void irq9(); 		// 与 IRQ2 相接，可设定给其他硬件
extern void irq10(); 		// 建议网卡使用
extern void irq11(); 		// 建议 AGP 显卡使用
extern void irq12(); 		// 接 PS/2 鼠标，也可设定给其他硬件
extern void irq13(); 		// 协处理器使用
extern void irq14(); 		// IDE0 传输控制使用
extern void irq15(); 		// IDE1 传输控制使用

#endif // IDT_H_

