sub rsp,0x20
mov edx,0x0D
lea rcx, ds:[0x00007FF7D719773D]
call qword ptr ds:[0x00007FF7D6BA3C48] // QString::fromAscii_helper()
mov qword ptr ss:[rbp+0x67], rax
mov rcx, qword ptr ds:[0x00007FF7D7197FF0]
lea rdx, ds:[0x00007FF7D71975E2] // IP storage area
call qword ptr ds:[0x00007FF7D6BA5BC0] // QLineEdit::text(void)
mov rax, qword ptr ds:[0x00007FF7D6BB43F0] // AuGlobal
mov rcx, qword ptr ds:[rax]
add rcx, 0x238
lea rdx, ss:[rbp+0x67]
lea r8, ds:[0x00007FF7D71975E2] // IP storage area
call qword ptr ds:[0x00007FF7D6BB4318] // AuSettings::writeEntry(), saves host to registry
lea rcx, ss:[rbp+0x67]
call qword ptr ds:[0x00007FF7D6BA3C38]
add rsp, 0x20
mov edx, 0x11
lea rcx, ds:[0x00007FF7D6C32650]
jmp 0x00007FF7D673CD09
