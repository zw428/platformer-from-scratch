#pragma once

#ifndef ANIM_H
#define ANIM_H

#include "image.h"
#include <vector>

class anim : public image
{
public:
	anim();
	void draw();

	unsigned short clip_width() const;
	void clip_width( unsigned short width );
	unsigned short clip_offset() const;
	void clip_offset( unsigned short offset );

	void add_frame_dur( unsigned short t );

	unsigned short num_frames() const;

	bool at_end() const;
	void reset();
private:
	void handle_frame_count();

	unsigned short _clip_offset;
	unsigned short _clip_width;

	std::vector<unsigned short> _frame_durs;

	unsigned short _frame_counter;

	unsigned short _index;
};

#endif
