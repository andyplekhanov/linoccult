//------------------------------------------------------------------------------
//
// File:    loAstOrbChebMaker.h
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

#ifndef LO_AST_ORB_CHEB_MAKER_H
#define LO_AST_ORB_CHEB_MAKER_H

#include "apsabschebmaker.h"
#include "apsvec3d.h"

namespace aps {

  namespace apsastrodata {
    class APSJPLEph;
  }

  namespace apslinoccult {

using apsmathlib::APSAbsChebMaker;
using apsmathlib::APSVec3d;
using apsastrodata::APSJPLEph;

class LOChebMakerSubModule;
class LOModuleChebAstOrbCalc;
class LOAstOrbCalc;

//======================= LOAstOrbChebMaker ==========================

class LOAstOrbChebMaker : public APSAbsChebMaker
{
  private:

    LOModuleChebAstOrbCalc * pModule;

    LOAstOrbCalc           * pLOAstOrbCalc;

  protected:

    virtual APSVec3d GetValue( const double t );

  public:

    LOAstOrbChebMaker( LOChebMakerSubModule * pLOChebMakerSubModule,
                       const APSJPLEph * apJPLEph, const double ObservationEpoch,
                       const double M, const double W, const double O,
                       const double I, const double E, const double A,
                       const double ET_UT, const double T_eqx0, const double aT_eqx );

    virtual ~LOAstOrbChebMaker( void );
};

}}

#endif

//---------------------------- End of file ---------------------------

