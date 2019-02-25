#ifndef POINT_CHANGES_H
# define POINT_CHANGES_H

#include "../includes/server.h"

# if BUFFER_SIZE <= 4
#  define BUFFSIZE_BIT 2
# elif BUFFER_SIZE <= 8
#  define BUFFSIZE_BIT 3
# elif BUFFER_SIZE <= 16
#  define BUFFSIZE_BIT 4
# elif BUFFER_SIZE <= 32
#  define BUFFSIZE_BIT 5
# elif BUFFER_SIZE <= 64
#  define BUFFSIZE_BIT 6
# elif BUFFER_SIZE <= 128
#  define BUFFSIZE_BIT 7
# elif BUFFER_SIZE <= 256
#  define BUFFSIZE_BIT 8
# elif BUFFER_SIZE <= 512
#  define BUFFSIZE_BIT 9
# elif BUFFER_SIZE <= 1024
#  define BUFFSIZE_BIT 10
# elif BUFFER_SIZE <= 2048
#  define BUFFSIZE_BIT 11
# elif BUFFER_SIZE <= 4096
#  define BUFFSIZE_BIT 12
# elif BUFFER_SIZE <= 8192
#  define BUFFSIZE_BIT 13
# elif BUFFER_SIZE <= 16384
#  define BUFFSIZE_BIT 14
# elif BUFFER_SIZE <= 32768
#  define BUFFSIZE_BIT 15
# elif BUFFER_SIZE <= 65536
#  define BUFFSIZE_BIT 16
# elif BUFFER_SIZE <= 131072
#  define BUFFSIZE_BIT 17
# elif BUFFER_SIZE <= 262144
#  define BUFFSIZE_BIT 18
# elif BUFFER_SIZE <= 524288
#  define BUFFSIZE_BIT 19
# elif BUFFER_SIZE <= 1048576
#  define BUFFSIZE_BIT 20
# else
#  define BUFFSIZE_BIT 32
# endif

#endif
