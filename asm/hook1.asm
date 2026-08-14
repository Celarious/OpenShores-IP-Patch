// This hooks the earliest point of the program startup, right after the entry point

jmp 0x00007FF7E2477809 // jmp to our SetState call

sub rsp, 0x28 // Necessary shadow space for all calls
mov ecx, 0x01 // Per Windows calling convention, the first argument is passed with RCX
call qword ptr ds:[0x00007FF7E248029E] // The ClientInterface.dll SetState IAT
add rsp, 0x28
jmp 0x00007FF7E1C9C00C
