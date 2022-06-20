#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char; // 8 bit address
using Word = unsigned short; // 16 bit address

using u32 = unsigned int; // 32 bit value

struct MemoryRAM
{
	static constexpr u32 MAX_MEMORY = 1024 * 64; // maximum size of RAM in the Commodore 
	Byte Data[MAX_MEMORY]; // Emulated RAM
	
	void Initialize() // initialize memory to default
	{
		for(u32 i = 0; i < MAX_MEMORY; i++) Data[i] = 0; // zeroing memory
	}
	
	Byte operator[](u32 Address) const // operator to access the memory like an array
	{
		// needs assertion of address in bounds
		return Data[Address];
	}
};

struct CPU
{
	Word PC; // Program Counter
	Word SP; // Stack Pointer
	
	// Registers
	Byte A; //Accumulator Register
	Byte X; // index Register X
	Byte Y; // index Register Y
	
	// Statuts Flags
	Byte C : 1; // Carry Flag
	Byte Z : 1; // Zero Flag
	Byte I : 1; // Interrupt Disable
	Byte D : 1; // Decimal Mode
	Byte B : 1; // Break Command
	Byte V : 1; // Overflow Flag
	Byte N : 1; // Negative Flag

	void Reset(MemoryRAM & Ram) // initialize internals of the CPU to a default state
	{
	
		PC = 0xFFFC; // position of the reset vector(???) 
		SP = 0x0100; // initial call of stack pointer(???)
		
		// status flags default state
		C = 0;
		Z = 0;
		I = 0;
		D = 0;
		B = 0;
		V = 0;
		N = 0; 
		
		// registers default state
		A = 0;
		X = 0;
		Y = 0;
		
		Ram.Initialize(); // setting the RAM to the default state
	}
	
	Byte FetchByte(u32 & Cycles, MemoryRAM & Ram) // accessing the data
	{
		Byte Data = Ram[PC]; // Saving the data
		PC++; // increasing Program Counter
		Cycles--; // decreasing remaing cycles
		
		return Data;
	}
	
	void Execute(u32 Cycles, MemoryRAM & Ram) // executing instructions
	{
		for(Cycles; Cycles > 0;) // loop to decrease cycles fetching isntructions
		{
			Byte CurrentInstruction = FetchByte(Cycles, Ram); // saving data
			(void) CurrentInstruction; // to remove
		}
	}
};

int main()
{
	// """"POST""""
	CPU Cpu; 
	MemoryRAM Ram;
	
	// Commodore initialization
	Cpu.Reset(Ram);
	
	return 0;
}
