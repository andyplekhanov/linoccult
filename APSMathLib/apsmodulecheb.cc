//------------------------------------------------------------------------------
//
// File:    apsmodulecheb.cc
//
// Purpose: Module for three dimensional Chebyshev approximation.
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

#include "apsmodulecheb.h"

namespace aps {

  namespace apsmathlib {

//================================== APSModuleCheb =================================

APSModuleCheb :: APSModuleCheb( APSSubModule * pOwner ) :
                 APSModule( "APSModuleCheb", pOwner )
{
}

APSModuleCheb :: ~APSModuleCheb( void )
{
}

const std::string APSModuleCheb :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case APS_MODULE_CHEB_NO_ERROR:
      return("No error\n");
    case APS_MODULE_CHEB_TIME:
      return("Wrong time interval.\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

}}

//---------------------------- End of file ---------------------------

