//------------------------------------------------------------------------------
//
// File:    loWriteEventData.h
//
// Purpose: Class for writing occultation events data base for LinOccult.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 28.12.2004
//         version 0.2 13.02.2005 Storing events
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

#ifndef LO_WRITE_EVENT_DATA_H
#define LO_WRITE_EVENT_DATA_H

#include <string>

#include "loAbsEventDataIO.h"

namespace aps {

  namespace apslib {
    class APSOBinFile;
  }

  namespace apslinoccult {

using apslib::APSOBinFile;

class LOData;
class LOEvent;
class LOEventDataWriterSubModule;
class LOModuleEventDataWriter;

//======================= LOWriteEventData ==========================

class LOWriteEventData : public LOAbsEventDataIO
{
  private:

    LOModuleEventDataWriter * pModule;
    APSOBinFile             * pOutputFile;

    bool WriteHeader( LOEventData * pLOEventData ) const;

    bool WriteEvent( LOEvent * pEvent, int & Count, const double MjdStart, const double MjdEnd ) const;

  public:

    LOWriteEventData( LOEventDataWriterSubModule * pLOEventDataWriterSubModule, const std::string & EventDataFileName );

    virtual ~LOWriteEventData( void );

    int Write( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------



