//------------------------------------------------------------------------------
//
// File:    apsastorbcalc.cc
//
// Purpose: Class for calculating asteroid orbit.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 22.05.2004
//                 1.0 11.01.2006 apsastorbcalc
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

#include "apsastorbcalc.h"
#include "apsmoduleastorbcalc.h"
#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsjpleph.h"
#include "apsde.h"
#include "apsvec3d.h"
#include "apsmat3d.h"

namespace aps {

  namespace apsastroalg {

//=================== APSAstOrbIntegFunction ======================

APSAstOrbIntegFunction :: APSAstOrbIntegFunction( const APSJPLEph * apJPLEph ) :
                          APSAbsIntegFunction( Neqn ), pJPLEph( apJPLEph )
{
  double emrat = apJPLEph->GetConst( "EMRAT" );

  GM[ 0 ] = apJPLEph->GetConst( "GMS" );
  GM[ 1 ] = apJPLEph->GetConst( "GM1" );
  GM[ 2 ] = apJPLEph->GetConst( "GM2" );

  double gmb = apJPLEph->GetConst( "GMB" );

  GM[ 3 ] = gmb * emrat / ( 1.0 + emrat );
  GM[ 10 ] = gmb / ( 1.0 + emrat );

  GM[ 4 ] = apJPLEph->GetConst( "GM4" );
  GM[ 5 ] = apJPLEph->GetConst( "GM5" );
  GM[ 6 ] = apJPLEph->GetConst( "GM6" );
  GM[ 7 ] = apJPLEph->GetConst( "GM7" );
  GM[ 8 ] = apJPLEph->GetConst( "GM8" );
  GM[ 9 ] = apJPLEph->GetConst( "GM9" );
}

APSAstOrbIntegFunction :: ~APSAstOrbIntegFunction( void )
{
}

APSVec3d APSAstOrbIntegFunction :: AccelJPL( const double Mjd, const APSVec3d & r ) const
{
  int      iPlanet;
  APSVec3d a, r_p, d;
  double   D;
  
  // Solar attraction
  D = Norm( r );
  a = - GM[ 0 ] * r / ( D * D * D );

  // Planetary perturbation

  for ( iPlanet = 1; iPlanet <= 10; iPlanet++ ) {
    APSVec3d r_planet = pJPLEph->GetPosEph( Mjd, iPlanet, apsastrodata::Sun );

    r_p = apsmathlib::R_x( EQU2ECL * apsmathlib::Rad ) * r_planet; // From equatorial to ecliptic

    d = r - r_p;

    // Direct acceleration
    D = Norm( d );
    a += - GM[ iPlanet ] * d / ( D * D * D );
  
    // Indirect acceleration
    D = Norm( r_p );
    a += - GM[ iPlanet ] * r_p / ( D * D * D );
  }

  return( a );
}

void APSAstOrbIntegFunction :: Run( const double X, const double Y[], double dYdX[] ) const
{
  APSVec3d r = APSVec3d( Y[ 1 ], Y[ 2 ], Y[ 3 ] );
  APSVec3d a = AccelJPL( X, r );

  dYdX[0] = 0.0;
  dYdX[1] = Y[ 4 ];  // velocity
  dYdX[2] = Y[ 5 ];  // velocity
  dYdX[3] = Y[ 6 ];  // velocity
  dYdX[4] = a[ apsmathlib::x ];  // acceleration
  dYdX[5] = a[ apsmathlib::y ];  // acceleration
  dYdX[6] = a[ apsmathlib::z ];  // acceleration
}

//======================= APSAstOrbCalc ==========================

APSAstOrbCalc :: APSAstOrbCalc( APSSubModule * pAPSSubModule,
                                const APS_INTEGRATION_TYPE aIntegType,
                                const APSAstOrbIntegFunction * IntegFunction,
                                const double ObservationEpoch,
                                const APSVec3d & r,
                                const APSVec3d & v,
                                const double a_eps,
                                const double a_abserr ) :
                                IntegType( aIntegType ), ETMjdCurrent( ObservationEpoch ),
                                eps( a_eps ), abs_err_val( a_abserr )
{
  pModule      = new APSModuleAstOrbCalc( pAPSSubModule );

  if( aIntegType != APS_INTEGRATION_DE ) {
    pModule->ErrorMessage( APS_ASTORBCALC_TYPE );
  }

  IntegMethod  = new APSDE( IntegFunction );

  ETMjdCurrent = ObservationEpoch;

  Y = new double[ IntegFunction->GetNeqn() + 1 ];

  Y[ 0 ] = 0.0;  // Unused
  Y[ 1 ] = r[ apsmathlib::x ];
  Y[ 2 ] = r[ apsmathlib::y ];
  Y[ 3 ] = r[ apsmathlib::z ];
  Y[ 4 ] = v[ apsmathlib::x ];
  Y[ 5 ] = v[ apsmathlib::y ];
  Y[ 6 ] = v[ apsmathlib::z ];
}

APSAstOrbCalc :: ~APSAstOrbCalc( void )
{
  delete [] Y;
  delete IntegMethod;
  delete pModule;
}

int APSAstOrbCalc :: Integrate( const double End )
{
  apsmathlib::DE_STATE State  = apsmathlib::DE_INIT;
  double               relerr = eps;
  double               abserr = abs_err_val;
    
  do {                        
    IntegMethod->Integ( Y, ETMjdCurrent, End, relerr, abserr, State );
    
    if( State == apsmathlib::DE_INVALID_PARAMS ) { 
      pModule->ErrorMessage( APS_ASTORBCALC_PARAM );
      return( 1 );
    }
  } while( State > apsmathlib::DE_DONE );

  return( 0 );
}

APSVec3d APSAstOrbCalc :: GetR( void ) const
{
  return( APSVec3d( Y[ 1 ], Y[ 2 ], Y[ 3 ] ) );
}

APSVec3d APSAstOrbCalc :: GetV( void ) const
{
  return( APSVec3d( Y[ 4 ], Y[ 5 ], Y[ 6 ] ) );
}

}}

//---------------------------- End of file ---------------------------

