// Contains the opcode convertor function.

// Include all standard C++ libraries
#include <bits/stdc++.h>

// Checks if a character is hex
bool isHex(char ch)
{
    return ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F'));
}

// Converts from hex to decimal
uint32_t hextodec(std::string string)
{
    std::stringstream stream(string);
    uint32_t x;
    stream >> std::hex >> x;
    return x;
}

// Writes a word to the fout file
void writeword(uint16_t instr, std::ofstream &fout)
{
    // Convert it to big endian
    uint8_t big = (instr & 0xFF00) >> 8;
    uint8_t small = instr & 0xFF;
    
    // Write it to the file
    fout.write(reinterpret_cast<const char*>(&big), 1);
    fout.write(reinterpret_cast<const char*>(&small), 1);
}

// Writes a byte to the fout file
void writebyte(uint8_t byte, std::ofstream &fout)
{
    // Write it to the file
    fout.write(reinterpret_cast<const char*>(&byte), 1);
}

// Macros for better usability
#define has_addr(opcode) \
    /* Read the adress as hex in the instr and if it's not valid end this */ \
    if(!(ss >> std::hex >> instr))  {   flag = 1;   return; }   \
    /* Make the opcode */   \
    instr |= opcode;    \
    flag = 0x00;

#define simple(opcode) \
    /* Set the opcode directly */   \
    instr = opcode, flag = 0x00;

#define byte_transfer() \
    /* Read all bytes and write them */ \
    while(ss >> std::hex >> instr)  \
        writebyte((uint8_t)instr, fout);    \
    /* Flag 2 to mark the transfer */   \
    flag = 0x02;

#define ld_I_addr(opcode)    \
    /* Set the byte in the opcode */    \
    std::stringstream(dest) >> std::hex >> instr;   \
    /* Make the opcode */   \
    instr |= opcode;    \
    flag = 0x00;

#define ld_reg_byte(opcode)    \
    /* Set the byte in the opcode */    \
    std::stringstream(dest) >> std::hex >> instr;   \
    /* Read which register needs to be updated */   \
    uint16_t aux;    \
    std::stringstream(src.substr(1, 1)) >> std::hex >> aux; \
    /* Make the opcode */   \
    instr |= opcode;    \
    instr |= aux << 8;  \
    flag = 0x00;

#define unknown()   \
    printf("{E}: Unknown keyword: %s!\n", word.c_str());    \
    instr = 0x0000, flag = 0x01;

// Converts an instruction. If it is unknown or can't be parsed, it gets converted to a NOP.
void convert(std::string input, uint16_t &instr, uint16_t& flag, std::ofstream &fout)
{
    // Convert this to a stringstream so we can get the words from it
    std::stringstream ss(input);
    std::string word;

    // Read first word
    ss >> word;

    // Compare it and generate the corect opcode

    // Clear screen
    if(word == "CLS")       {   simple(0x00E0);         }   // Clear screen
    else if(word == "RET")  {   simple(0x00EE);         }   // Return from function call
    else if(word == "SYS")  {   has_addr(0x0000);       }   // Syscall (not implemented in most emulators)
    else if(word == "JP")   {   has_addr(0x1000);       }   // Jump
    else if(word == "CALL") {   has_addr(0x2000);       }   // Call function
    else if(word == "RAW")  {   byte_transfer();        }   // Write raw bytes
    else if(word == "LD")   {                               // Load function (can have multiple patterns)
        // Read the source
        std::string src, dest;
        if(!(ss >> src))
        {
            printf("{E}: Unknown load destination!\n");
            flag = 0x01;
        }

        // Load to register
        if(src[0] == 'V')
        {
            // Read the source
            if(!(ss >> dest))
            {
                printf("{E}: Unknown load source %s!\n", dest.c_str());
                flag = 0x01;
            }
            
            // Load byte to register
            if(isHex(dest[0]) && dest[1] != 'T')  {   ld_reg_byte(0x6000);    }
            // Load delta timer to register
            else if(dest[0] == 'D' && dest[1] == 'T')
            {
                instr = 0xF007;
                instr |= hextodec(src.substr(1, 1)) << 8;
                flag = 0x00;
            }
            else
            {
                printf("{E}: Unknown load source %s!\n", dest.c_str());
                flag = 0x01;
            }
        }
        // Load to I
        else if(src == "I")
        {
            // Read the source
            if(!(ss >> dest))
            {
                printf("{E}: Unknown load source %s!\n", dest.c_str());
                flag = 0x01;
            }

            // Load adress to I
            if(isHex(dest[0]))    {   ld_I_addr(0xA000);  }
            else
            {
                printf("{E}: Unknown load source %s!\n", dest.c_str());
                flag = 0x01;
            }
        }
        else if(src == "DT")
        {
            // Read the source
            if(!(ss >> dest))
            {
                printf("{E}: Unknown load source!\n");
                flag = 0x01;
            }

            // Load to DT
            if(dest[0] == 'V' && isHex(dest[1]))
            {
                instr = 0xF015;
                instr |= hextodec(dest.substr(1, 1)) << 8;
                flag = 0x00;
            }
            else
            {
                printf("{E}: Unknown load source %s!\n", dest.c_str());
                flag = 0x01;
            }     
        }
        else
        {
            printf("{E}: Unknown load destination %s!\n", src.c_str());
            flag = 0x01;
        }
    }
    else if(word == "DRW")  {                               // Draw opcode
        std::string src, dest, size;
        if(!(ss >> src >> dest >> size))
        {
            printf("{E}: Unknown draw function pattern %s!\n", src.c_str());
            flag = 0x01;
        }

        // Check for correct format
        if(src[0] == 'V' && dest[0] == 'V' && isHex(size[0]))
        {
            // Create the opcode
            instr = 0;
            instr |= 0xD000;
            instr |= hextodec(src.substr(1, 1)) << 8;
            instr |= hextodec(dest.substr(1, 1)) << 4;
            instr |= hextodec(size.substr(0, 1));
            flag = 0x00;
        }
        else
        {
            printf("{E}: Unknown draw function pattern %s!\n", src.c_str());
            flag = 0x01;
        }
    }
    else if(word != "")     {   unknown();              }   // Unknown opcode
    else    {   flag = 0x03;    }                           // Empty line
}