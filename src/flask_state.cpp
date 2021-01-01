#include "flask_state.h"

flask_state_c::flask_state_c( std::vector< flask_c > *flasks ) {

	// ������������� ������� �����
	_move_chain.clear( );

	// ��� �� ��� ��������, ��� ������� �����
	_deep = 0;
	_total_move_count = 0;

	// ��������� ������
	_flask = *flasks;

	// ������� ��� ��������� ����
	_calc_move_list( );
}

// ����� ���� ������� �����������, ����� �������� ����� �� ����������� ���
// � �� ����� ���������� ����������
flask_state_c::flask_state_c( move_s *applied_move, std::vector< flask_c > *flasks, std::vector< move_s > *move_chain, uint16_t *deep ) {

	// ����������� ����������� -> check C++11 usage
	// ====
	// ��������� ������
	_flask = *flasks;

	// ��������� ������� �����������
	_move_chain = *move_chain;

	// ��� ����������� ������� ������ �������
	_deep = *deep;
	_deep++;

	// �������������
	_result = 0;

	// ��������� ���
	apply_move( applied_move );

	// ���������� ��� � ������� �����������
	_move_chain.push_back( { *applied_move } );

	// ������� ��� ��������� ����
	_calc_move_list( );

	// ��������� �� ������ ����� �������� �����������
	_check_applied_move( applied_move );

	// ��� �������� �����
	_total_move_count += _move_list.size( );
}

// ����� ���������� ���� � ��������
void flask_state_c::apply_move( move_s *move ) {

	// flask_id0 -> flask_id1
	// ����� ����� ����� ���������
	// ����� ������������ ���������� ������������ ���������
	flask_c *fl0 = &_flask[ move->flask_id0 ];
	flask_c *fl1 = &_flask[ move->flask_id1 ];
	color_e color = fl0->upper_color( );

	// ���������� ���������, ������� ����� �������� �� 0
	unsigned to_be_unfilled = fl0->unfill_count( );

	#ifdef ALLOW_PARTIAL_FILL
		// ���������� ��������� ������ � 1
		unsigned empty_slots = fl1->free_count( );
	#else

	#endif
	#ifdef ALLOW_PARTIAL_FILL
		// ����� �������� ��� �����
		if ( to_be_unfilled <= empty_slots ) {
			fl0->unfill( to_be_unfilled );
			fl1->fill( to_be_unfilled, color );
		} else {
			// ����� �������� �����
			fl0->unfill( empty_slots );  		// �������� ������� �����
			fl1->fill( empty_slots, color );	// �������� �� ���������
		}
	#else
		fl0->unfill( to_be_unfilled );
		fl1->fill( to_be_unfilled, color );
	#endif

}

// ����������� ������� ������� ���������
bool flask_state_c::main_solve( void ) {

	std::cout << "Solving started\n";

	// ���� ���� ��������� ���� ��� ���������� ���������
	if ( _move_list.size( ) ) {
		// ������ ����� �������� �� ������ ��������� ���
		for ( unsigned i = 0; i < _move_list.size( ); i++ ) {
			std::cout << "Move " << i << " of " << _move_list.size( ) - 1 << "\n";
			flask_state_c *new_flask_state;

			new_flask_state = new flask_state_c( &_move_list[ i ], &_flask, &_move_chain, &_deep );

			auto start_time = std::chrono::steady_clock::now( );

			// ���� ������� ������
			new_flask_state->solve( );

			if ( new_flask_state->get_result( ) == SOLVE_FOUND )
				return SOLVE_FOUND;

			auto end_time = std::chrono::steady_clock::now( );
			auto elapsed = std::chrono::duration_cast< std::chrono::milliseconds>( end_time - start_time );
			std::cout << "Computation time = " << ( double )elapsed.count( ) << " msec\n";

			delete new_flask_state;
		}
		std::cout << "Solve ended. Total combinations checked = " << _total_move_count << "\n";
	}
	return SOLVE_NOT_FOUND;
}

// ����������� ������� ������� ���������
void flask_state_c::solve( void ) {

	// ����������� �� ������� �������� �� ������ ����
	if ( _deep >= MAX_MOVE_DEEP ) {
		_result = SOLVE_NOT_FOUND;
		return;
	}

	// ���� �� ��� ������ ��������� ���������
	if ( filled_correct( ) ) {
		std::cout << "Filled correct. state = \n";
		for ( unsigned i = 0; i < _flask.size( ); i++ ) {
			_flask[ i ].print( );
			std::cout << "\n";
		}
		std::cout << "Move chain = \n";
		for ( unsigned i = 0; i < _move_chain.size( ); i++ ) {
			std::cout << _move_chain[ i ].flask_id0 << " -> " << _move_chain[ i ].flask_id1 << "\n";
			std::cout << "Total move count = " << _move_chain.size( ) << "\n";
		}
		_result = SOLVE_FOUND;
		return;
	}

	// ���� ���� ��������� ����
	if ( _move_list.size( ) ) {
		// ������ ����� �������� �� ������ ��������� ���
		for ( unsigned i = 0; i < _move_list.size( ); i++ ) {
			flask_state_c *new_flask_state;
			new_flask_state = new flask_state_c( &_move_list[ i ], &_flask, &_move_chain, &_deep );

			// ���� ������� ������
			new_flask_state->solve( );
			if ( new_flask_state->get_result( ) == SOLVE_FOUND ) {
				delete new_flask_state;
				_result = SOLVE_FOUND;
				return;
			}

			delete new_flask_state;
		}
	}
	_result = SOLVE_NOT_FOUND;
	return;
}

bool flask_state_c::get_result( void ) {
	return _result;
}

// true, ���� � ������ ������ ��� ����� ���������
bool flask_state_c::filled_correct( void ) {
	bool t = 1;
	for ( unsigned i = 0; i < _flask.size( ); i++ )
		if ( !( _flask[ i ].every_color_same( ) ) ) {
			t = 0;
			break;
		}
	return t;
}

// ����� ������� ������ ��������� �����
void flask_state_c::_calc_move_list( void ) {
	_move_list.clear( );
	// ��� �� ���� �������
	for ( unsigned i = 0; i < _flask.size( ); i++ ) {
		if ( _flask[ i ].upper_color( ) == empty ) {
			continue;
		}

		for ( unsigned j = 0; j < _flask.size( ); j++ ) {
			// ������ i -> ������ ����������
			// ������ j -> ���� ����������
			if ( i != j ) { // ���� ��� �� ���� � �� �� ������
				// ���� ����� ����� ������
				color_e c_fl0 = _flask[ i ].upper_color( );
				color_e c_fl1 = _flask[ j ].upper_color( );

				// color -> empty
				if ( c_fl1 == empty ) {
					_move_list.push_back( { i, j } );   // ������� ��������� ���
					continue;
				}

				// ��� ������ �� ������
				if ( c_fl0 == c_fl1 &&              // ����� ���������
						#ifdef ALLOW_PARTIAL_FILL
							_flask[ j ].free_count( ) ) {     // ���� ���� �� ���� ��������� ���� �� ������ ������
						#else
							// ������� ������, ���� �� ����� �������� ��� ����� �������� ����� �� ������ ������ �� ������
							_flask[ i ].unfill_count( ) <= _flask[ j ].free_count( ) ) {
						#endif
					_move_list.push_back( { i, j } );   // ������� ��������� ���
				}
			}   // if i != j
		}   // second for
	}   // first for
}   // _calc_move_list

// ����� ������� ���, �������� ������������
void flask_state_c::_check_applied_move( move_s *app_move ) {
	for ( unsigned i = 0; i < _move_list.size( ); i++ ) {
		if ( _move_list[ i ].same_inverse( *app_move ) ) {
			_move_list.erase( _move_list.begin( ) + i );
			break;
		}
	}
}   // _check_applied_move
