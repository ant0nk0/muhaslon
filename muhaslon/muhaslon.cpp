#include "solver.h"
#include "configuration.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");

	if (argc < 3)
	{
		std::cout << "Too small number of arguments." << std::endl;
		std::cout << "Usage: muhaslon <start/end word file path> <vocabulary file path>" << std::endl;
		return 1;
	}

	try
	{
		auto configuration = std::make_shared<MuhaSlon::Configuration>(argv[1], argv[2]);
		configuration->Initialize();

		auto solution = MuhaSlon::Solver(configuration).Run();;

		for (auto const& word : solution)
			std::cout << word << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}

