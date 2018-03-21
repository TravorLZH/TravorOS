#include <def.h>
#ifndef	__BITSET32_H_
#define	__BITSET32_H_
#define	BIT_INDEX(a)	(a/32)
#define	BIT_OFFSET(a)	(a%32)
typedef size_t bitset_t;
#ifdef	__cplusplus
extern	"C"{
#endif
extern void bitset_init(bitset_t *bitset,void *start,size_t length);
extern void bitset_set(bitset_t *bitset,size_t n);
extern void bitset_clear(bitset_t *bitset,size_t n);
extern size_t bitset_test(bitset_t *bitset,size_t n);
#ifdef	__cplusplus
}
#endif
#endif
