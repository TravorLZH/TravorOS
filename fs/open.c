#include <kernel/fs.h>

void open_fs(fs_node_t *node,uint8_t read,uint8_t write)
{
	if(node->open!=0){
		node->open(node);
	}
}

