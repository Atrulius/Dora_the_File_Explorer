#pragma once

#include <iostream>
#include <fstream>

using namespace std;


class File {

public:

	File(string );

	string sPath;
	string sLocation;
	string sName;
	string sExtension;

    string Get_Content();

	void Delete();
};