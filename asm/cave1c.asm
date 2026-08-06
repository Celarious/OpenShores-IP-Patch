push r12
push r13
sub rsp, 0x60
lea rdx, ds:[0x00007FF7D71975E2] // IP storage area
mov rcx,qword ptr ds:[7FF7D7197FF0] // QString QLineEdit::text(void), this is how we extract the host the user entered
call qword ptr ds:[0x00007FF7D6BA5BC0]
mov rax, qword ptr gs:[0x0000000000000060] // this gs:60 pointer is the PEB, used for fetching the image base of the exe for >2gb ASLR-stable resolutions
mov rax, qword ptr ds:[rax+0x10]
add rax, 0x813050
lea rcx, ds:[0x00007FF7D7197574]
call qword ptr ds:[rax]
add rax, 0x15B768
mov rax,qword ptr ds:[rax]
mov qword ptr ds:[0x00007FF7D71975EF], rax // AuGlobal base storage, so we don't keep re-resolving it
mov rcx,rax
jmp 0x00007FF7D71975FC // mini-cave entry, used for replacing scene.hazeron.net and mail.hazeron.net
mov qword ptr ds:[0x00007FF7D7197700], rcx
mov rcx, qword ptr ds:[0x00007FF7D7197700]
add rcx, 0x218
push rax
sub rsp, 0x20
lea rdx, ds:[0x00007FF7D71975E2] // IP storage area
call qword ptr ds:[0x00007FF7D6BA3930]
add rsp, 0x20
mov rcx, qword ptr ds:[0x00007FF7D7197700]
add rcx, 0x160
lea rdx, ds:[0x00007FF7D71975E2] // IP storage area
sub rsp, 0x20
call qword ptr ds:[0x00007FF7D6BA3930]
add rsp, 0x20
pop rax
jmp 0x00007FF7D7197505 // mini-cave exit, back to regular cave1c
mov rdx,qword ptr ds:[rax]
movzx r8d,word ptr ds:[rdx+0x148]
add rdx, 0x150
lea rdx, ss:[rsp+0x40]
mov rax,qword ptr gs:[60] // probably should store the PEB resolution somewhere instead of duplicating this, but eh
mov rax,qword ptr ds:[rax+10]
add rax,813050
lea rcx, ds:[0x00007FF7D71975AF]
call qword ptr ds:[rax]
add rax, 0x2F58
add rsp, 0x60
pop r13
pop r12
mov r8d, 0x4175 // hardcoded port 16757, used for login
lea rdx, ds:[0x00007FF7D71975E2] // IP storage area
jmp rax
