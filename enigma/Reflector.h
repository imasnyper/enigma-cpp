#pragma once
#include <string>
#include <vector>

enum ReflectorType{a, b, c};

class Reflector
{
public:
	std::vector<int> forwardWiring;

	Reflector()
	{
		this->forwardWiring = decodeWiring("ZYXWVUTSRQPONMLKJIHGFEDCBA");
	}
	
	Reflector(std::string encoding)
	{
		this->forwardWiring = decodeWiring(encoding);
	}

	static Reflector Create(ReflectorType name)
	{
		switch(name)
		{
		case b:
			return Reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT");
		case c:
			return Reflector("FVPJIAOYEDRZXWGCTKUQSBNMHL");
		default:
			return Reflector();
		}
	}

	int forward(int c)
	{
		return this->forwardWiring.at(c);
	}

protected:
	static std::vector<int> decodeWiring(std::string encoding)
	{
		std::vector<char> charWiring{ encoding.begin(), encoding.end() };
		std::vector<int> wiring;

		for (auto ch : charWiring)
			wiring.push_back(ch - 65);

		return wiring;
	}
};