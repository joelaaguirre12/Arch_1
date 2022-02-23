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

/* Personal stringCompare function */
bool stringCompare(char* str1, char* str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2) {
			return false;
		}
		*str1++;
		*str2++;
	}
	return true;
}


/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	// Load, Store, Add, Addi
	// AND, OR, XOR (Extra Credit)
	char** tokens = tokenize(instr, ' ');
	char* op = tokens[0];
	char* rd = tokens[1];
	char* rs1 = tokens[2];
	//char* imm = tokens[3]; // AKA rs2
	if (stringCompare(op, "ADD")) {
		printf("%s\n", op);
		printf("%s\n", rd);
		printf("%s\n", rs1);
		//printf("%s\n", imm);
	}
	else if (stringCompare(op, "ADDI")) {
		printf("%s\n", op);
		printf("%s\n", rd);
		printf("%s\n", rs1);
		//printf("%s\n", imm);
	}
	else if (stringCompare(op, "SW")) {
		printf("%s\n", op);
		printf("%s\n", rd);
		printf("%s\n", rs1);
		//printf("%s\n", imm);
	}
	else if (stringCompare(op, "LW")) {
		printf("%s\n", op);
		printf("%s\n", rd);
		printf("%s\n", rs1);
		//printf("%s\n", imm);
	}
	return true;
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
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();
	interpret("ADD X6 X0 X29");
	interpret("ADDI X6 X6 329");
	interpret("LW X7 1000(X5)");
	interpret("SW X5 1000(X0)");

	return 0;
}
