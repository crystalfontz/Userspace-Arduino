/*
  
  Copyright (c) 2014 Mitul Vekariya <vekariya93@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  Modified 28 September 2010 by Mark Sproul

*/

#ifndef _DEBUG_
#define _DEBUG_

#include <stdio.h>
#include <stdarg.h>
#include <time.h>


#ifdef __cplusplus
extern "C" {
#endif

void trace_debug(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_ */
