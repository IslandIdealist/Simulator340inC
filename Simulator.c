#include <string.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int reg[8] = {0,0,0,0,0,0,0,0};
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
	int opcodesSize = *(&opcodesSize + 1) - opcodesSize;
	int fieldValue = 0;

	while(pc < lines-1)
	{
		opcode = mem[pc]>>22;

		for(int i = 0; i < opcodesSize; i++)
		{
			if(opcode == opcodes[i])
			{
				if(opcode == 0)
				{
					int regA = 0;
					int regB = 0;
					int destination = 0;

					mem[pc] = mem[pc] - (opcode<<22);
					regA = mem[pc]>>19;
					mem[pc] = mem[pc] - (regA<<19);
					regB = mem[pc]>>16;
					mem[pc] = mem[pc] - (regB<<16);
					destination = mem[pc]>>0;
					mem[pc] = mem[pc] - (destination<<0);

					reg[destination] = reg[regA] + reg[regB];
					printf("Reg[1] contents is: %d\n", reg[1]);

				}
				else if(opcode == 2)
				{
					int regA = 0;
                                        int regB = 0;
                                        int offset = 0;

                                        mem[pc] = mem[pc] - (opcode<<22);
                                        regA = mem[pc]>>19;
                                        mem[pc] = mem[pc] - (regA<<19);
                                        regB = mem[pc]>>16;
                                        mem[pc] = mem[pc] - (regB<<16);
                                        offset = mem[pc]>>0;
                                        mem[pc] = mem[pc] - (offset<<0);
                                        reg[regA] = regB + offset;
                                        printf("Reg[%d] contents is: %d\n", regA, reg[regA]);

				}
/*				else if()
                                {


                                }
				else if()
                                {


                                }
				else if()
                                {


                                }
				else if()
                                {


                                }
				else if()
                                {


                                }
				else if()
                                {


                                }*/
			}

		}


		pc++;
	}

	return 0;

}

