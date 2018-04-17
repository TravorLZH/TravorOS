#define	_ALLOC_SKIP_DEFINE
#include <def.h>
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
	return NULL;
}

int liballoc_free(void *addr,int pages)
{
	return 0;
}
