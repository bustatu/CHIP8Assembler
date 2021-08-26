# https://github.com/dmatlack/chip8/blob/master/roms/programs/Minimal%20game%20%5BRevival%20Studios%2C%202007%5D.ch8
# To be compiled with: https://github.com/bustatu/CHIP8Assembler

# START
CLS         # Clears the screen                                                 0x200
CALL 214    # Calls the initialisation function at 0x214                        0x202
CALL 21A    # Calls the draw function at 0x21A to draw sprite                   0x204

# Main loop
CALL 21A    # Calls the draw function at 0x21A to delete sprite                 0x206
CALL 220    # Calls the input checking function at 0x220                        0x208
CALL 21A    # Calls the draw function at 0x21A to draw sprite                   0x20A
LD V0 01    #                                                                   0x20C
LD DT V0    # Loads in the delta timer value 0x01                               0x20E
CALL 242    # Calls delta timer checker function at adress 0x242                0x210
JP 206      # Loops back to 0x206 to delete the sprite.                         0x212

# Initialisation function at 0x214
LD V3 20    # Loads in register 3 value 0x20 (X coord.)                         0x214
LD V4 19    # Loads in register 4 value 0x19 (Y coord.)                         0x216
RET         # Returns from the initialisation function                          0x218

# Draw routine at 0x21A
LD I 24A    #                                                                   0x21A
DRW V3 V4 6 # Draws sprite at adress 24A at coords V3 V4 with height 6          0x21C
RET         # Returns from the function                                         0x21E

# Input checking function at 0x220

    # Down movement
    LD V0 08    #                                                               0x220
    SKP V0      # Skips next instruction if key 8 has been pressed.             0x222
    JP 228      # Jumps to up movement at adress 0x228                          0x224
    ADD V4 01   # Move down 1 pixel                                             0x226

    # Up movement
    LD V0 02    #                                                               0x228
    SKP V0      # Skips next instruction if key 2 has been pressed.             0x22A
    JP 230      # Jumps to left movement at adress 0x230                        0x22C
    ADD V4 FF   # Move up 1 pixel by adding and overflowing                     0x22E

    # Left movement
    LD V0 04    #                                                               0x230
    SKP V0      # Skips next instruction if key 4 has been pressed.             0x232
    JP 238      # Jumps to right movement at adress 0x238                       0x234
    ADD V3 FF   # Move left 1 pixel by adding and overflowing                   0x236

    # Right movement
    LD V0 06    #                                                               0x238
    SKP V0      # Skips next instruction if key 6 has been pressed.             0x23A
    JP 240      # Jumps to adress 0x240                                         0x23C
    ADD V3 01   # Move right 1 pixel                                            0x23E

RET         # Returns from input function call                                  0x240

# Delta time checker function at adress 0x242
LD V0 DT    #                                                                   0x242
SE V0 00    #                                                                   0x244
JP 242      # Loop while delta timer is not 0                                   0x246
RET         # Return from delta timer checker function                          0x248

# Sprite data
RAW 3C 18 FF 18 24 E7   # Player sprite                                         0x24A
RAW 7E FF 99 E7 3C      # Unused skull sprite                                   0x250