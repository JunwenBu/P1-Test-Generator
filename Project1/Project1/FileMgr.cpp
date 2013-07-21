///////////////////////////////////////////////////////////////////////
// FileMgr.cpp                                                       //              
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////
#include "FileMgr.h"

using namespace WinTools_Extracts;

// constructor
FileMgr::FileMgr(int argc, char* argv[])
{
  _argc = argc;
  _argv = argv;
}

// get files which file pattern is "pattern" under directory "path",
// store names of this files into a fileSet(Vector<string>)
FileMgr::fileSet FileMgr::findFiles(const std::string& path, const std::string& pattern)
{
  // eventually will use XML config file to possibly modify fileSet
  FileHandler fh;
  fh.setCurrentDirectory(path);
  return fh.getFiles(pattern);
}

// get a line of the content of file
std::string FileMgr::getLine(const std::string& filename)
{
  File file(filename,File::in);
  file.isGood(); // to see whether file is in good condition
  return file.getLine();
}

// write a line of content stored in 'textline' into file named 'filename'
void FileMgr::putLine(const std::string& filename, const std::string& textline)
{
  File file(filename,File::out);
  file.isGood(); // to see whether file is in good condition
  file.putLine(textline);
}

// store content of a file line by line into a vector<sting> and
// return a vector<string> object
FileMgr::fileSet FileMgr::storeFile(const std::string& filename)
{
  File file(filename,File::in); //
  std::string textline;
  FileMgr::fileSet temp;
  while (file.isGood())
  { // to see whether file is in good condition
    textline=file.getLine();
    temp.push_back(textline);
  }
  return temp;
}

// copy file form directory fsource, copy it to fdest directory and rename it
void FileMgr::copyAndRenameFile(const std::string& fsource, const std::string& fdest)
{
  // read file in binary format
  File source(fsource, File::in, File::binary);
  if(!source.isGood())
  { // to see whether file is in good condition
    FileHandler fh;
    std::cout << "\n  can't open file\n";
    std::cout << "\n  looking for:\n  ";
    std::cout << fh.getFullPath(source.name()) << "\n";
  }
  else
  { 
    source.blockSize();
    File dest(fdest, File::out, File::binary);
    // if file is in good condition, copy blocks into destination file
    if(dest.isGood())
    {
      while(source.isGood())
      {
        File::block b = source.getBlock();
        dest.putBlock(b);
      }
    }
    else
    { // if copy operation fails, print out fail information
      std::cout << "\n  copy fail !\n";
      std::cout << "Can not find file path."<<std::endl;
    }
  }
}

// --------------------- < test stub > -----------------------------
#ifdef TEST_FILEMGR
int main(int argc, char* argv[])
{
  // find files to test
  // assumes path may be named by argv[1]
  // assumes patterns may be named by argv[2], argv{3}, ...

  std::string path = ".";
  std::string pattern = "*.*";
  std::vector<std::string> tempVec;

  int count = 2;

  while(count < argc)
  {
    if(argc == 1)
      path = ".";
    else
      path = argv[1];
    if(argc == 2)
      pattern = "*.*";
    else
      pattern = argv[count++];
    //if(count == 3)
    //  std::cout << "\nProcessing files in: " << std::endl;
    FileMgr fm(argc, argv);
    // test copyAndRenameFile Functoiin
    fm.copyAndRenameFile("../template/template.vcxproj","../template/copy.vcxproj");
    // test storeFile Function
    tempVec=fm.storeFile("../template/template.vcxproj");
    for(FileMgr::fileSet::iterator iter=tempVec.begin();
      iter!=tempVec.end();++iter)
    {
      std::cout<<*iter<<" "<<std::endl;
    }
  }
}
// end < test stub >
#endif
