// We replace the string that the exe uses in QImage::load() to instead check our own Background.png

// Hijacks original code
jmp 0x00007FF6CFD4778B

// Cave code
lea rcx, ds:[0x00007FF6CFD47777] // 0x00007FF6CFD47777 is the address of the cave space where we store the null-terminated "Background.png" ASCII string
jmp 0x00007FF6CF2F9BAF

// jmp back returns to QString::fromAscii_helper, preventing disruption of other original code functions
