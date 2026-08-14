// Sets state 2, during the Qt+Au initialization after the CRT setup

jmp 0x00007FF7EB577823 // jmp to our SetState call

sub rsp, 0xB28 // Restores the large stack space from the original code
mov r15, rdx // Original instruction
sub rsp, 0x20 // Our own temporary shadow space for our call per windows ABI
mov ecx, 0x02 // Int 2
call qword ptr ds:[0x00007FF7EB58029E] // SetState() call
add rsp, 0x20
jmp 0x00007FF7EAD62A5B
