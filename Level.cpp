#include "Level.h"

Level::Level(map<string, sf::Texture> &textures, string name)
{
	string folderName="levels/" +name;
	map_=Map(textures, folderName+ "/level");
	
	file<> xmlFile((folderName+ "/waves.xml").c_str());
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<> *waves=doc.first_node();
	xml_node<> *wave=waves->first_node();
	while(wave)
	{
		int timeInSeconds=atoi(wave->first_attribute("timeInSeconds")->value());
		int zombies=atoi(wave->first_attribute("zombies")->value());
		int ghosts=atoi(wave->first_attribute("ghosts")->value());
		int godzillas=atoi(wave->first_attribute("godzillas")->value());
		vector<int> enemies;
		enemies.push_back(zombies);
		enemies.push_back(ghosts);
		enemies.push_back(godzillas);
		
		waves_.push_back(Wave(timeInSeconds, enemies));
		wave=wave->next_sibling();
	}
}

void Level::draw(sf::RenderWindow &window)
{
	map_.draw(window);
}