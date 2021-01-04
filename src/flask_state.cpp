#include "flask_state.h"

flask_state_c::flask_state_c( std::vector< flask_c > *flasks ) {

	// Инициализация цепочки ходов
	_move_chain.clear( );

	// Тут хз что написать, все понятно блять
	_deep = 0;
	_total_move_count = 0;

	// Сохраняем фласки
	_flask = *flasks;

	// Считаем все доступные ходы
	_calc_move_list( );
}

// Здесь надо сделать конструктор, после создания сразу же применяется ход
// И не нужно передавать предыдущий
flask_state_c::flask_state_c( move_s *applied_move, std::vector< flask_c > *flasks, std::vector< move_s > *move_chain, uint16_t *deep ) {

	// Конструктор копирования -> check C++11 usage
	// ====
	// Сохраняем фласки
	_flask = *flasks;

	// Сохраняем цепочку перемещений
	_move_chain = *move_chain;

	// Для ограничения глубины поиска решений
	_deep = *deep;
	_deep++;

	// Инициализация
	_result = 0;

	// Применяем ход
	apply_move( applied_move );

	// Добавляяем ход в цепочку перемещений
	_move_chain.push_back( { *applied_move } );

	// Считаем все доступные ходы
	_calc_move_list( );

	// Исключаем из списка ходов обратный предыдущему
	_check_applied_move( applied_move );

	// Для подсчета ходов
	_total_move_count += _move_list.size( );
}

// Метод применения хода к сотоянию
void flask_state_c::apply_move( move_s *move ) {

	// flask_id0 -> flask_id1
	// Цвета точно будут одинаковы
	// Здесь определяется количество перемещаемых элементов
	flask_c *fl0 = &_flask[ move->flask_id0 ];
	flask_c *fl1 = &_flask[ move->flask_id1 ];
	color_e color = fl0->upper_color( );

	// Количество элементов, которые можно перелить из 0
	unsigned to_be_unfilled = fl0->unfill_count( );

	#ifdef ALLOW_PARTIAL_FILL
		// Количество свободных слотов в 1
		unsigned empty_slots = fl1->free_count( );
	#else

	#endif
	#ifdef ALLOW_PARTIAL_FILL
		// Можем перелить все слоты
		if ( to_be_unfilled <= empty_slots ) {
			fl0->unfill( to_be_unfilled );
			fl1->fill( to_be_unfilled, color );
		} else {
			// Можем перелить часть
			fl0->unfill( empty_slots );  		// Отливаем сколько можем
			fl1->fill( empty_slots, color );	// Дольется до максимума
		}
	#else
		fl0->unfill( to_be_unfilled );
		fl1->fill( to_be_unfilled, color );
	#endif

}

// Рекурсивная функция решения состояния
bool flask_state_c::main_solve( void ) {

	std::cout << "Solving started\n";

	// Если есть доступные ходы для начального состояния
	if ( _move_list.size( ) ) {
		// Создаю новую ситуацию на каждый доступный ход
		for ( unsigned i = 0; i < _move_list.size( ); i++ ) {
			std::cout << "Move " << i << " of " << _move_list.size( ) - 1 << "\n";
			flask_state_c *new_flask_state;

			new_flask_state = new flask_state_c( &_move_list[ i ], &_flask, &_move_chain, &_deep );

			auto start_time = std::chrono::steady_clock::now( );

			// Если удалось решить
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

// Рекурсивная функция решения состояния
void flask_state_c::solve( void ) {

	// Ограничение на глубину проверки по одному ходу
	if ( _deep >= MAX_MOVE_DEEP ) {
		_result = SOLVE_NOT_FOUND;
		return;
	}

	// Если не все фласки заполнены правильно
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

	// Если есть доступные ходы
	if ( _move_list.size( ) ) {
		// Создаю новую ситуацию на каждый доступный ход
		for ( unsigned i = 0; i < _move_list.size( ); i++ ) {
			flask_state_c *new_flask_state;
			new_flask_state = new flask_state_c( &_move_list[ i ], &_flask, &_move_chain, &_deep );

			// Если удалось решить
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

// true, если в каждой фласке все цвета одинаковы
bool flask_state_c::filled_correct( void ) {
	bool t = 1;
	for ( unsigned i = 0; i < _flask.size( ); i++ )
		if ( !( _flask[ i ].every_color_same( ) ) ) {
			t = 0;
			break;
		}
	return t;
}

// Метод создает список доступных ходов
void flask_state_c::_calc_move_list( void ) {
	_move_list.clear( );
	// Иду по всем фласкам
	for ( unsigned i = 0; i < _flask.size( ); i++ ) {
		if ( _flask[ i ].upper_color( ) == empty ) {
			continue;
		}

		for ( unsigned j = 0; j < _flask.size( ); j++ ) {
			// Фласка i -> откуда переливаем
			// Фласка j -> куда переливаем
			if ( i != j ) { // Если это не одна и та же фласка
				// Беру цвета обоих фласок
				color_e c_fl0 = _flask[ i ].upper_color( );
				color_e c_fl1 = _flask[ j ].upper_color( );

				// color -> empty
				if ( c_fl1 == empty ) {
					_move_list.push_back( { i, j } );   // Генерим доступный ход
					continue;
				}

				// Обе фласки не пустые
				if ( c_fl0 == c_fl1 &&              // Цвета совпадают
						#ifdef ALLOW_PARTIAL_FILL
							_flask[ j ].free_count( ) ) {     // Есть хотя бы один свободный слот во второй фласке
						#else
							// Образно говоря, если мы можем перелить все слоты верхнего цвета из первой фласки во вторую
							_flask[ i ].unfill_count( ) <= _flask[ j ].free_count( ) ) {
						#endif
					_move_list.push_back( { i, j } );   // Генерим доступный ход
				}
			}   // if i != j
		}   // second for
	}   // first for
}   // _calc_move_list

// Метод удаляет ход, обратный примененному
void flask_state_c::_check_applied_move( move_s *app_move ) {
	for ( unsigned i = 0; i < _move_list.size( ); i++ ) {
		if ( _move_list[ i ].same_inverse( *app_move ) ) {
			_move_list.erase( _move_list.begin( ) + i );
			break;
		}
	}
}   // _check_applied_move
