#include "level_loader.h"
#include "manager.h"
#include <fstream>
#include <sstream>
#include "block.h"
#include "player.h"
#include "npc.h"
#include "teleport_box.h"

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

		if ( buf == "map" )
		{
			std::getline(ifs,buf);
			process_map_str(buf.c_str());
		}

		if ( buf == "camera" )
		{
			std::getline(ifs,buf);
			process_camera_str(buf.c_str());
		}

		if ( buf == "trigger" )
		{
			std::getline(ifs,buf);
			process_trigger_str(buf.c_str());
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

	manager::instance()->resources.add_texture(path.c_str(),name.c_str());

	return true;
}

bool level_loader::process_sound_str(std::string str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	manager::instance()->resources.add_sound(path.c_str(),name.c_str());

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

	temp->dimens.x(std::stoi(x));
	temp->dimens.y(std::stoi(y));
	temp->dimens.w(std::stoi(w));
	temp->dimens.h(std::stoi(h));

	temp->type( block_solid );

	manager::instance()->the_map.add_object(temp);

	return true;
}

bool level_loader::process_font_str(std::string str)
{
	std::stringstream ss(str);
	std::string name;
	std::string path;
	ss >> name;
	ss >> path;

	manager::instance()->resources.add_font( path.c_str(), name.c_str() );

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
		temp->dimens.x(x_num);
		temp->dimens.y(y_num);
		manager::instance()->the_map.add_object(temp);
	}
	else if ( type == "npc" )
	{
		npc* temp = new npc;
		temp->dimens.x(x_num);
		temp->dimens.y(y_num);
		manager::instance()->the_map.add_object(temp);
	}


	return true;
}

bool level_loader::process_map_str(std::string str)
{
	std::stringstream ss(str);
	std::string x, y;

	ss >> x;
	ss >> y;

	unsigned x_num = std::stoi(x);
	unsigned y_num = std::stoi(y);

	manager::instance()->the_map.init(x_num,y_num);


	return true;
}

bool level_loader::process_camera_str(std::string str)
{
	std::stringstream ss(str);
	std::string x, y, w, h;

	ss >> x;
	ss >> y;
	ss >> w;
	ss >> h;

	SDL_Rect r;

	r.x = std::stoi(x);
	r.y = std::stoi(y);
	r.w = std::stoi(w);
	r.h = std::stoi(h);

	manager::instance()->cam.set_camera( r );


	return true;
}

bool level_loader::process_trigger_str(std::string str)
{
	std::stringstream ss(str);
	std::string type, x, y, w, h;

	ss >> type;
	ss >> x;
	ss >> y;
	ss >> w;
	ss >> h;

	int x_num = std::stoi(x);
	int y_num = std::stoi(y);
	unsigned w_num = std::stoi(w);
	unsigned h_num = std::stoi(h);

	trigger* t = 0;

	if ( type == "teleporter" )
	{
		std::string x_dest, y_dest;

		ss >> x_dest;
		ss >> y_dest;
		int x_dest_num = std::stoi(x_dest);
		int y_dest_num = std::stoi(y_dest);

		t = new teleport_box();
		dynamic_cast<teleport_box*>(t)->set_dest( x_dest_num, y_dest_num );
	}
	/*else if ( type == "death" )
	{
		t = new death_box;
	}*/
	else
	{
		return false;
	}

	t->dimens.x(x_num);
	t->dimens.y(y_num);
	t->dimens.w(w_num);
	t->dimens.h(h_num);

	manager::instance()->the_map.add_object( t );

	return true;
}
