#pragma once
#include <memory>
#include <list>

namespace MuhaSlon
{

//! interface for Configuration
class IConfiguration
{
public:
	typedef std::shared_ptr<IConfiguration> Ptr;
	typedef std::shared_ptr<std::string> StringPtr;
	typedef std::list<std::string> Vocabulary;
	typedef std::shared_ptr<Vocabulary> VocabularyPtr;

public:
	virtual StringPtr GetStartWord() = 0;
	virtual StringPtr GetEndWord() = 0;
	virtual VocabularyPtr GetVocabulary() = 0;
};

} // namespace MuhaSlon