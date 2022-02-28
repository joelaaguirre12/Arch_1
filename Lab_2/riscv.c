#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#include <string.h>

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

/**
 * Prints all 32 registers in column-format
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/* Personal stringCompare function */
bool stringCompare(char* str1, char* str2) {
	while (*str1 != '\0' || *str2 != '\0') {
		if ((*str1 != *str2) || (*str1 == '\0' && *str2 != '\0') || (*str1 != '\0' && *str2 == '\0')) {
			return false;
		}
		*str1++;
		*str2++;
	}
	return true;
}

/* Function to specifically take a register in the format 'X0000000' and remove the X and return the register number */
int32_t regTokenize(char* reg) {
	char** r = tokenize(reg, 'X');
	return atoi(r[0]);
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	// Load, Store, Add, Addi
	// AND, OR, XOR (Extra Credit)
	char* mem_file = "mem.txt";
	char** tokens = tokenize(instr, ' ');
	char* op = tokens[0]; // operation
	int rd = regTokenize(tokens[1]); // first argument is always a register
	if (stringCompare(op, "ADD")) {
		int rs1 = regTokenize(tokens[2]);
		int rs2 = regTokenize(tokens[3]);
		//printf("%s, %d, %d, %d\n", op, rd, rs1, rs2);
		reg[rd] = reg[rs1] + reg[rs2];
		print_regs();
		return true;
	}
	else if (stringCompare(op, "ADDI")) {
		int rs1 = regTokenize(tokens[2]);
		int imm = atoi(tokens[3]);
		//printf("%s, %d, %d, %d\n", op, rd, rs1, imm);
		reg[rd] = reg[rs1] + imm;
		print_regs();
		return true;
	}
	else if (stringCompare(op, "SW")) {
		// M[R[rs1] + imm]] = R[rd]
		char** immAndReg1 = tokenize(tokens[2], '(');
		int32_t imm = atoi(immAndReg1[0]);
		char* reg1 = immAndReg1[1];
		char** tokReg1 = tokenize(reg1, ')');
		int32_t rs1 = regTokenize(tokReg1[0]);
		int32_t address = reg[rs1] + imm;
		//printf("%s, %d, %d, %d\n", op, rd, rs1, imm);
		write_address(reg[rd], address, mem_file);
		int32_t read = read_address(address, mem_file);
		printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read);
		return true;
	}
	else if (stringCompare(op, "LW")) {
		// R[rd] = M[R[rs1] + imm]]
		char** immAndReg1 = tokenize(tokens[2], '(');
		int32_t imm = atoi(immAndReg1[0]);
		char* reg1 = immAndReg1[1];
		char** tokReg1 = tokenize(reg1, ')');
		int32_t rs1 = regTokenize(tokReg1[0]);
		int32_t address = reg[rs1] + imm;
		//printf("%s, %d, %d, %d\n", op, rd, rs1, imm);
		int32_t read = read_address(address, mem_file);
		printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read);
		reg[rd] = read_address(address, mem_file);
		return true;
	}
	return false;
}

/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}


/**
 * Your code goes in the main
 *
 */
int main(){
	char* mem_file = "mem.txt";
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	printf("Intitial registers:\n");
	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();
	printf("Interpret ADD X6 X4 X29...\n");
	interpret("ADD X6 X4 X29");

	printf("Interpret ADDI X6 X8 329...\n");
	interpret("ADDI X6 X8 329");

	printf("Interpret SW X5 80(X8)...\n");
	interpret("SW X5 80(X8)");

	printf("Interpret LW X7 52(X5)...\n");
	interpret("LW X7 52(X5)");
	print_regs();

	return 0;
}
