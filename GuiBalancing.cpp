#include "GuiBalancing.h"

GuiBalancing::GuiBalancing() {
	choice_=sfg::ComboBox::Create();
	choice_->GetSignal(sfg::ComboBox::OnSelect).Connect(&GuiBalancing::onItemSelected, this);

	entry_=sfg::Entry::Create();
	entry_->GetSignal(sfg::Entry::OnTextChanged).Connect(&GuiBalancing::onTextChanged, this);
	
	scale_=sfg::Scale::Create(0, 256, 0.25);
	scale_->GetAdjustment()->GetSignal(sfg::Adjustment::OnChange).Connect(&GuiBalancing::onScaleAdjustment, this);
	
	//First argument: Are new elements inserted below or to the right? Second argument: Spacing between widgets
	box_=sfg::Box::Create( sfg::Box::VERTICAL, 5.0f );
	//Second argument: whether button and label increase when box/window is resized
	box_->Pack(choice_);
	box_->Pack(entry_);
	box_->Pack(scale_);

	//Create a window (which has a background an a titlebar, no resize!) and add the box to it. Also set the window's title.
	window_=sfg::Window::Create(/*sfg::Window::BACKGROUND | sfg::Window::TITLEBAR*/);
	window_->SetTitle( "Hello world!" );
	window_->Add( box_ );
	window_->SetRequisition(sf::Vector2f(300, 150));
}

void GuiBalancing::onItemSelected()
{
	scale_->SetValue(items_[choice_->GetSelectedText()]);
}

void GuiBalancing::onTextChanged()
{
	string text=entry_->GetText();
	float value=atof(text.c_str());
	scale_->SetValue(value);
	
	items_[choice_->GetSelectedText()]=value;
}

void GuiBalancing::onScaleAdjustment()
{
	float value=scale_->GetValue();
	stringstream text;
	text << value;
	entry_->SetText(text.str());
	
	items_[choice_->GetSelectedText()]=value;
}

float GuiBalancing::getScaleValue()
{
	return scale_->GetValue();
}

void GuiBalancing::addItem(pair<string, float> item)
{
	items_.insert(item);
	choice_->AppendItem(item.first);
}

map<string, float> GuiBalancing::getItems()
{
	return items_;
}

sfg::Window::Ptr GuiBalancing::getWindow()
{
	return window_;
}