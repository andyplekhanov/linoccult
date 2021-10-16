//------------------------------------------------------------------------------
//
// File:    loReadEventData.h
//
// Purpose: Class for reading occultation events data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 13.02.2005
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

#ifndef LO_READ_EVENT_DATA_H
#define LO_READ_EVENT_DATA_H

#include <string>

#include "loAbsEventDataIO.h"

namespace aps {

  namespace apslib {
    class APSIBinFile;
  }

  namespace apslinoccult {

using apslib::APSIBinFile;

class LOData;
class LOEventData;
class LOEventDataReaderSubModule;
class LOModuleEventDataReader;

//======================= LOReadEventData ==========================

class LOReadEventData : public LOAbsEventDataIO
{
  private:

    LOModuleEventDataReader * pModule;
    APSIBinFile             * pInputFile;

    int ReadHeader( int & RecordsNumber ) const;

    int ReadEvent( LOEventData * pLOEventData, int & Count, const double MjdStart, const double MjdEnd ) const;

  public:

    LOReadEventData( LOEventDataReaderSubModule * pLOEventDataReaderSubModule, const std::string & EventDataFileName );

    virtual ~LOReadEventData( void );

    int Read( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------
