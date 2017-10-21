/***************************************************************
  ****          ****
  **   *********  **   БП-002 :: ЗАМЕНА ДЕЛЕНИЯ НА УМНОЖЕНИЕ
  **  **     **   **   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  **        **    **   Исходный код к выпуску
  **       **     **   Беседы о программировании - 002
  **   ********   **   
  **     **       **
  **    **        **
  **   **     **  **
  **  *********   **
  ****          ****
               [ФАЙЛ] CalcInv.cpp
              [АВТОР] Караваев Артём Михайлович
  [ЭЛЕКТРОННЫЙ АДРЕС] zealint@zealcomputing.ru
               [САЙТ] http://zealcomputing.ru
             [СОЗДАН] 23.12.2015
             [ВЕРСИЯ] 1.00 от 24.12.2015
  [ИСТОРИЯ ИЗМЕНЕНИЙ]
  ==== v0.00 == 23.12.2015 ====
  Файл создан автором, реализованы все функции.
  ==== v1.00 == 24.12.2015 ====
  Изменён начальный выбор m, подбирается так, чтобы (1<<m)>=a.
***************************************************************/

#include <stdio.h>

typedef unsigned int int32u;
typedef unsigned long long int64u;

/**
 * Перевод строки в число типа int32u
 */
int32u atou ( const char * str ) {
	int32u i = 0, res = 0;
	while ( str [ i ] != '\0' ) {
		res *= 10;
		res += str [ i ] - '0';
		++ i;
	}
	return res;
}


int main ( int argc, char * argv [ ] ) {

	int32u a, // Максимальное значение числителя
	       d; // знаменатель
  
	if ( argc != 3 ) {
		fprintf ( stderr, "\n\n\t\tUsage :: calcinv.exe a d\n" );
		fprintf ( stderr, "\t\ta - maximal dividend, d - divisor\n" );
		fprintf ( stderr, "\t\ta >= d\n\n" );
		return 0;
	}

	a = atou ( argv [ 1 ] );
	d = atou ( argv [ 2 ] );
	
	if ( d == 0 ) {
		fprintf ( stderr, "\n\n\t\tERROR :: d = 0\n\n" );
		return 1;
	}

	if ( a < d ) {
		fprintf ( stderr, "\n\n\t\tERROR :: a < d\n\n" );
		return 1;
	}

	int32u m, n = 0;
	int64u p2m, a_max, s, k, v;

	fprintf ( stdout, "\nInput: a <= %u\n       d = %u\n\n", a, d );

	// нужно сделать d не четным
	while ( ( d & 1 ) == 0 ) {
		n ++;
		d >>= 1;
	}

	// Особый случай, когда d степень двойки
	if ( d == 1 ) {
		fprintf ( stdout, "Power of 2!\nv = 1\nm = %u\n\n", n );
		return 0;
	}  	

	// Подбираем m.
	m = 0;
	while ( ( int64u ( 1 ) << m ) < a )
		m ++;
	for ( ; ; ++ m ) {
		p2m = ( int64u ( 1 ) << m );
		k = ( d - 1 ) - ( p2m - 1 ) % d;
		s = ( p2m + k - 1 ) / ( d * k ) + 1;
		a_max = s * d - ( s * d * k ) / ( p2m + k ) - 1;
		// если m подошло, выходим
		if ( a_max >= a )
			break;
	}
	v = ( p2m - 1 ) / d + 1;
		
	fprintf ( stdout, "v(mul) = %I64u\nm(shr) = %u\nk = %I64u\ns = %I64u\na_max = %I64u\n\n", v, m + n, k, s, a_max );

	return 0;
}
