//------------------------------------------------------------------------------
//
// File:    loModuleEventPosWriter.cc
//
// Purpose: Module for position events data writing.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 27.02.2005
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

#include "loModuleEventPosWriter.h"
#include "loEventPosWriterSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleEventPosWriter =================================

LOModuleEventPosWriter :: LOModuleEventPosWriter( LOEventPosWriterSubModule * pOwner ) :
                          APSModule( "LOModuleEventPosWriter", pOwner )
{
}

LOModuleEventPosWriter :: ~LOModuleEventPosWriter( void )
{
}

const std::string LOModuleEventPosWriter :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_EVENT_POS_WRITER_NO_ERROR:
      return("No error\n");
    case LO_EVENT_POS_WRITER_OPEN_FILE:
      return("Can't create position file.\n");
    case LO_EVENT_POS_WRITER_HEADER:
      return("Can't write header.\n");
    case LO_EVENT_POS_WRITER_EVENT:
      return("Can't write event.\n");
    case LO_EVENT_POS_WRITER_START_WRITING:
      return("Start writing positions file.");
    case LO_EVENT_POS_WRITER_FINISH_WRITING:
      return("Position files has been written.");
    case LO_EVENT_POS_WRITER_PROGRESS:
      return("*");
    case LO_EVENT_POS_WRITER_NEW_LINE:
      return("\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOEventPosWriterSubModule * LOModuleEventPosWriter :: GetLOEventPosWriterSubModule( void ) const
{
  return( static_cast<const LOEventPosWriterSubModule *>( GetOwnerPtr() ) );
}

}}

//---------------------------- End of file ---------------------------
