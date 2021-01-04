#include "move.h"

// Вернет true, если ходы соответсвуют в инверсии
bool move_s::same_inverse( move_s &inv ) {
	return ( flask_id0 == inv.flask_id1 &&
	         flask_id1 == inv.flask_id0 );
}

move_s::operator==( move_s &mv) {
	return ( flask_id0 == mv.flask_id0 &&
	         flask_id1 == mv.flask_id1 );
}
