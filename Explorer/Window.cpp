#include "Window.h"

Window::Window() {

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	Initialize_Variables();
	Initialize_winMain();
}

void Window::Initialize_Variables() {

	winMain = nullptr;

	iMouse_X = sf::Mouse::getPosition().x;
	iMouse_Y = sf::Mouse::getPosition().y;
}

void Window::Initialize_winMain() {

	videoMode.height = 500;
	videoMode.width = 750;

	winMain = new sf::RenderWindow(videoMode, "Explorer", sf::Style::Default);
}

Window::~Window() {

	delete winMain;
}

bool Window::Is_Open() {

	return winMain->isOpen();
}

void Window::Poll_Events() {

	while (winMain->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {

			winMain->close();
			break;
		}

		if (event.type == sf::Event::KeyPressed) {

			if (event.key.code == sf::Keyboard::Delete) {

				Delete_Selection();
			}
		}
	}
}

void Window::Update() {

	
}

void Window::Refresh() {


}

void Window::Create(std::string sFile_Name) {

	Refresh();
}

void Window::Delete_Selection() {

	for (int i = 0; i < sSelected_Files.size(); i++)
		remove((sCurrent_Path + "\\" + sSelected_Files[i]).c_str());

	Refresh();
}

bool Window::Mouse_Moved() {

	if (sf::Mouse::getPosition().x - winMain->getPosition().x != iMouse_X || sf::Mouse::getPosition().y - winMain->getPosition().y != iMouse_Y) {

		iMouse_X = sf::Mouse::getPosition().x - winMain->getPosition().x;
		iMouse_Y = sf::Mouse::getPosition().y - winMain->getPosition().y;

		return 1;
	}

	return 0;
}