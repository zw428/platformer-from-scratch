#include "level_loader.h"
#include "manager.h"
#include <fstream>
#include <sstream>
#include "block.h"
#include "player.h"
#include "npc.h"

level_loader::level_loader()
{
}

bool level_loader::load_level(std::string path)
{
	std::string full_path = manager::instance()->data_path() + path;;

	std::string buf;
	std::ifstream ifs(full_path);

	while ( ifs >> buf )
	{
		if ( buf == "texture" )
		{
			std::getline(ifs,buf);
			process_texture_str(buf.c_str());
		}

		if ( buf == "sound" )
		{
			std::getline(ifs,buf);
			process_sound_str(buf.c_str());
		}

		if ( buf == "character" )
		{
			std::getline(ifs,buf);
			process_character_str(buf.c_str());
		}

		if ( buf == "block" )
		{
			std::getline(ifs,buf);
			process_block_str(buf.c_str());
		}

		if ( buf == "font" )
		{
			std::getline(ifs,buf);
			process_font_str(buf.c_str());
		}
	}

	ifs.close();

	return true;
}

bool level_loader::process_texture_str(std::string str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	manager::instance()->add_texture(path.c_str(),name.c_str());

	return true;
}

bool level_loader::process_sound_str(std::string str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	manager::instance()->add_sound(path.c_str(),name.c_str());

	return true;
}

bool level_loader::process_block_str(std::string str)
{
	std::stringstream ss(str);
	std::string image_name, x, y, w, h;

	ss >> image_name;
	ss >> x;
	ss >> y;
	ss >> w;
	ss >> h;

	block* temp = new block;

	temp->x(std::stoi(x));
	temp->y(std::stoi(y));
	temp->w(std::stoi(w));
	temp->h(std::stoi(h));

	temp->type( solid );

	manager::instance()->get_map()->add_object(temp);

	return true;
}

bool level_loader::process_font_str(std::string str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	manager::instance()->add_font( path.c_str(), name.c_str() );

	return true;
}

bool level_loader::process_character_str(std::string str)
{
	std::stringstream ss(str);
	std::string type, image_name, x, y;

	ss >> type;
	ss >> x;
	ss >> y;

	unsigned short x_num = std::stoi(x);
	unsigned short y_num = std::stoi(y);

	if ( type == "player" )
	{
		player* temp = new player;
		temp->x(x_num);
		temp->y(y_num);
		manager::instance()->get_map()->add_object(dynamic_cast<object*>(temp));
	}
	else if ( type == "npc" )
	{
		npc* temp = new npc;
		temp->dest(x_num,y_num);
		temp->x(x_num);
		temp->y(y_num);
		manager::instance()->get_map()->add_object(dynamic_cast<object*>(temp));
	}


	return true;
}
