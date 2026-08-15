// Hooks right after AuGlobal is initialized

jmp 0x00007FF70238785E

mov ecx, 0x04 // Moves int 4 into ECX
call qword ptr ds:[0x00007FF70239029E] // Calls SetState()
lea rax, ds:[0x00007FF701DE7538] // Stolen instruction restoration
jmp 0x00007FF70186201E // jmp back to original code
