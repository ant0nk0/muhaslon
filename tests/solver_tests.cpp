#include "solver.h"
#include "types.h"
#include "word_item.h"
#include <gmock/gmock.h>

using namespace MuhaSlon;

struct MockConfiguration : IConfiguration
{
	MOCK_METHOD0(Initialize,void());
	MOCK_METHOD0(GetStartWord,StringPtr());
	MOCK_METHOD0(GetEndWord,StringPtr());
	MOCK_METHOD0(GetVocabulary,VocabularyPtr());
};

TEST(SolverTests,KOT2POB)
{
	auto configuration = std::make_shared<MockConfiguration>();

	auto startWord = std::make_shared<IConfiguration::StringPtr::element_type>("KOT");
	auto endWord = std::make_shared<IConfiguration::StringPtr::element_type>("POB");

	auto vocabulary = std::make_shared<IConfiguration::Vocabulary>();
	vocabulary->push_back(*startWord);
	vocabulary->push_back(*endWord);
	vocabulary->push_back("POT");

	EXPECT_CALL(*configuration.get(), GetStartWord())
		.WillRepeatedly(
			testing::Return(
				startWord
			)
		);

	EXPECT_CALL(*configuration.get(), GetEndWord())
		.WillRepeatedly(
			testing::Return(
				endWord
			)
		);

	EXPECT_CALL(*configuration.get(), GetVocabulary())
		.WillRepeatedly(
			testing::Return(
				vocabulary
			)
		);

	Types::Solution correctSolution;
	correctSolution.emplace_back("KOT");
	correctSolution.emplace_back("POT");
	correctSolution.emplace_back("POB");

	auto solution = Solver(configuration).Run();

	EXPECT_EQ(solution, correctSolution);
}

TEST(SolverTests,KOT2KOM)
{
	auto configuration = std::make_shared<MockConfiguration>();

	auto startWord = std::make_shared<IConfiguration::StringPtr::element_type>("KOT");
	auto endWord = std::make_shared<IConfiguration::StringPtr::element_type>("KOM");

	auto vocabulary = std::make_shared<IConfiguration::Vocabulary>();
	vocabulary->push_back(*startWord);
	vocabulary->push_back("KOP");
	vocabulary->push_back("KOC");
	vocabulary->push_back("KOK");
	vocabulary->push_back(*endWord);

	EXPECT_CALL(*configuration.get(), GetStartWord())
		.WillRepeatedly(
			testing::Return(
				startWord
			)
		);

	EXPECT_CALL(*configuration.get(), GetEndWord())
		.WillRepeatedly(
			testing::Return(
				endWord
			)
		);

	EXPECT_CALL(*configuration.get(), GetVocabulary())
		.WillRepeatedly(
			testing::Return(
				vocabulary
			)
		);

	Types::Solution correctSolution;
	correctSolution.emplace_back("KOT");
	correctSolution.emplace_back("KOM");

	auto solution = Solver(configuration).Run();

	EXPECT_EQ(solution, correctSolution);
}

TEST(SolverTests,KOT2KOT)
{
	auto configuration = std::make_shared<MockConfiguration>();

	auto word = std::make_shared<IConfiguration::StringPtr::element_type>("KOT");

	auto vocabulary = std::make_shared<IConfiguration::Vocabulary>();
	vocabulary->push_back(*word);
	vocabulary->push_back("KOK");
	vocabulary->push_back("KOH");

	EXPECT_CALL(*configuration.get(), GetStartWord())
		.WillRepeatedly(
			testing::Return(
				word
			)
		);

	EXPECT_CALL(*configuration.get(), GetEndWord())
		.WillRepeatedly(
			testing::Return(
				word
			)
		);

	EXPECT_CALL(*configuration.get(), GetVocabulary())
		.WillRepeatedly(
			testing::Return(
				vocabulary
			)
		);

	Types::Solution correctSolution;
	correctSolution.emplace_back("KOT");

	auto solution = Solver(configuration).Run();

	EXPECT_EQ(solution, correctSolution);
}