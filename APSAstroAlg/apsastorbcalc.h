//------------------------------------------------------------------------------
//
// File:    apsastorbcalc.h
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

#ifndef APSASTORBCALC_H
#define APSASTORBCALC_H   1

#include "apsvec3d.h"
#include "apsmat3d.h"
#include "apsabsinteg.h"

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apsmathlib {
    class APSVec3d;
    class APSMat3d;
    class APSDE;
  }

  namespace apsastrodata {
    class APSJPLEph;
  }

  namespace apsastroalg {

class APSModuleAstOrbCalc;

using apslib::APSSubModule;
using apsmathlib::APSVec3d;
using apsmathlib::APSMat3d;
using apsmathlib::APSDE;
using apsmathlib::APSAbsIntegFunction;
using apsastrodata::APSJPLEph;

typedef enum {
  APS_INTEGRATION_DE = 0
} APS_INTEGRATION_TYPE;

//=================== APSAstOrbIntegFunction ======================

class APSAstOrbIntegFunction : public APSAbsIntegFunction
{
  private:

    static const int     Neqn = 6;              // Number of differential eqns.

    const APSJPLEph * pJPLEph;
    double            GM[ 11 ];

    APSVec3d AccelJPL( const double Mjd, const APSVec3d & r ) const;

  public:

    APSAstOrbIntegFunction( const APSJPLEph * apJPLEph );

    virtual ~APSAstOrbIntegFunction( void );

    virtual void Run( const double X, const double Y[], double dYdX[] ) const;
};

//======================= APSAstOrbCalc ==========================

class APSAstOrbCalc
{
  private:

    static constexpr double   def_eps    = 1.0e-10; // Relative accuracy
    static constexpr double   def_abserr = 0.0;     // Absolute accuracy

    APSModuleAstOrbCalc        * pModule;
    const APS_INTEGRATION_TYPE   IntegType;
    APSDE                      * IntegMethod;
    double                     * Y;
    double                       ETMjdCurrent;
    double                       eps;
    double                       abs_err_val;

  public:

    APSAstOrbCalc( APSSubModule * pAPSSubModule,
                   const APS_INTEGRATION_TYPE aIntegType,
                   const APSAstOrbIntegFunction * IntegFunction,
                   const double ObservationEpoch,
                   const APSVec3d & r,
                   const APSVec3d & v,
                   const double a_eps = def_eps,
                   const double a_abserr = def_abserr );

    virtual ~APSAstOrbCalc( void );

    int Integrate( const double End );

    APS_INTEGRATION_TYPE GetIntegType( void ) const
      { return( IntegType ); }

    double GetCurrentETTime( void ) const
      { return( ETMjdCurrent ); }

    APSVec3d GetR( void ) const;

    APSVec3d GetV( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------



