// This hooks right after QCoreApplication::arguments(), where game launch arguments are processed

jmp 0x00007FF702387847 // jmp to our SetState() code

mov ecx, 0x03 // Moves int 3 into ECX
call qword ptr ds:[0x00007FF70239029E] // Calls SetState IAT
lea rcx, ss:[rsp+0x40] // Stolen instruction restoration
jmp 0x00007FF701851F6A // jmp back to original code
