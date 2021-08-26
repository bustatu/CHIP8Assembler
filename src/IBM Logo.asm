# https://github.com/dmatlack/chip8/blob/master/roms/programs/IBM%20Logo.ch8
# To be compiled with: https://github.com/bustatu/CHIP8Assembler

# START
CLS                         0x200

# Draw first sprite
LD I 22A                    0x202
LD V0 0C                    0x204
LD V1 08                    0x206
DRW V0 V1 F                 0x208

# Draw second sprite
ADD V0 09                   0x20A
LD I 239                    0x20C
DRW V0 V1 F                 0x20E

# Draw third sprite
LD I 248                    0x210
ADD V0 08                   0x212
DRW V0 V1 F                 0x214

# Draw fourth sprite
ADD V0 04                   0x216
LD I 257                    0x218
DRW V0 V1 F                 0x21A

# Draw fifth sprite
ADD V0 08                   0x21C
LD I 266                    0x21E
DRW V0 V1 F                 0x220    

# Draw sixth sprite
ADD V0 08                   0x222
LD I 275                    0x224
DRW V0 V1 F                 0x226

# Lock up with an infinite loop
JP 228                      0x228

# First sprite at 0x22A     (letter I)
RAW FF 00 FF 00 3C 00 3C 00 3C 00 3C 00 FF 00 FF

# Second sprite at 0x239    (half of B)
RAW FF 00 FF 00 38 00 3F 00 3F 00 38 00 FF 00 FF

# Third sprite at 0x248     (second half of B)
RAW 80 00 E0 00 E0 00 80 00 80 00 E0 00 E0 00 80

# Fourth sprite at 0x257    (first third of M)
RAW F8 00 FC 00 3E 00 3F 00 3B 00 39 00 F8 00 F8

# Fifth sprite at 0x266     (second third of M)
RAW 03 00 07 00 0F 00 BF 00 FB 00 F3 00 E3 00 43

# Sixth sprite at 0x275     (last third of M)
RAW E0 00 E0 00 80 00 80 00 80 00 80 00 E0 00 E0