import <iostream>;
import <string>;
#ifdef _WIN32
#include <Windows.h>
#endif

import BrainFuck;

int main(int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
	if (argc != 2) {
		std::cout << "Please input 1 filename in your terminal!";
		return -1;
	}
	BrainFuck brainfuck(argv[1]);
	brainfuck.compile();
	return 0;
}