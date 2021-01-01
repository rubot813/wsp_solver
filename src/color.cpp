#include "color.h"

std::string color_to_string( color_e c ) {
	std::string str;
	switch ( c ) {
	case empty:
		str = "empty";
		break;
	case red:
		str = "red";
		break;
	case green:
		str = "green";
		break;
	case blue:
		str = "blue";
		break;
	default:
		str = "unknown. add to color_to_string";
	}
	return str;
}
