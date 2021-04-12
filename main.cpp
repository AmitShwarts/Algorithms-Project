#include "program.h"

void killProgram();
int main(int argc, char **argv)
{
	// init
	set_terminate(killProgram);
	
	if(argc < 3)
	{
		throw std::invalid_argument("Not enough arguments");
	}
	
	// execute program
	std::string inputFileName = argv[1], outputFileName = argv[2];
	executeProgram(inputFileName, outputFileName);
	
	return 0;
}
void killProgram()
{
	
	std::cout << std::endl << "Invalid input" << std::endl;
	exit(1);
}

