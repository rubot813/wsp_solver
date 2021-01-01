#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#ifdef _MSVC_LANG
#include <cstring>
#endif

enum color_e {
	empty = 0,
	l_blue,
	orange,
	brown,
	grey,
	yellow,
	l_green,
	violet,
	green,
	pink,
	blue,
	red,
	d_green,
};

std::string color_to_string( color_e c );

#endif // COLOR_H
