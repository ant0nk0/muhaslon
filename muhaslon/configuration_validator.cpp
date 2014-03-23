#include "configuration_validator.h"
#include <string>

namespace MuhaSlon
{

template <typename T>
void CheckParameter(T param, const std::string& name)
{
	if (!param.typename get())
		throw std::runtime_error(std::string("Invalid " + name).c_str());

	if (param->typename empty())
		throw std::runtime_error(std::string("Can't be empty " + name).c_str());
}

void ConfigurationValidator::Check(IConfiguration::Ptr configuration)
{
	auto startWord = configuration->GetStartWord();
	CheckParameter(startWord, "Start word");

	auto endWord = configuration->GetEndWord();
	CheckParameter(endWord, "End word");

	auto vocabulary = configuration->GetVocabulary();
	CheckParameter(vocabulary, "Vocabulary");

	if (startWord->size() != endWord->size())
		throw std::runtime_error("Size of Start/End words not equals");
	
	bool hasStartWord = false;
	bool hasEndWord = false;

	for (auto const& word : *vocabulary)
	{
		if (word == *startWord)
			hasStartWord = true;

		if (word == *endWord)
			hasEndWord = true;
	}

	if (!hasStartWord)
		throw std::runtime_error("Vocabulary does not contain Start word");

	if (!hasEndWord)
		throw std::runtime_error("Vocabulary does not contain End word");
}

} // namespace MuhaSlon