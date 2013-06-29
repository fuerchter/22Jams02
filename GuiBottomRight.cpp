#include "GuiBottomRight.h"

GuiBottomRight::GuiBottomRight(sf::Vector2u windowSize) {
	preview_=sfg::Label::Create("Zombies: 0, Ghosts: 0, Godzillas: 0");
	timer_=sfg::Label::Create("2 seconds left");
	gold_=sfg::Label::Create("0 Gold");
	

	//First argument: Are new elements inserted below or to the right? Second argument: Spacing between widgets
	box_=sfg::Box::Create( sfg::Box::HORIZONTAL, 5.0f );
	//Second argument: whether button and label increase when box/window is resized
	box_->Pack( preview_, false);
	box_->Pack( timer_, false);
	box_->Pack( gold_, false);	

	//Create a window (which has a background an a titlebar, no resize!) and add the box to it. Also set the window's title.
	window_=sfg::Window::Create(sfg::Window::BACKGROUND);
	window_->SetTitle( "Hello world!" );
	window_->Add( box_ );
	
	window_->SetPosition(sf::Vector2f(windowSize.x-window_->GetRequisition().x, windowSize.y-window_->GetRequisition().y));
}

sfg::Window::Ptr GuiBottomRight::getWindow()
{
	return window_;
}

void GuiBottomRight::update(float dt, vector<int> enemyTypes, int timer, int gold)
{
	string previewString;
	previewString="Zombies: ";
	stringstream zombies;
	zombies << enemyTypes[Enemy::EnemyType::Zombie];
	previewString+=zombies.str();
	previewString+=" Ghosts: ";
	stringstream ghosts;
	ghosts << enemyTypes[Enemy::EnemyType::Ghost];
	previewString+=ghosts.str();
	previewString+=" Godzillas: ";
	stringstream godzillas;
	godzillas << enemyTypes[Enemy::EnemyType::Godzilla];
	previewString+=godzillas.str();
	preview_->SetText(previewString);

	stringstream timerString;
	timerString << timer;
	timer_->SetText(timerString.str()+ " seconds left");
	
	stringstream goldString;
	goldString << gold;
	gold_->SetText(goldString.str()+ " Gold");
}