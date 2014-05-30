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

#include "debug.h"
#include <stdlib.h>

void trace_debug(const char * fmt, ...)
{
	const char *p;
	va_list argp;
	int i;
	char *s;
	time_t current_time;
	struct tm * time_info;
	char timeString[9];  // space for "HH:MM:SS\0"

	time(&current_time);
	time_info = localtime(&current_time);

	strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
	printf("[%s]: ", timeString);
	
	va_start(argp, fmt);
	for(p = fmt; *p != '\0'; p++)
	{
		if(*p != '%')
		{
			putchar(*p);
			continue;
		}
		
		switch(*++p)
		{
			case 'c':
				i = va_arg(argp, int);
				putchar(i);
				break;

			case 'd':
				i = va_arg(argp, int);
				printf("%d", i);
				break;

			case 's':
				s = va_arg(argp, char *);
				fputs(s, stdout);
				break;

			case 'x':
				i = va_arg(argp, int);
				printf("%d", i);
				break;

			case '%':
				putchar('%');
				break;
		}
	}
	va_end(argp);


}
