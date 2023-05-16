#pragma once

#include "File.h"

class Folder {

public:

	class Content {

	public:

		Content();
		Content(string Root_Path, vector<string> Names);

		string Path;

		vector<string> Files;
		vector<string> Folders;
	};

	Folder();
	Folder(string Path);

	string sPath;
	string sLocation;
	string sName;

	void Initialize_Path(string Path);

	void Delete(string Name);

	void Create(string Name);

	Content Get_Content();
};