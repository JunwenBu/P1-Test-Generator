#pragma once
// TestLogger.h -ver1.0 2/6/2012
// Author: Junwen bu
// implements a TestLogger interface
#ifndef TEST_EXPORTS
#define TEST_EXPORTS
#endif
#ifndef TESTLOGGER_H
#define TESTLOGGER_H

#include "TokenizerTestDriver.h"

class TEST_API TokenizerTestLogger
{
public:
  // constructor
  TokenizerTestLogger();

  virtual ~TokenizerTestLogger(void);

  static TokenizerTestLogger* create();
  // initial Logger information
  std::string initialInfo();

  // print out result of case test to console window
  bool caseResult(std::string input,std::string ouptup,std::string expect);

  // print out result of test
  std::string testResult(ITest* pTest);

};

#endif























