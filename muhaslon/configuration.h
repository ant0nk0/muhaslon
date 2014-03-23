#pragma once

#include "iconfiguration.h"
#include "non_copyable.h"
#include <memory>

namespace MuhaSlon
{

//! Configures Start word, End word and the vocabulary
class Configuration : public IConfiguration, NonCopyable
{
public:
	typedef std::shared_ptr<Configuration> Ptr;

public:
	Configuration(const std::string& stardEndWordsPath, const std::string& vocabularyPath);
	~Configuration();

public:
	virtual void Initialize();

	// implementation of IConfiguration
	virtual StringPtr GetStartWord() override;
	virtual StringPtr GetEndWord() override;
	virtual VocabularyPtr GetVocabulary() override;

protected:
	// protected for testing
	void ReadStartEndWords(std::istream& stream);
	void ReadVocabulary(std::istream& stream);
	void SetInitialized();

private:
	void CheckInitialized() const;

private:
	StringPtr m_StartWord;
	StringPtr m_EndWord;
	VocabularyPtr m_Vocabulary;
	std::string m_StartEndWordPath;
	std::string m_VocabularyPath;
	bool m_Initialized;
};

} // namespace MuhaSlon