#include <iostream>
#include <cstdlib>
#include <sstream>
#include "passgen.h"
using namespace std;

std::string exec(const char* cmd);
std::string paste();
std::string copy(const char * new_clipboard);

const string initFilename = "init";

int main(int argc, char *argv[]) {
		string input;
		if (argc == 2)
				input = string(argv[1]);
		else {				cout << "Usage: " << argv[0] << " <pass_phrase>" << endl;
				exit(1);
		}
		PASSGEN pg;
		pg.init(initFilename);
		string pass = pg.generate(input, 10); 
		cout << pass << endl;

		//TODO: Make it work only with specific key
		//Copy to clipboard
		//string exec = "echo \"" + pass + "\" | xclip -selection \"clipboard\"";
		//system(exec.c_str());
		copy(pass.c_str());
		return 0;
}

std::string exec(const char* cmd) {
		FILE* pipe = popen(cmd, "r");
		if (!pipe) return "ERROR";
		char buffer[128];
		std::string result = "";
		while(!feof(pipe)) {
				if(fgets(buffer, 128, pipe) != NULL)
				{
						result += buffer;
				}
		}
		pclose(pipe);
		return result;
}

std::string paste()
{
		return exec("pbpaste");
}

std::string copy(const char * new_clipboard)
{
		std::stringstream cmd;
		cmd << "echo \"" << new_clipboard << "\" | pbcopy";
		return exec(cmd.str().c_str());
}
