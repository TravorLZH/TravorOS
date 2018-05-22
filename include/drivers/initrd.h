#ifndef	__INITRD_H_
#define	__INITRD_H_
#include <kernel/fs.h>

typedef struct {
	uint32_t nfiles;
} initrd_header_t;

typedef struct {
	uint8_t magic;
	uint8_t name[64];
	uint32_t offset;
	uint32_t length;
} initrd_file_header_t;

#ifdef	__cplusplus
extern	"C"{
#endif
extern fs_node_t *init_initrd(uint32_t location);
#ifdef	__cplusplus
}
#endif
#endif
