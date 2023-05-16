#include "Folder.h"

Folder::Content::Content() {

}
Folder::Content::Content(string Root_Path, vector<string> Names) {

	Path = Root_Path;

	for (int i = 0; i < Names.size(); i++)
		if (filesystem::is_directory(Root_Path + "\\" + Names[i]))
			Folders.push_back(Names[i]);
		else
			Files.push_back(Names[i]);
}

Folder::Folder() {

	Initialize_Path("C:");
}

Folder::Folder(string Path) {

	Initialize_Path(Path);
}

void Folder::Initialize_Path(string Path) {

	sPath = Path;
	sLocation = Path.substr(0, Path.find_last_of("\\"));
	sName = Path.substr(Path.find_last_of("\\") + 1);
}

void Folder::Delete(string Name) {

	string Path = sPath;

	if (Name != "")
		Path += "\\" + Name;

	if (is_regular_file(Path))
		remove(Path);
	if (is_directory(Path))
		remove_all(Path);

	if (sPath == Path)
		delete this;
}

void Folder::Create(string Name) {

	string Path = sPath + "\\" + Name;

    if (!create_directory(Path))
    {
        ofstream file(Path);
        file.close();
    }
}

Folder::Content Folder::Get_Content() {

	vector<string> Names;

	for (const auto& entry : directory_iterator(sPath))
		Names.push_back(entry.path().filename().string());

	return Content(sPath, Names);
}