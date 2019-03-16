#include <string.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int reg[] = {0,0,0,0,0,0,0,0};
	int regSize = sizeof(reg) / sizeof(int);
        int lineNumber = 0;
        char c;
        char *fnamein;
        char *fnameout;
        int len;
        int validInstruction = 0;
        char line[30];
        int lines = 0;

        while (( c = getopt(argc, argv, "i:o:" )) != -1)
        {
                switch(c)
                {
                        case 'i':
                                len = strlen(optarg);
                                fnamein = malloc((len+1)*sizeof(char)+1);
                                memset(fnamein,0,len+1);
                                strncpy(fnamein, optarg, len);
                        break;
                        case 'o':
                                len = strlen(optarg);
                                fnameout = malloc((len+1)*sizeof(char)+1);
                                memset(fnameout,0,len+1);
                                strncpy(fnameout, optarg, len);
                        break;
                default:
                        printf("Error.");
                        exit(0);
                }

        }

        FILE *in = fopen(fnamein, "r");//open file to read from

        if (in == NULL)//if no read file, error out
        {
                printf("Error");
                exit(-1);
        }

        while(fgets(line, 30, in) != NULL)//count number of lines in input file
        {
                lines++;
//printf("Line number is: %d\n", lines);
        }

        int fclose( FILE *in );

        FILE *firstpass = fopen(fnamein,"r");

        if(lines==0)
        {
		printf("Error: Empty file\n");
                exit(0);
        }

	int mem[lines-1];
	int index = 0;
	char section[100];
	char *chunk;

	while(fgets(section, 99, firstpass) != NULL)//count number of lines in input file
        {
		chunk = strtok(section, "\n");
		if( chunk != NULL)
		{
                      	mem[index] = atoi(chunk);
			index++;
		}
        }

        int fclose( FILE *in );

	for(int i = 0; i < lines-1; i++)
	{
//printf("mem[%d] is: %d\n", i, mem[i]);
	}

	int pc = 0;
	int opcode;
	int opcodes[8] = {0,1,2,3,4,5,6,7};
	int opcodesSize = sizeof(opcodes) / sizeof(int);
	int fieldValue = 0;

        printf("\n@@@\nstate:\n");
        printf("\tpc %d\n", pc);
        printf("\tmemory:\n");

        for(int i = 0; i < lines; i++)
        {
     		printf("\t\tmem[%d]=%d\n", i, mem[i]);
        }

        printf("\tregisters:\n");

        for(int i = 0; i < regSize; i++)
        {
        	printf("\t\treg[%d]=%d\n", i, reg[i]);
        }

        printf("end state\n");

	while(pc < lines)
	{
		opcode = mem[pc]>>22;
		printf("opcode is: %d\n", opcode);

		for(int i = 0; i < opcodesSize; i++)
		{
			if(opcode == opcodes[i])
			{
				if(opcode == 0)//AND
				{
					int regA = 0;
					int regB = 0;
					int destination = 0;
					int memory = mem[pc];

					memory = memory - (opcode<<22);
					regA = memory>>19;
					memory = memory - (regA<<19);
					regB = memory>>16;
					memory = memory - (regB<<16);
					destination = memory>>0;
					memory = memory - (destination<<0);

					reg[destination] = reg[regA] + reg[regB];
					i = opcodesSize;

				}
				else if(opcode == 1)//NAND -- OUTPUT MIGHT BE OFF?
                                {
                                        int regA = 0;
                                        int regB = 0;
                                        int destination = 0;
					int memory = mem[pc];

                                        memory = memory - (opcode<<22);
                                        regA = memory>>19;
                                        memory = memory - (regA<<19);
                                        regB = memory>>16;
                                        memory = memory - (regB<<16);
                                        destination = memory>>0;
                                        memory = memory - (destination<<0);

                                        reg[destination] = ~(reg[regA] & reg[regB]);
					i = opcodesSize;
                                }
				else if(opcode == 2)//LW
				{
					int regA = 0;
                                        int regB = 0;
                                        int offset = 0;
					int memory = mem[pc];

                                        memory = memory - (opcode<<22);
                                        regA = memory>>19;
                                        memory = memory - (regA<<19);
                                        regB = memory>>16;
                                        memory = memory - (regB<<16);
                                        offset = memory>>0;
                                       	memory = memory - (offset<<0);
                                        reg[regA] = regB + offset;
					i = opcodesSize;

				}
				else if(opcode == 3)//SW
                                {
					int regA = 0;
                                        int regB = 0;
                                        int offset = 0;
					int memory = mem[pc];

                                        memory = memory - (opcode<<22);
                                        regA = memory>>19;
                                        memory = memory - (regA<<19);
                                        regB = memory>>16;
                                        memory = memory - (regB<<16);
                                        offset = memory>>0;
                                        memory = memory - (offset<<0);

					mem[pc] = reg[regB] + offset;
					i = opcodesSize;

                                }
				else if(opcode == 4)//BEQ
                                {
					int regA = 0;
                                        int regB = 0;
                                        int offset = 0;
                                        int memory = mem[pc];

                                        memory = memory - (opcode<<22);
                                        regA = memory>>19;
                                        memory = memory - (regA<<19);
                                        regB = memory>>16;
                                        memory = memory - (regB<<16);
                                        offset = memory>>0;
                                        memory = memory - (offset<<0);

					if(reg[regA] == reg[regB])
					{
						pc = pc + offset;
					}

                                }
				else if(opcode == 5)//JALR -- NO WORKY
                                {
					int regA = 0;
                                        int regB = 0;
                                        int offset = 0;
                                        int memory = mem[pc];

                                        memory = memory - (opcode<<22);
                                        regA = memory>>19;
                                        memory = memory - (regA<<19);
                                        regB = memory>>16;
                                        memory = memory - (regB<<16);
                                        offset = memory>>0;
                                        memory = memory - (offset<<0);

                                        reg[regA] = pc + 1;
					reg[regB] = 0; 
					i = opcodesSize;

                                }
				else if(opcode == 6)//HALT
                                {
					pc++;

        printf("\n@@@\nstate:\n");
        printf("\tpc %d\n", pc);
        printf("\tmemory:\n");

        for(int i = 0; i < lines; i++)
        {
                printf("\t\tmem[%d]=%d\n", i, mem[i]);
        }

        printf("\tregisters:\n");

        for(int i = 0; i < regSize; i++)
        {
                printf("\t\treg[%d]=%d\n", i, reg[i]);
        }

                printf("end state\n");
					printf("HALTED.\n");
					exit(0);
				}
			}

		}


	pc++;

	printf("\n@@@\nstate:\n");
        printf("\tpc %d\n", pc);
        printf("\tmemory:\n");

        for(int i = 0; i < lines; i++)
        {
                printf("\t\tmem[%d]=%d\n", i, mem[i]);
        }

        printf("\tregisters:\n");

        for(int i = 0; i < regSize; i++)
        {
                printf("\t\treg[%d]=%d\n", i, reg[i]);
        }

        	printf("end state\n");
	}

	return 0;

}
