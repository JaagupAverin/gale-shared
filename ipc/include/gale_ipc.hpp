#pragma once

#include <stdint.h>

enum MessageType {
	MSG_TYPE_GET_VERSION,
	MSG_TYPE_RSP_VERSION,
};

struct IpcMessage {
	uint16_t type;
	uint16_t size;
	void* data;
};
