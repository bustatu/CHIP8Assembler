# https://github.com/dmatlack/chip8/blob/master/roms/games/Tetris%20%5BFran%20Dachille%2C%201991%5D.ch8
# To be compiled with: https://github.com/bustatu/CHIP8Assembler

# START
LD I 2B4    # Store the adress of the dot sprite in I           0x200
CALL 3E6    #                                                   0x202
CALL 2B6    # Initialise register values                        0x204

ADD V0 1    #                                                   0x206
DRW V0 V1 1 #                                                   0x208
SE V0 25    #                                                   0x20A
JP 206      # Loop while register 0 is not 0x25                 0x20C

ADD V1 FF   #                                                   0x20E
DRW V0 V1 1 #                                                   0x210
LD V0 1A    #                                                   0x212
DRW V0 V1 1 #                                                   0x214
LD V0 25    #                                                   0x216
SE V1 0     #                                                   0x218
JP 20E      # Loop while register 1 is not 0x00                 0x21A

RND V4 70   #                                                   0x21C
SNE V4 70   #                                                   0x21E
JP 21C      # Loop while the random value we get is 0x70        0x220

RND V3 3    #                                                   0x222
LD V0 1E    #                                                   0x224
LD V1 3     #                                                   0x226
CALL 25C    #   Get piece type's sprite pointed by I            0x228

LD DT V5    #   Load value in V5 in DT                          0x22A
DRW V0 V1 4 #                                                   0x22C
SE VF 1     #                                                   0x22E
JP 23C      #   Draw piece and check for colision               0x230
DRW V0 V1 4
ADD V1 FF
DRW V0 V1 4
CALL 340
JP 21C
SKNP V7
CALL 272
SKNP V8
CALL 284
SKNP V9
CALL 296
SKP V2
JP 250
LD V6 0
LD DT V6
LD V6 DT
SE V6 0
JP 23C
DRW V0 V1 4
ADD V1 1
JP 22A

# Function at 0x25C
LD I 2C4                                                        0x25C
ADD I V4                                                        0x25E
LD V6 0                                                         0x260
SNE V3 1                                                        0x262
LD V6 4                                                         0x264
SNE V3 2                                                        0x266
LD V6 8                                                         0x268
SNE V3 3                                                        0x26A
LD V6 C                                                         0x26C
ADD I V6                                                        0x26E
RET                                                             0x270

DRW V0 V1 4
ADD V0 FF
CALL 334
SE VF 1
RET
DRW V0 V1 4
ADD V0 1
CALL 334
RET
DRW V0 V1 4
ADD V0 1
CALL 334
SE VF 1
RET
DRW V0 V1 4
ADD V0 FF
CALL 334
RET
DRW V0 V1 4
ADD V3 1
SNE V3 4
LD V3 0
CALL 25C
CALL 334
SE VF 1
RET
DRW V0 V1 4
ADD V3 FF
SNE V3 FF
LD V3 3
CALL 25C
CALL 334
RET

# Dot sprite
RAW 80 00                                                       0x2B4

# Function at 0x2B6
LD V7 05                                                        0x2B6
LD V8 06                                                        0x2B8
LD V9 04                                                        0x2BA
LD V1 1F                                                        0x2BC
LD V5 10                                                        0x2BE
LD V2 7                                                         0x2C0
RET                                                             0x2C2

SNE V0 E0
Unknown disassembly! 0
SNE V0 C0
SNE V0 0
CLS
SNE V0 0
SNE V0 60
SNE V0 0
SNE V0 40
LD V0 0
CALL E0
Unknown disassembly! 0
RND V0 40
SNE V0 0
CLS
LD V0 V0
SNE V0 40
RND V0 0
CLS
CALL 0
LD V0 40
SNE V0 0
LD V0 VE
Unknown disassembly! 0
SNE V0 C0
LD V0 V0
RND V0 60
Unknown disassembly! 0
SNE V0 C0
LD V0 V0
RND V0 60
Unknown disassembly! 0
LD V0 VC
SNE V0 0
Unknown disassembly! 60
RND V0 0
LD V0 VC
SNE V0 0
Unknown disassembly! 60
RND V0 0
RND V0 C0
Unknown disassembly! 0
RND V0 C0
Unknown disassembly! 0
RND V0 C0
Unknown disassembly! 0
RND V0 C0
Unknown disassembly! 0
SNE V0 40
SNE V0 40
Unknown disassembly! F0
Unknown disassembly! 0
SNE V0 40
SNE V0 40
Unknown disassembly! F0
Unknown disassembly! 0
DRW V0 V1 4
LD V6 35
ADD V6 FF
SE V6 0
JP 338
RET
LD I 2B4
LD VC V1
SE VC 1E
ADD VC 1
SE VC 1E
ADD VC 1
SE VC 1E
ADD VC 1
CALL 35E
SNE VB A
CALL 372
SNE V1 VC
RET
ADD V1 1
JP 350
LD V0 1B
LD VB 0
DRW V0 V1 1
SE VF 0
ADD VB 1
DRW V0 V1 1
ADD V0 1
SE V0 25
JP 362
RET
LD V0 1B
DRW V0 V1 1
ADD V0 1
SE V0 25
JP 374
LD VE V1
LD VD VE
ADD VE FF
LD V0 1B
LD VB 0
DRW V0 VE 1
SE VF 0
JP 390
DRW V0 VE 1
JP 394
DRW V0 VD 1
ADD VB 1
ADD V0 1
SE V0 25
JP 386
SNE VB 0
JP 3A6
ADD VD FF
ADD VE FF
SE VD 1
JP 382
CALL 3C0
SE VF 1
CALL 3C0
ADD VA 1
CALL 3C0
LD V0 VA
LD VD 7
AND V0 VD
SNE V0 4
ADD V5 FE
SNE V5 2
LD V5 4
RET
LD I 700
LD [I] V2
LD I 804
LD B VA
LD V2 [I]
LD F V0
LD VD 32
LD VE 0
DRW VD VE 5
ADD VD 5
LD F V1
DRW VD VE 5
ADD VD 5
LD F V2
DRW VD VE 5
LD I 700
LD V2 [I]
LD I 2B4
RET

# Function at 0x3E6
LD VA 0                                                         0x3E6
LD V0 19                                                        0x3E8
RET                                                             0x3EA

RAW 37 23                                                       0x3EC