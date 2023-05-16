#include "Window.h"

string To_Upper(string String) {

	std::transform(String.begin(), String.end(), String.begin(), ::toupper);

	return String;
}

string Format_With_Commas(int Number) {

	string s = to_string(Number);

	int n = s.length() - 3;
	int end = (Number >= 0) ? 0 : 1;
	while (n > end) {
		s.insert(n, ",");
		n -= 3;
	}

	return s;
}

Window::Window() {

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	Initialize_Variables();
	Initialize_winMain();

	Current_Folder.Initialize_Path("C:\\Users\\TobiasEmberland\\Desktop");

	Refresh();
}

Window::~Window() {

	delete winMain;
}

void Window::Initialize_Variables() {

	winMain = nullptr;

	iMouse_X = sf::Mouse::getPosition().x;
	iMouse_Y = sf::Mouse::getPosition().y;

	font.loadFromFile("Font.ttf");
}

void Window::Initialize_winMain() {

	videoMode.height = 500;
	videoMode.width = 750;

	winMain = new sf::RenderWindow(videoMode, "Explorer", sf::Style::Default);
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

		if (event.type == sf::Event::Resized) {

			sf::FloatRect visibleArea;

			visibleArea.width = event.size.width;
			visibleArea.height = event.size.height;

			winMain->setView(sf::View(visibleArea));
		}
	}
}

void Window::Update() {

	winMain->clear(sf::Color(31, 31, 31));

	Draw_Items();

	winMain->display();
}

void Window::Refresh() {

	Current_Folder_Content = Current_Folder.Get_Content();

	Update();
}

void Window::Draw_Items() {

	for (int folder = 0; folder < Current_Folder_Content.Folders.size(); folder++) {

		string Name = Current_Folder_Content.Folders[folder];

		sf::RectangleShape rect;

		rect.setPosition(10, 10 + folder * 21);
		rect.setFillColor(sf::Color(255, 231, 145));
		rect.setSize(sf::Vector2f(10, 14));
		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color(239, 204, 75));

		winMain->draw(rect);

		sf::Text text;

		text.setFont(font);
		text.setCharacterSize(14);
		text.setFillColor(sf::Color(255, 255, 255));

		text.setPosition(27, 7 + folder * 21);
		text.setString(Name);
		winMain->draw(text);

		text.setPosition(150, 7 + folder * 21);
		text.setString("Folder");
		winMain->draw(text);

		Folder open_Folder(Current_Folder_Content.Path + "\\" + Name);

		Folder::Content open_Content = open_Folder.Get_Content();

		text.setPosition(300, 7 + folder * 21);
		text.setString(to_string(open_Content.Folders.size() + open_Content.Files.size()) + " Items");
		winMain->draw(text);
	}
	for (int file = 0; file < Current_Folder_Content.Files.size(); file++) {

		string Name = Current_Folder_Content.Files[file];

		sf::RectangleShape rect;

		rect.setPosition(10, 10 + (Current_Folder_Content.Folders.size() + file) * 21);
		rect.setFillColor(sf::Color(248, 248, 248));
		rect.setSize(sf::Vector2f(10, 14));
		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color(148, 148, 148));

		winMain->draw(rect);

		sf::Text text;

		text.setFont(font);
		text.setCharacterSize(14);
		text.setFillColor(sf::Color(255, 255, 255));

		string Name2 = Name;

		if (Name.length() > 13)
			Name2 = Name.substr(0, 13) + "...";

		text.setPosition(27, 7 + (Current_Folder_Content.Folders.size() + file) * 21);
		text.setString(Name2);
		winMain->draw(text);

		text.setPosition(150, 7 + (Current_Folder_Content.Folders.size() + file) * 21);
		text.setString(To_Upper(Name.substr(Name.find_last_of(".") + 1)) + " File");
		if (Name.find(".") == string::npos)
			text.setString("File");
		winMain->draw(text);

		text.setPosition(300, 7 + (Current_Folder_Content.Folders.size() + file) * 21);
		text.setString(Format_With_Commas(filesystem::file_size(filesystem::path(Current_Folder_Content.Path + "\\" + Name))) + " Bytes");
		winMain->draw(text);
	}
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