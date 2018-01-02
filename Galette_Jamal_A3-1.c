//Jamal Galette
//CGS3269
//Assignment 3                                                                                                    
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

// make the struct to take in both of the input file numbers

typedef struct inStruct{
	int opCode;
	int addr;
}ghost;


int main(void){

		//variable declaration

		int j;
		int accumulator = 0;
		int MAR = 0;
		int MDR = 0;
		int PC = 10;
		int DM[10];

	// Read in file line by line

	FILE *ifp;
	ifp = fopen("input.txt", "r");

	// Running the Im, mdr, IR through the struct
	ghost IM[MAX];
	ghost IR;
	ghost MDR2;

	IR.opCode = 1;
	IR.addr = 0;

			//Error message for a file that doesnt exist
			if (ifp == NULL){
				printf("File cannot open!");
				exit(1);
			}

			//When the file is found alert the user
			else
				printf("File can now be used! \n");

			//store values 
			for (j = 0; j < 10; j++){
				IM[j].opCode = 0;
				IM[j].addr = 0;
				DM[j] = 0;
			}
			//While the user isnt trying to exit the program do the following:
			//store first number in opcode and second on addr
			while (IR.opCode != 7){
				int k = 0;
				fscanf(ifp, "%d", &IM[k].opCode);
				fscanf(ifp, "%d", &IM[k].addr);

				//if exiting break out
				if (IM[k].opCode == 7){
					break;
				}

		//REGULAR PRINT STATEMENT FOR STAUTS OF PC AND ETC	
		printf("PC = %d | accumulator = %d, Mem = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n", PC, accumulator, DM[0], DM[1], DM[2], DM[3], DM[4], DM[5], DM[6], DM[7], DM[8], DM[9]);

		//read function storing the values of the input file
		MAR = PC;
		PC = PC + 1;
		MDR2.opCode = IM[k].opCode;
		MDR2.addr = IM[k].addr;
		IR.addr = MDR2.addr;
		IR.opCode = MDR2.opCode;

		k++;

		//running a switch statement to determine the use of each function
		//which allows users to add,store,subtract,jmp,skipz
		switch (IR.opCode){
		case 1: // Load 
			MAR = IR.addr;
			MDR = DM[MAR];
			accumulator = MDR;
			printf("Loading variables ");
			break;

		case 2: // Add
			MAR = IR.addr;
			MDR = DM[MAR];
			accumulator = accumulator + MDR;
			printf("Adding variables ");
			break;

		case 3: // giving the accumulator a new 0 value, savinf addr to mar, and mdr to accumaltor
			MAR = IR.addr;
			MDR = accumulator;
			DM[MAR] = MDR;
			accumulator = 0;
			printf("Storing variables ");
			break;

		case 4: // subtact function which takes value of mdr from accumulator
			MAR = IR.addr;
			MDR = DM[MAR];
			accumulator = accumulator - MDR;
			printf("Subtracting variables");
			break;

		case 5: // ask user for input of a number
			printf("Input a number\n");
			scanf("%d", &accumulator);
			break;

		case 6: // show the resuts on screen
			printf("AC = %d\n", accumulator);
			break;

		case 7: // End the program 
			break;

		case 8: // jmp back to addr
			PC = IR.addr;
			break;

		case 9: // SkipZ
			if (DM[MAR] == 0)
				PC++;
			break;
		}
	}
	printf("Program is now Complete. \n");
	//printf("Be Safe Though "\n);
	return 0;
}
