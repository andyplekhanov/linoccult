//------------------------------------------------------------------------------
//
// File:    loReadUpdatesData.h
//
// Purpose: Class for reading updates data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 17.04.2005
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

#ifndef LO_READ_UPDATES_DATA_H
#define LO_READ_UPDATES_DATA_H

#include <string>

namespace aps {

  namespace apslib {
    class APSIStrFile;
  }

  namespace apslinoccult {

using apslib::APSIStrFile;

class LOData;
class LOUpdateData;
class LOUpdatesDataReaderSubModule;
class LOModuleUpdatesDataReader;

//======================= LOReadUpdatesData ==========================

class LOReadUpdatesData
{
  private:

    LOModuleUpdatesDataReader * pModule;
    APSIStrFile               * pInputFile;

    bool ParseLine( const std::string & Str,
                    std::string & sAsteroidID,
                    std::string & sEpoch,
                    std::string & sMeanAnomaly,
                    std::string & sPericenter,
                    std::string & sLongNode,
                    std::string & sInclination,
                    std::string & sEccenticity,
                    std::string & sSemimajorAxis,
                    std::string & sMajor,
                    std::string & sMinor,
                    std::string & sPA ) const;

    int ReadUpdate( LOUpdateData * pLOUpdateData, const std::string & Str, const int LineNumber ) const;

  public:

    LOReadUpdatesData( LOUpdatesDataReaderSubModule * pLOUpdatesDataReaderSubModule, const std::string & UpdatesDataFileName );

    virtual ~LOReadUpdatesData( void );

    int Read( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------
