#ifndef GUIBALANCING
#define GUIBALANCING

#include <cstdlib>
#include <sstream>
#include <map>
using namespace std;

#include <SFGUI/SFGUI.hpp>

class GuiBalancing {
	public:
		GuiBalancing();
		// Our button click handler.
		void onItemSelected();
		void onTextChanged();
		void onScaleAdjustment();
		float getScaleValue();
		void addItem(pair<string, float> item);
		map<string, float> getItems();
		//Desktop has to handle events and update in main
		sfg::Window::Ptr getWindow();
	private:
		map<string, float> items_;
		//Create everything as Ptr and call their create() functions;
		sfg::ComboBox::Ptr choice_;
		sfg::Entry::Ptr entry_;
		sfg::Scale::Ptr scale_;
		sfg::Box::Ptr box_;
		sfg::Window::Ptr window_;
};

#endif