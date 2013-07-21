#include "BuildTestDriver.h"
///////////////////////////////////////////////////////////////////////
// BuildTestDriver.cpp - Build TestDriver Packages                   //              
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////
using namespace WinTools_Extracts;
BuildTestDriver::BuildTestDriver(std::string name)
  :TDname(name){}

// Load Template Files From path, use a string& to store path infomation
std::vector<std::string> BuildTestDriver::loadTemplateFiles(const std::string& path)
{
  FileHandler fh;
  // set current driectory 
  fh.setCurrentDirectory(path);
  // if file pattern is ".template", then the file is a template
  return fh.getFiles(".template");
}

// read name of the testItem then generate name of the File
std::string BuildTestDriver::genCodeFileName(std::string& tempname)
{
  std::string temp=tempname;
  // erase ".template"
  temp=TDname+temp.erase(temp.length()-9);
  return temp;
}

// generate Test Package Files in directory codepath
std::vector<std::string> BuildTestDriver::createTestDriverFiles(const std::string& tempath, const std::string& codepath, std::vector<std::string> templates)
{
  std::vector<std::string> nameVect;
  std::string name;
  for(std::vector<std::string>::iterator iter=templates.begin();
    iter!=templates.end();++iter)
  { // we don't need to change the content of "ITest.h". 
    if(iter->compare("ITest.h.template")!=0)
    {
      name=this->genCodeFileName(*iter);
      FileMgr::copyAndRenameFile(tempath+"/"+*iter,codepath+"/"+name);
      if(iter->find(".cpp")==iter->npos)
        nameVect.push_back(name.erase(name.length()-2));
    }
  }
  // create a file from template file and copy content of template file into codepath
  FileMgr::copyAndRenameFile(tempath+"/"+"ITest.h.template",codepath+"/ITest.h");
  return nameVect;
}

// use function replaceKeyWords to replace the keywords in a group of files
void BuildTestDriver::doReplace(const std::string& codepath, std::vector<std::string> templates, std::vector<std::string> roots)
{
  std::string keyword="<--insert-->";
  std::string replace="";
  // insert #include block into ITest.h
  for(std::vector<std::string>::iterator iter=roots.begin();
    iter!=roots.end();++iter)
  {
    replace+=("#include \""+*iter+"\"\n");
  }
  replaceKeyWords(codepath+"/ITest.h",keyword,replace);
  // replace the keywords in other generated files
  keyword="<--replace-->";
  replace=this->TDname;
  for(std::vector<std::string>::iterator itert=templates.begin();
    itert!=templates.end();++itert)
  { 
    if(itert->compare("ITest.h.template")!=0)
      replaceKeyWords(codepath+"/"+this->genCodeFileName(*itert),keyword,replace);
  }
}

//  private function: 
// replace every keyword in the file 
void BuildTestDriver::replaceKeyWords(const std::string& filename, std::string& keyword, std::string& replace)
{
  std::string filetext="";
  std::string linetext="";
  
  std::fstream file(filename,std::ios::in|std::ios::out);
  if(!file)
  { // if fail to open the file, print "error" message.
    std::cerr<<filename+" error"<<std::endl;
    exit(1);
  }
  int strPos;
  while(std::getline(file,linetext))
  { // find keyword line by line
    while((strPos=linetext.find(keyword.c_str()))!=-1)
    { // change keyword to "replace" word
      linetext.replace(strPos, keyword.length(), replace.c_str());
    }
    filetext+=linetext+"\n";
  }
  file.clear();
  file.sync();
  file.seekp(0);
  file<<filetext; //output string filetext to file
  file.close();
}

// -------------- < test stub > --------------------
#ifdef TEST_BUILDTESTDRIVER
int main(int argc, char* argv[])
{
  std::string test="test.cpp.template";
  BuildTestDriver btd("Name");
  // test genCodeFileName Function
  std::cout<<"Test GenFileName Function:  "<<btd.genCodeFileName(test)<<std::endl;
  std::vector<std::string> vec; // store name of template files
  vec.push_back("TestDataGenerator.cpp.template");
  vec.push_back("TestDataGenerator.h.template");
  vec.push_back("TestDriver.cpp.template");
  vec.push_back("TestDriver.h.template");
  vec.push_back("TestLogger.cpp.template");
  vec.push_back("TestLogger.h.template");
  vec.push_back("ITest.h.template");
  std::string tempath="../template";
  std::string codepath="../TestPath";
  std::string root="Root";
  std::vector<std::string> roots;
  roots.push_back(root);
  // test createTestDriverFiles Function
  btd.createTestDriverFiles(tempath,codepath,vec);
  // test doRepalce Function
  btd.doReplace(codepath,vec, roots);
}
// end < test stub >
#endif