#include <stdio.h>
#include "protocol_debug.h"

void protocol_debug_print(protocol_t* protocol)
{
	protocol_Board* board = protocol->board;

	printf("--- Protocol Debug Print ---\n");
	printf("Board Name             : %s\n", board->name);
	printf("Firmware Version       : %d.%d.%d.%d\n",
		board->firmware_version.major,
		board->firmware_version.minor,
		board->firmware_version.build,
		board->firmware_version.revision);
	printf("Protocol Version       : %d.%d.%d.%d\n",
		board->protocol_version.major,
		board->protocol_version.minor,
		board->protocol_version.build,
		board->protocol_version.revision);
	printf("Watchdog Timeout       : %d (msec)\n", board->watchdog_timeout);
	printf("Number of Devices      : %d\n", board->devices_count);
	for (int i = 0; i < board->devices_count; i++) {
		protocol_Device* device = &board->devices[i];
		printf("Device                 : %s\n", device->name);
		printf(" Description           : %s\n", device->description);
		switch (device->status) {
		case protocol_DeviceStatus_Ready:
			printf(" Status                : Ready\n");
			break;
		case protocol_DeviceStatus_ActiveWait:
			printf(" Status                : ActiveWait\n");
			break;
		case protocol_DeviceStatus_Active:
			printf(" Status                : Active\n");
			break;
		case protocol_DeviceStatus_Error:
			printf(" Status                : Error\n");
			break;
		}
		printf(" Status Message        : %s\n", device->status_message);
		printf(" ID                    : %d\n", i);
		switch (device->type) {
		case protocol_DeviceType_Unknown:
			printf(" Type                  : Unknown\n");
			break;
		case protocol_DeviceType_Sensor:
			printf(" Type                  : Sensor\n");
			break;
		case protocol_DeviceType_Playback:
			printf(" Type                  : Playback\n");
			break;
		case protocol_DeviceType_Model:
			printf(" Type                  : Model\n");
			break;
		}

		for (int j = 0; j < device->options_count; j++) {
			protocol_Option* option = &device->options[j];
			printf(" Option                : %s\n", option->name);
			printf("   Description         : %s\n", option->description);
			printf("   ID                  : %d\n", option->option_id);
			switch (option->which_value) {
			case protocol_Option_int_type_tag:
				printf("   Type                : Integer\n");
				printf("   Current             : %d\n", option->value.int_type.current_value);
				printf("   Default             : %d\n", option->value.int_type.default_value);
				printf("   Min                 : %d\n", option->value.int_type.min_value);
				printf("   Max                 : %d\n", option->value.int_type.max_value);
				break;
			case protocol_Option_float_type_tag:
				printf("   Type                : Float\n");
				printf("   Current             : %f\n", option->value.float_type.current_value);
				printf("   Default             : %f\n", option->value.float_type.default_value);
				printf("   Min                 : %f\n", option->value.float_type.min_value);
				printf("   Max                 : %f\n", option->value.float_type.max_value);
				break;
			case protocol_Option_bool_type_tag:
				printf("   Type                : Boolean\n");
				printf("   Current             : %s\n", option->value.float_type.current_value ? "True" : "False");
				printf("   Default             : %s\n", option->value.float_type.default_value ? "True" : "False");
				break;
			case protocol_Option_oneof_type_tag:
				printf("   Type                : OneOf\n");
				printf("   Current Index       : %d\n", option->value.oneof_type.current_index);
				printf("   Default Index       : %d\n", option->value.oneof_type.default_index);
				printf("   OneOf               : ");
				for (int k = 0; k < option->value.oneof_type.items_count; k++) {
					printf("[%d]=%s, ", k, option->value.oneof_type.items[k]);
				}
				printf("\n");
			default:
				break;
			}
		}
		for (int j = 0; j < device->streams_count; j++) {
			protocol_StreamConfig* stream = &device->streams[j];
			printf(" Stream                : %s\n", stream->name);
			printf("   ID                  : %d\n", j);
			switch (stream->direction) {
			case protocol_StreamDirection_InputStream:
				printf("   Direction           : InputStream\n");
				break;
			case protocol_StreamDirection_OutputStream:
				printf("   Direction           : OutputStream\n");
				break;
			default:
				break;
			}
			switch (stream->datatype) {
			case protocol_DataType_DATA_TYPE_UNKNOWN:
				printf("   Type                : UNKNOWN\n");
				break;
			case protocol_DataType_DATA_TYPE_U8:
				printf("   Type                : U8\n");
				break;
			case protocol_DataType_DATA_TYPE_S8:
				printf("   Type                : S8\n");
				break;
			case protocol_DataType_DATA_TYPE_U16:
				printf("   Type                : U16\n");
				break;
			case protocol_DataType_DATA_TYPE_S16:
				printf("   Type                : S16\n");
				break;
			case protocol_DataType_DATA_TYPE_U32:
				printf("   Type                : U32\n");
				break;
			case protocol_DataType_DATA_TYPE_S32:
				printf("   Type                : S32\n");
				break;
			case protocol_DataType_DATA_TYPE_F32:
				printf("   Type                : F32\n");
				break;
			case protocol_DataType_DATA_TYPE_F64:
				printf("   Type                : F64\n");
				break;
			default:
				break;
			}
			printf("   Frequency           : %f\n", stream->frequency);
			printf("   Max Frames          : %d\n", stream->max_frame_count);
			printf("   Scale               : %f\n", stream->scale);
			printf("   Offset              : %f\n", stream->offset);
			printf("   Rank                : %d\n", stream->shape_count);
			printf("   Shape               :\n");
			for (int k = 0; k < stream->shape_count; k++) {
				printf("    Dimension %d\n", k);
				printf("     Size              : %d\n", stream->shape[k].size);
				printf("     Name              : %s\n", stream->shape[k].name);
				printf("     Labels            : ");
				for (int l = 0; l < stream->shape[k].labels_count; l++) {
					char* label = stream->shape[k].labels[l];
					if (l != 0)
						printf(", ");
					printf("%s", label == NULL ? "null" : label);
				}
				printf("\n");
			}
		}
	}

}