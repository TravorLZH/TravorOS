/* paging.h: Internal Paging features*/
#ifndef	__PAGING_H_
#define	__PAGING_H_
typedef struct page_struct{
	char present:1;
	char writable:1;
	char user:1;
	char accessed:1;
	char dirty:1;
	char unused:7;
	size_t frame:20;
}page_t;
#endif
