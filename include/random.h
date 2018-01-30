/* random.h functions about random */
#ifndef	__RANDOM_H_
#define	__RANDOM_H_
#define	RAND_MAX	32768
#ifdef	__cplusplus
extern	"C"{
#endif
extern void srand(unsigned int seed);
extern unsigned long rand(void);
#ifdef	__cplusplus
}
#endif
#endif

