#pragma once
// TokenizerTestDataGenerator.h ver1.0 
// Author: Junwen Bu
// implements an TestGenerator interface

#ifndef TEST_EXPORTS
#define TEST_EXPORTS
#endif
#ifndef TESTDATAGENERATOR_H
#define TESTDATAGENERATRO_H

#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

#include "TokenizerTestDriver.h"

class TEST_API TokenizerTestDataGenerator
{
public:
  // constructor
  TokenizerTestDataGenerator();

  virtual ~TokenizerTestDataGenerator(void);

  // implement TestGenerator interface
  static TokenizerTestDataGenerator* create();

  // store test data from file line by line
  std::vector<std::string> storeFileByLine(std::ifstream &is);
};
#endif































