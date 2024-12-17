#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "model.pb.h"
#include "protocol.h"
#include "pmem.h"


#ifdef PMEM_NO_MALLOC
static bool _protocol_used = false;
static protocol_t _protocol;
static bool _devices_used = false;
static protocol_Device _devices[MAX_DEVICES];
static bool _device_managers_used = false;
static device_manager_t _device_managers[MAX_DEVICES];
static bool plist_used[MAX_ALLOCATED_PLISTS] = { 0 };
static char* plist[MAX_ALLOCATED_PLISTS][MAX_PLIST_ITEMS];
static bool stream_config_used[MAX_DEVICES] = { 0 };
static protocol_StreamConfig stream_config[MAX_DEVICES][MAX_STREAMS_PER_DEVICE];

static void* __pmem_realloc(void* ptr, int new_count, bool* used, void* pool, int pool_size);
static void __pmem_free(void* ptr, bool* used, void* pool);
#endif

#ifndef PMEM_PANIC_MESSAGE
#define PMEM_PANIC_MESSAGE(msg) UNUSED(msg)
#endif

#ifndef PMEM_DEBUG_MESSAGE
#define PMEM_DEBUG_MESSAGE(msg) UNUSED(msg)
#endif

/******* protocol_t *******/

protocol_t* pmem_alloc_protocol() 
{
#ifdef PMEM_NO_MALLOC
	return (protocol_t*)__pmem_realloc(NULL, 1, &_protocol_used, &_protocol, 1);
#else
	return (protocol_t*)malloc(sizeof(protocol_t));	
#endif
}

void pmem_free_protocol(protocol_t* ptr) 
{
#ifdef PMEM_NO_MALLOC
	__pmem_free(ptr, &_protocol_used, &_protocol);
#else
	free(ptr);	
#endif
}


/******* char** plist *******/

char** pmem_alloc_plist(int new_count) 
{
#ifdef PMEM_NO_MALLOC
	if (new_count > MAX_PLIST_ITEMS) {
		PMEM_PANIC_MESSAGE("pmem_alloc_plist: Out of memory. Increase MAX_PLIST_ITEMS.");
		return NULL;
	}

	for (int i = 0; i < MAX_ALLOCATED_PLISTS; i++) {
		if (plist_used[i])
			continue;

		plist_used[i] = true;
		return plist[i];
	}

	PMEM_PANIC_MESSAGE("pmem_alloc_plist: Out of memory. Increase MAX_ALLOCATED_PLISTS.");
	return NULL;
#else
	return (char**)malloc(sizeof(char*) * new_count);
#endif
}

void pmem_free_plist(char** item) 
{
#ifdef PMEM_NO_MALLOC
	for (int i = 0; i < MAX_ALLOCATED_PLISTS; i++) {
		if (!plist_used[i])
			continue;

		if (plist[i] == item) {
			plist_used[i] = false;
			return;
		}
    }
	PMEM_PANIC_MESSAGE("pmem_free_plist: Invalid pointer.");
	return;
#else
	free(item);
#endif
}

pb_bytes_array_t* pmem_alloc_blob(int size) {
#ifdef PMEM_NO_MALLOC
#error Not yet implemented
#else
	return (pb_bytes_array_t*)malloc(PB_BYTES_ARRAY_T_ALLOCSIZE(size));
#endif
}

void pmem_free_blob(pb_bytes_array_t* blob) {
#ifdef PMEM_NO_MALLOC
#error Not yet implemented
#else
	free(blob);
#endif
}


/******* protocol_Device *******/

protocol_Device* pmem_realloc_Device(protocol_Device* ptr, int new_count) 
{
#ifdef PMEM_NO_MALLOC
	return (protocol_Device*)__pmem_realloc(ptr, new_count, &_devices_used, _devices, MAX_DEVICES);
#else
	return (protocol_Device*)realloc(ptr, sizeof(protocol_Device) * new_count);
#endif
}

void pmem_free_Device(protocol_Device *ptr)
{
#ifdef PMEM_NO_MALLOC
	__pmem_free(ptr, &_devices_used, _devices);
#else
	free(ptr);
#endif
}

/******* device_manager_t *******/

device_manager_t* pmem_realloc_device_manager(device_manager_t* ptr, int new_count) 
{
#ifdef PMEM_NO_MALLOC
	return (device_manager_t*)__pmem_realloc(ptr, new_count, &_device_managers_used, _device_managers, MAX_DEVICES);
#else
	return (device_manager_t*)realloc(ptr, sizeof(device_manager_t) * new_count);
#endif
}

void pmem_free_device_manager(device_manager_t* ptr)
{
#ifdef PMEM_NO_MALLOC
	__pmem_free(ptr, &_device_managers_used, _device_managers);
#else
	free(ptr);
#endif
}


/******* protocol_StreamConfig *******/

protocol_StreamConfig* pmem_realloc_StreamConfig(protocol_StreamConfig* ptr, int new_count)
{
#ifdef PMEM_NO_MALLOC
	if (new_count > MAX_STREAMS_PER_DEVICE) {
		PMEM_PANIC_MESSAGE("pmem_realloc_StreamConfig: Out of memory. Increase MAX_STREAMS_PER_DEVICE.");
		return NULL;
	}

	if (ptr == NULL) {
		for (int i = 0; i < MAX_DEVICES; i++) {
			if (stream_config_used[i])
				continue;

			stream_config_used[i] = true;
			return stream_config[i];
		}

		PMEM_PANIC_MESSAGE("pmem_realloc_StreamConfig: Out of memory. Increase MAX_DEVICES.");
		return NULL;
	}
	else 
	{
		for (int i = 0; i < MAX_DEVICES; i++) {
			if (stream_config_used[i])
				continue;

			if(ptr == stream_config[i])			
			    return stream_config[i];
		}

		PMEM_PANIC_MESSAGE("pmem_realloc_StreamConfig: Invalid pointer.");
		return NULL;
	}
#else
	return (protocol_StreamConfig*)realloc(ptr, sizeof(protocol_StreamConfig) * new_count);
#endif
}

void pmem_free_StreamConfig(protocol_StreamConfig* ptr) 
{
#ifdef PMEM_NO_MALLOC
	for (int i = 0; i < MAX_DEVICES; i++) {
		if (!stream_config_used[i])
			continue;

		if (ptr == stream_config[i]) {
			stream_config_used[i] = false;
			return;
		}
	}
	PMEM_PANIC_MESSAGE("pmem_free_StreamConfig: Invalid pointer.");
#else
	free(ptr);
#endif
}

/******* protocol_Option *******/

protocol_Option* pmem_realloc_Option(protocol_Option* ptr, int new_count) 
{
	// TODO: Fix this!
	return (protocol_Option*)realloc(ptr, sizeof(protocol_Option) * new_count);
}

void pmem_free_Option(protocol_Option* ptr) 
{
	// TODO: Fix this!
	free(ptr);
}


#ifdef PMEM_NO_MALLOC

static void* __pmem_realloc(void* ptr, int new_count, bool* used, void* pool, int pool_size)
{
	if (new_count > pool_size)
	{
		PMEM_PANIC_MESSAGE("pmem_realloc: Out of memory.");
		return NULL;
	}

	if (ptr == NULL)
	{
		if (*used)
		{
			PMEM_PANIC_MESSAGE("pmem_realloc: Only one block may be allocated.");
			return NULL;
		}
		else
		{
			*used = true;
			return pool;
		}
	}
	else if (ptr == pool)
	{
		if (!*used)
		{
			PMEM_PANIC_MESSAGE("pmem_realloc: Pointer not allocated.");
			return NULL;
		}
		return pool;
	}
	else
	{
		PMEM_PANIC_MESSAGE("pmem_realloc: Invalid pointer.");
		return NULL;
	}
}

static void __pmem_free(void* ptr, bool* used, void* pool)
{
	if (ptr == NULL)
		return;

	if (ptr != pool)
	{
		PMEM_PANIC_MESSAGE("pmem_free: Invalid pointer.");
	}
	else 
	{
		if (!*used)
			PMEM_PANIC_MESSAGE("pmem_free: Pointer not allocated");
		*used = false;
	}
}

#endif /* PMEM_NO_MALLOC */
