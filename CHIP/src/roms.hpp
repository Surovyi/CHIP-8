#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

class Roms
{
public:

	//get all roms in a directory
	void Initialize()
	{
		std::string path = "roms";
		for (auto& p : std::filesystem::directory_iterator(path)) {
			m_roms.push_back(p.path().string());
			std::cout << "[ROM FOUND]: " << p.path() << '\n';
		}
		m_romsCount = m_roms.size();

		std::cout << "\n[ROMS COUNT]: " << m_romsCount << " roms found!" << std::endl;
	}

	std::vector<std::string> GetRomsList()
	{
		return m_roms;
	}

	size_t GetRomsCount()
	{
		return m_romsCount;
	}

	std::string GetRomData(unsigned int romIndex)
	{
		if (romIndex >= m_romsCount) {
			std::cerr << "Failed to open rom with index [" << romIndex << "]. Index is greater than expected!" << std::endl;
			return nullptr;
		}

		std::ifstream romStream;
		std::string rom;

		romStream.open(m_roms[romIndex], std::ios::binary);
		if (romStream.is_open() == false) {
			std::cerr << "Failed to open rom with index [" << romIndex << "]" << std::endl;
			return nullptr;
		}

		romStream.seekg(0, std::ios::end);
		rom.reserve(romStream.tellg());
		romStream.seekg(0, std::ios::beg);
		rom.assign((std::istreambuf_iterator<char>(romStream)), std::istreambuf_iterator<char>());

		std::cout << "[ROM DATA]: " << rom << std::endl;
		return rom;
	}

private:
	std::vector<std::string> m_roms;
	size_t m_romsCount;
};