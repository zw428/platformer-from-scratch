#pragma once

#ifndef CHUNK_PROP_H
#define CHUNK_PROP_H

class chunk_prop
{
public:
	short x;
	short y;

	bool operator==( const chunk_prop& cp ) const;
	bool operator!=( const chunk_prop& cp ) const;
};

#endif
