#pragma once

#include "non_copyable.h"
#include <list>
#include <memory>

namespace MuhaSlon
{

//! Word Graph element
class WordItem : NonCopyable
{
public:
	typedef WordItem* Ptr;
	typedef std::list<Ptr> WordLinks;

public:
	//! The only one object maker
	static std::unique_ptr<WordItem> Make(const std::string& word);

public:
	//! Get value (the word)
	const std::string& Get() const;

	//! Get Links to near words
	const WordLinks& Links() const;

	//! Add link to near word
	void AddLink(WordItem::Ptr link);

	//! Returns is this item already used in path of words
	bool IsUsed() const;

	//! Set this word used or not used in path of words
	void SetUsed(bool value);

private:
	//! Can be constructed only via Make() method
	WordItem(const std::string& word);

private:
	std::string m_Value;
	WordLinks m_Links;
	bool m_IsUsed;
};

} // namespace MuhaSlon