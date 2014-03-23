#include "word_guard.cpp"
#include "near_words_checker.cpp"
#include "configuration.cpp"
#include "word_item.cpp"
#include "configuration_validator.cpp"
#include "solver.cpp"
#include <gmock-gtest-all.cc>

int main(int argc, char** argv)
{
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}

