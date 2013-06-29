#ifndef GUIBOTTOMRIGHT
#define GUIBOTTOMRIGHT

#include <sstream>
using namespace std;

#include <SFGUI/SFGUI.hpp>

#include "Enemy.h"

class GuiBottomRight {
	public:
		GuiBottomRight(sf::Vector2u windowSize);
		// Our button click handler.
		//void greetButtonClick();
		//Building::BuildingType getChoice();
		sfg::Window::Ptr getWindow();
		void update(float dt, vector<int> enemyTypes, int timer, int gold);
	private:
		//Create everything as Ptr and call their create() functions;
		sfg::Label::Ptr preview_;
		sfg::Label::Ptr timer_;
		sfg::Label::Ptr gold_;
		sfg::Box::Ptr box_;
		sfg::Window::Ptr window_;
};

#endif