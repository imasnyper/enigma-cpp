#pragma once
#include <vector>
#include <string>

#include "Reflector.h"

enum class RotorType{i, ii, iii, iv, v, vi, vii, viii, z};

class Rotor
{
protected:
	RotorType name;
	std::vector<int> forwardWiring;
	std::vector<int> backwardWiring;

	int rotorPosition;
	int notchPosition;
	int ringSetting;

	bool twoNotch;

public:
	Rotor()
	{
		this->name = RotorType::z;
		this->forwardWiring = decodeWiring("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		this->backwardWiring = inverseWiring(this->forwardWiring);
		this->rotorPosition = 0;
		this->notchPosition = 0;
		this->ringSetting = 0;
		this->twoNotch = false;
	}
	
	Rotor(RotorType name, std::string encoding, int rotorPosition, int notchPosition, int ringSetting)
	{
		this->name = name;
		this->forwardWiring = decodeWiring(encoding);
		this->backwardWiring = inverseWiring(this->forwardWiring);
		this->rotorPosition = rotorPosition;
		this->notchPosition = notchPosition;
		this->ringSetting = ringSetting;
		this->twoNotch = false;
	}

	Rotor(RotorType name, std::string encoding, int rotorPosition, int notchPosition, int ringSetting, bool twoNotch)
	{
		this->name = name;
		this->forwardWiring = decodeWiring(encoding);
		this->backwardWiring = inverseWiring(this->forwardWiring);
		this->rotorPosition = rotorPosition;
		this->notchPosition = notchPosition;
		this->ringSetting = ringSetting;
		this->twoNotch = twoNotch;
	}

	static Rotor Create(RotorType name, int rotorPosition, int ringSetting)
	{
		switch (name)
		{
		case RotorType::i:
			return Rotor(RotorType::i, "EKMFLGDQVZNTOWYHXUSPAIBRCJ", rotorPosition, 16, ringSetting);
		case RotorType::ii:
			return Rotor(RotorType::ii, "AJDKSIRUXBLHWTMCQGZNPYFVOE", rotorPosition, 4, ringSetting);
		case RotorType::iii:
			return Rotor(RotorType::iii, "BDFHJLCPRTXVZNYEIWGAKMUSQO", rotorPosition, 21, ringSetting);
		case RotorType::iv:
			return Rotor(RotorType::iv, "ESOVPZJAYQUIRHXLNFTGKDCMWB", rotorPosition, 9, ringSetting);
		case RotorType::v:
			return Rotor(RotorType::v, "VZBRGITYUPSDNHLXAWMJQOFECK", rotorPosition, 25, ringSetting);
		case RotorType::vi:
			return Rotor(RotorType::vi, "JPGVOUMFYQBENHZRDKASXLICTW", rotorPosition, 0, ringSetting, true);
		case RotorType::vii:
			return Rotor(RotorType::vii, "NZJHGRCXMYSWBOUFAIVLPEKQDT", rotorPosition, 0, ringSetting, true);
		case RotorType::viii:
			return Rotor(RotorType::viii, "FKQHTLXOCBJSPDZRAMEWNIUYGV", rotorPosition, 0, ringSetting, true);
		default:
			return Rotor(RotorType::z, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", rotorPosition, 0, ringSetting);
		}
	}

	RotorType getName() { return name; }

	int getPosition() { return rotorPosition; }

	int forward(int c)
	{
		return encipher(c, this->rotorPosition, this->ringSetting, this->forwardWiring);
	}

	int backward(int c)
	{
		return encipher(c, this->rotorPosition, this->ringSetting, this->backwardWiring);
	}

	bool isAtNotch()
	{
		if (!this->twoNotch)
			return this->notchPosition == this->rotorPosition;
		
		return this->rotorPosition == 12 || this->rotorPosition == 25;
	}

	void turnover()
	{
		this->rotorPosition = (this->rotorPosition + 1) % 26;
	}

protected:
	static std::vector<int> decodeWiring(std::string encoding)
	{
		std::vector<char> charWiring(encoding.begin(), encoding.end());
		std::vector<int> wiring;
		for (auto ch : charWiring)
			wiring.push_back(ch - 65);

		return wiring;
	}

	static std::vector<int> inverseWiring(std::vector<int> wiring)
	{
		std::vector<int> inverse(wiring.size());
		for (int i = 0; i < wiring.size(); i++)
		{
			int forward = wiring.at(i);
			inverse.at(forward) = i;
		}
		return inverse;
	}

	static int encipher(int k, int pos, int ring, std::vector<int> mapping)
	{
		int shift = pos - ring;
		return (mapping.at((k + shift + 26) % 26) - shift + 26) % 26;
	}

	
};

class TwoNotchRotor : public Rotor
{
public:
	TwoNotchRotor(RotorType name, std::string encoding, int rotorPosition, int notchPosition, int ringSetting)
		: Rotor(name, encoding, rotorPosition, notchPosition, ringSetting)
	{
		
	}
	
	bool isAtNotch() { return this->rotorPosition == 12 || this->rotorPosition == 25; }
};