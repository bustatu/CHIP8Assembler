// Include all standard C++ libraries
#include <bits/stdc++.h>

// Include the opcode convertor
#include "convert.cpp"

// Clear the comment from the line if it exists in the input
void removecomments(std::string &input)
{
    // Find first ;
    size_t pos = input.find("#");

    // Keep only everything before it
    if(pos != std::string::npos)
        input = input.substr(0, pos);
}

int main(int argc, char* argv[])
{
    // Check for correct usage
    if(argc != 3)
    {
        printf("\033[1;31m");
        printf("{E}: Incorrect usage. Use the path of the assembly file as a parameter for the executable and another one for the output file and nothig else!\n");
        printf("{I}: Expected arguments: 3, got %d arguments!\n", argc);
        printf("\033[0m");
        return EXIT_FAILURE;
    }

    // Input and output files
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    // Input line
    std::string line;
    uint32_t linecount = 0;

    // Output flag and byte
    uint16_t instr = 0, flag = 0;
    uint16_t big = 0, small = 0;
    
    while(!fin.eof())
    {
        // Read current line
        getline(fin, line);
        linecount++;

        // Remove any comments
        removecomments(line);

        // If not empty
        if(line.size() != 0)
        {
            // Convert the line to a byte
            convert(line, instr, flag, fout);

            // Check the resulting operation
            switch(flag)
            {
                // Success, we can write it to the file
                case 0x00:
                    writeword(instr, fout);
                    break;
                // Unknown assembly, ignoring output
                case 0x01:
                    printf("{W}: Unknown assembly at line: %d! Ignoring ouput...\n", linecount);
                    break;
                // Raw byte data has been copied
                case 0x02:
                    //printf("{I}: Raw byte data has been copied!\n");
                    break;
                // Empty line
                case 0x03:
                    break;
                default:
                    printf("{W}: Unknown flag state: %02X\n", flag);
                    break;
            }
        }
    }

    return EXIT_SUCCESS;
}