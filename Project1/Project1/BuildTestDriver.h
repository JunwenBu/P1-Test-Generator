#ifndef BUILDTESTDRIVER_H
#define BUILDTESTDRIVER_H
///////////////////////////////////////////////////////////////////////
// BuildTestDriver.h - Build TestDriver Packages                     //              
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////

/* Package Operations:
* ===================
* This package is used to generate Test Pakage files including
* NameTestLogger.h/.cpp; NameTestDriver.h/.cpp; NameTestDataGeneratro.h/.cpp
* and ITest.h
*
* Required Files:
* ===============
* FileMgr.h, FileMgr.cpp
* FileSystem.h, FileSystem.cpp
*
* Function Catalog:
* ==========================
* BuildTestDriver
* loadTemplateFiles
* genCodeFileName
* createTestDriverFiles
* doReplace
*
* Private Function Catalog:
* ==========================
* replaceKeyWords
*
*/
#include "FileMgr.h"
#include "FileSystem.h"

class BuildTestDriver
{
public:
	// Load Template Files From path, use a string& to store path infomation
	BuildTestDriver(std::string name);

	// read name of the testItem then generate name of the File
	std::vector<std::string> loadTemplateFiles(const std::string& templatePath);

	// generate Test Package Files in directory codepath
	std::string genCodeFileName(std::string& tempname);

	// replace every keyword in the file by replace
	std::vector<std::string> createTestDriverFiles(const std::string& tempath, const std::string& codepath, std::vector<std::string> templates);

	// use function replaceKeyWords to replace the keywords in a group of files
	void doReplace(const std::string& codepath, std::vector<std::string> filenames, std::vector<std::string> roots);

private:
	// replace every "keyword" in the file by string "replace"
	void replaceKeyWords(const std::string& filename, std::string& keyword, std::string& replace);
	std::string TDname;
};

#endif