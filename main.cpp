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
	string pass = pg.generate(input, 10); 
	cout << pass << endl;

	//TODO: Make it work only with specific key
	//Copy to clipboard
	string exec = "echo \"" + pass + "\" | xclip -selection \"clipboard\"";
	system(exec.c_str());
	return 0;
}
