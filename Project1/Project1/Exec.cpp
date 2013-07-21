///////////////////////////////////////////////////////////////////////
// Exec.cpp - runs the Project1:BuildTestHarness                     //              
// ver 1.1 2/8/2012                                                  //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// Application: CSE 687 Project1                                     //
// Author:      Junwen Bu                                            //
///////////////////////////////////////////////////////////////////////
#include <iostream>
#include "XmlReader.h"
#include "FileMgr.h"
#include "DependencyTools.h"
#include "BuildTestDriver.h"
#include "GenProj.h"
using namespace WinTools_Extracts;

// define includeSet and strVector
typedef std::vector<std::pair<std::string,std::vector<std::string>>> includeSet;
typedef std::vector<std::string> strVector;

// Get Test Files'information from a .xml file if no xml file is found, use the default 
// test name and assume that all the source code files in the specified directory 
// are to be tested and that the interfaces are found in the specified directory.
void GetTestFileInfo(FileMgr& fm, strVector xmlVec,std::string& path, std::string& xml,
	std::string& testName, FileMgr::fileSet& hFileList, FileMgr::fileSet& cppFileList)
{
	if(!xmlVec.empty())
	{
		for(strVector::iterator iter=xmlVec.begin();iter!=xmlVec.end();iter++)
		{
			xml+=*iter;
		}
		std::cout<<"Open conf.xml"<<std::endl;
		XmlReader rdr(xml);
		rdr.next();
		while (rdr.tag().compare("Path")!=0)
		{ // Get TestPath and store it to string path; 
			rdr.next();
		}
		path=rdr.body();
		rdr.next();
		testName=rdr.body();
		std::cout<<"Get TestName :  "<<testName<<std::endl;
		strVector listVector;
		while(rdr.next())
		{ // get File List
			if(rdr.tag().compare("List")==0)
			{
				std::string listBody=rdr.body();
				if(listBody.find(".h")!=listBody.npos)
					hFileList.push_back(listBody);
				if(listBody.find(".cpp")!=listBody.npos)
					cppFileList.push_back(listBody);
			}
		}
	}else
	{ // if there is no xml files
		hFileList=fm.findFiles(path,"*.h");
		cppFileList=fm.findFiles(path,"*.cpp");
	}
}

// generate test driver code including logger and datagen
strVector buildTestDriver(std::string& testName, FileMgr& fm, std::vector<std::string>& rootVec)
{
	std::cout<<std::endl;
	BuildTestDriver buildTD(testName);
	// print out information to show "Building TestDriver Process" start
	std::cout<<"\n=============================""==========================="
		"\nStart building TestDriver Pakages."<<std::endl;
	std::string tempath = "../template";
	std::string tempattern = "*.template";

	// get template files
	FileMgr::fileSet templates=fm.findFiles(tempath, tempattern);
	std::string codepath="../TestPath";
	strVector packNameVector = buildTD.createTestDriverFiles(tempath,codepath,templates);
	buildTD.doReplace(codepath,templates,rootVec);
	std::cout<<"Packages building complete in the PATH: "<<codepath<<std::endl;
	return packNameVector;
}

// --------------------< MAIN FUNCTION >----------------------------------
// assumes path may be named by argv[1], patterns may be named by argv[2], argv{3}, ...
int main(int argc, char* argv[]) 
{ // initialization
	std::string path = "../TestPath",pattern = "*.*";
	std::string testName="<DEFAULT>";
	FileMgr fm(argc, argv);
	std::string xml="";
	FileMgr::fileSet hFileList;
	FileMgr::fileSet cppFileList;
	strVector rootVec;
	int count = 2;
	while(count < argc)
	{
		if(argc == 1) path = ".";
		else path = argv[1];
		if(argc == 2) pattern = "*.*";
		else pattern = argv[count++];
		if(count == 3)
			std::cout << "  Start Test Harness:\n==========================="<<
			"=============================\nProcessing files in: " <<
			argv[1]<< std::endl;
		FileMgr::fileSet files = fm.findFiles(path, pattern);
		strVector xmlVec=fm.storeFile("conf.xml");

		// -------------------- < Get Test File Information & Find Root > -----------------------
		GetTestFileInfo(fm,xmlVec,path,xml,testName,hFileList,cppFileList);
		std::set<std::string> includeFiles=findDependOnFiles(cppFileList, hFileList, fm);
		rootVec=findRootVector(includeFiles,hFileList);
		std::cout<<"\n========================================================"
			"\nFind Root -> "<<"Root File name: \n  ";
		for(std::vector<std::string>::iterator iter=rootVec.begin();
			iter!=rootVec.end();++iter)  
			std::cout<<*iter<<" ";  
		if (testName.compare("<DEFAULT>")==0&&rootVec.size()!=0)
			testName=removeDotH(rootVec[0]);
	}

	// ----------------- < generate test driver code including logger and datagenerator > --------
	strVector packNameVector=buildTestDriver(testName,fm,rootVec);
	// ------------------- < generate Visual Studio project > ----------------
	strVector projFileInfo;
	for(strVector::iterator iter=hFileList.begin();iter!=hFileList.end();++iter)
	{
		projFileInfo.push_back((iter->erase(iter->length()-2)));
	}
	// print out information show the process "Generating Visual Studio Project" is starting.
	std::cout<<"\n========================================================"
		"\nStart generating TestDriver Pakages."<<std::endl;
	for(strVector::iterator itern=packNameVector.begin();itern!=packNameVector.end();++itern)
	{
		projFileInfo.push_back(*itern);
	}

	std::string templateProjF="../template/template.vcxproj", projFilePath="../TestPath";
	GenProj genproj(testName);
	std::string projStr=genproj.putProjectString(templateProjF,projFileInfo);
	genproj.generateProjectFile(projFilePath, projStr);
	std::cout<<"Pakages generated successfully in the PATH: "
		<<projFilePath<<std::endl<<std::endl;
}
// end Exec.cpp