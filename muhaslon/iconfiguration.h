#pragma once
#include <memory>
#include <list>

namespace MuhaSlon
{

class IConfiguration
{
public:
	typedef std::shared_ptr<IConfiguration> Ptr;
	typedef std::shared_ptr<std::string> StringPtr;
	typedef std::list<std::string> Vocabulary;
	typedef std::shared_ptr<Vocabulary> VocabularyPtr;

public:
	virtual void Initialize() = 0;
	virtual StringPtr GetStartWord() = 0;
	virtual StringPtr GetEndWord() = 0;
	virtual VocabularyPtr GetVocabulary() = 0;
};

} // namespace MuhaSlon