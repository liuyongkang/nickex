;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
;
; idt_flush.s idt_flush������ʵ��
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
;ISR_NOERRCODE 255


[EXTERN idt_handler]
[GLOBAL isr_common_stub]
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
; ���洦����״̬�������ں�ģʽ�Σ����ô����������ָ�
irq_common_stub:
	pusha 			; ѹ�� edi, esi, ebp, esp, ebx, edx, ecx, eax

	mov ax, ds
	push eax 		; �������ݶ�������

	mov ax, 0x10 		; �����ں����ݶ�������
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	push esp
	call irq_handler
	add esp, 4

	pop ebx 		; ���¼���ԭ�������ݶ�������
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	mov ss, bx

	popa 			; ���� edi, esi, ebp, esp, ebx, edx, ecx, eax
	add esp, 8 		; �����������ISR��
	iret 			; ���� cs, eip, EFLAGS, ss, esp

