/*
 * `eyva' - application-widely used variables
 * Copyright (C) 2011 ayekat (martin.weber@epfl.ch)
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _VARIABLES_H_
#define _VARIABLES_H_

/* This is the size of a message head following the eyva protocol:
 */
#define MESSAGE_HEAD_SIZE 4

/* This is the size of the network buffer:
 */
#define BUFFER_SIZE (MESSAGE_HEAD_SIZE+65335)

/* This is the maximum size of the exception message:
 */
#define BUFFER_EXCEPTION_MSG 80

/* Release version:
 */
#define VERSION_MAJOR_RELEASE 0
#define VERSION_MINOR_RELEASE 1
#define VERSION_MAJOR_PATCH 0
#define VERSION_MINOR_PATCH 0

#endif

