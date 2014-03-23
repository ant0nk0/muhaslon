#pragma once

#include "iconfiguration.h"
#include <memory>

namespace MuhaSlon
{

class Configuration : public IConfiguration
{
public:
	typedef std::shared_ptr<Configuration> Ptr;

public:
	Configuration(const std::string& stardEndWordsPath, const std::string& vocabularyPath);
	~Configuration();

public:
	// implementation of IConfiguration
	virtual void Initialize() override;
	virtual StringPtr GetStartWord() override;
	virtual StringPtr GetEndWord() override;
	virtual VocabularyPtr GetVocabulary() override;

protected:
	void ReadStartEndWords(std::istream& stream);
	void ReadVocabulary(std::istream& stream);

private:
	StringPtr m_StartWord;
	StringPtr m_EndWord;
	VocabularyPtr m_Vocabulary;
	std::string m_StartEndWordPath;
	std::string m_VocabularyPath;
};

} // namespace MuhaSlon