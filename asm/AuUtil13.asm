// This patch modifies the scrolling login text. For simplicity, a tiny .cave PE section was added to AuUtil13.dll, and the hijack was entirely contained within it

// Original code hijacked to jmp to our new .cave
jmp 0x00007FF880E45013

// The code in our new cave
lea rcx, ds:[0x00007FF880E45000]
mov edx, 0x0D
call qword ptr ds:[0x00007FF880E20198] // QString::fromAscii_helper call, to convert our raw version string into a QString
mov qword ptr ss:[rbp-0x50], rax // rbp-50 is where the original code expects the version string to be
jmp 0x00007FF880E1D220

// The null-terminated ASCII version bytes stored in the auutil cave
56 30 2E 30 2E 34 20 28 32 30 32 36 29 00
