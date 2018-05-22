#include <kernel/fs.h>

void close_fs(fs_node_t *node)
{
	if(node->close!=0){
		node->close(node);
	}
}
