#pragma once
#include <set>
#include <sstream>
#include <vector>
#include <string>

class Plugboard
{
private:
	std::vector<int> wiring;



public:
	Plugboard()
	{
		this->wiring = decodePlugboard("");
	}
	
	Plugboard(std::string connections)
	{
		this->wiring = decodePlugboard(connections);
	}

	static std::vector<int> identityPlugboard()
	{
		std::vector<int> mapping;
		for (int i = 0; i < 26; ++i)
		{
			mapping.push_back(i);
		}
		return mapping;
	}

	int forward(int c)
	{
		return this->wiring.at(c);
	}

	static std::set<int> getUnpluggedCharacters(std::string plugboard)
	{
		std::set<int> unpluggedCharacters;

		for (int i = 0; i < 26; ++i)
			unpluggedCharacters.insert(i);

		if (plugboard == "")
			return unpluggedCharacters;

		std::istringstream plugStream(plugboard);
		std::vector<std::string> pairings{ std::istream_iterator<std::string>{plugStream}, std::istream_iterator<std::string>{} };

		for (auto pairing : pairings)
		{
			int c1 = pairing.at(0) - 65;
			int c2 = pairing.at(1) - 65;

			unpluggedCharacters.erase(c1);
			unpluggedCharacters.erase(c2);
		}

		return unpluggedCharacters;
	}

	static std::vector<int> decodePlugboard(std::string plugboard)
	{
		if (plugboard == "")
			return identityPlugboard();

		std::istringstream plugStream(plugboard);
		std::vector<std::string> pairings{ std::istream_iterator<std::string>{plugStream}, std::istream_iterator<std::string>{} };
		std::set<int> pluggedCharacters;
		std::vector<int> mapping = identityPlugboard();

		for (auto pairing : pairings)
		{
			if (pairing.size() != 2)
				return identityPlugboard();

			int c1 = pairing.at(0) - 65;
			int c2 = pairing.at(1) - 65;

			if (pluggedCharacters.find(c1) != pluggedCharacters.end() || pluggedCharacters.find(c2) != pluggedCharacters.end())
				return identityPlugboard();

			pluggedCharacters.insert(c1);
			pluggedCharacters.insert(c2);

			mapping.at(c1) = c2;
			mapping.at(c2) = c1;
		}

		return mapping;
	}
};