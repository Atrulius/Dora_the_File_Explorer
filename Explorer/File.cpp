#include "File.h"

File::File(string Path) {

    sPath = Path;
    sLocation = Path.substr(0, Path.find_last_of("\\"));
    sName = Path.substr(Path.find_last_of("\\"), Path.find_last_of(".") - Path.find_last_of("\\"));
    sExtension = Path.substr(Path.find_last_of(".") + 1, Path.length() - Path.find_last_of(".") - 1);

    cout << "Path: " << sPath << "\n";
    cout << "Location: " << sLocation << "\n";
    cout << "Name: " << sName << "\n";
    cout << "Extension: " << sExtension << "\n\n";
}

string File::Get_Content() {

    ifstream fileStream(sPath);

    return string((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
}

void File::Delete() {

    remove(sPath.c_str());
    delete this;
}