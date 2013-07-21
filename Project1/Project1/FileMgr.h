#ifndef FILEMGR_H
#define FILEMGR_H
///////////////////////////////////////////////////////////////////////
// FileMgr.h                                                         //              
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////

/* Package Operations:
 * ===================
 * This package is used to do File System Management
 * Use some facilities of FileSystem Package
 *
 * Required Files:
 * ===============
 * FileSystem.h, FileSystem.cpp
 *
 * Function Catalog:
 * ==========================
 * findFiles
 * getLine
 * putLine
 * storeFile
 * removeDotH
 * copyAndRenameFile
 *
 * Private Function Catalog:
 * ==========================
 * NULL
 */

#include <vector>
#include <string>
#include <iostream>
#include "FileSystem.h"

class FileMgr
{
public:
  // typedef fileSet
  typedef std::vector<std::string> fileSet;

  // default constructor 
  FileMgr::FileMgr(){};

  // constructor (int, char*)
  FileMgr(int argc, char* argv[]);

  // get files which file pattern is "pattern" under directory "path",
  // store names of this files into a fileSet(Vector<string>)
  fileSet findFiles(const std::string& path, const std::string& pattern);
  
  // get a line of the content of file
  std::string getLine(const std::string& filename);

  // write a line of content stored in 'textline' into file named 'filename'
  void putLine(const std::string& filename,const std::string& textline);

  // store content of a file line by line into a vector<sting> and
  // return a vector<string> object
  fileSet storeFile(const std::string& filename);

  // copy file form directory fsource, copy it to fdest directory and rename it
  void static copyAndRenameFile(const std::string& sourcename, const std::string& destname);

private:
  // designed to meet main function parametres
  int _argc;
  char** _argv;
};
#endif
