#include "GuiBottomRight.h"

GuiBottomRight::GuiBottomRight(sf::Vector2u windowSize) {
	preview_=sfg::Label::Create("");
	timer_=sfg::Label::Create("");
	goldTimer_=sfg::Label::Create("");
	gold_=sfg::Label::Create("");
	

	//First argument: Are new elements inserted below or to the right? Second argument: Spacing between widgets
	waveBox_=sfg::Box::Create( sfg::Box::HORIZONTAL, 5.0f );
	goldBox_=sfg::Box::Create( sfg::Box::HORIZONTAL, 5.0f );
	box_=sfg::Box::Create( sfg::Box::VERTICAL, 5.0f );
	//Second argument: whether button and label increase when box/window is resized
	waveBox_->Pack( timer_, false);
	waveBox_->Pack( preview_, false);
	goldBox_->Pack( goldTimer_, false);
	goldBox_->Pack( gold_, false);
	box_->Pack( waveBox_, false);
	box_->Pack( goldBox_, false);

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

void GuiBottomRight::update(float dt, sf::RenderWindow &window, vector<int> enemyTypes, int timer, int goldTimer, int gold)
{
	window_->SetPosition(sf::Vector2f(window.getSize().x-window_->GetRequisition().x, window.getSize().y-window_->GetRequisition().y));
	
	string previewString;
	previewString="";
	stringstream zombies;
	zombies << enemyTypes[Enemy::EnemyType::Zombie];
	previewString+=zombies.str();
	previewString+=" Zombies ";
	stringstream ghosts;
	ghosts << enemyTypes[Enemy::EnemyType::Ghost];
	previewString+=ghosts.str();
	previewString+=" Ghosts ";
	stringstream godzillas;
	godzillas << enemyTypes[Enemy::EnemyType::Godzilla];
	previewString+=godzillas.str();
	previewString+=" Godzillas";
	preview_->SetText(previewString);

	stringstream timerString;
	timerString << timer;
	timer_->SetText("Next wave: " +timerString.str()+ " seconds |");
	
	stringstream goldTimerString;
	goldTimerString << goldTimer;
	goldTimer_->SetText("More Gold: " +goldTimerString.str()+ " seconds |");
	
	stringstream goldString;
	goldString << gold;
	gold_->SetText(goldString.str()+ " Gold");
}