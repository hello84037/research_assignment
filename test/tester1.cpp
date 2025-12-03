#define CATCH_CONFIG_MAIN // Tells Catch2 to provide a main() function
#include <catch2/catch_all.hpp>
#include <fstream>
#include <string>
#include "alg_strings.h"
#include "alg_stopwatch.h"
#include "../src/part1.cpp"

using namespace std;

void RunComparison(std::string pattern, std::string text, int requiredIndex, std::string testname)
{
	std::cout << "Test: " << testname << std::endl;

	KMP kmp(pattern);
	StopWatch sw;
	int index = kmp.search(text);
	std::cout << "KMP: " << sw.elapsed_time_milli_seconds() << " ms" << std::endl;
	REQUIRE(index == requiredIndex);

	RabinKarp rk(pattern);
	sw.reset();
	int rk_index = rk.search(text);
	std::cout << "RabinKarp: " << sw.elapsed_time_milli_seconds() << " ms" << std::endl;
	REQUIRE(rk_index == requiredIndex);
}

TEST_CASE("Small Pattern with Small Text at the Start", "[SmallVSmallAtStart]")
{
	std::string pattern = "abc";
	std::string text = "abcaskdjfoskdnfbcpqradbc";
	RunComparison(pattern, text, 0, "Small Pattern with Small Text at the Start");
}

TEST_CASE("Small Pattern with Small Text at the End", "[SmallVSmallAtEnd]")
{
	std::string pattern = "abc";
	std::string text = "bcaskdjfoskdnfbcpqradabc";
	RunComparison(pattern, text, 21, "Small Pattern with Small Text at the End");
}

TEST_CASE("Large Pattern with Small Text at the End", "[LargeVSmallAtEnd]")
{
	std::string pattern = "bcaskdjfoskdnfbcpqradbc";
	std::string text = "abcaskdjfoskdnfbcpqradbc";
	RunComparison(pattern, text, 1, "Large Pattern with Small Text at the End");
}

TEST_CASE("Large Pattern with Small Text at the Start", "[LargeVSmallAtStart]")
{
	std::string pattern = "abcaskdjfoskdnfbcpqradb";
	std::string text = "abcaskdjfoskdnfbcpqradbc";
	RunComparison(pattern, text, 0, "Large Pattern with Small Text at the Start");
}

TEST_CASE("Small Pattern with Large Text at the End", "[SmallVLargeAtEnd]")
{
	std::string pattern = "abc";
	std::string text = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.  Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth. Abraham Lincoln November 19, 1863abc";
	RunComparison(pattern, text, 1508, "Small Pattern with Large Text at the End");
}

TEST_CASE("Small Pattern with Large Text at the Start", "[SmallVLargeAtStart]")
{
	std::string pattern = "abc";
	std::string text = "abcFour score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.  Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth. Abraham Lincoln November 19, 1863";
	RunComparison(pattern, text, 0, "Small Pattern with Large Text at the Start");
}

TEST_CASE("Large Pattern with Large Text at the End", "[LargeVLargeAtEnd]")
{
	std::string pattern = "our score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.  Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth. Abraham Lincoln November 19, 1863abc";
	std::string text = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.  Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth. Abraham Lincoln November 19, 1863abc";
	RunComparison(pattern, text, 1, "Large Pattern with Large Text at the End");
}

// Change me or remove me to appropriately test part1 of this assignment
TEST_CASE("Large Pattern with Large Text at the Start", "[LargeVLargeAtStart]")
{
	std::string pattern = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.  Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth. Abraham Lincoln November 19, 1863ab";
	std::string text = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.  Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we can not dedicate -- we can not consecrate -- we can not hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth. Abraham Lincoln November 19, 1863abc";
	RunComparison(pattern, text, 0, "Large Pattern with Large Text at the Start");
}