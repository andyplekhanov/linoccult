//------------------------------------------------------------------------------
//
// File:    apsrandom.c
//
// Purpose: Random number generator based on Galua fields
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 27.05.2004
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

#include "apsrandom.h"

namespace aps {

  namespace apslib {

const uint32_t Poly = 2147483735U;

static uint32_t Current = 1;

static int Sum( const uint32_t Number )
{
  unsigned int i;
  uint32_t     Register;
  int          Count;

  Count = 0;
  Register = 1;

  for( i = 0; i < 8 * sizeof( uint32_t ); i++ ) {
    if( Register & Number ) {
      Count++;
    }

    Register = Register + Register;
  }

  return( Count );
}

static uint32_t GenerateNextNumber( void )
{
  if( Sum( Current & Poly ) % 2 ) {
    Current = Current + Current;
    Current++;
  }
  else {
    Current = Current + Current;
  }

  return( Current );
}

void SetCurrent( const uint32_t NewCurrent )
{
  Current = NewCurrent;
}

uint32_t GetCurrent( void )
{
  return( Current );
}

uint32_t GetRandomNumber( const uint32_t Module )
{
  if( Module ) {
    return( ( GenerateNextNumber() - 1 ) % Module );
  }

  return( 0 );
}

}}

//---------------------------- End of file ---------------------------

