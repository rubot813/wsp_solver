#include "flask.h"

flask_c::flask_c( color_e *colors ) {
	for ( unsigned i = 0; i < SLOT_COUNT; i++ )
		_color[ i ] = colors[ i ];
}

bool flask_c::is_empty( void ) {
	bool emp = 1;
	for ( unsigned i = 0; i < SLOT_COUNT; i++ )
		if ( _color[ i ] != empty ) {
			emp = 0;
			break;
		}

	return emp;
}

// Количество свободных слотов
unsigned flask_c::free_count( void ) {
	unsigned cnt = 0;
	for ( unsigned i = SLOT_COUNT - 1; i >= 0; i-- ) {
		if ( _color[ i ] == empty )
			cnt++;
		else
			break;
	}
	return cnt;
}

// Возвращает верхний цвет
// empty если фласка пуста
color_e flask_c::upper_color( void ) {
	color_e c = empty;
	for ( signed i = SLOT_COUNT - 1; i >= 0; i-- )
		if ( _color[ i ] != empty ) {
			c = _color[ i ];
			break;
		}
	return c;
}

// Возвращает количество элементов, которые можно перелить за ход
unsigned flask_c::unfill_count( void ) {
	unsigned cntr = 0;
	color_e up_color = upper_color( );  // Верхний цвет

	// Переработать, чтобы не было двух return
	if ( up_color == empty )
		return 0;

	// Идем сверху вниз и ищем upper_color цвет
	for ( signed i = SLOT_COUNT - 1; i >= 0; i-- ) {
		// Пропуск всех empty
		if ( _color[ i ] == empty )
			continue;

		// Если встретили свой цвет ++
		// Иначе выход из цикла
		if ( _color[ i ] == up_color ) {
			cntr++;
		} else
			break;
	}
	return cntr;
}

// Удаляет нужное количество цветов сверху, исключая empty
void flask_c::unfill( unsigned cnt ) {
	signed tmp = cnt;
	// Идем сверху вниз и ищем upper_color цвет
	for ( signed i = SLOT_COUNT - 1; i >= 0; i-- ) {
		// Пропуск всех empty
		if ( _color[ i ] == empty )
			continue;
		else {
			_color[ i ] = empty;
			tmp--;
		}

		// Удалили нужное количество цветов
		if ( !tmp )
			break;
	}

	// dbg
	if( tmp )
		std::cout << "unfill error!";
}

// Доливает сверху cnt слотов
void flask_c::fill( unsigned cnt, color_e color ) {
	unsigned cntr = cnt;
	color_e cl = color == empty ? upper_color( ) : color;
	for ( unsigned i = 0; i < SLOT_COUNT; i++ ) {
		if ( _color[ i ] == empty ) {
			_color[ i ] = cl;
			cntr--;
		}
		if ( !cntr )
			break;
	}
}

// Вернет true, если все цвета одинаковы ( или empty )
bool flask_c::every_color_same( void ) {
	bool t = 1;
	color_e c = _color[ 0 ];
	for ( unsigned i = 1; i < SLOT_COUNT; i++ )
		if ( _color[ i ] != c ) {
			t = 0;
			break;
		}
	return t;
}

void flask_c::print( void ) {
	std::cout << "[";
	for ( signed i = SLOT_COUNT - 1; i >= 0; i-- ) {
		std::cout << i << "=" << color_to_string( _color[ i ] ) << " ";
	}
	std::cout << "]";
}
