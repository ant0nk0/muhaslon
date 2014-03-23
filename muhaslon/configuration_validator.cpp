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
	CheckParameter(configuration->GetStartWord(), "Start word");
	CheckParameter(configuration->GetEndWord(), "End word");
	CheckParameter(configuration->GetVocabulary(), "Vocabulary");

	if (configuration->GetStartWord()->size() != configuration->GetEndWord()->size())
		throw std::runtime_error("Size of Start/End words not equals");
}

} // namespace MuhaSlon