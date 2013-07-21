#ifndef DEPENDENCYTOOLS_H
#define DEPENDENCYTOOLS_H
///////////////////////////////////////////////////////////////////////
// DependencyTools.h                                                 //              
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////

/* Package Operations:
* ===================
* This Package contains some functions used to find the denpendency roots
* of the files to be tested, latter will contain other functions to build
* dependency graph.
*
* Required Files:
* ===============
* FileMgr.h, FileMgr.cpp
*
* Function Catalog:
* ==========================
* findInclude
* findHeadfile
* findIncludeFiles
* printOutHeadfiles
* removeDotH
* findDependOnFiles
* findRootVector
*
* Private Function Catalog:
* ==========================
* NULL
*/

#include <vector>
#include <set>
#include <ctype.h>
#include <stack>
#include <iostream>
#include "FileMgr.h"
typedef std::vector<std::pair<std::string,std::vector<std::string>>> includeSet;

// return true if the textline contains "#include", else return false
bool findInclude(const std::string& textline);

// get name of the file include
// eg. if #include "name.h", get name and store it to a string
std::string findHeadfile(const std::string& textline);

// store names of headfiles into a set
includeSet findIncludeFiles(const std::string filename, FileMgr::fileSet storedfile);

// print out headfile information
void printOutHeadfiles(includeSet vec, std::string filename);

// remove ".h" at the end of the headname sting
// eg. input "name.h", output "name"
std::string removeDotH(std::string headname);

// If a file is included by other files then it is a denpen-on file,
// this function is used to find such files
std::set<std::string> findDependOnFiles(FileMgr::fileSet fcpp, FileMgr::fileSet fh, FileMgr &fm);

// find root files of test package and store the results in a vector<string>
std::vector<std::string> findRootVector(std::set<std::string> includeFiles,FileMgr::fileSet fh);
#endif