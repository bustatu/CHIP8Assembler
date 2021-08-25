// Contains the opcode convertor function.

// Include all standard C++ libraries
#include <bits/stdc++.h>

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

#define ld_reg_byte(opcode)    \
    /* Make the opcode */   \
    instr |= opcode;    \
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
    else if(word == "SYS")  {   has_addr(0x0000);       }   // Syscall (not implemented in most emulators)
    else if(word == "JP")   {   has_addr(0x1000);       }   // Jump
    else if(word == "CALL") {   has_addr(0x2000);       }   // Call function
    else if(word == "RAW")  {   byte_transfer();        }   // Write raw bytes
    else if(word == "LD")
    {
        // Read the source
        std::string src, dest;
        if(!(ss >> src))
        {
            printf("{E}: Unknown load destination %s!\n", src.c_str());
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
            if('0' <= dest[0] && dest[0] >= '9')
            {
                ld_reg_byte(0x6000);
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
    else                    {   unknown();              }   // Unknown opcode
}