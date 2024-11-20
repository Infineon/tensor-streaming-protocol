
#ifndef _PMEM_H_
#define _PMEM_H_

/*
* Define to use static memory instead of malloc, realloc and free. 
*/
// #define PMEM_NO_MALLOC

/* If PMEM_NO_MALLOC is defined these are used */
#define MAX_DEVICES 3
#define MAX_PLIST_ITEMS 5
#define MAX_ALLOCATED_PLISTS (MAX_DEVICES * 4)
#define MAX_STREAMS_PER_DEVICE 2


// Uncomment do disable prints
// #define PMEM_PANIC_MESSAGE(msg) printf("[PANIC] %s\r\n", msg)
// #define PMEM_DEBUG_MESSAGE(msg) printf("[DEBUG] %s\r\n", msg)



/******************************************************************************/

/* malloc - free */

protocol_t* pmem_alloc_protocol();
void pmem_free_protocol(protocol_t* item);

char** pmem_alloc_plist(int count);
void pmem_free_plist(char** item);


/* realloc - free */
protocol_Device* pmem_realloc_Device(protocol_Device* old, int new_count);
void pmem_free_Device(protocol_Device* item);

device_manager_t* pmem_realloc_device_manager(device_manager_t* old, int new_count);
void pmem_free_device_manager(device_manager_t* item);

protocol_StreamConfig* pmem_realloc_StreamConfig(protocol_StreamConfig* old, int new_count);
void pmem_free_StreamConfig(protocol_StreamConfig* item);

protocol_Option* pmem_realloc_Option(protocol_Option* old, int new_count);
void pmem_free_Option(protocol_Option* item);

#endif /* _PMEM_H_ */
