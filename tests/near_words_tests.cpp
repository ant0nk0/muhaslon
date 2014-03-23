#include "near_words_checker.h"
#include <gmock/gmock.h>

using namespace MuhaSlon;

TEST(TestNearWords,EmptyWords)
{
	EXPECT_FALSE(Helpers::CheckWordsAreNear("", ""));
}

TEST(TestNearWords,OneOfWordsEmpty)
{
	EXPECT_FALSE(Helpers::CheckWordsAreNear("aaa", ""));
}

TEST(TestNearWords,DifferentSize)
{
	EXPECT_FALSE(Helpers::CheckWordsAreNear("aaa", "bb"));
}

TEST(TestNearWords,SameWords)
{
	EXPECT_FALSE(Helpers::CheckWordsAreNear("aaa", "aaa"));
}

TEST(TestNearWords,OneLetterDiffersAtEnd)
{
	EXPECT_TRUE(Helpers::CheckWordsAreNear("aaa", "aaz"));
}

TEST(TestNearWords,OneLetterDiffersAtBegin)
{
	EXPECT_TRUE(Helpers::CheckWordsAreNear("aaa", "zaa"));
}

TEST(TestNearWords,OneLetterDiffersAtMiddle)
{
	EXPECT_TRUE(Helpers::CheckWordsAreNear("aaa", "aza"));
}

TEST(TestNearWords,TwoMoreLettersDiffers)
{
	EXPECT_FALSE(Helpers::CheckWordsAreNear("aaa", "azz"));
}
