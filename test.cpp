#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "ggentropy.h"

int main() {
	uint8_t entropy[ 16 ];
	if( !ggentropy( entropy, sizeof( entropy ) ) )
		return 1;

	for( size_t i = 0; i < sizeof( entropy ); i++ ) {
		printf( "%02" PRIx8, entropy[ i ] );
	}
	printf( "\n" );

	return 0;
}
