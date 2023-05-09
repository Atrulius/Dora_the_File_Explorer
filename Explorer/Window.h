#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <Windows.h>

#include "File.h"

class Window {

private:

	sf::RenderWindow* winMain;
	sf::VideoMode videoMode;
	sf::Event event;

	std::string sCurrent_Path;

	std::vector<File> Selected_Files;

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

	void Create(std::string sFile_Name);
	void Delete_Selection();

	bool Mouse_Moved();
};