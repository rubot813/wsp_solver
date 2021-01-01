#include "move.h"
#include "flask.h"
#include "flask_state.h"

// static init
uint32_t flask_state_c::_total_move_count = 0;

int main( void ) {
	// DBG
	color_e c0[ 4 ];
	c0[ 3 ] = l_blue;
	c0[ 2 ] = orange;
	c0[ 1 ] = brown;
	c0[ 0 ] = grey;

	color_e c1[ 4 ];
	c1[ 3 ] = grey;
	c1[ 2 ] = yellow;
	c1[ 1 ] = l_green;
	c1[ 0 ] = violet;

	color_e c2[ 4 ];
	c2[ 3 ] = orange;
	c2[ 2 ] = green;
	c2[ 1 ] = pink;
	c2[ 0 ] = l_blue;

	color_e c3[ 4 ];
	c3[ 3 ] = blue;
	c3[ 2 ] = yellow;
	c3[ 1 ] = red;
	c3[ 0 ] = yellow;

	color_e c4[ 4 ];
	c4[ 3 ] = brown;
	c4[ 2 ] = violet;
	c4[ 1 ] = orange;
	c4[ 0 ] = yellow;

	color_e c5[ 4 ];
	c5[ 3 ] = d_green;
	c5[ 2 ] = l_green;
	c5[ 1 ] = green;
	c5[ 0 ] = d_green;

	color_e c6[ 4 ];
	c6[ 3 ] = green;
	c6[ 2 ] = blue;
	c6[ 1 ] = red;
	c6[ 0 ] = blue;

	// ====

	color_e c7[ 4 ];
	c7[ 3 ] = brown;
	c7[ 2 ] = l_green;
	c7[ 1 ] = brown;
	c7[ 0 ] = red;

	color_e c8[ 4 ];
	c8[ 3 ] = pink;
	c8[ 2 ] = l_green;
	c8[ 1 ] = l_blue;
	c8[ 0 ] = violet;

	color_e c9[ 4 ];
	c9[ 3 ] = violet;
	c9[ 2 ] = green;
	c9[ 1 ] = orange;
	c9[ 0 ] = pink;

	color_e c10[ 4 ];
	c10[ 3 ] = grey;
	c10[ 2 ] = pink;
	c10[ 1 ] = d_green;
	c10[ 0 ] = d_green;

	color_e c11[ 4 ];
	c11[ 3 ] = grey;
	c11[ 2 ] = red;
	c11[ 1 ] = l_blue;
	c11[ 0 ] = blue;

	color_e c12[ 4 ];
	c12[ 3 ] = empty;
	c12[ 2 ] = empty;
	c12[ 1 ] = empty;
	c12[ 0 ] = empty;

	color_e c13[ 4 ];
	c13[ 3 ] = empty;
	c13[ 2 ] = empty;
	c13[ 1 ] = empty;
	c13[ 0 ] = empty;

	// ====

	flask_c flask0( c0 );
	flask_c flask1( c1 );
	flask_c flask2( c2 );
	flask_c flask3( c3 );
	flask_c flask4( c4 );
	flask_c flask5( c5 );
	flask_c flask6( c6 );
	flask_c flask7( c7 );
	flask_c flask8( c8 );
	flask_c flask9( c9 );
	flask_c flask10( c10 );
	flask_c flask11( c11 );
	flask_c flask12( c12 );
	flask_c flask13( c13 );

	std::vector< flask_c > flasks;
	flasks.push_back( flask0 );
	flasks.push_back( flask1 );
	flasks.push_back( flask2 );
	flasks.push_back( flask3 );
	flasks.push_back( flask4 );
	flasks.push_back( flask5 );
	flasks.push_back( flask6 );
	flasks.push_back( flask7 );
	flasks.push_back( flask8 );
	flasks.push_back( flask9 );
	flasks.push_back( flask10 );
	flasks.push_back( flask11 );
	flasks.push_back( flask12 );
	flasks.push_back( flask13 );
	flask_state_c flask_state( &flasks );

	auto start_time = std::chrono::steady_clock::now( );

	if ( flask_state.main_solve( ) ) {
		std::cout << "SOLVED SUCCESFULLY\n";
	} else
		std::cout << "CANNOT SOLVE\n";

	auto end_time = std::chrono::steady_clock::now( );
	auto elapsed = std::chrono::duration_cast< std::chrono::milliseconds>( end_time - start_time );
	std::cout << "Total computation time = " << ( double )elapsed.count( ) << " msec\n";


	return 0;
}
