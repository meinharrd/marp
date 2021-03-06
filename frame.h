/**
 * File: frame.h
 * Author: Ethan Gordon
 * Owns the header of all MARP packets.
 **/

#ifndef FRAME_H
#define FRAME_H

#include <pthread.h>

/* Local files */
#include "network/socket.h"
#include "network/recursor.h"

#include "data/cache.h"
#include "data/local.h"

#include "object/query.h"
#include "object/response.h"

/* Holds Frame header and payload. */
typedef struct frame *Frame_T;

/**
 * Frame_T Frame_init(void)
 * Allocates a new Frame in the heap. 
 * @param: None
 * @return: An empty Frame or NULL on error, with errno set.
 **/
Frame_T Frame_init(void);

/**
 * Frame_T Frame_buildQuery(int, int, const void*, size_t)
 * @param authoritative: Only accept authoritative responses
 * @param recurseDepth: How many nodes to recurse to, 0 to disable
 * @param payload: buffer to send
 * @param payLen: Length of @param payload
 * @return a new Frame, or NULL on failur
 **/
Frame_T Frame_buildQuery(int authoritative, int recurseDepth, const void* payload, size_t payLen);

/**
 * const uint8_t Frame_getPayload(Frame_T, uint16_t*)
 * @param frame: To get the payload, can't be NULL
 * @param len: Value Parameter, overwritten with length of payload
 * @return pointer to the payload buffer
 **/
const uint8_t* Frame_getPayload(Frame_T frame, uint16_t* len);

/**
 * void Frame_printInfo(Frame_T)
 * @param frame: To print
 * @return None
 **/
void Frame_printInfo(Frame_T frame);

/**
 * int Frame_listen(Frame_T, Socket_T)
 * Block until a new frame is received via the socket over the network.
 * @param dest: Frame to fill, all contents will be overwritten
 * @param socket: Where to listen for data. Must not be NULL.
 * @param timeout: How long to wait, set to 0 to disable.
 * @return: size ofr frame in bytes  on Success, -1 on Failure or Timeout
 **/
int Frame_listen(Frame_T dest, Socket_T socket, int timeout);

/**
 * int Frame_respond(Frame_T, Socket_T)
 * Creates a new pthread in which to respond to the given Frame.
 * Note: The provided frame is automatically de-allocated.
 * @param frame: Must be an alread-filled frame.
 * @param socket: Must be an already connected or bound socket.
 * @return: The pthread pointer on success, or NULL on failure.
 **/
pthread_t* Frame_respond(Frame_T frame, Socket_T socket);

/**
 * int Frame_send(Frame_T, Socket_T, const char* uint16_t)
 * @param frame: To serialize and Send
 * @param socket: use to send
 * @param ip, port: Send to
 * @return: @see Socket_write(), same return value
 **/
int Frame_send(Frame_T frame, Socket_T socket, const char* ip, uint16_t port);

/**
 * void Frame_free(Frame_T)
 * @param frame: Frame to completely clean up and de-allocate.
 * @return: None
 **/
void Frame_free(Frame_T frame);


#endif
