#ifndef FLASK_H
#define FLASK_H

#include "color.h"

#define SLOT_COUNT          4       // Количество слотов во фласке

// Класс реализует одну фласку
class flask_c {
public:
	flask_c( color_e *colors );

	bool is_empty( void );

	// Количество свободных слотов
	unsigned free_count( void );

	// Возвращает верхний цвет
	// empty если фласка пуста
	color_e upper_color( void );

	// Возвращает количество элементов, которые можно перелить за ход
	unsigned unfill_count( void );

	// Удаляет нужное количество цветов сверху, исключая empty
	void unfill( unsigned cnt );

	// Доливает сверху cnt слотов
	void fill( unsigned cnt, color_e color = empty );

	// Вернет true, если все цвета одинаковы ( или empty )
	bool every_color_same( void );

	void print( void );

private:
	// 0 - самый нижний цвет
	// SLOT_COUNT - самый верхний
	color_e _color[ SLOT_COUNT ];
};
#endif // FLASK_H
