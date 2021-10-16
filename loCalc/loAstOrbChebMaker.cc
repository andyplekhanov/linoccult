//------------------------------------------------------------------------------
//
// File:    loAstOrbChebMaker.cc
//
// Purpose: Class for creating Chebyshev approximation for asteroid orbit.
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

#include "loAstOrbChebMaker.h"
#include "loChebMakerSubModule.h"
#include "loModuleChebAstOrbCalc.h"
#include "loAstOrbCalc.h"
#include "loChebAstOrbSubModule.h"

namespace aps {

  namespace apslinoccult {

LOAstOrbChebMaker :: LOAstOrbChebMaker( LOChebMakerSubModule * pLOChebMakerSubModule,
                                        const APSJPLEph * apJPLEph, const double ObservationEpoch,
                                        const double M, const double W, const double O,
                                        const double I, const double E, const double A,
                                        const double ET_UT, const double T_eqx0, const double aT_eqx ) :
                     APSAbsChebMaker()
{
  pModule = new LOModuleChebAstOrbCalc( pLOChebMakerSubModule );

  pLOAstOrbCalc = new LOAstOrbCalc( pModule->GetChebAstOrbSubModulePtr(), apsastroalg::APS_INTEGRATION_DE,
                                    apJPLEph, ObservationEpoch,
                                    M, W, O, I, E, A, ET_UT, T_eqx0, aT_eqx );
}

LOAstOrbChebMaker :: ~LOAstOrbChebMaker( void )
{
  delete pLOAstOrbCalc;
  delete pModule;
}

APSVec3d LOAstOrbChebMaker :: GetValue( const double t )
{
  APSVec3d r_equ;

  if( pLOAstOrbCalc->ProcessAsteroid( t, r_equ ) ) {
    pModule->ErrorMessage( LO_CHEBASTORBCALC_AST_PROCESS );
  }

  return( r_equ );
}

}}

//---------------------------- End of file ---------------------------
