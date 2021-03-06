/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Dynamic Virtual Channel
 *
 * Copyright 2010-2011 Vic Lee
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __DRDYNVC_MAIN_H
#define __DRDYNVC_MAIN_H

#include <winpr/wlog.h>

#include <freerdp/api.h>
#include <freerdp/svc.h>
#include <freerdp/addin.h>
#include <freerdp/client/drdynvc.h>

enum _DRDYNVC_STATE
{
	DRDYNVC_STATE_INITIAL,
	DRDYNVC_STATE_CAPABILITIES,
	DRDYNVC_STATE_READY,
	DRDYNVC_STATE_OPENING_CHANNEL,
	DRDYNVC_STATE_SEND_RECEIVE,
	DRDYNVC_STATE_FINAL
};
typedef enum _DRDYNVC_STATE DRDYNVC_STATE;

#define CREATE_REQUEST_PDU		0x01
#define DATA_FIRST_PDU			0x02
#define DATA_PDU			0x03
#define CLOSE_REQUEST_PDU		0x04
#define CAPABILITY_REQUEST_PDU		0x05

struct drdynvc_plugin
{
	CHANNEL_DEF channelDef;
	CHANNEL_ENTRY_POINTS_FREERDP channelEntryPoints;

	wLog* log;
	HANDLE thread;
	wStream* data_in;
	void* InitHandle;
	DWORD OpenHandle;
	wMessagePipe* MsgPipe;

	DRDYNVC_STATE state;
	DrdynvcClientContext* context;

	int version;
	int PriorityCharge0;
	int PriorityCharge1;
	int PriorityCharge2;
	int PriorityCharge3;
	int channel_error;

	IWTSVirtualChannelManager* channel_mgr;
};
typedef struct drdynvc_plugin drdynvcPlugin;

int drdynvc_write_data(drdynvcPlugin* plugin, UINT32 ChannelId, BYTE* data, UINT32 data_size);

#endif
