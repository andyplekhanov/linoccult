//------------------------------------------------------------------------------
//
// File:    loModuleAstOrbCalc.h
//
// Purpose: Module for asteroid orbit calculation.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.05.2004
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

#ifndef LO_MODULE_AST_ORB_CALC_H
#define LO_MODULE_AST_ORB_CALC_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apslinoccult {

using apslib::APSModule;
using apslib::APSSubModule;

class LOAPSAstOrbSubModule;

enum {
  LO_ASTORBCALC_NO_ERROR = 0,
  LO_ASTORBCALC_ET_UT,
  LO_ASTORBCALC_INTEGRATION
};

//======================= LOModuleAstOrbCalc ==========================

class LOModuleAstOrbCalc : public APSModule
{
  private:

    LOAPSAstOrbSubModule * pLOAPSAstOrbSubModule;

  public:

    LOModuleAstOrbCalc( APSSubModule * pAPSSubModule );

    virtual ~LOModuleAstOrbCalc( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    LOAPSAstOrbSubModule * GetAPSAstOrbSubModulePtr( void ) const
      { return( pLOAPSAstOrbSubModule ); }
};

}}

#endif

//---------------------------- End of file ---------------------------
