//------------------------------------------------------------------------------
//
// File:    apsabschebmaker.cc
//
// Purpose: Abstract class for creating three dimensional Chebyshev approximation.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 17.05.2004
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

#include <cmath>

#include "apsabschebmaker.h"
#include "apsmathconst.h"
#include "apsvec3d.h"

namespace aps {

  namespace apsmathlib {

APSAbsChebMaker :: APSAbsChebMaker( void )
{
}

APSAbsChebMaker :: ~APSAbsChebMaker( void )
{
}

int APSAbsChebMaker :: Create( const unsigned int Order, const double ta, const double tb,
                               double cX[], double cY[], double cZ[] )
{
  unsigned int   j;
  int            k;
  double         tau;
  double         t;
  double         fac;
  double       * T;
  APSVec3d       f;
  int            RetCode;

  RetCode = 0;

  T = new double[ Order + 1 ];

  for( j = 0; j <= Order; j++ ) {
    cX[ j ] = 0.0;
    cY[ j ] = 0.0;
    cZ[ j ] = 0.0;
  } 
  
  for( k = static_cast<int>( Order ); k >= 0; k-- ) {
    tau = cos( ( 2 * k + 1 ) * pi / ( 2 * Order + 2 ) );
    t = ( ( tb - ta ) / 2.0 ) * tau + ( ( tb + ta ) / 2.0 );
    f = GetValue( t );
    
    for( j = 0; j <= Order; j++ ) {
      switch( j ) {
        case 0:
          T[ 0 ] = 1.0;
        break;
        case 1:
          T[ 1 ] = tau;
        break;
        default:
          T[ j ] = 2.0 * tau * T[ j - 1 ] - T[ j - 2 ];
      };

      cX[ j ] += f[ x ] * T[ j ];
      cY[ j ] += f[ y ] * T[ j ];
      cZ[ j ] += f[ z ] * T[ j ];  
    }; 
  };

  fac = 2.0 / ( Order + 1 );

  for( j = 0; j <= Order; j++ ) {
    cX[ j ] *= fac;
    cY[ j ] *= fac;
    cZ[ j ] *= fac;
  }

  delete[] T;

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
