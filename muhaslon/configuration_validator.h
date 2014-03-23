#pragma once

#include "iconfiguration.h"
#include "non_copyable.h"

namespace MuhaSlon
{

class ConfigurationValidator : NonCopyable
{
public:
	//! Validate configuration. Throws std::runtime error if validation failed.
	static void Check(IConfiguration::Ptr configuration);

private:
	ConfigurationValidator();
};

} // namespace MuhaSlon