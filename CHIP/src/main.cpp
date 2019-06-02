#include "chip.hpp"
#include "window.hpp"
#include "roms.hpp"
#include <string>
#include <streambuf>
#include <filesystem>
#include <iostream>
#include <fstream>

int main()
{
	Chip CHIP8;
	Roms roms;

	Window window;
	window.init();

	CHIP8.initialize();
	roms.Initialize();

	
	
	

	CHIP8.loadGame(roms.GetRomData(2));


	std::cout << "[EMULATOR SIZE]: " << sizeof(CHIP8) << " bytes" << std::endl;
	CHIP8.step();

	while (CHIP8.isRunning && window.isRunning) {
		//emulate a single step of CHIP-8
		//CHIP8.step();
		//draw if neccessary
		window.run();
		//catch user input
		//CHIP8.catchKeys();
	}

	std::cout << "[EMULATOR]: Main loop was finished!" << std::endl;

	window.terminate();
	CHIP8.terminate();
	return 0;
}