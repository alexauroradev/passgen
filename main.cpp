#include <iostream>
#include <cstdlib>
#include "passgen.h"
using namespace std;

const string initFilename = "init";

int main(int argc, char *argv[])
{
	string input;
	if (argc == 2)
		input = string(argv[1]);
	else {
		cout << "Usage: " << argv[0] << " <pass_phrase>" << endl;
		exit(1);
	}
	PASSGEN pg;
	pg.init(initFilename);
	cout << pg.generate(input, 10) << endl;
	return 0;
}
