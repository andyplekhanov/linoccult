//------------------------------------------------------------------------------
//
// File:    apsmoduleetutreader.cc
//
// Purpose: Module for ET_UT data base reader.
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

#include "apsmoduleetutreader.h"
#include "apssubmodule.h"

namespace aps {

  namespace apsastroio {

//================================== APSModuleEtUtReader =================================

APSModuleEtUtReader :: APSModuleEtUtReader( APSSubModule * pAPSSubModule ) :
                         APSModule( "APSModuleEtUtReader", pAPSSubModule )
{
}

APSModuleEtUtReader :: ~APSModuleEtUtReader( void )
{
}

const std::string APSModuleEtUtReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case APS_ET_UT_READER_NO_ERROR:
      return("No error.\n");
    case APS_ET_UT_READER_OPEN_FILE:
      return("Can't open file.\n");
    case APS_ET_UT_READER_PARSE:
      return("Parse error.");
    case APS_ET_UT_READER_NEW_LINE:
      return("\n");
    case APS_ET_UT_READER_FINISH_READING:
      return("ET-UT file has been read.");
    case APS_ET_UT_READER_SORT:
      return("ET-UT file is not sorted.");
    case APS_ET_UT_READER_SKIP_HEADER:
      return("Can't skip header.");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

}}

//---------------------------- End of file ---------------------------
