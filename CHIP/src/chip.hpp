#pragma once

#include <string>

//can use memory starting from 0x200 location
constexpr int MEMORY_SHIFT = 0x200;

class Chip
{
public:
	//is CHIP-8 initialized and running.
	bool isRunning;
	//something changed.
	bool shouldDraw;

	void initialize()
	{
		opcode = 0;
		I = 0;
		sp = 0;
		PC = 0x200;
		isRunning = true;
	}

	//load game in binary format
	void loadGame(std::string game)
	{
		for (int i = 0; i < game.length(); i++) {
			memory[MEMORY_SHIFT + i] = game[i];
		}
		int a = 0;
	}

	void emulateStep()
	{
		
	}

	void terminate()
	{
		isRunning = false;
	}


private:
	//each opcode is a 2 byte long. This is a current opcode.
	unsigned short opcode;
	//CHIP-8 memory contains 4K bytes.
	unsigned char memory[4096];
	//16 registers starting from V0 to VF. VF is reserved for flags.
	unsigned char V[16];
	//address register (16 bits wide) stores a memory address.
	unsigned short I;
	//program counter (?)
	unsigned short PC;
	//graphics has a total of 64x32 pixels on a screen.
	unsigned char gfx[64 * 32];
	//timer will count down to zero when set above. Used by events.
	unsigned char delayTimer;
	//same as previous. Used by sounds. Will beep while not a zero.
	unsigned char soundTimer;
	//stack which stores return addresses while calling subroutines.
	unsigned short stack[16];
	//current stack pointer;
	unsigned short sp;
	//keypad that has 16 keys [0 to F].
	unsigned char key[16];
};