#pragma once

#include <list>
#include <memory>

namespace MuhaSlon
{

class WordItem
{
public:
	typedef WordItem* Ptr;
	typedef std::list<Ptr> WordLinks;

public:
	static std::unique_ptr<WordItem> Make(const std::string& word);

public:
	const std::string& Get() const;
	const WordLinks& Links() const;
	void AddLink(WordItem::Ptr link);
	bool IsUsed() const;
	void SetUsed(bool value);

private:
	WordItem(const std::string& word);

private:
	std::string m_Value;
	WordLinks m_Links;
	bool m_IsUsed;
};

} // namespace MuhaSlon