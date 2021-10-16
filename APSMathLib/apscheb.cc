//------------------------------------------------------------------------------
//
// File:    apscheb.cc
//
// Purpose: Three dimensional Chebyshev approximation.
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

#include "apscheb.h"
#include "apsmodulecheb.h"
#include "apsvec3d.h"

namespace aps {

  namespace apsmathlib {

APSCheb :: APSCheb( APSSubModule * pSubModule, const unsigned int aOrder,
                    const double * acX, const double * acY, const double * acZ, double ata, double atb )
{
  unsigned int i;

  pModule = new APSModuleCheb( pSubModule );

  Order = aOrder;

  cX = new double[ aOrder + 1 ];
  cY = new double[ aOrder + 1 ];
  cZ = new double[ aOrder + 1 ];

  for( i = 0; i <= aOrder; i++ ) {
    cX[ i ] = acX[ i ];
    cY[ i ] = acY[ i ];
    cZ[ i ] = acZ[ i ];
  }

  ta = ata;
  tb = atb;
}

APSCheb :: ~APSCheb( void )
{
  delete [] cX;
  delete [] cY;
  delete [] cZ;

  delete pModule;
}

int APSCheb :: Value( const double t, APSVec3d & Val )
{
  int      i;
  APSVec3d f1;
  APSVec3d f2;
  APSVec3d old_f1;
  double   tau;
  int      RetCode;

  RetCode = APS_MODULE_CHEB_NO_ERROR;

  if ( ( t >= ta ) && ( t <= tb ) ) {
    tau = ( 2.0 * t - ta - tb ) / ( tb - ta );  
  
    for( i = Order; i >= 1; i-- ) {
      old_f1 = f1;
      f1 = 2.0 * tau * f1 - f2 + APSVec3d( cX[ i ], cY[ i ], cZ[ i ] );  
      f2 = old_f1;
    }
  
    Val = tau * f1 - f2 + 0.5 * APSVec3d( cX[ 0 ], cY[ 0 ], cZ[ 0 ] );
  }
  else {
    pModule->ErrorMessage( APS_MODULE_CHEB_TIME );
    RetCode = APS_MODULE_CHEB_TIME;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------

