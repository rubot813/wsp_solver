#ifndef FLASK_H
#define FLASK_H

#include "color.h"

#define SLOT_COUNT          4       // ���������� ������ �� ������

// ����� ��������� ���� ������
class flask_c {
public:
	flask_c( color_e *colors );

	bool is_empty( void );

	// ���������� ��������� ������
	unsigned free_count( void );

	// ���������� ������� ����
	// empty ���� ������ �����
	color_e upper_color( void );

	// ���������� ���������� ���������, ������� ����� �������� �� ���
	unsigned unfill_count( void );

	// ������� ������ ���������� ������ ������, �������� empty
	void unfill( unsigned cnt );

	// �������� ������ cnt ������
	void fill( unsigned cnt, color_e color = empty );

	// ������ true, ���� ��� ����� ��������� ( ��� empty )
	bool every_color_same( void );

	void print( void );

private:
	// 0 - ����� ������ ����
	// SLOT_COUNT - ����� �������
	color_e _color[ SLOT_COUNT ];
};
#endif // FLASK_H
