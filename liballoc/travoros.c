#define	_ALLOC_SKIP_DEFINE
#include <kernel/memory.h>
#include "liballoc.h"

int liballoc_lock(void)
{
	return 0;
}

int liballoc_unlock(void)
{
	return 0;
}

void *liballoc_alloc(int pages)
{
	return alloc_pages(pages);
}

int liballoc_free(void *addr,int pages)
{
	free_pages(addr,pages);
	return 0;
}
