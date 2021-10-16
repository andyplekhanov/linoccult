//------------------------------------------------------------------------------
//
// File:    apssort.cc
//
// Purpose: Class for quick sorting
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 01.03.2004
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

#include "apssort.h"

namespace aps {

  namespace apsmathlib {

//------------------------------- APSSort ------------------------------

APSSort :: APSSort( void )
{
}

APSSort :: ~APSSort( void )
{
}

void APSSort :: QuickSort( const void ** ppArr, const int d, const int h, const int Type ) const
{
  int          i;
  int          j;
  const void * p;
  const void * tmp;

  i = h;
  j = d;

  p = ppArr[ (int) ( ( d + h ) / 2 ) ];

  do {
    while( Compare( ppArr[ j ], p, Type ) < 0 ) {
      j++;
    }

    while( Compare( ppArr[ i ], p, Type ) > 0 ) {
      i--;
    }

    if( i >= j ) {
      tmp = ppArr[ i ];
      ppArr[ i ] = ppArr[ j ];
      ppArr[ j ] = tmp;

      i--;
      j++;
    }
  } while( j <= i );

  if( d < i ) {
    QuickSort( ppArr, d, i, Type );
  }

  if( j < h ) {
    QuickSort( ppArr, j, h, Type );
  }
}

/*void APSSort :: QuickSort( const void ** ppArr, const int d, const int h, const int Type ) const
{
  int          i;
  int          j;
  const void * tmp;

  for( i = d; i <= h; i++ ) {
    for( j = i + 1; j <= h; j++ ) {
      if( Compare( ppArr[ i ], ppArr[ j ], Type ) > 0 ) {
        tmp = ppArr[ i ];
        ppArr[ i ] = ppArr[ j ];
        ppArr[ j ] = tmp;
      }
    }
  }
}*/

void APSSort :: Sort( const void ** ppArr, const int Size, const int Type ) const
{
  QuickSort( ppArr, 0, Size - 1, Type );
}

}}

//---------------------------- End of file ---------------------------
