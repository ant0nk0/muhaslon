#include "solver.h"
#include "configuration.h"
#include "near_words.h"
#include "word_guard.h"
#include <string>

namespace MuhaSlon
{

Solver::Solver(IConfiguration::Ptr configuration) : m_Configuration(configuration)
{
	if (m_Configuration->GetStartWord()->size() !=
		m_Configuration->GetEndWord()->size())
	{
		throw std::runtime_error("Start/end words differs by length");
	}

	auto const expectedWordSize = m_Configuration->GetStartWord()->size();
	WordItem::Ptr startWordItem = nullptr;
	WordItem::Ptr endWordItem = nullptr;

	for (auto const& word : *m_Configuration->GetVocabulary())
	{
		if (word.size() != expectedWordSize)
			continue;

		auto newItem = WordItem::Make(word);

		if (word == *m_Configuration->GetStartWord())
			startWordItem = m_StartWordItem = newItem.get();
		else if (word == *m_Configuration->GetEndWord())
			endWordItem = newItem.get();

		for (auto& item : m_AllWords)
			if (Helpers::CheckWordsAreNear(newItem->Get(), item->Get()))
			{
				newItem->AddLink(item.get());
				item->AddLink(newItem.get());
			}

			m_AllWords.push_back(std::move(newItem));
	}

	if (startWordItem == nullptr)
		throw std::runtime_error("Failed to find Start word in the vocabulary");

	if (endWordItem == nullptr)
		throw std::runtime_error("Failed to find End word in the vocabulary");
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

Types::WordsPath Solver::Run()
{
	Visit(m_StartWordItem);
	return m_BestPath;
}

} // namespace MuhaSlon