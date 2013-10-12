;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
;
;   boot.s 内核启动的地方
;   还定义了一些 multiboot header.
;
;
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


MBOOT_PAGE_ALIGN 	equ 	1 << 0 		; 表示加载内核和模块以一个页为来对齐
MBOOT_MEM_INFO 		equ 	1 << 1 		; 表示提供给内核的内存信息
MBOOT_HEADER_MAGIC 	equ 	0x1BADB002 	; 一个魔数


MBOOT_HEADER_FLAGS 	equ 	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM 		equ 	-(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


[BITS 32] 			; 所有指令都是32位的

[GLOBAL mboot] 			; 可从C开始'mboot'
[EXTERN code] 			; '.text'开始
[EXTERN bss] 			; '.bss'开始
[EXTERN end] 			; 最后可引导部分的结尾

mboot:
	dd  MBOOT_HEADER_MAGIC 		; grub将在内核文件中每隔四个字节寻找这个魔数
	dd  MBOOT_HEADER_FLAGS 		; grub加载文件或设置的方式
	dd  MBOOT_CHECKSUM 		; 确保以上值是正确的
   
	dd  mboot 			; 本地描述如
	dd  code 			; '.text'开始
	dd  bss 			; '.data'结束
	dd  end 			; 内核结束
	dd  start 			; 内核入口

[GLOBAL start]                  ; 内核入口
[EXTERN nx_main]                   ; C代码入口

start:
	push    ebx                 ; 加载multiboot header的位置

	; 启动内核
	cli                         ; 关闭中断
	call nx_main                ; 调用内核入口
	jmp $                       ; 进入死循环，停止处理器

