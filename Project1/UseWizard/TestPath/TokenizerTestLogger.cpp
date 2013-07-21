// TokenizerTestLogger.cpp -ver1.0
// Author: Junwen Bu

#include "TokenizerTestLogger.h"

  // constructor
TokenizerTestLogger::TokenizerTestLogger(void)
{

}

TokenizerTestLogger::~TokenizerTestLogger(void)
{
  //deallocate test resources here
}

  // initial Logger information
std::string TokenizerTestLogger::initialInfo()
{
  std::string info= "\n  Pretending to test the testdriver\n";
  info += "=========== Start Logging ==========\n\n";
  info +="\n========== Run Test:\n====================";
  std::cout<<info<<std::endl;
  return info;
}


TokenizerTestLogger* TokenizerTestLogger::create()
{
  return new TokenizerTestLogger();
}

  // print out result of case test to console window
bool TokenizerTestLogger::caseResult(std::string input, std::string output,std::string expect)
{
  std::string result="------------------- <Tokenizer Test> -------------------\nInput: "+input+"\nOutput: "
    +output+"\nExpect: "+expect+"\n----------------------";
  bool tag=!output.compare(expect);
  result+=(output.compare(expect)?" <Case Fail> ":" <Case Pass> ");
  result+="---------------------";
  std::cout<<result<<std::endl<<std::endl;
  return tag;
}

  // print out result of test
std::string TokenizerTestLogger::testResult(ITest* pTest)
{
  std::string result="Test Result: Test of Tokenizer ";
  result+=((pTest->test()) ? "passed!" : "failed!");
  std::cout<<result<<std::endl;
  return result;
}























































