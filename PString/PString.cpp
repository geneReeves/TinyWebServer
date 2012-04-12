/*
  PString.cpp - Lightweight printable string class
  Copyright (c) 2009 Mikal Hart.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "PString.h"

void PString::begin()
{
  _cur = _buf;
  if (_size > 0)
    _buf[0] = '\0';
}

size_t PString::write(uint8_t b)
{
  //if (_cur==0) return 0;
  if ((_cur + 1) < (_buf + _size))
  {
    *_cur++ = (char)b;
    *_cur = '\0';
    return (size_t)1;
  } else {
    return (size_t)0;
  }
}

int PString::format(char *str, ...) 
{ 
  va_list argptr;  
  va_start(argptr, str); 
  int ret = vsnprintf((char *)_cur, _size - (_cur - _buf), str, argptr);
  va_end(argptr);
  if (_size)
     while (*_cur) 
        ++_cur;
  return ret;
}

int PString::formatP(const char *str, ...) 
{ 
  va_list argptr;  
  va_start(argptr, str); 
  int ret = vsnprintf_P((char *)_cur, _size - (_cur - _buf), str, argptr);
  va_end(argptr);
  if (_size)
     while (*_cur) 
        ++_cur;
  return ret;
}

int PString::format(const __FlashStringHelper *str, ...) 
{ 
  va_list argptr;  
  va_start(argptr, str); 
  const prog_char *p = (const prog_char *)str;
  int ret = vsnprintf_P((char *)_cur, _size - (_cur - _buf), p, argptr);
  va_end(argptr);
  if (_size)
     while (*_cur) 
        ++_cur;
  return ret;
}

void PString::printP(const char *str)
{
  while (_buf[*_cur++] = pgm_read_byte(str++)) 
    if (*_cur == _size)
	  break;
  _buf[*_cur++] ='\0';
}



