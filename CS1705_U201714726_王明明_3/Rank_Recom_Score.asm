.MODEL FLAT,C
.DATA
 GA_SPACE EQU 22
 N=5
.CODE
Rank_Recom_Score PROC
    PUSH EBP
	MOV EBP,ESP
	MOV ECX, N-1					;���ѭ��ִ��N-1��
L1:
	MOV EBX, [EBP+8]		;��һ����Ʒƫ�Ƶ�ַ    
	XOR EDI, EDI        
	XOR EDX, EDX					;DX��¼�ô�ɨ���Ƿ���Ԫ�ؽ���
L2:
	MOV AX, [EBX+20]				;������Ʒ�Ƽ��ȷֱ����AX��DX
	MOV DX, [EBX+42]
	CMP AX, DX
	;�Ƚ�AX��DX��С����AX��BX����תL4,���򽻻�����Ʒ��Ϣ
	JAE  L4
	MOV DX, 1					;�ô�ɨ����Ԫ�ؽ���
	XOR ESI, ESI
L3:
	;����ǰ11���ֽ�
	MOV AL, [EBX+ESI]
	XCHG AL, BYTE PTR[EBX+ESI+ GA_SPACE]
	MOV [EBX+ESI], AL
	INC ESI
	CMP ESI, 22
	JB	L3
L4:
	ADD EBX, GA_SPACE					;�ƶ�����һ����Ʒ��λ��
	INC EDI					
	CMP EDI,ECX           
	JB  L2
	OR DX, DX
	JZ RETURN					;�ô�ɨ����Ԫ�ؽ������������
	LOOP L1         
RETURN:
	POP EBP
	RET
Rank_Recom_Score ENDP

END