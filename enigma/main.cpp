#include <iostream>

#include "Enigma.h"

using namespace std;

int main()
{
	string plainText = "HELLOWORLD";
	Enigma e1{ vector{RotorType::i, RotorType::ii, RotorType::iii}, b, vector{0, 0, 0}, vector{0,0,0}, "" };
	Enigma e2{ vector{RotorType::i, RotorType::ii, RotorType::iii}, b, vector{0, 0, 0}, vector{0,0,0}, "" };
	
	string encrypted = e1.encrypt(plainText);

	cout << "Original Phrase: " << endl;
	cout << plainText << endl;

	cout << "Encrypted: " << endl;
	cout << encrypted << endl;

	string decrypted = e2.encrypt(encrypted);
	cout << "Decrypting encrypted text: " << endl;
	cout << decrypted << endl;
	
}