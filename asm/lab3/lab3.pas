{$MODE TP}
const 
N: byte = 5;

var 
A:array[1..10] of byte;
i, r :byte;

begin
	writeln('Vvedite Massiv:');
	for i:=1 to N do	
		read(A[i]);
		{A[i] := i;}

	r := 0;
	{$ASMMODE intel}
	asm
	MOV BL ,0      { Счетчик повторяющихся букв }

	XOR RCX, RCX   { Счетчик для цикла}
	MOV RCX,N      
	DEC RCX

	MOV RSI,0      { Смещение в массиве }
	
	LEA RBP, A     { Адрес массива }

	@loop_point:
	MOV AL, [RBP+RSI] 
	ADD RSI,1 
	MOV DL, [RBP+RSI]
	DEC DL

	CMP AL, DL 
	JNE @false_1

	INC BL

	@false_1:
	
	CMP BL, 2
	JNE @false_2

	MOV AL, R
	INC AL
	MOV R, AL
	XOR BL,BL
	ADD RSI,1

	@false_2:
	LOOP @loop_point				
	end;
	
	writeln('Rezultat: ',R);
end.
