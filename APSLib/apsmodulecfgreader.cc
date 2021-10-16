//------------------------------------------------------------------------------
//
// File:    apsmodulecfgreader.cc
//
// Purpose: Module for config reader.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 07.03.2004
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

#include "apsmodulecfgreader.h"

namespace aps {

  namespace apslib {

//================================== APSModuleConfigReader =================================

APSModuleConfigReader :: APSModuleConfigReader( APSSubModule * pOwner ) :
                          APSModule( "APSModuleConfigReader", pOwner )
{
}

APSModuleConfigReader :: ~APSModuleConfigReader( void )
{
}

const std::string APSModuleConfigReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case APS_MODULE_CFG_READER_NO_ERROR:
      return("No error\n");
    case APS_MODULE_CFG_READER_PARSE_LINE:
      return("Parse error:");
    case APS_MODULE_CFG_READER_WRONG_TYPE:
      return("Wrong parameter type:");
    case APS_MODULE_CFG_READER_NOT_FOUND:
      return("Parameter not found:");
    case APS_MODULE_CFG_READER_EXISTS:
      return("Parameter exists:");
    case APS_MODULE_CFG_READER_VALUE:
      return("Wrong parameter value:");
    case APS_MODULE_CFG_READER_FILE_NOT_FOUND:
      return("");
    case APS_MODULE_CFG_READER_TYPE:
      return("Wrong type:");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

}}

//---------------------------- End of file ---------------------------

