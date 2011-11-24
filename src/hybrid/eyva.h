#ifndef _EYVA_H_
#define _EYVA_H_

/* This is the size of a message head following the eyva protocol:
 */
#define MESSAGE_HEAD_SIZE 4

/* This is the size of the network buffer:
 */
#define BUFFER_SIZE (MESSAGE_HEAD_SIZE+65335)

/* This is the maximum size of the exception message:
 */
#define BUFFER_EXCEPTION_MSG 80

/* Release version:
 */
#define VERSION_MAJOR_RELEASE 0
#define VERSION_MINOR_RELEASE 1
#define VERSION_PATCH 0

#endif

