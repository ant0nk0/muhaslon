#include "word_item.h"

namespace MuhaSlon
{


WordItem::WordItem(const std::string& word) 
	: m_Value(word), m_IsUsed()
{
}

void WordItem::SetUsed(bool value)
{
	m_IsUsed = value;
}

bool WordItem::IsUsed() const
{
	return m_IsUsed;
}

void WordItem::AddLink(WordItem::Ptr link)
{
	m_Links.push_back(link);
}

const WordItem::WordLinks& WordItem::Links() const
{
	return m_Links;
}

const std::string& WordItem::Get() const
{
	return m_Value;
}

std::unique_ptr<WordItem> WordItem::Make(const std::string& word)
{
	return std::unique_ptr<WordItem>(new WordItem(word));
}

} // namespace MuhaSlon