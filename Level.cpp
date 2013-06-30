#include "Level.h"

Level::Level(map<string, sf::Texture> &textures, string name, sf::Vector2u windowSize, sfg::Desktop &desktop):
guiBuildingChoice_(windowSize), guiBottomRight_(windowSize)
{
	string folderName="levels/" +name;
	map_=Map(textures, folderName+ "/level");
	
	//Loading the waves from the level file into waves_
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
	
	//Balancing stuff!
	gold_=50;
	scrollThreshold_=8;
	scrollSpeed_=128;
	incomeClockTime_=30;
	
	desktop.Add(guiBuildingChoice_.getWindow());
	desktop.Add(guiBottomRight_.getWindow());
	
	//Load the building tileset
	string buildingsName="assets/buildings.png";
	sf::Texture buildingsTexture;
	buildingsTexture.loadFromFile(buildingsName);
	textures.insert(pair<string, sf::Texture>(buildingsName, buildingsTexture));
	
	cursor_=sf::Sprite(textures[buildingsName]);
	
	//Half transparent preview
	cursor_.setColor(sf::Color(255, 255, 255, 122));
}

sf::FloatRect Level::getViewBounds()
{
	return sf::FloatRect(view_.getCenter().x-view_.getSize().x/2, view_.getCenter().y-view_.getSize().y/2, view_.getSize().x, view_.getSize().y);
}

void Level::update(float dt, sf::RenderWindow &window, map<string, sf::Texture> &textures)
{
	//Count down current wave timer
	if(waves_.front().getTimeInSeconds()>0)
	{
		waves_.front().update(dt);
	}
	else
	{
		//Attack!!!
	}
	
	//Scroll if mouse is scrollThreshold_ pixels from the screen edge
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
	
	sf::Vector2i tileSize(map_.getMap()->tileWidth, map_.getMap()->tileHeight);
	
	//Relative to map
	sf::Vector2i cursorPosition(getViewBounds().left+mousePosition.x, getViewBounds().top+mousePosition.y);
	sf::Vector2i offset(cursorPosition.x%tileSize.x, cursorPosition.y%tileSize.y);
	cursorPosition-=offset;
	
	Building::BuildingType choice=guiBuildingChoice_.getChoice();
	//Getting current building choice from tileset
	cursor_.setTextureRect(sf::IntRect(
	Building::getTilesetPosition(choice).x*tileSize.x,
	Building::getTilesetPosition(choice).y*tileSize.y,
	Building::getRect(choice, sf::Vector2i(0, 0)).width*tileSize.x,
	Building::getRect(choice, sf::Vector2i(0, 0)).height*tileSize.y));
	
	cursor_.setPosition(cursorPosition.x, cursorPosition.y);
	
	
	
	//If mouse is not on top of Building choice menu we can place
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !guiBuildingChoice_.getWindow()->GetAllocation().contains(mousePosition.x, mousePosition.y))
	{
		bool placable=true;
		
		//Placing on top of a stone?
		int stoneIndex=2;
		sf::IntRect potentialRect=Building::getRect(choice, sf::Vector2i(cursorPosition.x/tileSize.x, cursorPosition.y/tileSize.y));
		for(int x=potentialRect.left; x<potentialRect.left+potentialRect.width; x++)
		{
			for(int y=potentialRect.top; y<potentialRect.top+potentialRect.height; y++)
			{
				//Converts x, y position to onedimensional using the map pixel width
				int absolutePosition=x+y*map_.getMap()->width;
				if(map_.getMap()->layers[0]->data[absolutePosition]==stoneIndex)
				{
					placable=false;
					break;
				}
			}
		}
		
		//Placing on top of a building?
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
			//Have the money?
			if(gold_>=Building::getCost(choice))
			{
				if(choice!=Building::TownCenter)
				{
					//We want to build something other than a TC so does a TC exist?
					if(!buildings_.empty() && buildings_[0].getType()==Building::TownCenter)
					{
						buildings_.push_back(Building(choice, sf::Vector2i(potentialRect.left, potentialRect.top), textures, tileSize));
						gold_-=Building::getCost(choice);
					}
					else
					{
						cout << "You have to build a Town Center first!" << endl;
					}
				}
				else
				{
					//We want to build a TC so does a TC exist already?
					if(buildings_.empty() || buildings_[0].getType()!=Building::TownCenter)
					{
						buildings_.insert(buildings_.begin(), Building(choice, sf::Vector2i(potentialRect.left, potentialRect.top), textures, tileSize));
						gold_-=Building::getCost(choice);
					}
					else
					{
						cout << "A Town Center already exists!" << endl;
					}
				}
			}
			else
			{
				cout << "More Gold is required!" << endl;
			}
		}
		else
		{
			cout << "No building space!" << endl;
		}
	}
	
	//Updating information gui
	guiBottomRight_.update(dt, waves_.front().getEnemyTypes(), waves_.front().getTimeInSeconds(), gold_);
	
	
	if(incomeClock_.getElapsedTime().asSeconds()>=incomeClockTime_)
	{
		int income=0;
		for(vector<Building>::iterator buildingIt=buildings_.begin(); buildingIt!=buildings_.end(); buildingIt++)
		{
			income+=buildingIt->getMoney();
		}
		gold_+=income;
		incomeClock_.restart();
	}
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