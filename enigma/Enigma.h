#pragma once
#include "Rotor.h"
#include "Plugboard.h"
#include "Reflector.h"

class Enigma
{
public:
	Rotor leftRotor;
	Rotor middleRotor;
	Rotor rightRotor;

	Reflector reflector;

	Plugboard plugboard;


	Enigma(std::vector<RotorType> rotors, ReflectorType reflector, std::vector<int> rotorPositions, std::vector<int> ringSettings, std::string plugboardConnections)
	{
		this->leftRotor = Rotor::Create(rotors.at(0), rotorPositions.at(0), ringSettings.at(0));
		this->middleRotor = Rotor::Create(rotors.at(1), rotorPositions.at(1), ringSettings.at(1));
		this->rightRotor = Rotor::Create(rotors.at(2), rotorPositions.at(2), ringSettings.at(2));
		this->reflector = Reflector::Create(reflector);
		this->plugboard = Plugboard(plugboardConnections);
	}

	// Enigma(EnigmaKey key) { Enigma(key.rotors, b, key.indicators, key.rings, key.plugboard); }

	void rotate()
	{
		if (middleRotor.isAtNotch())
		{
			middleRotor.turnover();
			leftRotor.turnover();
		}
		else if (rightRotor.isAtNotch())
			middleRotor.turnover();

		rightRotor.turnover();
	}

	int encrypt(int c)
	{
		rotate();

		c = this->plugboard.forward(c);

		int c1 = rightRotor.forward(c);
		int c2 = middleRotor.forward(c1);
		int c3 = leftRotor.forward(c2);

		int c4 = reflector.forward(c3);

		int c5 = leftRotor.backward(c4);
		int c6 = middleRotor.backward(c5);
		int c7 = rightRotor.backward(c6);

		c7 = plugboard.forward(c7);

		return c7;
	}

	char encrypt(char c) { return static_cast<char>(encrypt(c - 65) + 65); }

	std::vector<char> encrypt(std::vector<char> input)
	{
		std::vector<char> output;
		for (int i = 0; i < input.size(); ++i)
		{
			output.push_back(encrypt(input.at(i)));
		}

		return output;
	}

	std::string encrypt(std::string input)
	{
		std::string output;
		for (auto ch : input)
		{
			output += encrypt(ch);
		}
		return output;
	}
};