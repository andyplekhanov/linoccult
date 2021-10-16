//------------------------------------------------------------------------------
//
// File:    loModuleEventDataReader.cc
//
// Purpose: Module for occultation events data reading.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 13.02.2005
//         version 0.2 15.02.2005 InputEventsFilePath was added
//         version 0.3 22.02.2005 InputEventsFilePath was removed.
//                                StartYear, StartMonth, StartDay, EndYear, EndMonth, EndDay
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

#include "loModuleEventDataReader.h"
#include "loEventDataReaderSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleEventDataReader =================================

LOModuleEventDataReader :: LOModuleEventDataReader( LOEventDataReaderSubModule * pOwner ) :
                           APSModule( "LOModuleEventDataReader", pOwner )
{
}

LOModuleEventDataReader :: ~LOModuleEventDataReader( void )
{
}

const std::string LOModuleEventDataReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_EVENT_DATA_READER_NO_ERROR:
      return("No error\n");
    case LO_EVENT_DATA_READER_OPEN_FILE:
      return("Can't open events file.\n");
    case LO_EVENT_DATA_READER_READ_ERROR:
      return("Read error.\n");
    case LO_EVENT_DATA_READER_WRONG_VERSION:
      return("Wrong file version.\n");
    case LO_EVENT_DATA_READER_WRONG_DESCRIPTOR:
      return("Wrong descriptor.\n");
    case LO_EVENT_DATA_READER_HEADER:
      return("Can't read header.\n");
    case LO_EVENT_DATA_READER_HEADER_INFO:
      return("Header info: ");
    case LO_EVENT_DATA_READER_EVENT:
      return("Can't read event.\n");
    case LO_EVENT_DATA_READER_START_READING:
      return("Start reading events file.");
    case LO_EVENT_DATA_READER_FINISH_READING:
      return("Events file has been read.");
    case LO_EVENT_DATA_READER_PROGRESS:
      return("*");
    case LO_EVENT_DATA_READER_NEW_LINE:
      return("\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOEventDataReaderSubModule * LOModuleEventDataReader :: GetLOEventDataReaderSubModule( void ) const
{
  return( static_cast<const LOEventDataReaderSubModule *>( GetOwnerPtr() ) );
}

int LOModuleEventDataReader :: GetStartYear( void ) const
{
  return( GetLOEventDataReaderSubModule()->GetStartYear() );
}

int LOModuleEventDataReader :: GetStartMonth( void ) const
{
  return( GetLOEventDataReaderSubModule()->GetStartMonth() );
}

int LOModuleEventDataReader :: GetStartDay( void ) const
{
  return( GetLOEventDataReaderSubModule()->GetStartDay() );
}

int LOModuleEventDataReader :: GetEndYear( void ) const
{
  return( GetLOEventDataReaderSubModule()->GetEndYear() );
}

int LOModuleEventDataReader :: GetEndMonth( void ) const
{
  return( GetLOEventDataReaderSubModule()->GetEndMonth() );
}

int LOModuleEventDataReader :: GetEndDay( void ) const
{
  return( GetLOEventDataReaderSubModule()->GetEndDay() );
}

}}

//---------------------------- End of file ---------------------------
