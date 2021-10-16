//------------------------------------------------------------------------------
//
// File:    apsmoduletaiutcreader.cc
//
// Purpose: Module for TAI_UTC data base reader.
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

#include "apsmoduletaiutcreader.h"
#include "apssubmodule.h"

namespace aps {

  namespace apsastroio {

//================================== APSModuleTaiUtcReader =================================

APSModuleTaiUtcReader :: APSModuleTaiUtcReader( APSSubModule * pAPSSubModule ) :
                         APSModule( "APSModuleTaiUtcReader", pAPSSubModule )
{
}

APSModuleTaiUtcReader :: ~APSModuleTaiUtcReader( void )
{
}

const std::string APSModuleTaiUtcReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case APS_TAI_UTC_READER_NO_ERROR:
      return("No error.\n");
    case APS_TAI_UTC_READER_OPEN_FILE:
      return("Can't open file.\n");
    case APS_TAI_UTC_READER_PARSE:
      return("Parse error.");
    case APS_TAI_UTC_READER_NEW_LINE:
      return("\n");
    case APS_TAI_UTC_READER_FINISH_READING:
      return("TAI-UTC file has been read.");
    case APS_TAI_UTC_READER_SORT:
      return("TAI-UTC file is not sorted.");
    case APS_TAI_UTC_READER_SKIP_HEADER:
      return("Can't skip header.");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

}}

//---------------------------- End of file ---------------------------
