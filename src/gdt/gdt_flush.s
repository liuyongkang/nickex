;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
;
; gdt_flush.s gdt_flush函数的实现
;
;
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


[GLOBAL gdt_flush] 	; 允许C程序调用

gdt_flush:
	mov eax, [esp+4] 	; 获得GDT的指针
	lgdt [eax] 		; 加载新的GDT指针

	mov ax, 0x10 		; 0x10是到代码段的偏移
	mov ds, ax 		; 加载所有的数据段选择器
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush 	; 0x08是到代码段的偏移 远跳
.flush:
	ret
