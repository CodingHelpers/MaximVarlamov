{(A^2+B^2)/(C^2-1)}
{(4^2+4^2)/(3^2-1)}
{(16 + 16)/(9 - 1)}
{32/8}
{4}



{$MODE TP}
var C: shortint;
var A,B,Y: smallint;

begin
	writeln ('Input A B C');
	{readln (A, B, C);}
	A := 4;
	B := 4;
	C := 3;

	{$ASMMODE intel}
	asm
		MOV AL, C
		IMUL AL
		DEC AX
		PUSH AX

		MOV AX, B
		IMUL AX
		MOV BX, AX
		MOV CX, DX
		
		MOV AX, A
		IMUL AX
		ADC DX, CX
		ADD AX, BX

		POP   CX
		IDIV  CX

		MOV  Y,AX
	end;

	writeln(Y);
end.
