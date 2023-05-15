#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace filesystem;

class File {

public:

	File(string Path);

	string sPath;
	string sLocation;
	string sName;
	string sExtension;

    string Get_Content();

	void Delete();
};