#include "Map.h"

Map::Map()
{

}

Map::Map(map<string, sf::Texture> &textures, string name)
{
	name+=".tmx";
	char * xml = (char*) loadFile( name.c_str(), true );

    NLTmxMap* loadedMap = NLLoadTmxMap( xml );

	
	
	for(vector<NLTmxMapTileset*>::iterator currentTileset=loadedMap->tilesets.begin(); currentTileset!=loadedMap->tilesets.end(); currentTileset++)
	{
		//Trim filename to assets
		(*currentTileset)->filename=(*currentTileset)->filename.substr((*currentTileset)->filename.find("assets"));
		
		sf::Texture texture;
		texture.loadFromFile((*currentTileset)->filename);
		textures.insert(pair<string, sf::Texture>((*currentTileset)->filename, texture));
	}
	
	//For each layer
	for(vector<NLTmxMapLayer*>::iterator currentLayer=loadedMap->layers.begin(); currentLayer!=loadedMap->layers.end(); currentLayer++)
	{
		//For each piece of data on currentLayer
		for(int layerIndex=0; layerIndex<(*currentLayer)->width*(*currentLayer)->height; layerIndex++)
		{
			//The sprites on the current layer
			vector<sf::Sprite> layerSprites;
			for(vector<NLTmxMapTileset*>::iterator currentTileset=loadedMap->tilesets.begin(); currentTileset!=loadedMap->tilesets.end(); currentTileset++)
			{
				int currentId=(*currentLayer)->data[layerIndex];
				/*if(layerIndex%41==0)
				{
					cout << "\n" << endl;
				}
				cout << currentId;*/
				//Pixelsize of current tileset
				sf::Vector2u tilesetSize=textures[(*currentTileset)->filename].getSize();
				//How many tiles (x and y) are in the current tileset
				sf::Vector2f tileCount;
				tileCount.x=tilesetSize.x/(*currentTileset)->tileWidth;
				tileCount.y=tilesetSize.y/(*currentTileset)->tileHeight;
				
				//The tile we need is in currentTileset (tileCount.x*tileCount.y is the last id within currentTileset)
				if(currentId>=(*currentTileset)->firstGid && currentId<=tileCount.x*tileCount.y)
				{
					
					//(*currentTileset)->filename
					sf::Sprite sprite(textures[(*currentTileset)->filename]);
					
					//Position on tileset in pixel
					sf::Vector2u texturePosition;
					
									//In tiles							conversion to pixel
					texturePosition.x=((currentId-1)%(int)tileCount.x)*(*currentTileset)->tileWidth; //-2?
					texturePosition.y=((currentId-1)/(int)tileCount.x)*(*currentTileset)->tileHeight;
					
					sf::IntRect textureRect(texturePosition.x, texturePosition.y, (*currentTileset)->tileWidth, (*currentTileset)->tileHeight);
					sprite.setTextureRect(textureRect);
					
					//Similar to above
					sf::Vector2i spritePosition;
					spritePosition.x=(layerIndex%((*currentLayer)->width))*(*currentTileset)->tileWidth;
					spritePosition.y=(layerIndex/((*currentLayer)->width))*(*currentTileset)->tileHeight;
					sprite.setPosition(spritePosition.x, spritePosition.y);
					
					layerSprites.push_back(sprite);
				}
			}
			sprites_.push_back(layerSprites);
		}
	}
	
	mapSize_.x=loadedMap->width*loadedMap->tileWidth;
	mapSize_.y=loadedMap->height*loadedMap->tileHeight;
}

sf::Vector2u Map::getMapSize()
{
	return mapSize_;
}

void Map::draw(sf::RenderWindow &window)
{
	for(vector<vector<sf::Sprite>>::iterator currentLayer=sprites_.begin(); currentLayer!=sprites_.end(); currentLayer++)
	{
		for(vector<sf::Sprite>::iterator currentSprite=currentLayer->begin(); currentSprite!=currentLayer->end(); currentSprite++)
		{
			window.draw(*currentSprite);			
		}
	}
}

void* Map::loadFile( const char * filename, bool appendNull ) {
    
    FILE* f = fopen( filename, "r" );
    if ( !f ) {
        return 0;
    }
    
    fseek( f, 0, SEEK_END );
    auto length = ftell( f ) + appendNull;
    fseek( f, 0, SEEK_SET );
    
    void* buffer = malloc( length );
    fread( buffer, length, 1, f );
    fclose( f );
    
    if ( appendNull ) {
        ((char*)buffer)[ length-1 ] = 0;
    }
    
    return buffer;
}