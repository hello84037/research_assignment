#include <iostream>
#include <string>
#include <fstream>
#include "alg_graphs.h"
#include "alg_strings.h"
#include "alg_stopwatch.h"
#include <random>

using namespace std;

// Structure to hold search results and timings
struct searchResult
{
  int textSize;
  int patternSize;
  double rabinKarpTimeMs;
  double kmpTimeMs;
};

enum class PatternLocation
{
  FRONT,
  MIDDLE,
  END,
};

// Read the entire content of a file into a string
std::string ReadFile(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file)
  {
    cerr << "Unable to open file " << filename << endl;
    return "";
  }

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  file.close();
  return content;
}

// Run KMP algorithm and return elapsed time in milliseconds
double RunKMP(std::string pattern, std::string text)
{
  KMP kmp(pattern);
  StopWatch sw;
  int index = kmp.search(text);
  return sw.elapsed_time_milli_seconds();
}

// Run Rabin-Karp algorithm and return elapsed time in milliseconds
double RunRabinKarp(std::string pattern, std::string text)
{
  RabinKarp rk(pattern);
  StopWatch sw;
  int pos = rk.search(text);
  return sw.elapsed_time_milli_seconds();
}

// Generate a random string of length n
std::string GenerateRandomString(size_t n)
{
  const char charset[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
  const size_t max_index = (sizeof(charset) - 1);
  std::string random_string;
  random_string.reserve(n);

  std::default_random_engine rng(std::random_device{}());
  std::uniform_int_distribution<> dist(0, max_index - 1);

  for (size_t i = 0; i < n; ++i)
  {
    random_string += charset[dist(rng)];
  }
  return random_string;
}

// Get a pattern from text at a random position
std::string GetPatternFromText(const std::string &text, size_t pattern_length)
{
  // Verify you can get a pattern of the requested length
  if (text.length() < pattern_length)
  {
    return "";
  }
  std::default_random_engine rng(std::random_device{}());
  std::uniform_int_distribution<> dist(0, text.length() - pattern_length);
  size_t start_index = dist(rng);
  return text.substr(start_index, pattern_length);
}

// Write search results to csv file
void WriteResultsToCSV(const std::string &filename, const std::vector<searchResult> &results)
{
  std::ofstream file(filename);
  if (!file)
  {
    cerr << "Unable to open file " << filename << " for writing." << endl;
    return;
  }

  file << "TextSize,PatternSize,RabinKarpTimeMs,KMPTimeMs\n";

  for (const auto &result : results)
  {
    file << result.textSize << ","
         << result.patternSize << ","
         << result.rabinKarpTimeMs << ","
         << result.kmpTimeMs << "\n";
  }

  file.close();
}

std::string GetPattern(std::string text, int pattern_size, PatternLocation location)
{
  if (text.length() < pattern_size)
  {
    return "";
  }
  if (location == PatternLocation::FRONT)
  {
    return text.substr(0, pattern_size);
  }
  else if (location == PatternLocation::END)
  {
    return text.substr(text.length() - pattern_size, pattern_size);
  }
  else if (location == PatternLocation::MIDDLE)
  {
    size_t start_index = (text.length() - pattern_size) / 2;
    return text.substr(start_index, pattern_size);
  }
}

// Process a single example of given pattern and text sizes.  Record the times for each of the algorithms.
searchResult ProcessSingleExample(int pattern_size, int text_size)
{
  std::string text = GenerateRandomString(text_size);
  std::string pattern = GetPatternFromText(text, pattern_size);

  double kmpTime = RunKMP(pattern, text);
  double rabinKarpTime = RunRabinKarp(pattern, text);

  searchResult result;
  result.textSize = text.length();
  result.patternSize = pattern.length();
  result.kmpTimeMs = kmpTime;
  result.rabinKarpTimeMs = rabinKarpTime;
  return result;
}

searchResult ProcessSingleExample(PatternLocation location, int pattern_size, std::string text)
{
  std::string pattern = GetPattern(text, pattern_size, location);

  double kmpTime = RunKMP(pattern, text);
  double rabinKarpTime = RunRabinKarp(pattern, text);

  searchResult result;
  result.textSize = text.length();
  result.patternSize = pattern.length();
  result.kmpTimeMs = kmpTime;
  result.rabinKarpTimeMs = rabinKarpTime;
  return result;
}

// Run through a series of examples and write results to CSV
void RunThroughRandomExamples()
{
  std::vector<searchResult> allResults;

  for (int i = 1000; i <= 1000000; i += 5000)
  {
    std::cout << "Processing text size: " << i << std::endl;
    for (int j = 100; j < 1000; j += 100)
    {
      allResults.push_back(ProcessSingleExample(j, i));
    }
  }

  WriteResultsToCSV("comparison_results.csv", allResults);
}

void ProcessPatterns(PatternLocation location, std::string text)
{
  std::vector<searchResult> allResults;

  for (int i = 1000; i <= text.length(); i += 5000)
  {
    allResults.push_back(ProcessSingleExample(location, i, text));
  }

  WriteResultsToCSV(std::to_string(static_cast<int>(location)) + "comparison_results.csv", allResults);
}

void RunThroughLocationExamples()
{
  int text_size = 1000000;
  std::string text = GenerateRandomString(text_size);

  // Test the front pattern
  std::cout << "Processing FRONT pattern examples." << std::endl;
  ProcessPatterns(PatternLocation::FRONT, text);
  // Test the middle pattern
  std::cout << "Processing MIDDLE pattern examples." << std::endl;
  ProcessPatterns(PatternLocation::MIDDLE, text);
  // Test the end pattern
  std::cout << "Processing END pattern examples." << std::endl;
  ProcessPatterns(PatternLocation::END, text);
}

/******************************************************************************
 *  Main program to compare Rabin-Karp and KMP string-matching algorithms.
 ******************************************************************************/
#ifndef UNIT_TESTING
int main(int argc, char *argv[])
{

  // If there are no arguments, run through examples
  if (argc == 2)
  {
    if (std::string(argv[1]) == "location")
    {
      RunThroughLocationExamples();
    }
    else if (std::string(argv[1]) == "random")
    {
      RunThroughRandomExamples();
    }
    return 0;
  }

  else if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " <size of pattern> <size of text>" << std::endl;
    return 1;
  }

  int pattern_size = std::stoi(argv[1]);
  int text_size = std::stoi(argv[2]);

  searchResult result = ProcessSingleExample(pattern_size, text_size);

  std::cout << "Text Size: " << result.textSize << std::endl;
  std::cout << "Pattern Size: " << result.patternSize << std::endl;
  std::cout << "KMP Time (ms): " << result.kmpTimeMs << std::endl;
  std::cout << "Rabin-Karp Time (ms): " << result.rabinKarpTimeMs << std::endl;

  return 0;
}
#endif
