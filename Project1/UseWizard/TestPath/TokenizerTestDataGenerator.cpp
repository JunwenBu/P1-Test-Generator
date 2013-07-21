// TokenizerTestDataGenerator.cpp -ver1.0
// Author: Junwen Bu

#include "TokenizerTestDataGenerator.h"

TokenizerTestDataGenerator::TokenizerTestDataGenerator(void)
{
  // initialize any test stuff here
}

TokenizerTestDataGenerator::~TokenizerTestDataGenerator(void)
{
  // deallocate test resources here
}

TokenizerTestDataGenerator* TokenizerTestDataGenerator::create()
{
  return new TokenizerTestDataGenerator;
}

  // store test data from file line by line
std::vector<std::string> TokenizerTestDataGenerator::storeFileByLine(std::ifstream &is)
{
  std::vector<std::string> linesOfText;
  std::string textline;
  while (std::getline(is, textline))
    linesOfText.push_back(textline);
  return linesOfText;
}












































