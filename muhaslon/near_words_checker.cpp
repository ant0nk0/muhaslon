#include "near_words_checker.h"
#include <cstdint>

namespace MuhaSlon
{
namespace Helpers
{

bool CheckWordsAreNear(const std::string& lhs, const std::string& rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	bool oneLetterDiffers = false;
	for (std::size_t i = 0; i < lhs.size(); ++i)
	{
		if (lhs[i] != rhs[i])
		{
			if (oneLetterDiffers)
				return false;

			oneLetterDiffers = true;
		}
	}

	return oneLetterDiffers;
}

} // namespace Helpers
} // namespace MuhaSlon