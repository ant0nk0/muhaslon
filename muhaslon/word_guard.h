#pragma once

#include "word_item.h"
#include "types.h"

namespace MuhaSlon
{

class WordGuard
{
public:
	WordGuard(WordItem::Ptr item, Types::WordsPath& path);
	~WordGuard();

private:
	WordItem::Ptr m_Item;
	Types::WordsPath& m_Path;
};
	
} // namespace MuhaSlon