#pragma once

#include "iconfiguration.h"
#include "types.h"
#include "non_copyable.h"
#include <unordered_map>
#include <string>

namespace MuhaSlon
{

//! Muha-Slon game solver
class Solver : NonCopyable
{
public:
	Solver(IConfiguration::Ptr configuration);
	~Solver();

public:
	Types::Solution Run();

private:
	bool IsBestPath(const Types::WordsPath& path);
	void Visit(WordItem::Ptr item);

private:
	IConfiguration::Ptr m_Configuration;
	std::unordered_map<std::string, std::unique_ptr<WordItem>> m_AllWords;
	Types::WordsPath m_Path;
	Types::WordsPath m_BestPath;
	WordItem::Ptr m_StartWordItem;
};

} // namespace MuhaSlon
