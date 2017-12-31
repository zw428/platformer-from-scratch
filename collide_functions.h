#ifndef COLLIDE_FUNCTIONS_H
#define COLLIDE_FUNCTIONS_H

class box;

bool box_in_box( unsigned x1, unsigned y1, unsigned w1, unsigned h1, unsigned x2, unsigned y2, unsigned w2, unsigned h2 );
bool box_in_box( box b1, box b2 );

#endif
