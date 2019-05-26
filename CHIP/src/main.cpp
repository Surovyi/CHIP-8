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

	
	std::cout << "\n[ROMS COUNT]: " << roms.GetRomsCount() << " roms found!" << std::endl;
	

	//CHIP8.loadGame(gameStr);


	std::cout << "[EMULATOR SIZE]: " << sizeof(CHIP8) << " bytes" << std::endl;

	while (CHIP8.isRunning && window.isRunning) {
		window.run();
	}

	window.terminate();
	CHIP8.terminate();
	return 0;
}