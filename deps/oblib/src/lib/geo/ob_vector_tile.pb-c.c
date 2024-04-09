/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */
/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ob_vector_tile.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ob_vector_tile.pb-c.h"
void   vector_tile__tile__value__init
                     (VectorTile__Tile__Value         *message)
{
  static const VectorTile__Tile__Value init_value = VECTOR_TILE__TILE__VALUE__INIT;
  *message = init_value;
}
void   vector_tile__tile__feature__init
                     (VectorTile__Tile__Feature         *message)
{
  static const VectorTile__Tile__Feature init_value = VECTOR_TILE__TILE__FEATURE__INIT;
  *message = init_value;
}
void   vector_tile__tile__layer__init
                     (VectorTile__Tile__Layer         *message)
{
  static const VectorTile__Tile__Layer init_value = VECTOR_TILE__TILE__LAYER__INIT;
  *message = init_value;
}
void   vector_tile__tile__init
                     (VectorTile__Tile         *message)
{
  static const VectorTile__Tile init_value = VECTOR_TILE__TILE__INIT;
  *message = init_value;
}
size_t vector_tile__tile__get_packed_size
                     (const VectorTile__Tile *message)
{
  assert(message->base.descriptor == &vector_tile__tile__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t vector_tile__tile__pack
                     (const VectorTile__Tile *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &vector_tile__tile__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t vector_tile__tile__pack_to_buffer
                     (const VectorTile__Tile *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &vector_tile__tile__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
VectorTile__Tile *
       vector_tile__tile__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (VectorTile__Tile *)
     protobuf_c_message_unpack (&vector_tile__tile__descriptor,
                                allocator, len, data);
}
void   vector_tile__tile__free_unpacked
                     (VectorTile__Tile *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &vector_tile__tile__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor vector_tile__tile__value__field_descriptors[7] =
{
  {
    "string_value",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    offsetof(VectorTile__Tile__Value, test_oneof_case),
    offsetof(VectorTile__Tile__Value, string_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "float_value",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FLOAT,
    offsetof(VectorTile__Tile__Value, test_oneof_case),
    offsetof(VectorTile__Tile__Value, float_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "double_value",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_DOUBLE,
    offsetof(VectorTile__Tile__Value, test_oneof_case),
    offsetof(VectorTile__Tile__Value, double_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "int_value",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT64,
    offsetof(VectorTile__Tile__Value, test_oneof_case),
    offsetof(VectorTile__Tile__Value, int_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "uint_value",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(VectorTile__Tile__Value, test_oneof_case),
    offsetof(VectorTile__Tile__Value, uint_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "sint_value",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_SINT64,
    offsetof(VectorTile__Tile__Value, test_oneof_case),
    offsetof(VectorTile__Tile__Value, sint_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "bool_value",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_BOOL,
    offsetof(VectorTile__Tile__Value, test_oneof_case),
    offsetof(VectorTile__Tile__Value, bool_value),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned vector_tile__tile__value__field_indices_by_name[] = {
  6,   /* field[6] = bool_value */
  2,   /* field[2] = double_value */
  1,   /* field[1] = float_value */
  3,   /* field[3] = int_value */
  5,   /* field[5] = sint_value */
  0,   /* field[0] = string_value */
  4,   /* field[4] = uint_value */
};
static const ProtobufCIntRange vector_tile__tile__value__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 7 }
};
const ProtobufCMessageDescriptor vector_tile__tile__value__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "vector_tile.Tile.Value",
  "Value",
  "VectorTile__Tile__Value",
  "vector_tile",
  sizeof(VectorTile__Tile__Value),
  7,
  vector_tile__tile__value__field_descriptors,
  vector_tile__tile__value__field_indices_by_name,
  1,  vector_tile__tile__value__number_ranges,
  (ProtobufCMessageInit) vector_tile__tile__value__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const uint64_t vector_tile__tile__feature__id__default_value = 0ull;
static const VectorTile__Tile__GeomType vector_tile__tile__feature__type__default_value = VECTOR_TILE__TILE__GEOM_TYPE__UNKNOWN;
static const ProtobufCFieldDescriptor vector_tile__tile__feature__field_descriptors[4] =
{
  {
    "id",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_UINT64,
    offsetof(VectorTile__Tile__Feature, has_id),
    offsetof(VectorTile__Tile__Feature, id),
    NULL,
    &vector_tile__tile__feature__id__default_value,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "tags",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(VectorTile__Tile__Feature, n_tags),
    offsetof(VectorTile__Tile__Feature, tags),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "type",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(VectorTile__Tile__Feature, type),
    &vector_tile__tile__geom_type__descriptor,
    &vector_tile__tile__feature__type__default_value,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "geometry",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(VectorTile__Tile__Feature, n_geometry),
    offsetof(VectorTile__Tile__Feature, geometry),
    NULL,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_PACKED,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned vector_tile__tile__feature__field_indices_by_name[] = {
  3,   /* field[3] = geometry */
  0,   /* field[0] = id */
  1,   /* field[1] = tags */
  2,   /* field[2] = type */
};
static const ProtobufCIntRange vector_tile__tile__feature__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor vector_tile__tile__feature__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "vector_tile.Tile.Feature",
  "Feature",
  "VectorTile__Tile__Feature",
  "vector_tile",
  sizeof(VectorTile__Tile__Feature),
  4,
  vector_tile__tile__feature__field_descriptors,
  vector_tile__tile__feature__field_indices_by_name,
  1,  vector_tile__tile__feature__number_ranges,
  (ProtobufCMessageInit) vector_tile__tile__feature__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const uint32_t vector_tile__tile__layer__version__default_value = 1u;
static const uint32_t vector_tile__tile__layer__extent__default_value = 4096u;
static const ProtobufCFieldDescriptor vector_tile__tile__layer__field_descriptors[6] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(VectorTile__Tile__Layer, name),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "features",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(VectorTile__Tile__Layer, n_features),
    offsetof(VectorTile__Tile__Layer, features),
    &vector_tile__tile__feature__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "keys",
    3,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(VectorTile__Tile__Layer, n_keys),
    offsetof(VectorTile__Tile__Layer, keys),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "values",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(VectorTile__Tile__Layer, n_values),
    offsetof(VectorTile__Tile__Layer, values),
    &vector_tile__tile__value__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "extent",
    5,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(VectorTile__Tile__Layer, extent),
    NULL,
    &vector_tile__tile__layer__extent__default_value,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "version",
    15,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(VectorTile__Tile__Layer, version),
    NULL,
    &vector_tile__tile__layer__version__default_value,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned vector_tile__tile__layer__field_indices_by_name[] = {
  4,   /* field[4] = extent */
  1,   /* field[1] = features */
  2,   /* field[2] = keys */
  0,   /* field[0] = name */
  3,   /* field[3] = values */
  5,   /* field[5] = version */
};
static const ProtobufCIntRange vector_tile__tile__layer__number_ranges[2 + 1] =
{
  { 1, 0 },
  { 15, 5 },
  { 0, 6 }
};
const ProtobufCMessageDescriptor vector_tile__tile__layer__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "vector_tile.Tile.Layer",
  "Layer",
  "VectorTile__Tile__Layer",
  "vector_tile",
  sizeof(VectorTile__Tile__Layer),
  6,
  vector_tile__tile__layer__field_descriptors,
  vector_tile__tile__layer__field_indices_by_name,
  2,  vector_tile__tile__layer__number_ranges,
  (ProtobufCMessageInit) vector_tile__tile__layer__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue vector_tile__tile__geom_type__enum_values_by_number[4] =
{
  { "UNKNOWN", "VECTOR_TILE__TILE__GEOM_TYPE__UNKNOWN", 0 },
  { "POINT", "VECTOR_TILE__TILE__GEOM_TYPE__POINT", 1 },
  { "LINESTRING", "VECTOR_TILE__TILE__GEOM_TYPE__LINESTRING", 2 },
  { "POLYGON", "VECTOR_TILE__TILE__GEOM_TYPE__POLYGON", 3 },
};
static const ProtobufCIntRange vector_tile__tile__geom_type__value_ranges[] = {
{0, 0},{0, 4}
};
static const ProtobufCEnumValueIndex vector_tile__tile__geom_type__enum_values_by_name[4] =
{
  { "LINESTRING", 2 },
  { "POINT", 1 },
  { "POLYGON", 3 },
  { "UNKNOWN", 0 },
};
const ProtobufCEnumDescriptor vector_tile__tile__geom_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "vector_tile.Tile.GeomType",
  "GeomType",
  "VectorTile__Tile__GeomType",
  "vector_tile",
  4,
  vector_tile__tile__geom_type__enum_values_by_number,
  4,
  vector_tile__tile__geom_type__enum_values_by_name,
  1,
  vector_tile__tile__geom_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor vector_tile__tile__field_descriptors[1] =
{
  {
    "layers",
    3,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(VectorTile__Tile, n_layers),
    offsetof(VectorTile__Tile, layers),
    &vector_tile__tile__layer__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned vector_tile__tile__field_indices_by_name[] = {
  0,   /* field[0] = layers */
};
static const ProtobufCIntRange vector_tile__tile__number_ranges[1 + 1] =
{
  { 3, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor vector_tile__tile__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "vector_tile.Tile",
  "Tile",
  "VectorTile__Tile",
  "vector_tile",
  sizeof(VectorTile__Tile),
  1,
  vector_tile__tile__field_descriptors,
  vector_tile__tile__field_indices_by_name,
  1,  vector_tile__tile__number_ranges,
  (ProtobufCMessageInit) vector_tile__tile__init,
  NULL,NULL,NULL    /* reserved[123] */
};
