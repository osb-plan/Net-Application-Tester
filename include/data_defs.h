#ifndef DATA_DEFS_H
#define DATA_DEFS_H

#include <stdint.h>
#include "user_code/user.h"

#define MSGIN_HEADER_LEN    2
#define MSGIN_DATA_LEN      256
#define MSGIN_LEN           MSGIN_HEADER_LEN + MSGIN_DATA_LEN

#define SOFWARE_VERSION     "0.1"

/******************************************************************************/
/*                               ENUM SECTION                                 */
/******************************************************************************/
typedef enum {
    BIT = 0,
    U8,
    U16,
    U32,
    TEXT,
    CUSTOM,
} FIELD_TYPE;

typedef enum {
    FIXED = 0,
    BINARY,
    SWAP
} VARIATION_TYPE;

/******************************************************************************/
/*                      VARIATION STRUCT  SECTION                             */
/******************************************************************************/

typedef struct {
    float value;
} __attribute__((packed)) VARIATION_TYPE_FIXED;


typedef struct {
    float val1;
    float val2;
    
} __attribute__((packed)) VARIATION_TYPE_BINARY;

typedef struct {
    float increment;
    float val1;
    float val2;
    
} __attribute__((packed)) VARIATION_TYPE_SWAP;


typedef struct  {
    VARIATION_TYPE var_type;
    void * var_description;
} __attribute__((packed)) VARIATION;

typedef struct{
    char * field_name;
    FIELD_TYPE field_type;
    VARIATION variation;      
} __attribute__((packed)) DATA;

typedef struct field{
    DATA field_info;
    struct field * next;
} __attribute__((packed)) FIELD;


/******************************************************************************/
/*                      THREAD SECTION MANAGEMENT                             */
/******************************************************************************/

typedef struct {
    uint32_t ms_interval;
    PACKET_TYPE msg_type_id;

} __attribute__((packed)) CHARACTERISTICS_THREAD;

typedef struct {
    PACKET_TYPE type;
    uint8_t spare;

} __attribute__((packed)) HEADER;

typedef struct {
    HEADER header;
    uint8_t data[MSGIN_DATA_LEN];
} __attribute__((packed)) MSGIN_PACKET;


#endif // DATA_DEFS_H
