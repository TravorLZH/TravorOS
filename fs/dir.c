#include <kernel/fs.h>

struct dirent *readdir_fs(fs_node_t *node,uint32_t index)
{
	if((node->flags&0x7)==FS_DIRECTORY&&node->readdir!=0){
		return node->readdir(node,index);
	}
	return NULL;
}

fs_node_t *finddir_fs(fs_node_t *node,char *name)
{
	if((node->flags&0x7)==FS_DIRECTORY&&node->finddir!=0){
		return node->finddir(node,name);
	}
	return NULL;
}
