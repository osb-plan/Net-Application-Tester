#ifndef DATA_DEFS_H
#define DATA_DEFS_H

#include <stdint.h>
#include "user_code/user.h"

#define MSGIN_HEADER_LEN    2
#define MSGIN_DATA_LEN      256
#define MSGIN_LEN           MSGIN_HEADER_LEN + MSGIN_DATA_LEN

#define SOFWARE_VERSION     "0.1"

#define NAME_CHAR_DEPTH 64

/******************************************************************************/
/*                               ENUM SECTION                                 */
/******************************************************************************/
typedef enum {
    U8 = 0,
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
typedef struct build_packet
{
    uint32_t byte_len;
    float actual_value;
    struct build_packet *next;
    
} PACKET_BUILDER;

typedef struct {
    float value;
} __attribute__((packed)) VARIATION_TYPE_FIXED;


typedef struct {
    float val1;
    float val2;
    
} __attribute__((packed)) VARIATION_TYPE_BINARY;

typedef struct {
    float delta_up;
    float start_value;
    float end_value;
    
} __attribute__((packed)) VARIATION_TYPE_SWAP;


typedef struct  {
    VARIATION_TYPE var_type;
    void * var_description;
} __attribute__((packed)) VARIATION;

typedef struct{
    char field_name[NAME_CHAR_DEPTH];
    FIELD_TYPE field_type;
    unsigned int field_repeat_time;
    VARIATION *variation;      
} __attribute__((packed)) DATA;

typedef struct field{
    DATA field_info;
    struct field * next;
} __attribute__((packed)) FIELD;

typedef struct{
    unsigned int id;
    char * name;
    FIELD *first_field;    	
} __attribute__((packed)) STRUCT_DESCRIPTION;

/******************************************************************************/
/*                      THREAD SECTION MANAGEMENT                             */
/******************************************************************************/

typedef struct {
    uint32_t id_field;;
    FIELD *field;
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
