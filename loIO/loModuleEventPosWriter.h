//------------------------------------------------------------------------------
//
// File:    loModuleEventPosWriter.h
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

#ifndef LO_MODULE_EVENT_POS_WRITER_H
#define LO_MODULE_EVENT_POS_WRITER_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSModule;

class LOEventPosWriterSubModule;

enum {
  LO_EVENT_POS_WRITER_NO_ERROR = 0,
  LO_EVENT_POS_WRITER_OPEN_FILE,
  LO_EVENT_POS_WRITER_HEADER,
  LO_EVENT_POS_WRITER_EVENT,
  LO_EVENT_POS_WRITER_START_WRITING,
  LO_EVENT_POS_WRITER_FINISH_WRITING,
  LO_EVENT_POS_WRITER_PROGRESS,
  LO_EVENT_POS_WRITER_NEW_LINE
};

//======================= LOModuleEventPosWriter ==========================

class LOModuleEventPosWriter : public APSModule
{
  private:

    const LOEventPosWriterSubModule * GetLOEventPosWriterSubModule( void ) const;

  public:

    LOModuleEventPosWriter( LOEventPosWriterSubModule * pOwner );

    virtual ~LOModuleEventPosWriter( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
