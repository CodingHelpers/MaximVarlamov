{(A^2+B^2)/(C^2-1)}
{(4^2+4^2)/(3^2-1)}
{(16 + 16)/(9 - 1)}
{32/8}
{4}



{$MODE TP}
var C:     byte;
var A,B,Y: word;

begin
	writeln ('Input A B C');
	readln (A, B, C);

	{$ASMMODE intel}
	asm
		MOV AL, C
		MUL AL
		DEC AX
		PUSH AX

		MOV AX, B
		MUL AX
		MOV BX, AX
		MOV CX, DX
		
		MOV AX, A
		MUL AX
		ADC DX, CX
		ADD AX, BX
		
		POP  CX
		DIV CX
		MOV  Y,AX
	end;

	writeln(Y);
end.
