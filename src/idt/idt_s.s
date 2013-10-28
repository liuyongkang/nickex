;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
;
; idt_flush.s idt_flush函数的实现
;
;
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[GLOBAL idt_flush] 		; 允许C程序调用
idt_flush:
	mov eax, [esp+4] 	; 获取IDT指针
	lidt [eax] 		; 加载IDT指针
	ret

%macro ISR_NOERRCODE 1 		; 定义宏，带一个参数
[GLOBAL isr%1]
isr%1:
	cli 			
	push 0
	push %1
	jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
[GLOBAL isr%1]
isr%1:
	cli
	push %1
	jmp isr_common_stub
%endmacro

; 定义中断处理函数
ISR_NOERRCODE  0 	; 0 #DE 除 0 异常
ISR_NOERRCODE  1 	; 1 #DB 调试异常
ISR_NOERRCODE  2 	; 2 NMI
ISR_NOERRCODE  3 	; 3 BP 断点异常 
ISR_NOERRCODE  4 	; 4 #OF 溢出 
ISR_NOERRCODE  5 	; 5 #BR 对数组的引用超出边界 
ISR_NOERRCODE  6 	; 6 #UD 无效或未定义的操作码 
ISR_NOERRCODE  7 	; 7 #NM 设备不可用(无数学协处理器) 
ISR_ERRCODE    8 	; 8 #DF 双重故障(有错误代码) 
ISR_NOERRCODE  9 	; 9 协处理器跨段操作 
ISR_ERRCODE   10 	; 10 #TS 无效TSS(有错误代码) 
ISR_ERRCODE   11 	; 11 #NP 段不存在(有错误代码) 
ISR_ERRCODE   12 	; 12 #SS 栈错误(有错误代码) 
ISR_ERRCODE   13 	; 13 #GP 常规保护(有错误代码) 
ISR_ERRCODE   14 	; 14 #PF 页故障(有错误代码) 
ISR_NOERRCODE 15 	; 15 CPU 保留 
ISR_NOERRCODE 16 	; 16 #MF 浮点处理单元错误 
ISR_ERRCODE   17 	; 17 #AC 对齐检查 
ISR_NOERRCODE 18 	; 18 #MC 机器检查 
ISR_NOERRCODE 19 	; 19 #XM SIMD(单指令多数据)浮点异常

; 20~31 Intel 保留
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
; 32～255 用户自定义
;ISR_NOERRCODE 255


[EXTERN idt_handler]
[GLOBAL isr_common_stub]
; 中断服务程序
isr_common_stub:
	pusha

	mov ax, ds
	push eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	push esp
	call idt_handler
	add esp, 4

	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	popa
	add esp, 8
	iret
.end:

%macro IRQ 2
[GLOBAL irq%1]
irq%1:
	cli
	push byte 0
	push byte %2
	jmp irq_common_stub
%endmacro

IRQ 	0, 	32
IRQ 	1, 	33
IRQ 	2, 	34
IRQ 	3, 	35
IRQ 	4, 	36
IRQ 	5, 	37
IRQ 	6, 	38
IRQ 	7, 	39
IRQ 	8, 	40
IRQ 	9, 	41
IRQ 	10, 	42
IRQ 	11, 	43
IRQ 	12, 	44
IRQ 	13, 	45
IRQ 	14, 	46
IRQ 	15, 	47


[EXTERN] irq_handler
[GLOBAL] irq_common_stub
; 保存处理器状态，设置内核模式段，调用处理函数，最后恢复
irq_common_stub:
	pusha 			; 压入 edi, esi, ebp, esp, ebx, edx, ecx, eax

	mov ax, ds
	push eax 		; 保存数据段描述符

	mov ax, 0x10 		; 加载内核数据段描述符
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	push esp
	call irq_handler
	add esp, 4

	pop ebx 		; 重新加载原来的数据段描述符
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	mov ss, bx

	popa 			; 弹出 edi, esi, ebp, esp, ebx, edx, ecx, eax
	add esp, 8 		; 清除错误代码和ISR码
	iret 			; 弹出 cs, eip, EFLAGS, ss, esp

