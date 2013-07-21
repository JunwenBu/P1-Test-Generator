#include "DependencyTools.h"
///////////////////////////////////////////////////////////////////////
// DependencyTools.cpp                                               //              
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////

typedef std::vector<std::pair<std::string,std::vector<std::string>>> includeSet;
typedef std::pair<std::string,bool> rootIdentifyPair;

// return true if the textline contains "#include", else return false
bool findInclude(const std::string& textline)
{
  size_t locpos=textline.find("#include");
  if (locpos!=textline.npos) // if find "#include" 
    return true; // return true
  else           // if "#include" not be found
    return false; 
}

// get name of the file include
// eg. if #include "name.h", get name and store it to a string
std::string findHeadfile(const std::string& textline)
{
  if(findInclude(textline))
  {
    size_t startpos=textline.find("\"");//find " 
    if(startpos==textline.npos)
      return ""; // if " not found return empty string
    else{
      size_t endpos=textline.find(".h\""); // find .h"
      return textline.substr(startpos+1,endpos-startpos-1); //return name of the headfile 
    }
  }
  else return ""; // if not found return empty string
}

// store names of headfiles into a set
includeSet findIncludeFiles(std::string filename,FileMgr::fileSet storedfile)
{
  includeSet temp;
  std::pair<std::string,std::vector<std::string>> pair;
  pair.first=filename;
  for(size_t i=0; i<storedfile.size(); ++i)
  {
    std::string head=findHeadfile(storedfile[i]);
    // a "sameName.cpp" will include "sameName.h", consider such case, 
    // eliminate this "sameName.h"
    if(head.compare("")!=0 && (head+".cpp").compare(filename)!=0)
      pair.second.push_back(head);
  }
  temp.push_back(pair);
  return temp;
}

// print out headfile information
void printOutHeadfiles(includeSet vec, std::string filename)
{
  std::cout<<filename<<" includes:"<<std::endl;
  // initialize iterator
  for(includeSet::iterator iter=vec.begin(); iter!=vec.end();++iter)
  {
    if(iter->first.compare(filename)==0)
    {
      for(std::vector<std::string>::iterator iter2=iter->second.begin();
        iter2!=iter->second.end();++iter2)
      {
        std::cout<<*iter2<<" ";
      }
      break;
    }
  }
  return;
}

// remove ".h" at the end of the headname sting
// eg. input "name.h", output "name"
std::string removeDotH(std::string headname)
{
  headname.erase(headname.length()-2);
  return headname;
}

// If a file is included by other files then it is a denpen-on file,
// this function is used to find such files
std::set<std::string> findDependOnFiles(FileMgr::fileSet fcpp, FileMgr::fileSet fh, FileMgr &fm)
{
    std::set<std::string> includeFiles;
    FileMgr::fileSet temp;
    for(size_t i=0; i<fcpp.size(); ++i)
    { //store content of cppFile[i]
      temp=fm.storeFile(fcpp[i]);
      for(size_t j=0; j<temp.size(); ++j)
      { //temp[j] is a line of text
        std::string head=findHeadfile(temp[j]);
        std::string headcpp=head+".cpp";
        if(head.compare("")!=0 && headcpp.compare(fcpp[i])!=0)
          includeFiles.insert(head);
      }
    }
   
    for(size_t i=0; i<fh.size(); ++i)
    { //store content of hFile[i]
      temp=fm.storeFile(fh[i]);
      for(size_t j=0; j<temp.size(); ++j)
      { //temp[j] is a line of text
        std::string head=findHeadfile(temp[j]);
        if(head.compare("")!=0)
          includeFiles.insert(head);
      }
    }
    return includeFiles;
}

// find root files of test package and store the results in a vector<string>
std::vector<std::string> findRootVector(std::set<std::string> includeFiles,FileMgr::fileSet fh)
{
  // second elementof the rootIdentifyPair is a boolean value used to mark a root
  // if true is a root, if false not a root
  std::vector<rootIdentifyPair> rootIdentifyVector; 
  for(FileMgr::fileSet::iterator iter=fh.begin();iter!=fh.end();++iter)
  {
    rootIdentifyPair rootIdentifyUnit;
    rootIdentifyUnit.first=*iter;
    rootIdentifyUnit.second=true;
    for(std::set<std::string>::iterator iter1=includeFiles.begin();
      iter1!=includeFiles.end();++iter1)
      {
        if(!iter->compare(*iter1+".h"))
        {
          rootIdentifyUnit.second=false;
          break;
        }
      }
      // add rootIdentifyUnit into root-Identify-Vector
      rootIdentifyVector.push_back(rootIdentifyUnit);
    }
    // rootVec is used to store root file names
    std::vector<std::string> rootVec;
    for(std::vector<rootIdentifyPair>::iterator it=rootIdentifyVector.begin();
      it!=rootIdentifyVector.end();++it)
    {
      if(it->second==true)
        rootVec.push_back(it->first);
    }
    // return a vector contains names of the root files
    return rootVec;
}

// ----------------- < test stub > -------------------
#ifdef TEST_DEPENDENCYTOOLS
int main()
{
  // initialize data
  std::vector<std::string> rootVec; 
  std::vector<std::string> cppFileList;
  std::vector<std::string> hFileList;
  cppFileList.push_back("A.cpp");
  cppFileList.push_back("B.cpp");
  cppFileList.push_back("C.cpp");
  cppFileList.push_back("D.cpp");
  hFileList.push_back("A.h");
  hFileList.push_back("B.h");
  hFileList.push_back("C.h");
  hFileList.push_back("D.h");
  // test findDependOnFiles Function
  std::set<std::string> includeFiles=findDependOnFiles(cppFileList, hFileList, FileMgr());
  rootVec=findRootVector(includeFiles,hFileList);
  std::cout<<"\nFind Root -> "<<"Root File name: \n  ";
  for(std::vector<std::string>::iterator iter=rootVec.begin();
      iter!=rootVec.end();++iter)
  {  
    std::cout<<*iter<<" ";  
  }
}
// end < test stub >
#endif