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

