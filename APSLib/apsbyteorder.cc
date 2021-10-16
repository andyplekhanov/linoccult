//------------------------------------------------------------------------------
//
// File:    apsbyteorder.cc
//
// Purpose: Byte order in currect computer
//   
// (c) 2006-2020 Plekhanov Andrey
//
// Initial version 0.1 23.02.2006
// Swap for long   0.2 09.01.2020
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//------------------------------------------------------------------------------

#include "apsbyteorder.h"

namespace aps {

  namespace apslib {

typedef union
{
  char a[ 4 ];
  int32_t i;
} MyUnion;

APSByteOrder :: APSByteOrder( void )
{
  MyUnion m;

  ArchType = ABS_ARCH_UNKNOWN;

  m.i = 0x12345678;

  if( ( m.a[ 0 ] == 0x78 ) &&
      ( m.a[ 1 ] == 0x56 ) &&
      ( m.a[ 2 ] == 0x34 ) &&
      ( m.a[ 3 ] == 0x12 ) ) {
    ArchType = ABS_ARCH_LITTLE;
  }
  else {
    if( ( m.a[ 0 ] == 0x12 ) &&
        ( m.a[ 1 ] == 0x34 ) &&
        ( m.a[ 2 ] == 0x56 ) &&
        ( m.a[ 3 ] == 0x78 ) ) {
      ArchType = ABS_ARCH_BIG;
    }
  }
}

typedef union
{
  char  a[ 2 ];
  int16_t s;
} ShortUnion;

int16_t APSByteOrder :: SwapShort( const int16_t Short ) const
{
  char       TmpChar;
  ShortUnion s;

  s.s      = Short;
  TmpChar  = s.a[ 0 ];
  s.a[ 0 ] = s.a[ 1 ];
  s.a[ 1 ] = TmpChar;

  return( s.s );
}

typedef union
{
  char a[ 4 ];
  int32_t i;
} IntUnion;

typedef union
{
  char a[ 8 ];
  int64_t i;
} LongUnion;

int32_t APSByteOrder :: SwapInteger( const int32_t Int ) const
{
  char     TmpChar;
  IntUnion i;

  i.i = Int;

  TmpChar  = i.a[ 0 ];
  i.a[ 0 ] = i.a[ 3 ];
  i.a[ 3 ] = TmpChar;

  TmpChar  = i.a[ 1 ];
  i.a[ 1 ] = i.a[ 2 ];
  i.a[ 2 ] = TmpChar;

  return( i.i );
}

int64_t APSByteOrder :: SwapLong( const int64_t Long ) const
{
  char      TmpChar;
  LongUnion i;

  i.i = Long;

  TmpChar  = i.a[ 0 ];
  i.a[ 0 ] = i.a[ 7 ];
  i.a[ 7 ] = TmpChar;

  TmpChar  = i.a[ 1 ];
  i.a[ 1 ] = i.a[ 6 ];
  i.a[ 6 ] = TmpChar;

  TmpChar  = i.a[ 2 ];
  i.a[ 2 ] = i.a[ 5 ];
  i.a[ 5 ] = TmpChar;

  TmpChar  = i.a[ 3 ];
  i.a[ 3 ] = i.a[ 4 ];
  i.a[ 4 ] = TmpChar;

  return( i.i );
}

typedef union
{
  char  a[ 4 ];
  float f;
} FltUnion;

float APSByteOrder :: SwapFloat( const float Flt ) const
{
  char     TmpChar;
  FltUnion f;

  f.f = Flt;

  TmpChar  = f.a[ 0 ];
  f.a[ 0 ] = f.a[ 3 ];
  f.a[ 3 ] = TmpChar;

  TmpChar  = f.a[ 1 ];
  f.a[ 1 ] = f.a[ 2 ];
  f.a[ 2 ] = TmpChar;

  return( f.f );
}

typedef union
{
  char   a[ 8 ];
  double d;
} DblUnion;

double APSByteOrder :: SwapDouble( const double Dbl ) const
{
  char     TmpChar;
  DblUnion d;

  d.d = Dbl;

  TmpChar  = d.a[ 0 ];
  d.a[ 0 ] = d.a[ 7 ];
  d.a[ 7 ] = TmpChar;

  TmpChar  = d.a[ 1 ];
  d.a[ 1 ] = d.a[ 6 ];
  d.a[ 6 ] = TmpChar;

  TmpChar  = d.a[ 2 ];
  d.a[ 2 ] = d.a[ 5 ];
  d.a[ 5 ] = TmpChar;

  TmpChar  = d.a[ 3 ];
  d.a[ 3 ] = d.a[ 4 ];
  d.a[ 4 ] = TmpChar;

  return( d.d );
}

}}

//---------------------------- End of file ---------------------------
