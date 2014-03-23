#include "configuration_validator.h"
#include <gmock/gmock.h>

using namespace MuhaSlon;

struct MockConfiguration : IConfiguration
{
	MOCK_METHOD0(Initialize,void());
	MOCK_METHOD0(GetStartWord,StringPtr());
	MOCK_METHOD0(GetEndWord,StringPtr());
	MOCK_METHOD0(GetVocabulary,VocabularyPtr());
};

struct TestConfigurationValidator : testing::Test
{
	std::shared_ptr<MockConfiguration> m_Config;

	virtual void SetUp() override
	{
		m_Config = std::make_shared<MockConfiguration>();
	}

	void InitStartWord(IConfiguration::StringPtr startWord)
	{
		EXPECT_CALL(*m_Config.get(), GetStartWord())
			.WillRepeatedly(
				testing::Return(
					startWord
				)
			);
	}

	void InitEndWord(IConfiguration::StringPtr endWord)
	{
		EXPECT_CALL(*m_Config.get(), GetEndWord())
			.WillRepeatedly(
				testing::Return(
					endWord
				)
			);
	}
	
	void Init(IConfiguration::StringPtr startWord,
			  IConfiguration::StringPtr endWord,
			  IConfiguration::VocabularyPtr vocabulary)
	{
		InitStartWord(startWord);
		InitEndWord(endWord);

		EXPECT_CALL(*m_Config.get(), GetVocabulary())
			.WillRepeatedly(
				testing::Return(
					vocabulary
				)
			);
	}
};

TEST_F(TestConfigurationValidator,EmptyStartWordPtr)
{
	InitStartWord(IConfiguration::StringPtr());
	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,EmptyStartWordValue)
{
	InitStartWord(std::make_shared<IConfiguration::StringPtr::element_type>(""));

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,EmptyEndWordPtr)
{
	InitStartWord(std::make_shared<IConfiguration::StringPtr::element_type>("some_value"));
	InitEndWord(IConfiguration::StringPtr());

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,EmptyEndWordValue)
{
	InitStartWord(std::make_shared<IConfiguration::StringPtr::element_type>("some_value"));
	InitEndWord(std::make_shared<IConfiguration::StringPtr::element_type>(""));

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,EmptyVocabularyPtr)
{
	auto someValue = std::make_shared<IConfiguration::StringPtr::element_type>("some_value");
	Init(someValue, someValue, IConfiguration::VocabularyPtr());

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,EmptyVocabulary)
{
	auto someValue = std::make_shared<IConfiguration::StringPtr::element_type>("some_value");
	Init(someValue, someValue, std::make_shared<IConfiguration::Vocabulary>());

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,AllOk)
{
	auto someValue = std::make_shared<IConfiguration::StringPtr::element_type>("some_value");
	auto voc = std::make_shared<IConfiguration::Vocabulary>();
	voc->push_back("some_value");

	Init(someValue, someValue, voc);

	EXPECT_NO_THROW(ConfigurationValidator::Check(m_Config));
}

TEST_F(TestConfigurationValidator,WordSizesNotEquals)
{
	auto startWord = std::make_shared<IConfiguration::StringPtr::element_type>("some_value");
	auto endWord = std::make_shared<IConfiguration::StringPtr::element_type>("some_value111");

	auto voc = std::make_shared<IConfiguration::Vocabulary>();
	voc->push_back("some_value");
	voc->push_back("some_value111");

	Init(startWord, endWord, voc);

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,StartWordNotInVocabulary)
{
	auto startWord = std::make_shared<IConfiguration::StringPtr::element_type>("some_value1");
	auto endWord = std::make_shared<IConfiguration::StringPtr::element_type>("some_value2");
	auto voc = std::make_shared<IConfiguration::Vocabulary>();
	voc->push_back("some_value2");

	Init(startWord, endWord, voc);

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}

TEST_F(TestConfigurationValidator,EndWordNotInVocabulary)
{
	auto startWord = std::make_shared<IConfiguration::StringPtr::element_type>("some_value1");
	auto endWord = std::make_shared<IConfiguration::StringPtr::element_type>("some_value2");
	auto voc = std::make_shared<IConfiguration::Vocabulary>();
	voc->push_back("some_value1");

	Init(startWord, endWord, voc);

	EXPECT_THROW(ConfigurationValidator::Check(m_Config), std::runtime_error);
}
