//------------------------------------------------------------------------------
//
// File:    loChebAstOrbSubModule.h
//
// Purpose: Submodule for asteroid orbit calculation in Chebyshev approximation module.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
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

#ifndef LO_CHEB_AST_ORB_SUB_MODULE_H
#define LO_CHEB_AST_ORB_SUB_MODULE_H

#include <string>

#include "apssubmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSSubModule;

class LOModuleChebAstOrbCalc;

//======================= LOChebAstOrbSubModule ==========================

class LOChebAstOrbSubModule : public APSSubModule
{
  public:

    LOChebAstOrbSubModule( LOModuleChebAstOrbCalc * pOwner );

    virtual ~LOChebAstOrbSubModule( void );

    virtual int WarningMessage( const int MsgNumber, const std::string & pMsg, const APSAbsModule * pSubModule ) const;

    const LOModuleChebAstOrbCalc * GetLOModuleChebAstOrbCalcPtr( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
