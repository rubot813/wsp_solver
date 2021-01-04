#ifndef MOVE_H
#define MOVE_H

// Класс описывает один ход
class move_s {
public:
	bool same_inverse( move_s &inv );
	operator==( move_s &mv);

	// Что и куда переместить
	unsigned flask_id0, flask_id1;
	// private?

};

#endif // MOVE_H
