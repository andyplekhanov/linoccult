//------------------------------------------------------------------------------
//
// File:    loAstOrbCalc.h
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

#ifndef LOASTORBCALC_H
#define LOASTORBCALC_H

#include "apsvec3d.h"
#include "apsmat3d.h"
#include "apsastorbcalc.h"

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apsastrodata {
    class APSJPLEph;
  }

  namespace apsastroalg {
    class APSAstOrbIntegFunction;
    class APSAstOrbCalc;
  }

  namespace apslinoccult {

using apslib::APSSubModule;
using apsmathlib::APSVec3d;
using apsmathlib::APSMat3d;
using apsastrodata::APSJPLEph;
using apsastroalg::APSAstOrbIntegFunction;
using apsastroalg::APSAstOrbCalc;

class LOModuleAstOrbCalc;

//======================= LOAstOrbCalc ==========================

class LOAstOrbCalc
{
  private:

    LOModuleAstOrbCalc     * pModule;
    APSAstOrbCalc          * pAPSAstOrbCalc;
    APSAstOrbIntegFunction * IntegFunction;
    const APSJPLEph        * pJPLEph;
    double                   ET_UT_DEF;
    double                   T_eqx;
    APSMat3d                 P;

    APSVec3d JPLSunPos( const double Mjd ) const;

  public:

    // Two different owners: loAstObrCalcSubModule, loChebAstOrbCalcSubModule
    LOAstOrbCalc( APSSubModule * pAPSSubModule,
                  const apsastroalg::APS_INTEGRATION_TYPE aIntegType,
                  const APSJPLEph * apJPLEph,
                  const double ObservationEpoch,
                  const double M, const double W, const double O,
                  const double I, const double E, const double A,
                  const double ET_UT, const double T_eqx0, const double aT_eqx );

    virtual ~LOAstOrbCalc( void );

    int ProcessAsteroid( const double MjdTime, APSVec3d & r_equ ) const;

    double GetCurrentETTime( void ) const;

    APSVec3d GetR( void ) const;

    APSVec3d GetV( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------


