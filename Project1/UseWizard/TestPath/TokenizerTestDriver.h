#pragma once
// TestDriver.h -ver1.0 2/6/2013
//
// Source: Jim Fawcett
// Modified by: Junwen Bu
// Do test by using facilities of TestDataGenerator and TestLogger

#ifndef TEST_EXPORTS
#define TEST_EXPORTS
#endif
#ifndef TESTDRIVER_H
#define TESTDRIVER_H

#include "ITest.h"
#include "TokenizerTestDataGenerator.h"
#include "TokenizerTestLogger.h"

class TokenizerTestDriver : public ITest
{
public:
  TokenizerTestDriver(void);
  virtual ~TokenizerTestDriver(void);
  virtual bool test();
  // inherits static creational function
};
#endif






















