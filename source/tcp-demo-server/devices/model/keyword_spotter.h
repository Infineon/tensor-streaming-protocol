/*
* ImagiNet Compiler 1.0.0+0ab2c4ad366da00c2c3aea0976e0fea212163bf4
* Copyright © 2023- Imagimob AB, All Rights Reserved.
*
* Generated at 12/11/2024 21:27:46 UTC. Any changes will be lost.
*
* Model ID  617d4ffc-751b-46dd-ac09-7091641a26f7
*
* Memory    Size                      Efficiency
* Buffers   10256 bytes (RAM)         90 %
* State     11592 bytes (RAM)         100 %
* Readonly  40432 bytes (Flash)       100 %
*
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-0
*
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | down
* 2           | up
*
* Exported functions:
*
*  @description: Try read data from model.
*  @param dataout Output Features. Output float[3].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_dequeue(float *dataout);
*
*  @description: Try write data to model.
*  @param datain Input features. Input float[1].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_enqueue(const float *datain);
*
*  @description: Closes and flushes streams, free any heap allocated memory.
*  void IMAI_finalize(void);
*
*  @description: Initializes buffers to initial state.
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_init(void);
*
*
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#include <stdint.h>
#define IMAI_API_QUEUE

typedef int8_t q7_t;         // 8-bit fractional data type in Q1.7 format.
typedef int16_t q15_t;       // 16-bit fractional data type in Q1.15 format.
typedef int32_t q31_t;       // 32-bit fractional data type in Q1.31 format.
typedef int64_t q63_t;       // 64-bit fractional data type in Q1.63 format.

// All symbols in order
#define IMAI_SYMBOL_MAP {"unlabelled", "down", "up"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0xfc, 0x4f, 0x7d, 0x61, 0x1b, 0x75, 0xdd, 0x46, 0xac, 0x09, 0x70, 0x91, 0x64, 0x1a, 0x26, 0xf7}

// First nibble is bit encoding, second nibble is number of bytes
#define IMAGINET_TYPES_NONE	(0x0)
#define IMAGINET_TYPES_FLOAT32	(0x14)
#define IMAGINET_TYPES_FLOAT64	(0x18)
#define IMAGINET_TYPES_INT8	(0x21)
#define IMAGINET_TYPES_INT16	(0x22)
#define IMAGINET_TYPES_INT32	(0x24)
#define IMAGINET_TYPES_INT64	(0x28)
#define IMAGINET_TYPES_Q7	(0x31)
#define IMAGINET_TYPES_Q15	(0x32)
#define IMAGINET_TYPES_Q31	(0x34)
#define IMAGINET_TYPES_BOOL	(0x41)
#define IMAGINET_TYPES_STRING	(0x54)
#define IMAGINET_TYPES_D8	(0x61)
#define IMAGINET_TYPES_D16	(0x62)
#define IMAGINET_TYPES_D32	(0x64)
#define IMAGINET_TYPES_UINT8	(0x71)
#define IMAGINET_TYPES_UINT16	(0x72)
#define IMAGINET_TYPES_UINT32	(0x74)
#define IMAGINET_TYPES_UINT64	(0x78)

// dataout [3] (12 bytes)
#define IMAI_DATAOUT_RANK (1)
#define IMAI_DATAOUT_SHAPE (((int[]){3})
#define IMAI_DATAOUT_COUNT (3)
#define IMAI_DATAOUT_TYPE float
#define IMAI_DATAOUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATAOUT_SHIFT 3
#define IMAI_DATAOUT_OFFSET 0
#define IMAI_DATAOUT_SCALE 1
#define IMAI_DATAOUT_SYMBOLS {"unlabelled", "down", "up"}

// datain [1] (4 bytes)
#define IMAI_DATAIN_RANK (1)
#define IMAI_DATAIN_SHAPE (((int[]){1})
#define IMAI_DATAIN_COUNT (1)
#define IMAI_DATAIN_TYPE float
#define IMAI_DATAIN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATAIN_SHIFT 0
#define IMAI_DATAIN_OFFSET 0
#define IMAI_DATAIN_SCALE 1
#define IMAI_DATAIN_SYMBOLS { }

#define IMAI_KEY_MAX (53)

// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_ERROR -2
#define IMAI_RET_STREAMEND -3

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3

// Exported methods
int IMAI_dequeue(float* restrict dataout);
int IMAI_enqueue(const float* restrict datain);
void IMAI_finalize(void);
int IMAI_init(void);

int IMAI_enqueue_batch_max_frames();

#ifdef IMAI_REFLECTION

typedef enum {
    IMAI_PARAM_UNDEFINED = 0,
    IMAI_PARAM_INPUT = 1,
    IMAI_PARAM_OUTPUT = 2,
    IMAI_PARAM_REFERENCE = 3,
    IMAI_PARAM_HANDLE = 7,
} IMAI_param_attrib;

typedef char* label_text_t;

typedef struct {
    char* name;
    int size;
    label_text_t* labels;
} IMAI_shape_dim;

typedef struct {
    char* name;
    IMAI_param_attrib attrib;
    int32_t rank;
    IMAI_shape_dim* shape;
    int32_t count;
    int32_t type_id;
    float frequency;
    int shift;
    float scale;
    long offset;
} IMAI_param_def;

typedef enum {
    IMAI_FUNC_ATTRIB_NONE = 0,
    IMAI_FUNC_ATTRIB_CAN_FAIL = 1,
    IMAI_FUNC_ATTRIB_PUBLIC = 2,
    IMAI_FUNC_ATTRIB_INIT = 4,
    IMAI_FUNC_ATTRIB_DESTRUCTOR = 8,
} IMAI_func_attrib;

typedef struct {
    char* name;
    char* description;
    void* fn_ptr;
    IMAI_func_attrib attrib;
    int32_t param_count;
    IMAI_param_def* param_list;
} IMAI_func_def;

typedef struct {
    uint32_t size;
    uint32_t peak_usage;
} IMAI_mem_usage;

typedef enum {
    IMAI_API_TYPE_UNDEFINED = 0,
    IMAI_API_TYPE_FUNCTION = 1,
    IMAI_API_TYPE_QUEUE = 2,
    IMAI_API_TYPE_QUEUE_TIME = 3,
    IMAI_API_TYPE_USER_DEFINED = 4,
} IMAI_api_type;

typedef struct {
    uint32_t api_ver;
    uint8_t id[16];
    IMAI_api_type api_type;
    char* prefix;
    IMAI_mem_usage buffer_mem;
    IMAI_mem_usage static_mem;
    IMAI_mem_usage readonly_mem;
    int32_t func_count;
    IMAI_func_def* func_list;
} IMAI_api_def;

IMAI_api_def* IMAI_api(void);
#endif /* IMAI_REFLECTION */

