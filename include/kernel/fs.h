#ifndef	__FS_H_
#define	__FS_H_
#include <def.h>

/* Definitions for inode types */
#define	FS_FILE		0x01
#define	FS_DIRECTORY	0x02
#define	FS_CHARDEV	0x03
#define	FS_BLOCKDEV	0x04
#define	FS_PIPE		0x05
#define	FS_SYMLINK	0x06
#define	FS_MOUNTPOINT	0x08

typedef uint32_t (*readfunc_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef uint32_t (*writefunc_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef void (*openfunc_t)(struct fs_node*);
typedef void (*closefunc_t)(struct fs_node*);
typedef struct dirent * (*readdirfunc_t)(struct fs_node*,uint32_t);
typedef struct fs_node * (*finddirfunc_t)(struct fs_node*,char *name);

/* Returned by readdir call */
struct dirent {
	char name[128];	// Filename
	uint32_t ino;	// Inode number, conforming to POSIX
};

/* Data structure of inode */
typedef struct fs_node {
	char name[128];		// The filename
	uint32_t mask;		// Permission bits
	uint32_t uid;
	uint32_t gid;
	uint32_t flags;		// Type of node
	uint32_t length;	// Size of file
	uint32_t impl;		// An implementation-defined number
	readfunc_t read;
	writefunc_t write;
	openfunc_t open;
	closefunc_t close;
	readdirfunc_t readdir;
	finddirfunc_t finddir;
	struct fs_node *ptr;	// Used by mountpoints and symlinks.
} fs_node_t;

uint32_t read_fs(fs_node_t *node,uint32_t offset,uint32_t size,uint8_t *buffer);
uint32_t write_fs(fs_node_t *node,uint32_t offset,uint32_t size,uint8_t *buffer);
void open_fs(fs_node_t *node,uint8_t read,uint8_t write);
void close_fs(fs_node_t *node);
struct dirent *readdir_fs(fs_node_t *node,index);
#ifdef	__cplusplus
extern	"C"{
#endif

#ifdef	__cplusplus
}
#endif
