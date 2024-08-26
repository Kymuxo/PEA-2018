.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib LIB.lib
SetConsoleTitleA PROTO :DWORD
ExitProcess PROTO : SDWORD	
GetStdHandle     PROTO : DWORD; получить handle вывода на консоль	  
WriteConsoleA    PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
copystring_ PROTO : DWORD, :DWORD
strsub  PROTO : DWORD, :SDWORD, :SDWORD, :DWORD
concat  PROTO : DWORD, :DWORD, :DWORD
lenstr  PROTO : DWORD
write_int PROTO : SDWORD
new_str PROTO
.data
name_buffer_for_NULL_string byte 201 dup(0)
buffer_string_for_return  byte 201 dup(0)		; буфер возврата строки из функции
a_begin_10 byte 201 dup(0)
.const
consolename db 'PEA-2018',0	;	CONSOLE NAME
ZAP_registers___ byte 'ERROR on size of variable', 0
ERROR_DIV_NULL byte 'ERROR IN DIVISION(NULL)', 0
ERROR_function_strsub byte 'ERROR IN function strsub', 0
ERROR_function_concat byte 'ERROR IN function concat', 0


.code
	main	PROC
push offset consolename
call SetConsoleTitleA
push	offset	a_begin_10
call write_str
jmp EXIT
EXIT_div_on_NULL:
push offset ERROR_DIV_NULL
call write_str
push -1
call ExitProcess
EXITstrsuberror:
push offset ERROR_function_strsub
call write_str
push -2
call ExitProcess
EXITconcaterror:
push offset ERROR_function_concat
call write_str
push -3
call ExitProcess
ZAP_registers__:
push offset ZAP_registers___
call write_str
push - 4
call ExitProcess
EXIT:
push 0
call ExitProcess		; завершение процесса Windows
main ENDP

write_str PROC uses eax ebx ecx edi esi, pstr: SDWORD
push - 11		; -11 - handle для стандартного вывода
call GetStdHandle
mov esi, pstr	; подсчет количества  цикл пока не нулевой символ и считать так количество символов
mov edi, -1		; символов(до 0h)
count:		; в выводимой
inc edi		; на консоль строке
cmp byte ptr[esi + edi], 0
jne count; количество символов->edi
push 0
push 0
push edi
push pstr		; адрес выводимой строки
push eax		; handle для вывода
call WriteConsoleA	; вывести на консоль
ret
write_str ENDP
end main