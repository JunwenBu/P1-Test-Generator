#pragma once
#ifndef TEST_EXPORTS
#define TEST_EXPORTS
#endif
#ifndef ITEST_H
#define ITEST_H
// ITest.h - ver1.0 2/6/2012
// Source: Jim Fawcett
// Modified by: Junwen Bu

// This class consisting ITest* creat() and bool() test.

// DLL_EXPORT
#ifdef TEST_EXPORTS
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif

// ----------- < include stub > ----------- 
// Include useful "include" stuff which are 
// included by TD, TDG, TDL and these stuff 
// are always used by normal applicaations.

#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <assert.h>

// Generator "include" according to the denpendency 
// structure of test files. 
#include "Tokenizer.h"


class TEST_API ITest
{
public:
  virtual bool test()=0;

  // create function is a factory method that creates 
  // instances of whatever classes needed to execute 
  // the test methods
  static ITest* create();

  virtual ~ITest() {}
};

#endif
