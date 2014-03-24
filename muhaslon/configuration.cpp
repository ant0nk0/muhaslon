#include "configuration.h"
#include <fstream>
#include <string>
#include <sstream>

namespace MuhaSlon
{

Configuration::Configuration(const std::string& stardEndWordsPath, const std::string& vocabularyPath) 
	: m_StartWord(std::make_shared<StringPtr::element_type>())
	, m_EndWord(std::make_shared<StringPtr::element_type>())
	, m_Vocabulary(std::make_shared<VocabularyPtr::element_type>())
	, m_StartEndWordPath(stardEndWordsPath)
	, m_VocabularyPath(vocabularyPath)
	, m_Initialized(false)
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

		if (!file.is_open())
		{
			std::stringstream ss;
			ss << "Failed to open start/end file: " << m_StartEndWordPath;
			throw std::invalid_argument(ss.str().c_str());
		}

		ReadStartEndWords(file);
		file.close();
	}

	{
		std::ifstream file;
		file.open(m_VocabularyPath);

		if (!file.is_open())
		{
			std::stringstream ss;
			ss << "Failed to open vocabulary file: " << m_VocabularyPath;
			throw std::invalid_argument(ss.str().c_str());
		}

		ReadVocabulary(file);
		file.close();
	}

	SetInitialized();
}

void Configuration::ReadStartEndWords(std::istream& stream)
{
	if (stream.eof())
		throw std::runtime_error("Failed to read start word");

	std::getline(stream, *m_StartWord);

	if (stream.eof())
		throw std::runtime_error("Failed to read end word");

	std::getline(stream, *m_EndWord);
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
	CheckInitialized();
	return m_Vocabulary;
}

IConfiguration::StringPtr Configuration::GetEndWord()
{
	CheckInitialized();
	return m_EndWord;
}

IConfiguration::StringPtr Configuration::GetStartWord()
{
	CheckInitialized();
	return m_StartWord;
}

void Configuration::CheckInitialized() const
{
	if (!m_Initialized)
		throw std::runtime_error("Configuration was not properly initialized");
}

void Configuration::SetInitialized()
{
	m_Initialized = true;
}

} // namespace MuhaSlon