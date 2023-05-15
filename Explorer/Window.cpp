#include "Window.h"

Window::Window() {

	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	Initialize_Variables();
	Initialize_winMain();

	Current_Folder.Initialize_Path("C:\\Users\\TobiasEmberland\\Cisco Packet Tracer 8.2.0");

	cout << Current_Folder.sPath << "\n";

	Refresh();
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

	winMain->clear(sf::Color(15, 15, 15));

	for (int Folder = 0; Folder < Current_Folder_Content.Folders.size(); Folder++) {

		sf::RectangleShape rect;

		rect.setPosition(10 + Folder * 55, 10);
		rect.setFillColor(sf::Color(255, 255, 255));
		rect.setSize(sf::Vector2f(50, 50));

		winMain->draw(rect);
	}
	for (int File = 0; File < Current_Folder_Content.Files.size(); File++) {

		sf::RectangleShape rect;

		rect.setPosition(10 + File * 55, 65);
		rect.setFillColor(sf::Color(255, 255, 255));
		rect.setSize(sf::Vector2f(50, 50));

		winMain->draw(rect);
	}

	winMain->display();
}

void Window::Refresh() {

	Current_Folder_Content = Current_Folder.Get_Content();

	Update();
}

void Window::Create(string Name) {

	Current_Folder.Create(Name);

	Refresh();
}

void Window::Delete_Selection() {

	for (int i = 0; i < Selected_Files.size(); i++)
		Current_Folder.Delete(Selected_Files[i].sName);

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