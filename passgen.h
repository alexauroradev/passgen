#ifndef PASSGEN_H
#define PASSGEN_H
#include "sha256.h"

class PASSGEN
{
	public:
		void init(std::string filename);
		std::string generate(std::string message, int passLength = 10);
	protected:
		std::string alphabet;
		int alphabetType;
		int depth;
		std::string seed;
		const static std::string LETTERS;
		const static std::string LETTERS_NUMBERS;
		const static std::string LETTERS_NUMBERS_MARKS;
		const static int MAX_DEPTH = 500;
		bool checkPass(std::string pass);
};

#endif // PASSGEN_H
