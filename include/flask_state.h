#ifndef FLASK_STATE_H
#define FLASK_STATE_H

#include <vector>
#include <chrono>
#include <thread>

#include "flask.h"
#include "move.h"

#define MAX_MOVE_DEEP		5	// Максимальная глубина поиска
#define ALLOW_PARTIAL_FILL		// Флаг разрешения ходов с неполной переливкой
#undef ALLOW_PARTIAL_FILL
#define THREAD_COUNT 2			// Количество потоков
#define SOLVE_FOUND			1
#define SOLVE_NOT_FOUND		0

// Описывает состояние поля
class flask_state_c {
public:
	// Конструктор для главного хода
	flask_state_c( std::vector< flask_c > *flasks );

	// Конструктор для последующих ходов
	flask_state_c( move_s *applied_move, std::vector< flask_c > *flasks, std::vector< move_s > *move_chain, uint16_t *deep );

	// Метод применения хода к сотоянию
	void apply_move( move_s *move );

	// Рекурсивная функция решения состояния
	bool main_solve( void );

	// Рекурсивная функция решения состояния
	void solve( void );

	// true, если в каждой фласке все цвета одинаковы
	bool filled_correct( void );

	// Получение результата решения
	bool get_result( void );

private:
	// methods

	// Метод создает список доступных ходов
	void _calc_move_list( void );

	// Метод удаляет ход, обратный примененному
	void _check_applied_move( move_s *app_move );

private:
	// vars

	// Контейнер фласок
	std::vector< flask_c > _flask;

	// Контейнер доступных ходов для ситуации
	std::vector< move_s > _move_list;

	// Цепочка перемещений, чтобы отслеживать сделаные ходы
	std::vector< move_s > _move_chain;

	// Глубина прохода
	uint16_t _deep;

	// Результат поиска решения классом
	// Действителен только при вызове через solve( )
	bool _result;

	// Для статистики - число всех совершенных ходов
	static uint32_t _total_move_count;
};

#endif // FLASK_STATE_H
