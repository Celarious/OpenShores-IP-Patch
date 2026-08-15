// We replace the string that the exe uses in QImage::load() to instead check our own Background.png

// Hijacks original code
jmp 0x00007FF6CFD4778B

// Cave code
lea rcx, ds:[0x00007FF6CFD47777] // 0x00007FF6CFD47777 is the address of the cave space where we store the null-terminated "Background.png" ASCII string
mov edx, 0x21 // sets length of string passed to QString::fromAscii_helper, in this case 21 chars for assets/Background.png (does not include null terminator)
jmp 0x00007FF6CF2F9BAF

// jmp back returns to QString::fromAscii_helper, preventing disruption of other original code functions

// String bytes
42 61 63 6B 67 72 6F 75 6E 64 2E 70 6E 67 00
