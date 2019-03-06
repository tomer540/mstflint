/*                  - Mellanox Confidential and Proprietary -
 *
 * Copyright (C) February 2010, Mellanox Technologies Ltd. ALL RIGHTS RESERVED.
 *
 * Except as specifically permitted herein, no portion of the information,
 * including but not limited to object code and source code, may be reproduced,
 * modified, distributed, republished or otherwise exploited in any form or by
 * any means for any purpose without the prior written permission of Mellanox
 * Technologies Ltd. Use of software subject to the terms and conditions
 * detailed in the file "LICENSE.txt".
 *
 * End of legal section ......................................................
 *
 *  adb_db.h - "C" wrapper module for adb_parser classes.
 *             This module provides an alternative "C" way to work with AdbInstance objects.
 *
 *  Version: $Id$
 *
 *  Author: Wasim Abu Moch (wasim@mellanox.co.il)
 */
#ifndef ADB_DB_H
#define ADB_DB_H

#include <stdio.h>
#include <common/compatibility.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void adb_db_t;
typedef void adb_node_t;
typedef void adb_field_t;
typedef void adb_limits_map_t;

typedef enum
{
    DB_FORMAT_STANDARD,
    DB_FORMAT_STANDARD_NO_ENUM,
    DB_FORMAT_FULL_DETAILS
} dump_format_t;

// TODO - this API isn't thread-safe because of the error reporting mechanism
// DB Functions
adb_db_t*       db_create();
int             db_load(adb_db_t *db, const char *adb_file_path, int add_reserved);
int             db_load_from_str(adb_db_t *db, const char *adb_data, int add_reserved);
void            db_destroy(adb_db_t *db);
const char*     db_get_last_err();

adb_limits_map_t* db_create_limits_map(adb_db_t *db);
void            db_destroy_limits_map(adb_limits_map_t *limits);

// Node Functions - *** node contains flat fields (full path leaves) ***
adb_node_t*     db_get_node(adb_db_t *db, const char *node_name);
void            db_node_destroy(adb_node_t *node);
void            db_node_name(adb_node_t *node, char name[]);
int             db_node_size(adb_node_t *node);
int             db_node_num_of_fields(adb_node_t *node);
adb_field_t*    db_node_get_field(adb_node_t *node, int field_idx);
adb_field_t*    db_node_get_field_by_path(adb_node_t *node, const char *path, int is_case_sensitive);
bool            db_node_dump(adb_node_t *node, u_int8_t buf[], dump_format_t format, FILE *stream);
bool            db_node_conditional_dump(adb_node_t *node, u_int8_t buf[], dump_format_t format,
                                         FILE *stream, adb_limits_map_t *values_map);
bool            db_node_range_dump(adb_node_t *node, u_int32_t from, u_int32_t to,
                                   u_int8_t buf[], dump_format_t format, FILE *stream);
bool            db_node_conditional_range_dump(adb_node_t *node, u_int32_t from, u_int32_t to,
                                               u_int8_t buf[], dump_format_t format, FILE *stream, adb_limits_map_t *values_map);

// Field Functions
void            db_field_name(adb_field_t *field, char name[]);
void            db_field_full_name(adb_field_t *field, int skip_level, char name[]);
int             db_field_offset(adb_field_t *field);
int             db_field_size(adb_field_t *field);
u_int64_t       db_field_value(adb_field_t *field, u_int8_t buf[]);
void            db_field_set_value(adb_field_t *field, u_int8_t buf[], u_int64_t value);
int             db_field_enum(adb_field_t *field, u_int64_t value, char enum_str[]);

// For debug only
void            db_print_nodes(adb_db_t *db);

#ifdef __cplusplus
}
#endif

#endif // ADB_DB_H