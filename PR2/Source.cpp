#include <iostream>

int main()
{
	std::cout << "Hello World!" << std::endl;
	char s1[256];
	char s2[256];
	char f[] = "%s";
	char fd[] = "%d\n";
	_asm
	{
		// записываем первую строку
		lea ebx, s1
		push ebx
		lea ecx, f
		push ecx
		call scanf
		add esp, 8
		// записываем вторую строку
		lea ebx, s2
		push ebx
		lea ecx, f
		push ecx
		call scanf
		add esp, 8
		//подготовка к сравнению
		lea ebx, s1
		mov ecx, -1
		dec ebx
		lea edx, s2
		dec edx
		//сравниваем по символам
		b1:
		inc ebx
		inc edx
		inc ecx
		mov al, [ebx]
		mov ah, [edx]
		cmp al, 0
		je comp
		jmp cont

		comp:
		cmp ah, 0
		je eql
		
		cont:
		cmp ah, 0
		je b3
		cmp al, ah
		je b1
		jl b2 //переход на запись того, что s1<s2
		jg b3 //переход на запись того, что s1>s2
		//s1=s2
		eql: 
		mov ecx, 0
		jmp result
		// s1<s2
		b2:
		mov ecx, 1
		jmp result
		//s1>s2
		b3:
		mov ecx, -1
		// вывод результата сравнения
		result:
		push ecx
		lea ebx, fd
		push ebx
		call printf
		add esp, 8
	}
}