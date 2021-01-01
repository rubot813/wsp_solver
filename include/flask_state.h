#ifndef FLASK_STATE_H
#define FLASK_STATE_H

#include <vector>
#include <chrono>
#include <thread>

#include "flask.h"
#include "move.h"

#define MAX_MOVE_DEEP		5	// ������������ ������� ������
#define ALLOW_PARTIAL_FILL		// ���� ���������� ����� � �������� ����������
#undef ALLOW_PARTIAL_FILL
#define THREAD_COUNT 2			// ���������� �������
#define SOLVE_FOUND			1
#define SOLVE_NOT_FOUND		0

// ��������� ��������� ����
class flask_state_c {
public:
	// ����������� ��� �������� ����
	flask_state_c( std::vector< flask_c > *flasks );

	// ����������� ��� ����������� �����
	flask_state_c( move_s *applied_move, std::vector< flask_c > *flasks, std::vector< move_s > *move_chain, uint16_t *deep );

	// ����� ���������� ���� � ��������
	void apply_move( move_s *move );

	// ����������� ������� ������� ���������
	bool main_solve( void );

	// ����������� ������� ������� ���������
	void solve( void );

	// true, ���� � ������ ������ ��� ����� ���������
	bool filled_correct( void );

	// ��������� ���������� �������
	bool get_result( void );

private:
	// methods

	// ����� ������� ������ ��������� �����
	void _calc_move_list( void );

	// ����� ������� ���, �������� ������������
	void _check_applied_move( move_s *app_move );

private:
	// vars

	// ��������� ������
	std::vector< flask_c > _flask;

	// ��������� ��������� ����� ��� ��������
	std::vector< move_s > _move_list;

	// ������� �����������, ����� ����������� �������� ����
	std::vector< move_s > _move_chain;

	// ������� �������
	uint16_t _deep;

	// ��������� ������ ������� �������
	// ������������ ������ ��� ������ ����� solve( )
	bool _result;

	// ��� ���������� - ����� ���� ����������� �����
	static uint32_t _total_move_count;
};

#endif // FLASK_STATE_H
