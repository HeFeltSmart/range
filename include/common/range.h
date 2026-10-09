/*
 * include/common/range.h
 * 
 * Copyright (C) 2026 Daniel J DeLuca
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://gnu.org>.
 */

#ifndef COMMON_RANGE_H
#define COMMON_RANGE_H

#include <stdbool.h>
#include <stdint.h>    /* For explicit types like uint16_t, uint8_t */
#include <sys/types.h> /* For standard system types like size_t, ssize_t */

#define RANGE_MACRO( type ) \
typedef struct              \
{                           \
    type minimum;           \
    type maximum;           \
} type##Range;

/* Pre-defined standard range types */
RANGE_MACRO(double)    /* Generates doubleRange */
RANGE_MACRO(float)     /* Generates floatRange */
RANGE_MACRO(char)      /* Generates charRange */
RANGE_MACRO(wchar_t)   /* Generates wchar_tRange */
RANGE_MACRO(uint16_t)  /* Generates uint16_tRange */
RANGE_MACRO(uint32_t)  /* Generates uint32_tRange */
RANGE_MACRO(int16_t)   /* Generates int16_tRange */
RANGE_MACRO(int32_t)   /* Generates int32_tRange */

/* Alias macro to generate custom-named range structures */
#define RANGE_ALIAS_MACRO( type, alias_name) \
typedef struct                               \
{                                            \
    type minimum;                            \
    type maximum;                            \
} alias_name##Range;

/* Pre-defined standard range types */
RANGE_MACRO(double)
RANGE_MACRO(float)
RANGE_MACRO(char)

/* Handle wchar carefully to match wcharRange casing */
RANGE_ALIAS_MACRO(wchar_t, wchar)

/* Fixed-width integer types with explicit capitalized aliases */
RANGE_ALIAS_MACRO(uint16_t, UInt16)
RANGE_ALIAS_MACRO(uint32_t, UInt32)
RANGE_ALIAS_MACRO(int16_t,  Int16)
RANGE_ALIAS_MACRO(int32_t,  Int32)

#define IN_RANGE( value, range ) \
( ( value >= range.minimum ) &&  \
  ( value <= range.maximum ) )

#define NOT_IN_RANGE( value, range ) \
!IN_RANGE( value, range )


/* 
 * 2D Bounding Box built completely from your existing range types.
 * Allows you to mix types if necessary (e.g., x uses Int16Range, y uses Int32Range).
 */
#define DEFINE_BOX_2D( x_range_type, y_range_type, name ) \
typedef struct                                            \
{                                                         \
    x_range_type x;                                       \
    y_range_type y;                                       \
} name##Box2D;

/* 3D Bounding Cube built from separate range types per dimension */
#define DEFINE_CUBE_3D( x_range_type, y_range_type, z_range_type, name ) \
typedef struct                                                           \
{                                                                        \
    x_range_type x;                                                      \
    y_range_type y;                                                      \
    z_range_type z;                                                      \
} name##Cube3D;


/* Check if a 2D point falls inside a composed bounding box */
#define IN_BOX_2D( x_val, y_val, box ) \
( IN_RANGE( x_val, (box).x ) &&        \
  IN_RANGE( y_val, (box).y ) )

/* Check if a 3D point falls inside a composed bounding cube */
#define IN_CUBE_3D( x_val, y_val, z_val, cube ) \
( IN_RANGE( x_val, (cube).x ) &&                \
  IN_RANGE( y_val, (cube).y ) &&                \
  IN_RANGE( z_val, (cube).z ) )

#endif
