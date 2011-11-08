#ifndef _EYVA_H_
#define _EYVA_H_

/* This is the size of a message head following the eyva protocol:
 */
#define MESSAGE_HEAD_SIZE 4

/* This is the size of the network buffer:
 */
#define BUFFER_SIZE (MESSAGE_HEAD_SIZE+653385)

/* This is the maximum size of the exception message:
 */
#define BUFFER_EXCEPTION_MSG 80

#endif

