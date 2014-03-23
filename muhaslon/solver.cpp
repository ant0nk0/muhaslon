#include "solver.h"
#include "configuration.h"
#include "near_words_checker.h"
#include "word_guard.h"
#include "configuration_validator.h"
#include <string>

namespace MuhaSlon
{

Solver::Solver(IConfiguration::Ptr configuration) : m_Configuration(configuration)
{
	ConfigurationValidator::Check(configuration);

	auto const expectedWordSize = m_Configuration->GetStartWord()->size();

	for (auto const& word : *m_Configuration->GetVocabulary())
	{
		if (word.size() != expectedWordSize)
			continue;

		if (m_AllWords.find(word) != m_AllWords.end())
			continue;

		auto newItem = WordItem::Make(word);

		if (word == *m_Configuration->GetStartWord())
			m_StartWordItem = newItem.get();

		for (auto& word : m_AllWords)
		{
			auto& item = word.second;

			if (Helpers::CheckWordsAreNear(newItem->Get(), item->Get()))
			{
				newItem->AddLink(item.get());
				item->AddLink(newItem.get());
			}
		}

		m_AllWords.emplace(word, std::move(newItem));
	}
}

Solver::~Solver()
{
}

bool Solver::IsBestPath(const Types::WordsPath& path)
{
	return m_BestPath.empty() || path.size() < m_BestPath.size();
}

void Solver::Visit(WordItem::Ptr item)
{
	if (!item || item->IsUsed())
		return;

	WordGuard used(item, m_Path);

	if (item->Get() == *m_Configuration->GetEndWord() && IsBestPath(m_Path))
		m_BestPath = m_Path;

	for (auto child : item->Links())
		Visit(child);
}

Types::Solution Solver::Run()
{
	Visit(m_StartWordItem);

	Types::Solution solution;

	for (auto item : m_BestPath)
		solution.push_back(item->Get());

	return solution;
}

} // namespace MuhaSlon