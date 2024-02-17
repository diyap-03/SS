#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *symtabFile, *optabFile;
    char line[100], label[10], opcode[10], operand[10];
    int locationCounter = 0;
    int startAddress = 0; // Initialize the start address to 0

    // Open the input, symbol table, and opcode table files
    inputFile = fopen("input1.txt", "r");
    symtabFile = fopen("symtab1.txt", "w");
    optabFile = fopen("optab1.txt", "w");

    if (inputFile == NULL || symtabFile == NULL || optabFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // Initialize an array to keep track of optab entries
    char optabEntries[100][10];
    int optabCount = 0;
    int cnt=0;
    int s;

    // Process the input file line by line
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Tokenize the line into label, opcode, and operand
        sscanf(line, "%s %s %s", label, opcode, operand);

        // Check for a comment or empty line
        if (line[0] == '.' || line[0] == '\n') {
            continue;
        }

        if (strcmp(opcode, "START") == 0) {
            // Set the start address from the operand
            startAddress = strtol(operand, NULL, 16);
            s = startAddress;
            locationCounter = startAddress;
        } else if (locationCounter == 0) {
            // If START was not encountered, start from 0
            locationCounter = 0;
        }

        if (strcmp(label, "-") != 0) { // Check if the label is not "-"
            // Write label and location counter to symbol table
            if(strcmp(opcode,"EQU")==0)
            {
                cnt=strtol(operand,NULL,16);
                fprintf(symtabFile, "%s\t%04X\n", label,cnt);

            }
            else{
                fprintf(symtabFile, "%s\t%04X\n", label, locationCounter);
            }

        }

        // Check if the opcode is not in optabEntries
        int isOpcodeInOptab = 0;
        for (int i = 0; i < optabCount; i++) {
            if (strcmp(opcode, optabEntries[i]) == 0) {
                isOpcodeInOptab = 1;
                break;
            }
        }

        if (!isOpcodeInOptab) {
            // Write opcode and its value to the opcode table
            fprintf(optabFile, "%s\t%02X\n", opcode, locationCounter);
            strcpy(optabEntries[optabCount], opcode);
            optabCount++;
        }




        // Increment location counter based on the opcode
        if (strcmp(opcode, "WORD") == 0) {
            locationCounter += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            int reswValue = atoi(operand);
            locationCounter += 3 * reswValue;
        } else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') {
                locationCounter += strlen(operand) - 3; // Adjust for 'C' and quotes
            } else if (operand[0] == 'X') {
                locationCounter += (strlen(operand) - 3) / 2; // Adjust for 'X' and quotes
            }
        } else if (strcmp(opcode, "RESB") == 0) {
            int resbValue = atoi(operand);
            locationCounter += resbValue;
        } else if(strcmp(opcode,"EQU") != 0){
            locationCounter += 3; // Default increment
        }
        if(strcmp(opcode,"ORG")==0)
        {
           startAddress = strtol(operand, NULL, 16);
            locationCounter = startAddress;
        }

    }

    printf("\nThe length of the code is: %d",locationCounter-s);



    // Close the files
    fclose(inputFile);
    fclose(symtabFile);
    fclose(optabFile);

    return 0;
}
