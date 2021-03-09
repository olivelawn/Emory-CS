	mov	%g0, %l0
	ba	LABEL1
	ba	LABEL2
	add	%l0, 1, %l0
LABEL1: ba 	LABEL3
	add	%l0, 2, %l0
LABEL2:	add	%l0, 2, %l0
	add	%l0, 8, %l0
LABEL3:	add	%l0, 16, %l0
	add	%l0, 32, %l0
	nop
	nop

X:
