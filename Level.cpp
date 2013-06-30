#include "Level.h"

Level::Level(map<string, sf::Texture> &textures, map<string, sf::SoundBuffer> &sounds, string name, sf::Vector2u windowSize, sfg::Desktop &desktop):
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
		
		waves_.push_back(Wave(timeInSeconds, enemies));
		
		wave=wave->next_sibling();
	}
	
	view_=sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
	
	BuildingStats townCenter;
	townCenter.cost=10;
	townCenter.moneyPerMinute=5;
	townCenter.damagePerSecond=0;
	townCenter.maxHp=100;
	townCenter.slowing=0;
	
	BuildingStats house;
	house.cost=10;
	house.moneyPerMinute=10;
	house.damagePerSecond=0;
	house.maxHp=100;
	house.slowing=0;
	
	BuildingStats wall;
	wall.cost=10;
	wall.moneyPerMinute=5;
	wall.damagePerSecond=0;
	wall.maxHp=100;
	wall.slowing=0.5;
	
	BuildingStats turret;
	turret.cost=10;
	turret.moneyPerMinute=5;
	turret.damagePerSecond=5;
	turret.maxHp=100;
	turret.slowing=0;
	
	BuildingStats bank;
	bank.cost=20;
	bank.moneyPerMinute=20;
	bank.damagePerSecond=0;
	bank.maxHp=100;
	bank.slowing=0;
	
	buildingStats_.insert(pair<Building::BuildingType, BuildingStats>(Building::TownCenter, townCenter));
	buildingStats_.insert(pair<Building::BuildingType, BuildingStats>(Building::House, house));
	buildingStats_.insert(pair<Building::BuildingType, BuildingStats>(Building::Wall, wall));
	buildingStats_.insert(pair<Building::BuildingType, BuildingStats>(Building::Turret, turret));
	buildingStats_.insert(pair<Building::BuildingType, BuildingStats>(Building::Bank, bank));
	
	EnemyStats zombie;
	zombie.hp=100;
	zombie.secondsPerHit=0.5;
	zombie.damagePerHit=2;
	
	EnemyStats ghost;
	ghost.hp=60;
	ghost.secondsPerHit=2;
	ghost.damagePerHit=20;
	
	EnemyStats godzilla;
	godzilla.hp=150;
	godzilla.secondsPerHit=4;
	godzilla.damagePerHit=25;
	
	enemyStats_.insert(pair<Enemy::EnemyType, EnemyStats>(Enemy::Zombie, zombie));
	enemyStats_.insert(pair<Enemy::EnemyType, EnemyStats>(Enemy::Ghost, ghost));
	enemyStats_.insert(pair<Enemy::EnemyType, EnemyStats>(Enemy::Godzilla, godzilla));
	
	//Balancing stuff!
	gold_=50;
	scrollThreshold_=8;
	scrollSpeed_=128;
	incomeClockTime_=15;
	baseDamage_=20;
	
	desktop.Add(guiBuildingChoice_.getWindow());
	desktop.Add(guiBottomRight_.getWindow());
	desktop.Add(guiBalancing_.getWindow());
	desktop.Add(guiBuildingBalancing_.getWindow());
	desktop.Add(guiEnemyBalancing_.getWindow());
	
	guiBalancing_.addItem(make_pair("scrollThreshold", scrollThreshold_));
	guiBalancing_.addItem(make_pair("scrollSpeed", scrollSpeed_));
	guiBalancing_.addItem(make_pair("incomeClockTime", incomeClockTime_));
	guiBalancing_.addItem(make_pair("baseDamage", baseDamage_));
	
	guiBuildingBalancing_.addItem(make_pair("TownCenter cost", buildingStats_[Building::TownCenter].cost));
	guiBuildingBalancing_.addItem(make_pair("TownCenter moneyPerMinute", buildingStats_[Building::TownCenter].moneyPerMinute));
	guiBuildingBalancing_.addItem(make_pair("TownCenter damagePerSecond", buildingStats_[Building::TownCenter].damagePerSecond));
	guiBuildingBalancing_.addItem(make_pair("TownCenter maxHp", buildingStats_[Building::TownCenter].maxHp));
	guiBuildingBalancing_.addItem(make_pair("TownCenter slowing", buildingStats_[Building::TownCenter].slowing));
	
	guiBuildingBalancing_.addItem(make_pair("House cost", buildingStats_[Building::House].cost));
	guiBuildingBalancing_.addItem(make_pair("House moneyPerMinute", buildingStats_[Building::House].moneyPerMinute));
	guiBuildingBalancing_.addItem(make_pair("House damagePerSecond", buildingStats_[Building::House].damagePerSecond));
	guiBuildingBalancing_.addItem(make_pair("House maxHp", buildingStats_[Building::House].maxHp));
	guiBuildingBalancing_.addItem(make_pair("House slowing", buildingStats_[Building::House].slowing));
	
	guiBuildingBalancing_.addItem(make_pair("Wall cost", buildingStats_[Building::Wall].cost));
	guiBuildingBalancing_.addItem(make_pair("Wall moneyPerMinute", buildingStats_[Building::Wall].moneyPerMinute));
	guiBuildingBalancing_.addItem(make_pair("Wall damagePerSecond", buildingStats_[Building::Wall].damagePerSecond));
	guiBuildingBalancing_.addItem(make_pair("Wall maxHp", buildingStats_[Building::Wall].maxHp));
	guiBuildingBalancing_.addItem(make_pair("Wall slowing", buildingStats_[Building::Wall].slowing));
	
	guiBuildingBalancing_.addItem(make_pair("Turret cost", buildingStats_[Building::Turret].cost));
	guiBuildingBalancing_.addItem(make_pair("Turret moneyPerMinute", buildingStats_[Building::Turret].moneyPerMinute));
	guiBuildingBalancing_.addItem(make_pair("Turret damagePerSecond", buildingStats_[Building::Turret].damagePerSecond));
	guiBuildingBalancing_.addItem(make_pair("Turret maxHp", buildingStats_[Building::Turret].maxHp));
	guiBuildingBalancing_.addItem(make_pair("Turret slowing", buildingStats_[Building::Turret].slowing));
	
	guiBuildingBalancing_.addItem(make_pair("Bank cost", buildingStats_[Building::Bank].cost));
	guiBuildingBalancing_.addItem(make_pair("Bank moneyPerMinute", buildingStats_[Building::Bank].moneyPerMinute));
	guiBuildingBalancing_.addItem(make_pair("Bank damagePerSecond", buildingStats_[Building::Bank].damagePerSecond));
	guiBuildingBalancing_.addItem(make_pair("Bank maxHp", buildingStats_[Building::Bank].maxHp));
	guiBuildingBalancing_.addItem(make_pair("Bank slowing", buildingStats_[Building::Bank].slowing));
	
	guiEnemyBalancing_.addItem(make_pair("Zombie hp", enemyStats_[Enemy::Zombie].hp));
	guiEnemyBalancing_.addItem(make_pair("Zombie secondsPerHit", enemyStats_[Enemy::Zombie].secondsPerHit));
	guiEnemyBalancing_.addItem(make_pair("Zombie damagePerHit", enemyStats_[Enemy::Zombie].damagePerHit));
	
	guiEnemyBalancing_.addItem(make_pair("Ghost hp", enemyStats_[Enemy::Ghost].hp));
	guiEnemyBalancing_.addItem(make_pair("Ghost secondsPerHit", enemyStats_[Enemy::Ghost].secondsPerHit));
	guiEnemyBalancing_.addItem(make_pair("Ghost damagePerHit", enemyStats_[Enemy::Ghost].damagePerHit));
	
	guiEnemyBalancing_.addItem(make_pair("Godzilla hp", enemyStats_[Enemy::Godzilla].hp));
	guiEnemyBalancing_.addItem(make_pair("Godzilla secondsPerHit", enemyStats_[Enemy::Godzilla].secondsPerHit));
	guiEnemyBalancing_.addItem(make_pair("Godzilla damagePerHit", enemyStats_[Enemy::Godzilla].damagePerHit));
	
	//Load the building tileset
	string buildingsName="assets/buildings.png";
	sf::Texture buildingsTexture;
	buildingsTexture.loadFromFile(buildingsName);
	textures.insert(pair<string, sf::Texture>(buildingsName, buildingsTexture));
	
	cursor_=sf::Sprite(textures[buildingsName]);
	
	//Half transparent preview
	cursor_.setColor(sf::Color(255, 255, 255, 122));
	
	string waveDefeatedName="assets/waveDefeated.wav";
	sf::SoundBuffer waveDefeated;
	waveDefeated.loadFromFile(waveDefeatedName);
	sounds.insert(pair<string, sf::SoundBuffer>(waveDefeatedName, waveDefeated));
	waveDefeated_.setBuffer(sounds[waveDefeatedName]);
	
	string incomeName="assets/income.wav";
	sf::SoundBuffer income;
	income.loadFromFile(incomeName);
	sounds.insert(pair<string, sf::SoundBuffer>(incomeName, income));
	income_.setBuffer(sounds[incomeName]);
}

sf::FloatRect Level::getViewBounds()
{
	return sf::FloatRect(view_.getCenter().x-view_.getSize().x/2, view_.getCenter().y-view_.getSize().y/2, view_.getSize().x, view_.getSize().y);
}

void Level::update(float dt, sf::RenderWindow &window, map<string, sf::Texture> &textures)
{
	map<string, float> balancing=guiBalancing_.getItems();
	scrollThreshold_=balancing["scrollThreshold"];
	scrollSpeed_=balancing["scrollSpeed"];
	incomeClockTime_=balancing["incomeClockTime"];
	baseDamage_=balancing["baseDamage"];
	
	map<string, float> buildingBalancing=guiBuildingBalancing_.getItems();
	buildingStats_[Building::TownCenter].cost=buildingBalancing["TownCenter cost"];
	buildingStats_[Building::TownCenter].moneyPerMinute=buildingBalancing["TownCenter moneyPerMinute"];
	buildingStats_[Building::TownCenter].damagePerSecond=buildingBalancing["TownCenter damagePerSecond"];
	buildingStats_[Building::TownCenter].maxHp=buildingBalancing["TownCenter maxHp"];
	buildingStats_[Building::TownCenter].slowing=buildingBalancing["TownCenter slowing"];
	
	buildingStats_[Building::House].cost=buildingBalancing["House cost"];
	buildingStats_[Building::House].moneyPerMinute=buildingBalancing["House moneyPerMinute"];
	buildingStats_[Building::House].damagePerSecond=buildingBalancing["House damagePerSecond"];
	buildingStats_[Building::House].maxHp=buildingBalancing["House maxHp"];
	buildingStats_[Building::House].slowing=buildingBalancing["House slowing"];
	
	buildingStats_[Building::Wall].cost=buildingBalancing["Wall cost"];
	buildingStats_[Building::Wall].moneyPerMinute=buildingBalancing["Wall moneyPerMinute"];
	buildingStats_[Building::Wall].damagePerSecond=buildingBalancing["Wall damagePerSecond"];
	buildingStats_[Building::Wall].maxHp=buildingBalancing["Wall maxHp"];
	buildingStats_[Building::Wall].slowing=buildingBalancing["Wall slowing"];
	
	buildingStats_[Building::Turret].cost=buildingBalancing["Turret cost"];
	buildingStats_[Building::Turret].moneyPerMinute=buildingBalancing["Turret moneyPerMinute"];
	buildingStats_[Building::Turret].damagePerSecond=buildingBalancing["Turret damagePerSecond"];
	buildingStats_[Building::Turret].maxHp=buildingBalancing["Turret maxHp"];
	buildingStats_[Building::Turret].slowing=buildingBalancing["Turret slowing"];
	
	buildingStats_[Building::Bank].cost=buildingBalancing["Bank cost"];
	buildingStats_[Building::Bank].moneyPerMinute=buildingBalancing["Bank moneyPerMinute"];
	buildingStats_[Building::Bank].damagePerSecond=buildingBalancing["Bank damagePerSecond"];
	buildingStats_[Building::Bank].maxHp=buildingBalancing["Bank maxHp"];
	buildingStats_[Building::Bank].slowing=buildingBalancing["Bank slowing"];
	
	map<string, float> enemyBalancing=guiEnemyBalancing_.getItems();
	enemyStats_[Enemy::Zombie].hp=enemyBalancing["Zombie hp"];
	enemyStats_[Enemy::Zombie].secondsPerHit=enemyBalancing["Zombie secondsPerHit"];
	enemyStats_[Enemy::Zombie].damagePerHit=enemyBalancing["Zombie damagePerHit"];
	
	enemyStats_[Enemy::Ghost].hp=enemyBalancing["Ghost hp"];
	enemyStats_[Enemy::Ghost].secondsPerHit=enemyBalancing["Ghost secondsPerHit"];
	enemyStats_[Enemy::Ghost].damagePerHit=enemyBalancing["Ghost damagePerHit"];
	
	enemyStats_[Enemy::Godzilla].hp=enemyBalancing["Godzilla hp"];
	enemyStats_[Enemy::Godzilla].secondsPerHit=enemyBalancing["Godzilla secondsPerHit"];
	enemyStats_[Enemy::Godzilla].damagePerHit=enemyBalancing["Godzilla damagePerHit"];
	
	for(vector<Wave>::iterator waveIt=waves_.begin(); waveIt!=waves_.end(); waveIt++)
	{
		if(waveIt==waves_.begin())
		{
			waveIt->changeEnemyStats(enemyStats_, true);
		}
		else
		{
			waveIt->changeEnemyStats(enemyStats_);
		}
	}
	
	for(vector<Building>::iterator buildingIt=buildings_.begin(); buildingIt!=buildings_.end(); buildingIt++)
	{
		buildingIt->setMoney(buildingStats_[buildingIt->getType()].moneyPerMinute);
		buildingIt->setDamagePerSecond(buildingStats_[buildingIt->getType()].damagePerSecond);
		buildingIt->setSlowing(buildingStats_[buildingIt->getType()].slowing);
	}

	
	int incomeTimeLeft=incomeClockTime_-incomeClock_.getElapsedTime().asSeconds();
	if(incomeTimeLeft<=0)
	{
		int income=0;
		for(vector<Building>::iterator buildingIt=buildings_.begin(); buildingIt!=buildings_.end(); buildingIt++)
		{
			income+=buildingIt->getMoney();
		}
		if(income>0)
		{
			income_.play();
			gold_+=income;
		}
		incomeClock_.restart();
	}

	if(!waves_.empty())
	{
		//Updating information gui
		guiBottomRight_.update(dt, window, waves_[0].getEnemyTypes(), waves_[0].getTimeInSeconds(), incomeTimeLeft, gold_);
		
		//Count down current wave timer
		if(waves_[0].getTimeInSeconds()>0)
		{
			waves_[0].update(dt);
		}
		else
		{
			//Getting building damage and slowing
			int totalDmgPerSec=baseDamage_;
			int totalSlowing=0;
			for(vector<Building>::iterator buildingIt=buildings_.begin(); buildingIt!=buildings_.end(); buildingIt++)
			{
				totalDmgPerSec+=buildingIt->getDamagePerSecond();
				totalSlowing+=buildingIt->getSlowing();
			}
			
			int buildingDamage=waves_[0].update(dt, totalDmgPerSec, totalSlowing);
			
			//Reducing building HP
			for(vector<Building>::iterator buildingIt=buildings_.begin(); buildingIt!=buildings_.end(); buildingIt++)
			{
				if(buildingDamage>0)
				{
					//cout << "Building HP: " << buildingIt->decreaseHp(0) << endl;
					if(buildingIt->decreaseHp(buildingDamage)<=0)
					{
						buildings_.erase(buildingIt);
						buildingIt--;
					}
				}
			}
			if(waves_[0].getEnemies().empty())
			{
				waveDefeated_.play();
				waves_.erase(waves_.begin());
			}
			
			if(buildings_.empty())
			{
				cout << "lose" << endl;
			}
		}
	}
	else
	{
		cout << "win" << endl;
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
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
	!guiBuildingChoice_.getWindow()->GetAllocation().contains(mousePosition.x, mousePosition.y) &&
	!guiBalancing_.getWindow()->GetAllocation().contains(mousePosition.x, mousePosition.y) &&
	!guiBuildingBalancing_.getWindow()->GetAllocation().contains(mousePosition.x, mousePosition.y) &&
	!guiEnemyBalancing_.getWindow()->GetAllocation().contains(mousePosition.x, mousePosition.y))
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
			if(gold_>=buildingStats_[choice].cost)
			{
				if(choice!=Building::TownCenter)
				{
					//We want to build something other than a TC so does a TC exist?
					if(!buildings_.empty() && buildings_[0].getType()==Building::TownCenter)
					{
						buildings_.push_back(Building(choice, sf::Vector2i(potentialRect.left, potentialRect.top), textures, tileSize, buildingStats_[choice]));
						gold_-=buildingStats_[choice].cost;
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
						buildings_.insert(buildings_.begin(), Building(choice, sf::Vector2i(potentialRect.left, potentialRect.top), textures, tileSize, buildingStats_[choice]));
						gold_-=buildingStats_[choice].cost;
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