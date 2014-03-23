#include "solver.h"
#include "configuration.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	//startWord = "KOT";
	//endWord = "TOT";

	//// TODO check length startWord && endWord

	//vocabulary.push_back("KOT");
	//vocabulary.push_back("TOH");
	//vocabulary.push_back("HOTA");
	//vocabulary.push_back("KOTS");
	//vocabulary.push_back("POT");
	//vocabulary.push_back("POTA");
	//vocabulary.push_back("TOT");
	//vocabulary.push_back("POB");


	//// check startWordItem != nullptr

	//Visit(startWordItem);

	//// GOT IT

	setlocale(LC_ALL, "");

	if (argc < 3)
	{
		std::cout << "Too small number of arguments" << std::endl;
		return 1;
	}

	try
	{
		auto configuration = std::make_shared<MuhaSlon::Configuration>(argv[1], argv[2]);

		MuhaSlon::Solver solver(configuration);
	
		auto bestPath = solver.Run();

		for (auto const& pathItem : bestPath)
			std::cout << pathItem->Get() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	return 0;
}

