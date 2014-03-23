#pragma once

#include "iconfiguration.h"

namespace MuhaSlon
{

class ConfigurationValidator
{
public:
	//! Validate configuration. Throws std::runtime error if validation failed.
	static void Check(IConfiguration::Ptr configuration);
};

} // namespace MuhaSlon