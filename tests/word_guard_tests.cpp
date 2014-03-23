#include "word_guard.h"
#include <gmock/gmock.h>

using namespace MuhaSlon;

TEST(WordGuardTest,UsedValueAndPath)
{
	auto wi = WordItem::Make("word");
	Types::WordsPath path;
	EXPECT_FALSE(wi->IsUsed());
	EXPECT_TRUE(path.empty());
	{
		WordGuard guard(wi.get(), path);
		EXPECT_TRUE(wi->IsUsed());
		EXPECT_EQ(path.size(), 1);
		EXPECT_EQ(path.back()->Get(), "word");
	}
	EXPECT_FALSE(wi->IsUsed());
	EXPECT_TRUE(path.empty());
}

TEST(WordGuardTest,WordItemIsNullptr)
{
	Types::WordsPath path;
	EXPECT_TRUE(path.empty());
	{
		WordGuard guard(nullptr, path);
		EXPECT_EQ(path.size(), 1);
		EXPECT_EQ(path.back(), nullptr);
	}
	EXPECT_TRUE(path.empty());
}
