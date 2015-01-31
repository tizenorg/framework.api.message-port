/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <tet_api.h>
#include <stdlib.h>
#include <message_port.h>
#include <bundle.h>

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_message_port_register_local_port_n(void);
static void utc_message_port_register_local_port_p(void);
static void utc_message_port_register_trusted_local_port_n(void);
static void utc_message_port_register_trusted_local_port_p(void);
static void utc_message_port_unregister_local_port_n(void);
static void utc_message_port_unregister_local_port_p(void);
static void utc_message_port_unregister_trusted_local_port_n(void);
static void utc_message_port_unregister_trusted_local_port_p(void);
static void uts_message_port_check_remote_port_n(void);
static void uts_message_port_check_remote_port_p(void);
static void uts_message_port_check_trusted_remote_port_n(void);
static void uts_message_port_check_trusted_remote_port_p(void);
static void utc_message_port_send_message_n(void);
static void utc_message_port_send_message_p(void);
static void utc_message_port_send_trusted_message_n(void);
static void utc_message_port_send_trusted_message_p(void);
static void utc_message_port_send_message_with_local_port_n(void);
static void utc_message_port_send_message_with_local_port_p(void);
static void utc_message_port_send_trusted_message_with_local_port_n(void);
static void utc_message_port_send_trusted_message_with_local_port_p(void);

struct tet_testlist tet_testlist[] = {
	{ utc_message_port_register_local_port_n, NEGATIVE_TC_IDX },
	{ utc_message_port_register_local_port_p, POSITIVE_TC_IDX },
	{ utc_message_port_register_trusted_local_port_n, NEGATIVE_TC_IDX },
	{ utc_message_port_register_trusted_local_port_p, POSITIVE_TC_IDX },
	{ utc_message_port_unregister_local_port_n, NEGATIVE_TC_IDX },
	{ utc_message_port_unregister_local_port_p, POSITIVE_TC_IDX },
	{ utc_message_port_unregister_trusted_local_port_n, NEGATIVE_TC_IDX },
	{ utc_message_port_unregister_trusted_local_port_p, POSITIVE_TC_IDX },
	{ uts_message_port_check_remote_port_n, NEGATIVE_TC_IDX },
	{ uts_message_port_check_remote_port_p, POSITIVE_TC_IDX },
	{ uts_message_port_check_trusted_remote_port_n, NEGATIVE_TC_IDX },
	{ uts_message_port_check_trusted_remote_port_p, POSITIVE_TC_IDX },
	{ utc_message_port_send_message_n, NEGATIVE_TC_IDX },
	{ utc_message_port_send_message_p, POSITIVE_TC_IDX },
	{ utc_message_port_send_trusted_message_n, NEGATIVE_TC_IDX },
	{ utc_message_port_send_trusted_message_p, POSITIVE_TC_IDX },
	{ utc_message_port_send_message_with_local_port_n, NEGATIVE_TC_IDX },
	{ utc_message_port_send_message_with_local_port_p, POSITIVE_TC_IDX },
	{ utc_message_port_send_trusted_message_with_local_port_n, NEGATIVE_TC_IDX },
	{ utc_message_port_send_trusted_message_with_local_port_p, POSITIVE_TC_IDX },
	{ NULL, 0 },
};


static void test_cb(int local_port_id, const char *remote_app_id, const char *remote_port, bundle *data);

static const int __local_port_id = 1;
static const char __local_port[] = "my_test_local_port";
static const char __remote_port[] = "my_test_remote_port";
static const char __remote_app_id[] = "remoteapp1";
static message_port_message_cb __message_cb = test_cb;
static message_port_trusted_message_cb __trusted_message_cb = test_cb;
static bundle* __bundle = NULL;

static const int __invalid_local_port_id = -1;
static const char* __invalid_local_port = NULL;
static const char* __invalid_remote_port = NULL;
static const char* __invalid_remote_app_id = NULL;
static message_port_message_cb __invalid_message_cb = NULL;
static message_port_trusted_message_cb __invalid_trusted_message_cb = NULL;
static bundle* __invalid_bundle = NULL;


void
startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
	__bundle = bundle_create();
}

void
cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");
	bundle_free(__bundle);
}


void
test_cb(int local_port_id, const char *remote_app_id, const char *remote_port, bundle *data)
{
}


void
utc_message_port_register_local_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_register_local_port(__local_port, __invalid_message_cb);
	dts_check_eq("message_port_register_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_register_local_port(__invalid_local_port, __message_cb);
	dts_check_eq("message_port_register_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_register_local_port_p(void)
{
	dts_message("message_port_register_local_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_register_local_port");
}

void
utc_message_port_register_trusted_local_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_register_trusted_local_port(__local_port, __invalid_trusted_message_cb);
	dts_check_eq("message_port_register_trusted_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_register_trusted_local_port(__invalid_local_port, __trusted_message_cb);
	dts_check_eq("message_port_register_trusted_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_register_trusted_local_port_p(void)
{
	dts_message("message_port_register_trusted_local_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_register_trusted_local_port");
}

void
utc_message_port_unregister_local_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_unregister_local_port(__invalid_local_port_id);
	dts_check_eq("message_port_unregister_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_unregister_local_port_p(void)
{
	dts_message("message_port_unregister_local_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_unregister_local_port");
}

void
utc_message_port_unregister_trusted_local_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_unregister_trusted_local_port(__invalid_local_port_id);
	dts_check_eq("message_port_unregister_trusted_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_unregister_trusted_local_port_p(void)
{
	dts_message("message_port_unregister_trusted_local_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_unregister_trusted_local_port");
}
void
uts_message_port_check_remote_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	res = message_port_check_remote_port(__remote_app_id, __invalid_remote_port, &exist);
	dts_check_eq("message_port_check_remote_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_check_remote_port(__invalid_remote_app_id, __remote_port, &exist);
	dts_check_eq("message_port_check_remote_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
uts_message_port_check_remote_port_p(void)
{
	dts_message("message_port_check_remote_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_check_remote_port");
}

void
uts_message_port_check_trusted_remote_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	res = message_port_check_trusted_remote_port(__remote_app_id, __invalid_remote_port, &exist);
	dts_check_eq("message_port_check__trusted_remote_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_check_trusted_remote_port(__invalid_remote_app_id, __remote_port, &exist);
	dts_check_eq("message_port_check__trusted_remote_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
uts_message_port_check_trusted_remote_port_p(void)
{
	dts_message("message_port_check_trusted_remote_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_check_trusted_remote_port");
}

void
utc_message_port_send_message_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message(__remote_app_id, __remote_port, __invalid_bundle);
	dts_check_eq("message_port_send_message", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_message(__remote_app_id, __invalid_remote_port, __bundle);
	dts_check_eq("message_port_send_message", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_message(__invalid_remote_app_id, __remote_port, __bundle);
	dts_check_eq("message_port_send_message", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_send_message_p(void)
{
	dts_message("message_port_send_message", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_send_message");
}

void
utc_message_port_send_trusted_message_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message(__remote_app_id, __remote_port, __invalid_bundle);
	dts_check_eq("message_port_send_trusted_message", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_trusted_message(__remote_app_id, __invalid_remote_port, __bundle);
	dts_check_eq("message_port_send_trusted_message", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_trusted_message(__invalid_remote_app_id, __remote_port, __bundle);
	dts_check_eq("message_port_send_trusted_message", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_send_trusted_message_p(void)
{
	dts_message("message_port_send_trusted_message", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_send_trusted_message");
}

void
utc_message_port_send_message_with_local_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message_with_local_port(__remote_app_id, __remote_port, __invalid_bundle, __local_port_id);
	dts_check_eq("message_port_send_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_message_with_local_port(__remote_app_id, __invalid_remote_port, __bundle, __local_port_id);
	dts_check_eq("message_port_send_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_message_with_local_port(__invalid_remote_app_id, __remote_port, __bundle, __local_port_id);
	dts_check_eq("message_port_send_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_message_with_local_port(__remote_app_id, __remote_port, __bundle, __invalid_local_port_id);
	dts_check_eq("message_port_send_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_send_message_with_local_port_p(void)
{
	dts_message("message_port_send_message_with_local_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_send_message_with_local_port");
}

void
utc_message_port_send_trusted_message_with_local_port_n(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __remote_port, __invalid_bundle, __local_port_id);
	dts_check_eq("message_port_send_trusted_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __invalid_remote_port, __bundle, __local_port_id);
	dts_check_eq("message_port_send_trusted_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_trusted_message_with_local_port(__invalid_remote_app_id, __remote_port, __bundle, __local_port_id);
	dts_check_eq("message_port_send_trusted_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __remote_port, __bundle, __invalid_local_port_id);
	dts_check_eq("message_port_send_trusted_message_with_local_port", res, MESSAGE_PORT_ERROR_INVALID_PARAMETER, "Must return MESSAGE_PORT_ERROR_INVALID_PARAMETER!");
}

void
utc_message_port_send_trusted_message_with_local_port_p(void)
{
	dts_message("message_port_send_trusted_message_with_local_port", "Cannot test postive case because the test app hasn't 'APP ID'");
	dts_pass("message_port_send_trusted_message_with_local_port");
}
