///////////////////////////////////////////////////////////////////////
// GenProj.cpp                                                       //
// ver 1.0                                                           //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Reference:   Jim Fawcett's GenProj Demo                           //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////

#include "GenProj.h"

// constructor 
GenProj::GenProj(std::string name):projectName(name)
{}

// return a string object storing the content of the .vcxproj file need to be generated 
std::string GenProj::putProjectString(std::string& templateFile,std::vector<std::string> files)
{
 
  std::ifstream in(templateFile);
  if(!in.good())
  {
    std::cout << "\n  could not open file \"" << templateFile << "\"\n\n";
    return "";
  }
  std::string xmlStr = readToEnd(in);
  XmlReader rdr(xmlStr);
  while(rdr.next())
  {
    std::string str=rdr.tag();
    if(rdr.tag()=="ClCompile")
      {     
      // does this element have "Include" attribute
      size_t start = rdr.position() - 1;
      if((rdr.attributes().size() == 0) || (rdr.attributes()[0].first != "Include"))
        continue;
      size_t end = xmlStr.find("/>",start) + 2;
      rdr.position(start);
      // here's where you insert your cpp files
      std::string dummyCpp = buildCPPsGroup(files);
      xmlStr = xmlStr.replace(start,end-start,dummyCpp.c_str());
      rdr.next();
    }
    else if(rdr.tag() == "ClInclude")
    {
      // does this element have "Include" attribute
      size_t start = rdr.position() - 1;
      if((rdr.attributes().size() == 0) || (rdr.attributes()[0].first != "Include"))
        continue;
      size_t end=xmlStr.find(".h\" />",start)+6;
      rdr.position(start);

      // here's where you insert your h files
      std::string dummyH=buildHsGroup(files);
      xmlStr.insert(end,dummyH.c_str());
      rdr.next();
    }
  }
  xmlStr.erase(xmlStr.length()-1,1); 
  return xmlStr;
}

// generate .vcxproj file under directory 'path'
void GenProj::generateProjectFile(const std::string& path, const std::string& xmlStr)
{
  // set .vcxproj file directory and name 
  std::string file=path+"/"+"Test"+this->projectName+".vcxproj";
  // output contents to .vcxproj file
  std::ofstream out(file,std::ofstream::binary);
  if(out.good())
  {
    out << xmlStr.c_str();
    out.close();
  }
}

// private functions: 

// read file content into string
std::string GenProj::readToEnd(std::ifstream& in)
{
  std::string temp;
  while(in.good())
  { // to see if file is in good condition
    temp += in.get();
  }
  return temp;
}

// build stuff about CPP file infomation and insert it into project file
std::string GenProj::buildCPPsGroup(std::vector<std::string> CPPfiles)
{
  std::string temp="";
  for(std::vector<std::string>::iterator iter=CPPfiles.begin();
    iter!=CPPfiles.end();++iter)
  { // text to insert into <ItemGroup>...</ItemGroup>
    temp+=("<ClCompile Include=\""+*iter+".cpp\" />");
  }
  return temp;
}

// build stuff about H file infomation and insert it into project file
std::string GenProj::buildHsGroup(std::vector<std::string> Hfiles)
{
  std::string temp="";
  for(std::vector<std::string>::iterator iter=Hfiles.begin();
    iter!=Hfiles.end();++iter)
  { // text to insert into <ItemGroup>...</ItemGroup>
    temp+=("<ClInclude Include=\""+*iter+".h\" />");
  }
  return temp;
}

//-----------< test stub >-----------------------
#ifdef TEST_GENPROJ 
int main()
{
  std::string projName="TestGenProj";
  GenProj genproj(projName);
  std::string templateProjF="../template/template.vcxproj";
  std::string path="../template";

  std::vector<std::string> testVec;
  testVec.push_back("A");
  testVec.push_back("B");
  testVec.push_back("C");
  testVec.push_back("D");

  std::string xmlStr=genproj.putProjectString(templateProjF,testVec);
  genproj.generateProjectFile(path, xmlStr);
}
// end < test stub >
#endif
