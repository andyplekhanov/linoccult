//------------------------------------------------------------------------------
//
// File:    loModuleEventDataReader.h
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

#ifndef LO_MODULE_EVENT_DATA_READER_H
#define LO_MODULE_EVENT_DATA_READER_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSModule;

class LOEventDataReaderSubModule;

enum {
  LO_EVENT_DATA_READER_NO_ERROR = 0,
  LO_EVENT_DATA_READER_OPEN_FILE,
  LO_EVENT_DATA_READER_READ_ERROR,
  LO_EVENT_DATA_READER_WRONG_DESCRIPTOR,
  LO_EVENT_DATA_READER_WRONG_VERSION,
  LO_EVENT_DATA_READER_HEADER_INFO,
  LO_EVENT_DATA_READER_HEADER,
  LO_EVENT_DATA_READER_EVENT,
  LO_EVENT_DATA_READER_START_READING,
  LO_EVENT_DATA_READER_FINISH_READING,
  LO_EVENT_DATA_READER_PROGRESS,
  LO_EVENT_DATA_READER_NEW_LINE
};

//======================= LOModuleEventDataReader ==========================

class LOModuleEventDataReader : public APSModule
{
  private:

    const LOEventDataReaderSubModule * GetLOEventDataReaderSubModule( void ) const;

  public:

    LOModuleEventDataReader( LOEventDataReaderSubModule * pOwner );

    virtual ~LOModuleEventDataReader( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    int GetStartYear( void ) const;

    int GetStartMonth( void ) const;

    int GetStartDay( void ) const;

    int GetEndYear( void ) const;

    int GetEndMonth( void ) const;

    int GetEndDay( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
