// the first code hijack we do during initial UI setup, before the program is visible
// makes the IP input field, including tooltip and placeholder text, within an empty CFF-injected PE section called .cave  

push rdi
push r13
push rax
push rcx
push rdx
push r8
push r9
push r10
sub rsp, 0x20
lea rbx, ds:[0x00007FF7D71970A3]
sub rbx, 0xE070A3
add rbx, 0xE07F80
mov ecx, 0x30
call 0x00007FF7D69BB930
mov r13,rax
mov qword ptr ss:[rbp+0x50],rax
mov rcx,rbx
call qword ptr ds:[0x00007FF7D6BA3CC0]
mov edx, 0x0D
lea rcx, ds:[0x00007FF7D719773D]
call qword ptr ds:[0x00007FF7D6BA3C48]
mov qword ptr ds:[0x00007FF7D7197750], rax
mov rax, qword ptr ds:[0x00007FF7D6BB43F0]
mov rcx,qword ptr ds:[rax]
add rcx, 0x238
mov rdx,rbx
lea r8, ds:[0x00007FF7D7197750]
mov r9, rbx
call qword ptr ds:[0x00007FF7D6BB4320]
mov rcx,r13
mov rdx,rbx
mov r8,r15
call qword ptr ds:[0x00007FF7D6BA5738]
mov rcx,rbx
call qword ptr ds:[0x00007FF7D6BA3C38]
mov qword ptr ds:[0x00007FF7D7197FF0], r13
or r9d, 0xFFFFFFFF
xor r8d,r8d
lea rdx, ds:[0x00007FF7D7197FAC]
lea rcx, ss:[rbp+0x50]
call qword ptr ds:[0x00007FF7D6BA3D38]
mov rdx, rax
mov rcx, qword ptr ds:[0x00007FF7D7197FF0]
call qword ptr ds:[0x00007FF7D6BA4708]
lea rcx, ss:[rbp+0x50]
call qword ptr ds:[0x00007FF7D6BA3C38]
lea rcx, ss:[rbp+0x50]
call qword ptr ds:[0x00007FF7D6BA3CC0]
or r9d, 0xFFFFFFFF
xor r8d,r8d  
lea rdx, ds:[0x00007FF7D7197EA0]
lea rcx, ss:[rbp+0x50]
call qword ptr ds:[0x00007FF7D6BA3D38]
mov rdx, rax
mov rcx, qword ptr ds:[0x00007FF7D7197FF0]
mov rax, qword ptr ds:[0x00007FF7D6BA5738]
sub rax, 0x143C10
add rax, 0x148580
call rax
lea rcx, ss:[rbp+0x50]
call qword ptr ds:[0x00007FF7D6BA3C38]
mov rdx, qword ptr ds:[0x00007FF7D7197FF0]
mov rcx,rdi
xor r8d,r8d
mov r9d,ebx
call qword ptr ds:[0x00007FF7D6BA46F8]
add rsp, 0x20
pop r10
pop r9
pop r8
pop rdx
pop rcx
pop rax
pop r13
pop rdi
mov rdx, qword ptr ds:[r15+0x38]
mov rcx,rdi
lea rax, ds:[0x00007FF7D719732B]
sub rax, 0xE0732B
add rax, 0x3A8063
jmp rax
