#ifndef ANIM_H
#define ANIM_H

#include "image.h"
#include <vector>

class anim : public image
{
public:
	anim();
	void draw();

	void clip_width( unsigned short width );
	void clip_offset( unsigned short offset );
	void frame_dur( unsigned short t );

	unsigned short clip_offset() const;
	unsigned short clip_width() const;
	unsigned short frame_dur() const;
private:
	void handle_frame_count();

	unsigned short _clip_offset;
	unsigned short _clip_width;
	unsigned short _frame_dur;

	unsigned short _frame_counter;

	unsigned short _index;
};

#endif
