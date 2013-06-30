#include "GuiBuildingChoice.h"

GuiBuildingChoice::GuiBuildingChoice(sf::Vector2u windowSize) {
	townCenter_=sfg::RadioButton::Create("TownCenter");
	townCenter_->SetActive(true);
	house_=sfg::RadioButton::Create("House", townCenter_->GetGroup());
	wall_=sfg::RadioButton::Create("Wall", townCenter_->GetGroup());
	turret_=sfg::RadioButton::Create("Turret", townCenter_->GetGroup());
	bank_=sfg::RadioButton::Create("Bank", townCenter_->GetGroup());
	
	//First argument: Are new elements inserted below or to the right? Second argument: Spacing between widgets
	box_=sfg::Box::Create( sfg::Box::VERTICAL, 5.0f );
	//Second argument: whether button and label increase when box/window is resized
	box_->Pack( townCenter_, false);
	box_->Pack( house_, false);
	box_->Pack( wall_, false);
	box_->Pack( turret_, false);
	box_->Pack( bank_, false);
	

	//Create a window (which has a background an a titlebar, no resize!) and add the box to it. Also set the window's title.
	window_=sfg::Window::Create(sfg::Window::BACKGROUND);
	window_->SetTitle( "Hello world!" );
	window_->Add( box_ );
	
	window_->SetPosition(sf::Vector2f(0, windowSize.y-window_->GetRequisition().y));
}

Building::BuildingType GuiBuildingChoice::getChoice()
{
	if(townCenter_->IsActive())
	{
		return Building::TownCenter;
	}
	else if(house_->IsActive())
	{
		return Building::House;
	}
	else if(wall_->IsActive())
	{
		return Building::Wall;
	}
	else if(turret_->IsActive())
	{
		return Building::Turret;
	}
	else if(bank_->IsActive())
	{
		return Building::Bank;
	}
	return Building::None;
}

sfg::Window::Ptr GuiBuildingChoice::getWindow()
{
	return window_;
}