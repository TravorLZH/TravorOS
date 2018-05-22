#include <kernel/fs.h>

uint32_t read_fs(fs_node_t *node,uint32_t offset,uint32_t size,uint8_t *buffer)
{
	if(node->read!=0){
		return node->read(node,offset,size,buffer);
	}
	return 0;
}

