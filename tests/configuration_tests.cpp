#include "configuration.h"
#include <sstream>
#include <gmock/gmock.h>

using namespace MuhaSlon;

class FakeConfiguration : public Configuration
{
public:
	FakeConfiguration(std::istream& startEnd, std::istream& vocabulary) 
		: Configuration("","")
		, m_StartEnd(startEnd)
		, m_Vocabulary(vocabulary)
	{
	}

public:
	virtual void Initialize() override
	{
		ReadStartEndWords(m_StartEnd);
		ReadVocabulary(m_Vocabulary);
		SetInitialized();
	}

private:
	std::istream& m_StartEnd;
	std::istream& m_Vocabulary;
};

struct ConfigurationTest : testing::Test
{
	std::stringstream se;
	std::stringstream voc;
};

TEST_F(ConfigurationTest,EverythingIsGood)
{
	{
		se << "KOT" << std::endl;
		se << "TOT" << std::endl;
	}

	{
		voc << "KOT" << std::endl;
		voc << "TOT" << std::endl;
		voc << "KOTTOT" << std::endl;
	}

	FakeConfiguration config(se, voc);
	config.Initialize();

	EXPECT_EQ(*config.GetStartWord(), "KOT");
	EXPECT_EQ(*config.GetEndWord(), "TOT");

	auto vocabulary = config.GetVocabulary();
	auto begin = vocabulary->begin();
	auto end = vocabulary->end();
	EXPECT_NE(std::find(begin, end, "KOT"), end);
	EXPECT_NE(std::find(begin, end, "TOT"), end);
	EXPECT_NE(std::find(begin, end, "KOTTOT"), end);
}

TEST_F(ConfigurationTest, MissedStartWord)
{
	FakeConfiguration config(se, voc);
	EXPECT_THROW(config.Initialize(), std::exception);
}

TEST_F(ConfigurationTest, MissedEndWord)
{
	{
		se << "KOT";
	}

	FakeConfiguration config(se, voc);
	EXPECT_THROW(config.Initialize(), std::exception);
}
