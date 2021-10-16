//------------------------------------------------------------------------------
//
// File:    loModuleEventDataWriter.cc
//
// Purpose: Module for occultation events data writing.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 08.02.2005
//         version 0.2 15.02.2005 OutputEventsFilePath was added
//         version 0.3 22.02.2005 OutputEventsFilePath was removed.
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

#include "loModuleEventDataWriter.h"
#include "loEventDataWriterSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleEventDataWriter =================================

LOModuleEventDataWriter :: LOModuleEventDataWriter( LOEventDataWriterSubModule * pOwner ) :
                           APSModule( "LOModuleEventDataWriter", pOwner )
{
}

LOModuleEventDataWriter :: ~LOModuleEventDataWriter( void )
{
}

const std::string LOModuleEventDataWriter :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_EVENT_DATA_WRITER_NO_ERROR:
      return("No error\n");
    case LO_EVENT_DATA_WRITER_OPEN_FILE:
      return("Can't create events file.\n");
    case LO_EVENT_DATA_WRITER_HEADER:
      return("Can't write header.\n");
    case LO_EVENT_DATA_WRITER_EVENT:
      return("Can't write event.\n");
    case LO_EVENT_DATA_WRITER_START_WRITING:
      return("Start writing events file.");
    case LO_EVENT_DATA_WRITER_FINISH_WRITING:
      return("Events file has been written.");
    case LO_EVENT_DATA_WRITER_PROGRESS:
      return("*");
    case LO_EVENT_DATA_WRITER_NEW_LINE:
      return("\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOEventDataWriterSubModule * LOModuleEventDataWriter :: GetLOEventDataWriterSubModule( void ) const
{
  return( static_cast<const LOEventDataWriterSubModule *>( GetOwnerPtr() ) );
}

int LOModuleEventDataWriter :: GetStartYear( void ) const
{
  return( GetLOEventDataWriterSubModule()->GetStartYear() );
}

int LOModuleEventDataWriter :: GetStartMonth( void ) const
{
  return( GetLOEventDataWriterSubModule()->GetStartMonth() );
}

int LOModuleEventDataWriter :: GetStartDay( void ) const
{
  return(GetLOEventDataWriterSubModule()->GetStartDay() );
}

int LOModuleEventDataWriter :: GetEndYear( void ) const
{
  return( GetLOEventDataWriterSubModule()->GetEndYear() );
}

int LOModuleEventDataWriter :: GetEndMonth( void ) const
{
  return( GetLOEventDataWriterSubModule()->GetEndMonth() );
}

int LOModuleEventDataWriter :: GetEndDay( void ) const
{
  return( GetLOEventDataWriterSubModule()->GetEndDay() );
}

}}

//---------------------------- End of file ---------------------------
