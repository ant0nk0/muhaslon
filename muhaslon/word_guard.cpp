#include "word_guard.h"

namespace MuhaSlon
{

WordGuard::WordGuard(WordItem::Ptr item, Types::WordsPath& path) 
	: m_Item(item), m_Path(path)
{
	if (m_Item)
		m_Item->SetUsed(true);

	m_Path.push_back(item);
}

WordGuard::~WordGuard()
{
	if (m_Item)
		m_Item->SetUsed(false);

	m_Path.pop_back();
}

} // namespace MuhaSlon