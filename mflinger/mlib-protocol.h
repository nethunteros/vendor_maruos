#ifndef MLIB_PROTOCOL_H
#define MLIB_PROTOCOL_H

/*
 * This defines the mflinger protocol.
 *
 * Note that some of the requests do not have responses. This
 * is a quick optimization so that the client does not need to
 * wait on a response for "streaming" style calls where a few
 * failures do not affect the end result. Cross your fingers
 * and hope for the best style.
 */

//
// Transport
//
#define M_SOCK_PATH "maru-bridge"

//
// Opcodes
//
#define M_CREATE_BUFFER             (1 << 5)
#define M_UPDATE_BUFFER             (1 << 6)
#define M_LOCK_BUFFER               (1 << 7)
#define M_UNLOCK_AND_POST_BUFFER    (1 << 8)

struct MRequestHeader {
    /* 
     * I experienced deep pain when micro-optimizing
     * this as a single char due to struct padding...
     *
     * Structure packing is not an option as the server
     * needs to read the op segment first to route requests.
     * And I don't want a fixed-length protocol.
     *
     * KISS = just use 4 bytes, jeez.
     */
    uint32_t op;
};
typedef struct MRequestHeader MRequestHeader;

struct MCreateBufferRequest {
    uint32_t width;
    uint32_t height;
};
typedef struct MCreateBufferRequest MCreateBufferRequest;

struct MCreateBufferResponse {
    int32_t id;        /* identifier for the created buffer */
    int32_t result;    /* 0 = success, -1 = failure */
};
typedef struct MCreateBufferResponse MCreateBufferResponse;

struct MUpdateBufferRequest {
    int32_t id;
    uint32_t xpos;
    uint32_t ypos;
};
typedef struct MUpdateBufferRequest MUpdateBufferRequest;

struct MUpdateBufferResponse {
    int32_t result;
};
typedef struct MUpdateBufferResponse MUpdateBufferResponse;

struct MLockBufferRequest {
    int32_t id;
};
typedef struct MLockBufferRequest MLockBufferRequest;

struct MLockBufferResponse {
    MBuffer buffer;
    int32_t result;
};
typedef struct MLockBufferResponse MLockBufferResponse;

struct MUnlockBufferRequest {
    int32_t id;
};
typedef struct MUnlockBufferRequest MUnlockBufferRequest;

#endif // MLIB_PROTOCOL_H