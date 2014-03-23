#include "configuration.h"
#include <fstream>
#include <string>

namespace MuhaSlon
{

Configuration::Configuration(const std::string& stardEndWordsPath, const std::string& vocabularyPath) 
	: m_StartWord(std::make_shared<StringPtr::element_type>())
	, m_EndWord(std::make_shared<StringPtr::element_type>())
	, m_Vocabulary(std::make_shared<VocabularyPtr::element_type>())
	, m_StartEndWordPath(stardEndWordsPath)
	, m_VocabularyPath(vocabularyPath)
{
}

Configuration::~Configuration()
{
}

void Configuration::Initialize()
{
	{
		std::ifstream file;
		file.open(m_StartEndWordPath);
		if (file.bad())
			throw std::invalid_argument(std::string("Failed to open start/end file: " + m_StartEndWordPath).c_str());

		ReadStartEndWords(file);
		file.close();
	}

	{
		std::ifstream file;
		file.open(m_VocabularyPath);

		if (file.bad())
			throw std::invalid_argument(std::string("Failed to open vocabulary file: " + m_VocabularyPath).c_str());

		ReadVocabulary(file);
		file.close();
	}
}

void Configuration::ReadStartEndWords(std::istream& stream)
{
	if (stream.eof())
		throw std::runtime_error("Failed to read start word");

	std::getline(stream, *m_StartWord);
	if (m_StartWord->empty())
		throw std::runtime_error("Start word can't be empty");

	if (stream.eof())
		throw std::runtime_error("Failed to read end word");

	std::getline(stream, *m_EndWord);

	if (m_EndWord->empty())
		throw std::runtime_error("End word can't be empty");
}

void Configuration::ReadVocabulary(std::istream& stream)
{
	while (!stream.eof())
	{
		std::string line;
		std::getline(stream, line);
		m_Vocabulary->emplace_back(line);
	}
}

IConfiguration::VocabularyPtr Configuration::GetVocabulary()
{
	return m_Vocabulary;
}

IConfiguration::StringPtr Configuration::GetEndWord()
{
	return m_EndWord;
}

IConfiguration::StringPtr Configuration::GetStartWord()
{
	return m_StartWord;
}

} // namespace MuhaSlon