#include "chip.hpp"
#include "window.hpp"
#include <string>
#include <streambuf>
#include <filesystem>
#include <iostream>
#include <fstream>

int main()
{
	Chip CHIP8;

	Window window;
	window.init();

	CHIP8.initialize();
	
	//get all roms in a directory
	std::string path = "roms";
	std::vector<std::string> roms;
	for (auto& p : std::filesystem::directory_iterator(path)) {
		roms.push_back(p.path().string());
		std::cout << p.path() << '\n';
	}

	std::ifstream game;
	game.open(roms[0], std::ios::binary);
	if (game.is_open() == false) {
		std::cerr << "Failed to open rom: " << roms[0] << std::endl;
		return 0;
	}

	std::string gameStr;
	game.seekg(0, std::ios::end);
	gameStr.reserve(game.tellg());
	game.seekg(0, std::ios::beg);
	gameStr.assign((std::istreambuf_iterator<char>(game)), std::istreambuf_iterator<char>());

	std::cout << "[ROM]: " << gameStr << std::endl;

	CHIP8.loadGame(gameStr);


	std::cout << sizeof(CHIP8) << " bytes" << std::endl;
	std::cin.get();

	window.terminate();
	return 0;
}