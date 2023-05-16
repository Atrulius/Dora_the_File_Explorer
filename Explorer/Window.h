#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Folder.h"

class Window {

private:

	sf::RenderWindow* winMain;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Font font;

	Folder Current_Folder;
	Folder::Content Current_Folder_Content;

	vector<File> Selected_Files;

	int iMouse_X;
	int iMouse_Y;

	void Initialize_Variables();
	void Initialize_winMain();

public:

	Window();
	~Window();

	bool Is_Open();

	void Poll_Events();

	void Update();
	void Refresh();

	void Draw_Items();

	void Create(string File_Name);
	void Delete_Selection();

	bool Mouse_Moved();
};