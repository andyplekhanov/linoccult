//------------------------------------------------------------------------------
//
// File:    apsbyteorder.h
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

#ifndef 	_APSBYTEORDER_H_
#define         _APSBYTEORDER_H_	1

#include <stdint.h>

namespace aps {

  namespace apslib {

enum
{
  ABS_ARCH_UNKNOWN = 0,
  ABS_ARCH_LITTLE,
  ABS_ARCH_BIG
};

class APSByteOrder
{
  private:

    int ArchType;

  public:

    APSByteOrder( void );

    ~APSByteOrder( void ) {}

    int GetArchType( void ) const
      { return( ArchType ); }

    int16_t SwapShort( const int16_t Short ) const;

    int32_t SwapInteger( const int32_t Int ) const;

    int64_t SwapLong( const int64_t Long ) const;

    float SwapFloat( const float Flt ) const;

    double SwapDouble( const double Dbl ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------

