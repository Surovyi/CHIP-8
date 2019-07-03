#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>

//can use memory starting from 0x200 location
constexpr int MEMORY_SHIFT = 0x200;
constexpr unsigned short DISPLAY_WIDTH = 64;
constexpr unsigned short DISPLAY_HEIGHT = 32;

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
		pc = MEMORY_SHIFT;
		isRunning = true;
		loadFontIntoMemory();
	}

	void loadFontIntoMemory()
	{
#pragma region Font
		unsigned char fonts[] = {
			// "0"
			0xF0,
			0x90,
			0x90,
			0x90,
			0xF0,
			// "1"
			0x20,
			0x60,
			0x20,
			0x20,
			0x70,
			// "2"
			0xF0,
			0x10,
			0xF0,
			0x80,
			0xF0,
			// "3"
			0xF0,
			0x10,
			0xF0,
			0x10,
			0xF0,
			// "4"
			0x90,
			0x90,
			0xF0,
			0x10,
			0x10,
			// "5"
			0xF0,
			0x80,
			0xF0,
			0x10,
			0xF0,
			// "6"
			0xF0,
			0x80,
			0xF0,
			0x90,
			0xF0,
			// "7"
			0xF0,
			0x10,
			0x20,
			0x40,
			0x40,
			// "8"
			0xF0,
			0x90,
			0xF0,
			0x90,
			0xF0,
			// "9"
			0xF0,
			0x90,
			0xF0,
			0x10,
			0xF0,
			// "A"
			0xF0,
			0x90,
			0xF0,
			0x90,
			0x90,
			// "B"
			0xE0,
			0x90,
			0xE0,
			0x90,
			0xE0,
			// "C"
			0xF0,
			0x80,
			0x80,
			0x80,
			0xF0,
			// "D"
			0xE0,
			0x90,
			0x90,
			0x90,
			0xE0,
			// "E"
			0xF0,
			0x80,
			0xF0,
			0x80,
			0xF0,
			// "F"
			0xF0,
			0x80,
			0xF0,
			0x80,
			0x80,
		};
#pragma endregion

		std::copy(fonts, fonts + 16 * 5, memory);
	}

	//load game in binary format
	void loadGame(std::string game)
	{
		std::cout << "[CHIP]: Loading game into memory! Game size: " << sizeof(game) << " bytes." << std::endl;

		for (int i = 0; i < game.length(); i++) {
			memory[MEMORY_SHIFT + i] = game[i];
		}
		int a = 0;
	}

	void keyPress(int k)
	{
		key[k] = 1;
	}

	void keyRelease(int k)
	{
		key[k] = 0;
	}

	void step()
	{
		////test 00e0
		//memory[pc] = 0x00;
		//memory[pc + 1] = 0xe0;

		////test 00ee
		//memory[pc] = 0x00;
		//memory[pc + 1] = 0xee;

		////test 1000
		//memory[pc] = 0x12;
		//memory[pc + 1] = 0x14;

		////test 2000
		//memory[pc] = 0x23;
		//memory[pc + 1] = 0x26;

		////test 3000
		//memory[pc] = 0x30;
		//memory[pc + 1] = 0x00;

		////test 4000
		//memory[pc] = 0x4a;
		//memory[pc + 1] = 0x00;

		////test 6000
		//memory[pc] = 0x6b;
		//memory[pc + 1] = 0x04;

		////test 7000
		//memory[pc] = 0x7d;
		//memory[pc + 1] = 0x01;

		////test 8xy0
		//memory[pc] = 0x88;
		//memory[pc + 1] = 0xd0;

		////test a000
		//memory[pc] = 0xa3;
		//memory[pc + 1] = 0x62;

		////test d000
		//memory[pc] = 0xd8;
		//memory[pc + 1] = 0x91;

		////test exa1
		//memory[pc] = 0xe0;
		//memory[pc + 1] = 0xa1;

		////test fx07
		//memory[pc] = 0xf0;
		//memory[pc + 1] = 0x07;

		////test fx15
		//memory[pc] = 0xf0;
		//memory[pc + 1] = 0x15;

		////test fx18
		//memory[pc] = 0xf1;
		//memory[pc + 1] = 0x18;

		////test fx29
		//memory[pc] = 0xfc;
		//memory[pc + 1] = 0x29;

		//test ff80 ???
		//test e010 ???


		//fetch
		opcode = memory[pc] << 8 | memory[pc + 1];
		std::cout << std::hex << "[OPCODE FETCH]: pc: 0x" << (int)memory[pc] << ". pc + 1: 0x" << (int)memory[pc + 1] << ". opcode: 0x" << opcode << std::endl;

		//decode
		switch (opcode & 0xF000) {
		case 0x0000:
		{
			switch (opcode & 0x00FF) {
			case 0x00E0: // Clear the display. (00E0 - CLS)
			{
				//Clear display
				break;
			}
			case 0x00EE: // Return from a subroutine. (00EE - RET) ready
			{
				pc = stack[sp];
				sp--;

				std::cout << "[OPCODE 0x00EE] pc: 0x" << pc << " | dec: " << std::dec << pc << " | sp: " << sp << std::endl;
				break;
			}
			default:
				std::cerr << "[OPCODE 0x0000]: Cannot find specified opcode: " << opcode << std::endl;
				break;
			}

			break;
		}
		case 0x1000: // Jump to location nnn. (1nnn - JP addr) ready
		{
			pc = opcode & 0x0FFF;
			std::cout << "[OPCODE 0x1000] pc: 0x" << pc << " | dec: " << std::dec << pc << std::endl;
			break;
		}
		case 0x2000: // Call subroutine at nnn. (2nnn - CALL addr) ready
		{
			stack[sp] = pc;
			pc = opcode & 0x0FFF;
			sp++;
			break;
		}
		case 0x3000: // Skip next instruction if Vx = kk. (3xkk - SE Vx, byte)
		{
			int x = opcode & 0x0F00 >> 8;
			int kk = opcode & 0x00FF;

			if (V[x] == kk) {
				pc += 4;
			} else {
				pc += 2;
			}

			break;
		}
		case 0x4000: // Skip next instruction if Vx != kk. (4xkk - SNE Vx, byte)
		{
			int x = opcode & 0x0F00 >> 8;
			int kk = opcode & 0x00FF;

			std::cout << "[OPCODE 0x4000] x: 0x" << x << " | 0x: " << kk << " | Vx: " << V[x] << std::endl;

			if (V[x] != kk) {
				pc += 4;
			} else {
				pc += 2;
			}

			break;
		}
		case 0x5000: // Skip next instruction if Vx = Vy. (5xy0 - SE Vx, Vy)
		{
			int x = (opcode & 0x0F00) >> 8;
			int y = (opcode & 0x00F0) >> 4;

			std::cout << "[OPCODE 0x5000] x: 0x" << x << " | dec: " << std::dec << x << std::endl;
			std::cout << "[OPCODE 0x5000] y: 0x" << y << " | dec: " << std::dec << y << std::endl;

			if (V[x] == V[y]) {
				pc += 4;
			} else {
				pc += 2;
			}

			break;
		}
		case 0x6000: // Set Vx = kk. (6xkk - LD Vx, byte) ready
		{
			int x = (opcode & 0x0F00) >> 8;
			int nn = (opcode & 0x00FF);

			std::cout << "[OPCODE 0x6000] x: 0x" << x << " | dec: " << std::dec << x << std::endl;
			std::cout << "[OPCODE 0x6000] nn: 0x" << nn << " | dec: " << std::dec << nn << std::endl;
			
			V[x] = nn;
			pc += 2;
			break;
		}
		case 0x7000: // Set Vx = Vx + kk. (7xkk - ADD Vx, byte) ready
		{
			int x = (opcode & 0x0F00) >> 8;
			int nn = (opcode & 0x00FF);

			std::cout << "[OPCODE 0x7000] x: 0x" << x << " | dec: " << std::dec << x << std::endl;
			std::cout << "[OPCODE 0x7000] nn: 0x" << nn << " | dec: " << std::dec << nn << std::endl;

			V[x] += nn;
			pc += 2;
			break;
		}
		case 0x8000:
		{
			int x = (opcode & 0x0F00) >> 8;
			int y = (opcode & 0x00F0) >> 4;

			switch (opcode & 0x000F) {
			case 0: // Set Vx = Vy. (8xy0 - LD Vx, Vy)
			{
				V[x] = V[y];

				std::cout << "[OPCODE 0x8000] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 1: // Set Vx = Vx OR Vy. (8xy1 - OR Vx, Vy)
			{
				V[x] = V[x] | V[y];

				std::cout << "[OPCODE 0x8001] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 2: // Set Vx = Vx AND Vy. (8xy2 - AND Vx, Vy)
			{
				V[x] = V[x] & V[y];

				std::cout << "[OPCODE 0x8002] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 3: // Set Vx = Vx XOR Vy. (8xy3 - XOR Vx, Vy)
			{
				V[x] = V[x] ^ V[y];

				std::cout << "[OPCODE 0x8003] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 4: // Set Vx = Vx + Vy, set VF = carry. (8xy4 - ADD Vx, Vy)
			{
				V[x] = V[x] + V[y];
				V[0xF] = V[x] > 0xFF;

				std::cout << "[OPCODE 0x8004] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 5: // Set Vx = Vx - Vy, set VF = NOT borrow. (8xy5 - SUB Vx, Vy)
			{
				V[0xF] = V[x] > V[y];
				V[x] = V[x] - V[y];

				std::cout << "[OPCODE 0x8005] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 6: // Set Vx = Vx SHR 1. (8xy6 - SHR Vx {, Vy})
			{
				V[0xF] = V[x] & 0x1;
				V[x] =V[x] / 2;

				std::cout << "[OPCODE 0x8006] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 7: // Set Vx = Vy - Vx, set VF = NOT borrow. (8xy7 - SUBN Vx, Vy)
			{
				V[0xF] = V[y] > V[x];
				V[x] = V[y] - V[x];

				std::cout << "[OPCODE 0x8007] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			case 0xE: // Set Vx = Vx SHL 1. (8xyE - SHL Vx {, Vy})
			{
				V[0xF] = (V[x] >> 7) & 0x1;
				V[x] = V[x] * 2;

				std::cout << "[OPCODE 0x800E] V[x]: 0x" << V[x] << " | dec: " << std::dec << V[x] << std::endl;

				break;
			}
			default:
				std::cerr << "[OPCODE 0x8000]: Cannot find specified opcode: " << opcode << std::endl;
				break;
			}

			pc += 2;
			break;
		}
		case 0x9000: //Skip next instruction if Vx != Vy. (9xy0 - SNE Vx, Vy)
		{
			int x = (opcode & 0x0F00) >> 8;
			int y = (opcode & 0x00F0) >> 4;

			if (V[x] != V[y]) {
				pc += 2;
			}

			std::cout << "[OPCODE 0xA000] V[x]: 0x" << V[x] << " | V[y]: " << V[y] << std::endl;

			pc += 2;
			break;
		}
		case 0xA000: //The value of register I is set to nnn. (Annn - LD I, addr) ready
		{
			int nnn = (opcode & 0x0FFF);

			std::cout << "[OPCODE 0xA000] nnn: 0x" << nnn << " | dec: " << std::dec << nnn << std::endl;

			I = nnn;
			pc += 2;
			break;
		}
		case 0xB000: //Jump to location nnn + V0. (Bnnn - JP V0, addr)
		{
			int nnn = (opcode & 0x0FFF);

			std::cout << "[OPCODE 0xB000] nnn: 0x" << nnn << " | dec: " << std::dec << nnn << std::endl;

			pc = nnn + V[0];
			break;
		}
		case 0xC000: //Set Vx = random byte AND kk. (Cxkk - RND Vx, byte)
		{
			int x = (opcode & 0x0F00) >> 8;
			int kk = (opcode & 0x00FF);
			int random = rand() % 256;

			std::cout << "[OPCODE 0xC000] x: 0x" << x << " | kk: 0x" << kk << " | random: " << random << std::endl;

			V[x] = random & kk;
			pc += 2;
			break;
		}
		case 0xD000: //Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision. (Dxyn - DRW Vx, Vy, nibble)
		{
			int x = (opcode & 0x0F00) >> 8;
			int y = (opcode & 0x00F0) >> 4;
			int n = (opcode & 0x000F);
			
			//read n-bytes memory
			unsigned char* mem = new unsigned char[n];
			for (int i = 0; i < n; i++) {
				mem[i] = memory[I + i];
			}

			for (int vx = V[x]; vx < V[x] + 8; vx++) {

			}

			//XOR
			V[x] = V[x] ^ V[y];

			pc += 2;
			break;
		}
		case 0xE000: //Set Vx = random byte AND kk. (Cxkk - RND Vx, byte)
		{
			int x = (opcode & 0x0F00) >> 8;
			switch (opcode & 0x000F) {
				case 0xE: // Skip next instruction if key with the value of Vx is pressed. (Ex9E - SKP Vx)
				{
					if (key[V[x]] != 0) {
						pc += 2;
					}
					break;
				}
				case 0x1: // Skip next instruction if key with the value of Vx is not pressed. (ExA1 - SKNP Vx)
				{
					if (key[V[x]] == 0) {
						pc += 2;
					}
					break;
				}
			}

			pc += 2;
			break;
		}
		case 0xF000: // The interpreter puts the value kk into register Vx. (6xkk - LD Vx, byte)
		{
			int x = (opcode & 0x0F00) >> 8;
			int nn = (opcode & 0x00FF);

			std::cout << "[OPCODE 0x6000] x: 0x" << x << " | dec: " << std::dec << x << std::endl;
			std::cout << "[OPCODE 0x6000] nn: 0x" << nn << " | dec: " << std::dec << nn << std::endl;

			V[x] = nn;
			pc += 2;
			break;
		}
		default:
			std::cerr << "[STEP]: Cannot find specified opcode: " << opcode << std::endl;
			break;
		}

		//execute
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
	//program counter
	unsigned short pc;
	//graphics has a total of 64x32 pixels on a screen.
	unsigned char gfx[DISPLAY_WIDTH * DISPLAY_HEIGHT];
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