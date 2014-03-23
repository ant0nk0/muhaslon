#include "solver.h"
#include "configuration.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");

	if (argc < 3)
	{
		std::cout << "Too small number of arguments" << std::endl;
		return 1;
	}

	try
	{
		auto configuration = std::make_shared<MuhaSlon::Configuration>(argv[1], argv[2]);
		configuration->Initialize();

		MuhaSlon::Solver solver(configuration);
	
		auto bestPath = solver.Run();

		for (auto const& pathItem : bestPath)
			std::cout << pathItem << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}

