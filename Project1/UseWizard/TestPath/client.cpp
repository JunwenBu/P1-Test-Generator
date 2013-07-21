// TestTokenizer.cpp
// Use TokenizerTestWizard
//
// source: Jim Fawcett
// Author: Junwen Bu


#include <iostream>
#include "ITest.h"
#include "TokenizerTestLogger.h"

int main()
{
  // This is a simple test to see whether 
  // the TestTokenizer can run well.
  TokenizerTestLogger* pTL = TokenizerTestLogger::create();
  pTL->initialInfo();
  ITest* pTest = ITest::create();
  pTL->testResult(pTest);
}