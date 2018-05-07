file(GLOB KERN_SOURCES *.c *.asm)
add_library(kern STATIC ${KERN_SOURCES})
