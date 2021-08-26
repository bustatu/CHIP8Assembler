// Include all standard C++ libraries
#include <bits/stdc++.h>

// Yoinked from my emulator implementation
// https://github.com/bustatu/EmulatorEngine
#define N000(opcode) ((opcode & 0xF000) >> 12)
#define NNN(opcode) (opcode & 0xFFF)
#define N00(opcode) ((opcode & 0xF00) >> 8)
#define NN(opcode) (opcode & 0xFF)
#define N0(opcode) ((opcode & 0xF0) >> 4)
#define N(opcode) (opcode & 0xF)

// Dissasembles an opcode
std::string disassembly(uint16_t opcode)
{
    std::stringstream result;
    // Hex is converted to uppercase NOTHING ELSE is affected
    result << std::hex << std::uppercase;
    switch(N000(opcode))
    {
        case 0x0:
            switch(NN(opcode))
            {
                case 0xE0:
                    result << "CLS";
                    break;
                case 0xEE:
                    result << "RET";
                    break;
                case 0xFF:
                    result << "HIGH";
                    break;
                default:
                    result << "Unknown disassembly! " << opcode;
                    break;
            }
            break;
        case 0x1:
            result << "JP " << NNN(opcode);
            break;
        case 0x2:
            result << "CALL " << NNN(opcode);
            break;
        case 0x3:
            result << "SE V" << N00(opcode) << " " << NN(opcode);
            break;
        case 0x4:
            result << "SNE V" << N00(opcode) << " " << NN(opcode);
            break;
        case 0x5:
            result << "SE V" << N00(opcode) << " V" << N0(opcode);
            break;
        case 0x6:
            result << "LD V" << N00(opcode) << " " << NN(opcode);
            break;
        case 0x7:
            result << "ADD V" << N00(opcode) << " " << NN(opcode);
            break;
        case 0x8:
            switch(N(opcode))
            {
                case 0x0:
                    result << "LD V" << N00(opcode) << " V" << N0(opcode);
                    break;
                case 0x1:
                    result << "OR V" << N00(opcode) << " V" << N0(opcode);
                    break;
                case 0x2:
                    result << "AND V" << N00(opcode) << " V" << N0(opcode);
                    break;
                case 0x3:
                    result << "XOR V" << N00(opcode) << " V" << N0(opcode);
                    break;
                case 0x4:
                    result << "ADD V" << N00(opcode) << " V" << N0(opcode);
                    break;
                case 0x5:
                    result << "SUB V" << N00(opcode) << " V" << N0(opcode);
                    break;
                case 0x6:
                    result << "SHR V" << N00(opcode);
                    break;
                case 0x7:
                    result << "SUBN V" << N00(opcode) << " V" << N0(opcode);
                    break;
                case 0xE:
                    result << "SHL V" << N00(opcode);
                    break;
                default:
                    result << "Unknown disassembly! " << opcode;
                    break;
            }
            break;
        case 0x9:
            result << "SNE V" << N00(opcode) << " V" << N0(opcode);
            break;
        case 0xA:
            result << "LD I " << NNN(opcode);
            break;
        case 0xB:
            result << "JP V0 " << NNN(opcode);
            break;
        case 0xC:
            result << "RND V" << N00(opcode) << " " << NN(opcode);
            break;
        case 0xD:
            result << "DRW V" << N00(opcode) << " V" << N0(opcode) << " " << N(opcode);
            break;
        case 0xE:
            switch(NN(opcode))
            {
                case 0x9E:
                    result << "SKP V" << N00(opcode);
                    break;
                case 0xA1:
                    result << "SKNP V" << N00(opcode);
                    break;
                default:
                    result << "Unknown disassembly! " << opcode;
                    break;
            }
            break;
        case 0xF:
            switch(NN(opcode))
            {
                case 0x07:
                    result << "LD V" << N00(opcode) << " DT";
                    break;
                case 0x0A:
                    result << "LD V" << N00(opcode) << " K";
                    break;
                case 0x15:
                    result << "LD DT V" << N00(opcode);
                    break;
                case 0x18:
                    result << "LD ST V" << N00(opcode);
                    break;
                case 0x1E:
                    result << "ADD I V" << N00(opcode);
                    break;
                case 0x29:
                    result << "LD F V" << N00(opcode);
                    break;
                case 0x30:
                    result << "LD HF V" << N00(opcode);
                    break;
                case 0x33:
                    result << "LD B V" << N00(opcode);
                    break;
                case 0x55:
                    result << "LD [I] V" << N00(opcode);
                    break;
                case 0x65:
                    result << "LD V" << N00(opcode) << " [I]";
                    break;
                case 0x75:
                    result << "LD R V" << N00(opcode);
                    break;
                case 0x85:
                    result << "LD V" << N00(opcode) << " R";
                    break;
                default:
                    result << "Unknown disassembly! " << opcode;
                    break;
            }
            break;
        default:
            result << "Unknown disassembly! " << opcode;
            break;
    }
    return result.str();
}