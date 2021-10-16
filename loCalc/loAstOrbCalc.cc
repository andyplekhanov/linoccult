//------------------------------------------------------------------------------
//
// File:    loAstOrbCalc.cc
//
// Purpose: Class for calculating asteroid orbit.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 22.05.2004
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

#include "loAstOrbCalc.h"
#include "loModuleAstOrbCalc.h"
#include "loAPSAstOrbSubModule.h"
#include "apsmathconst.h"
#include "apsastroconst.h"
#include "apsjpleph.h"
#include "apskepler.h"
#include "apsspheric.h"
#include "apsprecnut.h"
#include "apstime.h"

namespace aps {

  namespace apslinoccult {

//======================= LOAstOrbCalc ==========================

LOAstOrbCalc :: LOAstOrbCalc( APSSubModule * pAPSSubModule,
                              const apsastroalg::APS_INTEGRATION_TYPE aIntegType,
                              const APSJPLEph * apJPLEph,
                              const double ObservationEpoch,
                              const double M, const double W, const double O,
                              const double I, const double E, const double A,
                              const double ET_UT, const double T_eqx0, const double aT_eqx ) :
                              pJPLEph( apJPLEph ), ET_UT_DEF( ET_UT ), T_eqx( aT_eqx )
{
  APSMat3d PQR;
  APSVec3d r;
  APSVec3d v;

  pModule      = new LOModuleAstOrbCalc( pAPSSubModule );

  PQR = apsastroalg::GaussVec( O, I, W );
  PQR = apsastroalg::PrecMatrix_Ecl( T_eqx0, apsastroalg::T_J2000 ) * PQR;

  P   = apsastroalg::PrecMatrix_Ecl( apsastroalg::T_J2000, aT_eqx ); 

  apsastroalg::Ellip( apJPLEph->GetConst( "GMS" ), M, A, E, r, v );
  
  r = PQR * r;
  v = PQR * v;

  IntegFunction = new APSAstOrbIntegFunction( apJPLEph );

  pAPSAstOrbCalc = new APSAstOrbCalc( pModule->GetAPSAstOrbSubModulePtr(),
                                      apsastroalg::APS_INTEGRATION_DE,
                                      IntegFunction, ObservationEpoch,
                                      r, v );
}

LOAstOrbCalc :: ~LOAstOrbCalc( void )
{
  delete pAPSAstOrbCalc;
// Must be deleted after pAPSAstOrbCalc
  delete IntegFunction;
  delete pModule;
}

APSVec3d LOAstOrbCalc :: JPLSunPos( const double Mjd ) const
{
  APSVec3d r_sun = pJPLEph->SunEquPos( Mjd );

  // From equatorial to ecliptic
  r_sun = apsmathlib::R_x( apsastroalg::EQU2ECL * apsmathlib::Rad ) * r_sun;

  return( r_sun );
}

int LOAstOrbCalc :: ProcessAsteroid( const double MjdTime, APSVec3d & r_equ ) const
{
  double    ETMjdTime;
  APSVec3d  R_Sun;
  APSVec3d  r_helioc;
  APSVec3d  v_helioc;
  APSVec3d  r_geoc;
  double    dist;
  double    fac;
  double    ET_UT;
  bool      valid;
  int       RetCode = 0;

  apsastroalg::ETminUT( ( MjdTime - apsastroalg::MJD_J2000 ) / 36525.0, ET_UT, valid );

  if( !valid ) {
    pModule->WarningMessage( LO_ASTORBCALC_ET_UT );
    ET_UT = ET_UT_DEF;
  }

  ETMjdTime = MjdTime + ET_UT / 86400.0;

  if( !pAPSAstOrbCalc->Integrate( ETMjdTime ) ) {
    r_helioc = P * pAPSAstOrbCalc->GetR();
    v_helioc = P * pAPSAstOrbCalc->GetV();

    R_Sun = JPLSunPos( pAPSAstOrbCalc->GetCurrentETTime() );

    r_geoc = r_helioc + R_Sun;

    dist = Norm( r_geoc );
    fac  = dist / apsastroalg::c_light;
    r_geoc = r_geoc - fac * v_helioc;

    r_equ = apsastroalg::Ecl2EquMatrix( T_eqx ) * r_geoc;
  }
  else {
    pModule->ErrorMessage( LO_ASTORBCALC_INTEGRATION );    
    RetCode = LO_ASTORBCALC_INTEGRATION;
  }

  return( RetCode );
}

double LOAstOrbCalc :: GetCurrentETTime( void ) const
{
  return( pAPSAstOrbCalc->GetCurrentETTime() );
}

APSVec3d LOAstOrbCalc :: GetR( void ) const
{
  return( pAPSAstOrbCalc->GetR() );
}

APSVec3d LOAstOrbCalc :: GetV( void ) const
{
  return( pAPSAstOrbCalc->GetV() );
}

}}

//---------------------------- End of file ---------------------------


