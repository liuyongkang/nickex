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

