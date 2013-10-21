;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
;
; IDT��غ����ͺ�
;
;
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[GLOBAL idt_flush] 		; ����C�������
idt_flush:
	mov eax, [esp+4] 	; ��ȡIDTָ��
	lidt [eax] 		; ����IDTָ��
	ret

%macro ISR_NOERRCODE 1 		; ����꣬��һ������
[GLOBAL isr%1]
isr%1:
	cli 			
	push byte 0
	push byte %1
	jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
[GLOBAL isr%1]
isr%1:
	cli
	push byte %1
	jmp isr_common_stub
%endmacro

; �����жϴ�����
ISR_NOERRCODE  0 	; 0 #DE �� 0 �쳣
ISR_NOERRCODE  1 	; 1 #DB �����쳣
ISR_NOERRCODE  2 	; 2 NMI
ISR_NOERRCODE  3 	; 3 BP �ϵ��쳣 
ISR_NOERRCODE  4 	; 4 #OF ��� 
ISR_NOERRCODE  5 	; 5 #BR ����������ó����߽� 
ISR_NOERRCODE  6 	; 6 #UD ��Ч��δ����Ĳ����� 
ISR_NOERRCODE  7 	; 7 #NM �豸������(����ѧЭ������) 
ISR_ERRCODE    8 	; 8 #DF ˫�ع���(�д������) 
ISR_NOERRCODE  9 	; 9 Э��������β��� 
ISR_ERRCODE   10 	; 10 #TS ��ЧTSS(�д������) 
ISR_ERRCODE   11 	; 11 #NP �β�����(�д������) 
ISR_ERRCODE   12 	; 12 #SS ջ����(�д������) 
ISR_ERRCODE   13 	; 13 #GP ���汣��(�д������) 
ISR_ERRCODE   14 	; 14 #PF ҳ����(�д������) 
ISR_NOERRCODE 15 	; 15 CPU ���� 
ISR_NOERRCODE 16 	; 16 #MF ���㴦��Ԫ���� 
ISR_ERRCODE   17 	; 17 #AC ������ 
ISR_NOERRCODE 18 	; 18 #MC ������� 
ISR_NOERRCODE 19 	; 19 #XM SIMD(��ָ�������)�����쳣

; 20~31 Intel ����
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
; 32��255 �û��Զ���
ISR_NOERRCODE 255


[EXTERN idt_handler]
; �жϷ������
isr_common_stub:
	pusha

	mov ax, ds
	push eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call idt_handler

	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	popa
	add esp, 8
	iret
.end:

