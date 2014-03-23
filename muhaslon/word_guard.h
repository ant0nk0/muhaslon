#pragma once

#include "word_item.h"
#include "types.h"
#include "non_copyable.h"

namespace MuhaSlon
{

//! Make word used at begin and not used at and. Guard idiom
class WordGuard : NonCopyable
{
public:
	WordGuard(WordItem::Ptr item, Types::WordsPath& path);
	~WordGuard();

private:
	WordItem::Ptr m_Item;
	Types::WordsPath& m_Path;
};
	
} // namespace MuhaSlon