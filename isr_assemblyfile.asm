	.global Timer0IntHandler
	.global	toggle
Timer0IntHandler:
		MOV R0, #01

		MOV R1, #0024h
		MOV R2, #4003h
		ADD R1, R2, LSL #16
		STR R0, [R1]


		MOV R1, #5000h
		MOV R2, #4002h
		ADD R1, R2, LSL #16
		MOV R0, #0Eh
		ADD R1, R0, LSL #2
		LDR R0, [R1]


		CMP R0, #8
		BNE LOOP
		MOV R0, #01
LOOP:   MOV R0, R0, LSL #1
		STR R0, [R1]

		BX LR
