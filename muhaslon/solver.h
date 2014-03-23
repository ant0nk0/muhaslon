#pragma once

#include "iconfiguration.h"
#include "types.h"
#include <unordered_map>
#include <string>

namespace MuhaSlon
{

class Solver
{
public:

	Solver(IConfiguration::Ptr configuration);

	bool IsBestPath(const Types::WordsPath& path);

	void Visit(WordItem::Ptr item);

	Types::Solution Run();

private:
	IConfiguration::Ptr  m_Configuration;
	std::unordered_map<std::string, std::unique_ptr<WordItem>> m_AllWords;
	Types::WordsPath m_Path;
	Types::WordsPath m_BestPath;
	WordItem::Ptr m_StartWordItem;
};

} // namespace MuhaSlon
