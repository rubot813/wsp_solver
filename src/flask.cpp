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

// ���������� ��������� ������
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

// ���������� ������� ����
// empty ���� ������ �����
color_e flask_c::upper_color( void ) {
	color_e c = empty;
	for ( signed i = SLOT_COUNT - 1; i >= 0; i-- )
		if ( _color[ i ] != empty ) {
			c = _color[ i ];
			break;
		}
	return c;
}

// ���������� ���������� ���������, ������� ����� �������� �� ���
unsigned flask_c::unfill_count( void ) {
	unsigned cntr = 0;
	color_e up_color = upper_color( );  // ������� ����

	// ������������, ����� �� ���� ���� return
	if ( up_color == empty )
		return 0;

	// ���� ������ ���� � ���� upper_color ����
	for ( signed i = SLOT_COUNT - 1; i >= 0; i-- ) {
		// ������� ���� empty
		if ( _color[ i ] == empty )
			continue;

		// ���� ��������� ���� ���� ++
		// ����� ����� �� �����
		if ( _color[ i ] == up_color ) {
			cntr++;
		} else
			break;
	}
	return cntr;
}

// ������� ������ ���������� ������ ������, �������� empty
void flask_c::unfill( unsigned cnt ) {
	signed tmp = cnt;
	// ���� ������ ���� � ���� upper_color ����
	for ( signed i = SLOT_COUNT - 1; i >= 0; i-- ) {
		// ������� ���� empty
		if ( _color[ i ] == empty )
			continue;
		else {
			_color[ i ] = empty;
			tmp--;
		}

		// ������� ������ ���������� ������
		if ( !tmp )
			break;
	}

	// dbg
	if( tmp )
		std::cout << "unfill error!";
}

// �������� ������ cnt ������
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

// ������ true, ���� ��� ����� ��������� ( ��� empty )
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
