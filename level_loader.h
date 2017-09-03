#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <string>

class level_loader
{
public:
	level_loader();

	bool load_level(std::string path);

	bool process_texture_str(std::string str);
	bool process_font_str(std::string str);
	bool process_character_str(std::string str);
	bool process_sound_str(std::string str);
	bool process_block_str(std::string str);
};

#endif