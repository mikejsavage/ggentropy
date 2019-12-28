# ggentropy

ggentropy is a liberally licensed, cross platform, entropy library for
C++. You can use it to generate cryptographically secure random numbers,
safe for use as nonces and keys in cryptographic operations.

ggentropy supports Windows, MacOS, Linux and OpenBSD.


## Usage

ggentropy has one function:

```cpp
bool ggentropy( void * buf, size_t n );
```

which writes `n` bytes of crytographically secure random data to `buf`.
It returns true on success and false on failure. Some platforms place a
length restriction on `n`, so the library will exit on all platforms if
`n` is greater than 256.

Basic usage looks like this:

```cpp
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
```

`ggentropy` can fail. In long lived programs you should use it to seed a
userspace cryptographically secure psuedo-random number generator once
at program startup and use that for all future cryptographically secure
random data. For example, you can encrypt a stream of zeroes using a key
chosen by ggentropy, and use the output of the cipher as a random number
source.


## Implementation details

ggentropy uses the following functionality:

- Windows: [CryptGenRandom](https://docs.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptgenrandom)
- MacOS: /dev/urandom
- Linux: [getrandom](https://lwn.net/Articles/606141/) with a fallback to /dev/urandom
- OpenBSD: [arc4random_buf](https://man.openbsd.org/arc4random_buf)
