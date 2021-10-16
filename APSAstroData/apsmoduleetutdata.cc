//------------------------------------------------------------------------------
//
// File:    apsmoduleetutdata.cc
//
// Purpose: Module for ET_UT data base.
//   
// (c) Plekhanov Andrey
//
// Initial version 0.1
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

#include "apsmoduleetutdata.h"
#include "apssubmodule.h"

namespace aps {

  namespace apsastrodata {

//================================== APSModuleEtUtData =================================

APSModuleEtUtData :: APSModuleEtUtData( APSSubModule * pAPSSubModule ) :
                     APSModule( "APSModuleEtUtData", pAPSSubModule )
{
}

APSModuleEtUtData :: ~APSModuleEtUtData( void )
{
}

const std::string APSModuleEtUtData :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case APS_ET_UT_DATA_NO_ERROR:
      return("No error.\n");
    case APS_ET_UT_DATA_LESS:
      return("Time is less then minimum.\n");
    case APS_ET_UT_DATA_MORE:
      return("Time is more then maximum.\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

}}

//---------------------------- End of file ---------------------------
