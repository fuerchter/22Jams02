#ifndef GUIBUILDINGCHOICE
#define GUIBUILDINGCHOICE

#include <SFGUI/SFGUI.hpp>

#include "Building.h"

class GuiBuildingChoice {
	public:
		GuiBuildingChoice(sf::Vector2u windowSize);
		// Our button click handler.
		//void greetButtonClick();
		Building::BuildingType getChoice();
		sfg::Window::Ptr getWindow();
	private:
		//Create everything as Ptr and call their create() functions;
		sfg::RadioButton::Ptr townCenter_;
		sfg::RadioButton::Ptr house_;
		sfg::RadioButton::Ptr wall_;
		sfg::RadioButton::Ptr turret_;
		sfg::RadioButton::Ptr bank_;
		sfg::Box::Ptr box_;
		sfg::Window::Ptr window_;
};

#endif