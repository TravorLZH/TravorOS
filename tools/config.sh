#!/bin/sh
CONFIG_FILE=${PWD}/include/config.h
VERSION=`git describe --tags`
BUGREPORT="<travor_lzh@outlook.com>"
cat << EOT > $CONFIG_FILE
#ifndef	__CONFIG_H_
#define	__CONFIG_H_
/* TravorOS version */
#define	VERSION		"${VERSION}"
/* TravorOS bug report */
#define	BUGREPORT	"${BUGREPORT}"
#endif
EOT
