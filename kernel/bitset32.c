#include <string.h>
#include <bitset32.h>

void bitset_set(bitset_t *bitset,size_t n)
{
	bitset[BIT_INDEX(n)] |= (1 << BIT_OFFSET(n));
}

void bitset_clear(bitset_t *bitset,size_t n)
{
	bitset[BIT_INDEX(n)] &= ~(1 << BIT_OFFSET(n));
}

size_t bitset_test(bitset_t *bitset,size_t n)
{
	return bitset[BIT_INDEX(n)] & (1 << BIT_OFFSET(n));
}

