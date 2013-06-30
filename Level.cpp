#include "Level.h"

Level::Level(map<string, sf::Texture> &textures, string name, sf::Vector2u windowSize, sfg::Desktop &desktop):
gold_(50), guiBuildingChoice_(windowSize), guiBottomRight_(windowSize)
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
		
		waves_.push(Wave(timeInSeconds, enemies));
		wave=wave->next_sibling();
	}
	
	view_=sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
	
	scrollThreshold_=8;
	scrollSpeed_=128;
	
	desktop.Add(guiBuildingChoice_.getWindow());
	desktop.Add(guiBottomRight_.getWindow());
	
	string buildingsName="assets/buildings.png";
	sf::Texture buildingsTexture;
	buildingsTexture.loadFromFile(buildingsName);
	textures.insert(pair<string, sf::Texture>(buildingsName, buildingsTexture));
	
	cursor_=sf::Sprite(textures[buildingsName]);
	cursor_.setTextureRect(sf::IntRect(Building::getTilesetPosition(Building::TownCenter).x*32, Building::getTilesetPosition(Building::TownCenter).y*32, Building::getRect(Building::TownCenter, sf::Vector2i(0, 0)).width*32, Building::getRect(Building::TownCenter, sf::Vector2i(0, 0)).height*32));
	//Half transparent preview
	cursor_.setColor(sf::Color(255, 255, 255, 122));
}

sf::FloatRect Level::getViewBounds()
{
	return sf::FloatRect(view_.getCenter().x-view_.getSize().x/2, view_.getCenter().y-view_.getSize().y/2, view_.getSize().x, view_.getSize().y);
}

void Level::update(float dt, sf::RenderWindow &window, map<string, sf::Texture> &textures)
{
	if(waves_.front().getTimeInSeconds()>0)
	{
		waves_.front().update(dt);
	}
	else
	{
		//Attack!!!
	}
	
	//cout << getViewBounds().left+getViewBounds().width << " " << getViewBounds().top+getViewBounds().height << endl;
	sf::Vector2i mousePosition=sf::Mouse::getPosition(window);
	if(mousePosition.y<=scrollThreshold_ && getViewBounds().top-scrollSpeed_*dt>0)
	{
		view_.move(0, -scrollSpeed_*dt);
	}
	if(mousePosition.y>=(int)window.getSize().y-scrollThreshold_ && getViewBounds().top+getViewBounds().height+scrollSpeed_*dt<map_.getMapSize().y)
	{
		view_.move(0, scrollSpeed_*dt);
	}
	if(mousePosition.x<=scrollThreshold_ && getViewBounds().left-scrollSpeed_*dt>0)
	{
		view_.move(-scrollSpeed_*dt, 0);
	}
	if(mousePosition.x>=(int)window.getSize().x-scrollThreshold_ && getViewBounds().left+getViewBounds().width+scrollSpeed_*dt<map_.getMapSize().x)
	{
		view_.move(scrollSpeed_*dt, 0);
	}
	
	sf::Vector2i mapSize(map_.getMap()->tileWidth, map_.getMap()->tileHeight);
	
	sf::Vector2f cursorPosition(getViewBounds().left+mousePosition.x, getViewBounds().top+mousePosition.y);
	sf::Vector2f offset((int)cursorPosition.x%mapSize.x, (int)cursorPosition.y%mapSize.y);
	cursorPosition-=offset;
	
	Building::BuildingType choice=guiBuildingChoice_.getChoice();
	cursor_.setTextureRect(sf::IntRect(Building::getTilesetPosition(choice).x*32, Building::getTilesetPosition(choice).y*32, Building::getRect(choice, sf::Vector2i(0, 0)).width*32, Building::getRect(choice, sf::Vector2i(0, 0)).height*32));
	cursor_.setPosition((int)cursorPosition.x, (int)cursorPosition.y);
	
	
	
	//If mouse is not on top of Building choice menu we can place
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !guiBuildingChoice_.getWindow()->GetAllocation().contains(mousePosition.x, mousePosition.y))
	{
		bool placable=true;
		sf::IntRect potentialRect=Building::getRect(choice, sf::Vector2i(cursorPosition.x/mapSize.x, cursorPosition.y/mapSize.y));
		for(int x=potentialRect.left; x<potentialRect.left+potentialRect.width; x++)
		{
			for(int y=potentialRect.top; y<potentialRect.top+potentialRect.height; y++)
			{
				if(map_.getMap()->layers[0]->data[(int)x+y*map_.getMap()->width]==2)
				{
					placable=false;
					break;
				}
			}
		}
		
		for(vector<Building>::iterator buildingIt=buildings_.begin(); buildingIt!=buildings_.end(); buildingIt++)
		{
			if(potentialRect.intersects(buildingIt->getRect(buildingIt->getType(), buildingIt->getPosition())))
			{
				placable=false;
				break;
			}
		}
		
		if(placable)
		{
			if(gold_>=Building::getCost(choice))
			{
				if(choice!=Building::TownCenter)
				{
					if(!buildings_.empty() && buildings_[0].getType()==Building::TownCenter)
					{
						buildings_.push_back(Building(choice, sf::Vector2i(potentialRect.left, potentialRect.top), textures));
						gold_-=Building::getCost(choice);
					}
				}
				else
				{
					//No TC exists yet
					if(buildings_.empty() || buildings_[0].getType()!=Building::TownCenter)
					{
						buildings_.insert(buildings_.begin(), Building(choice, sf::Vector2i(potentialRect.left, potentialRect.top), textures));
						gold_-=Building::getCost(choice);
					}
				}
			}
		}
	}
	
	
	//cout << mousePosition.x << " " << mousePosition.y << endl;
	
	guiBottomRight_.update(dt, waves_.front().getEnemyTypes(), waves_.front().getTimeInSeconds(), gold_);
}

void Level::draw(sf::RenderWindow &window)
{
	window.setView(view_);
	map_.draw(window);
	for(vector<Building>::iterator buildingIt=buildings_.begin(); buildingIt!=buildings_.end(); buildingIt++)
	{
		buildingIt->draw(window);
	}
	window.draw(cursor_);
}