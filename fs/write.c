#include <kernel/fs.h>

uint32_t write_fs(fs_node_t *node,uint32_t offset,uint32_t size,uint8_t *buffer)
{
	if(node->write!=0){
		return node->write(node,offset,size,buffer);
	}
	return 0;
}

