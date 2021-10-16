//------------------------------------------------------------------------------
//
// File:    loModuleChebAstOrbCalc.cc
//
// Purpose: Module for asteroid orbit calculation for Chebyshev approximation module.
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

#include "loChebMakerSubModule.h"
#include "loModuleChebAstOrbCalc.h"
#include "loChebAstOrbSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleChebAstOrbCalc =================================

LOModuleChebAstOrbCalc :: LOModuleChebAstOrbCalc( LOChebMakerSubModule * pOwner ) :
                          APSModule( "LOChebAstOrbCalc", pOwner )
{
  pLOChebAstOrbSubModule = new LOChebAstOrbSubModule( this );
}

LOModuleChebAstOrbCalc :: ~LOModuleChebAstOrbCalc( void )
{
  delete pLOChebAstOrbSubModule;
}

const LOChebMakerSubModule * LOModuleChebAstOrbCalc :: GetLOChebMakerSubModulePtr( void ) const
{
  return( static_cast<const LOChebMakerSubModule *>( GetOwnerPtr() ) );
}

}}

//---------------------------- End of file ---------------------------
