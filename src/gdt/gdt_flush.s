;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
;
; gdt_flush.s gdt_flush������ʵ��
;
;
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


[GLOBAL gdt_flush] 	; ����C�������

gdt_flush:
	mov eax, [esp+4] 	; ���GDT��ָ��
	lgdt [eax] 		; �����µ�GDTָ��

	mov ax, 0x10 		; 0x10�ǵ�����ε�ƫ��
	mov ds, ax 		; �������е����ݶ�ѡ����
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush 	; 0x08�ǵ�����ε�ƫ�� Զ��
.flush:
	ret
