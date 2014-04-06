#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "passgen.h"


const std::string PASSGEN::LETTERS("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
const std::string PASSGEN::LETTERS_NUMBERS("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
const std::string PASSGEN::LETTERS_NUMBERS_MARKS("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-_=+");

void PASSGEN::init(std::string filename){
	std::ifstream initfile;
	initfile.open(filename.c_str());
	initfile >>  alphabetType;
	switch (alphabetType) {
		case 1:
			alphabet = PASSGEN::LETTERS;
			break;
		case 2:
			alphabet = PASSGEN::LETTERS_NUMBERS;
			break;
		case 3:
			alphabet = PASSGEN::LETTERS_NUMBERS_MARKS;
			break;
		default:
			std::cout << "The alphabet type is not implemented." << std::endl;
			exit(1);
			break;
	}
	initfile >> seed;
	depth = 0;
}

std::string PASSGEN::generate(std::string message, int passLength){
	depth++;
	if (depth > PASSGEN::MAX_DEPTH){
		std::cout << "Exceeded " << MAX_DEPTH << " recursion steps. Exiting..." << std::endl;
		exit(1);
	}

	std::string longMessage = message + seed;
	unsigned char *hash;
	std::string pass = "";

	int j = 0; // position in hash array
	int n = 0; // number of sha256 hashe generations
	for (int i = 0; i < passLength; i++){
		if (j == 0)
			sha256(longMessage + char(32 + n++), &hash);
		unsigned int d = int(hash[j]) * 256 + int(hash[j + 1]); //d = 0..65535
		char symbol = alphabet[d % alphabet.length()];
		pass += symbol;
		j = (j + 2) % 32;
	}

	if (checkPass(pass)){
		depth = 0;
		return pass;
	} else {
		return (generate(message + " ", passLength));
	}
}

bool PASSGEN::checkPass(std::string pass){
	if (alphabetType == 1) //Letters. No check performed
		return true;
	if (alphabetType == 2){ //Letters & numbers. Minimum 3 letters and 3 numbers.
		int nNumber = 0;
		int nLetter = 0;
		for (int i = 0; i < pass.length(); i++)
			if ((int(pass[i]) < 58) && (int(pass[i]) > 47))
				nNumber++;
			else
				nLetter++;
		return ((nNumber > 2) && (nLetter > 2));
	}
	if (alphabetType == 3){ //Letters & numbers & marks. Minimum 3 letters, 3 numbers and 1 mark.
		int nNumber = 0;
		int nLetter = 0;
		int nMark = 0;
		for (int i = 0; i < pass.length(); i++){
			if ((int(pass[i]) < 58) && (int(pass[i]) > 47))
				nNumber++;
			else if ( ((int(pass[i]) < 91) && (int(pass[i]) > 64)) || ((int(pass[i]) < 123) && (int(pass[i]) > 96)) )
				nLetter++;
			else
				nMark++;
		}
		return ((nNumber > 2) && (nLetter > 2) && (nMark > 0));
	}
	std::cout << "Not implemented pass check procedure for this alphabet" << std::endl;
	exit(1);
	return true;
}
