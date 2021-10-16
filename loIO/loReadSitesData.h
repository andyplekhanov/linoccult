//------------------------------------------------------------------------------
//
// File:    loReadSitesData.h
//
// Purpose: Class for reading sites data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 14.03.2005
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

#ifndef LO_READ_SITES_DATA_H
#define LO_READ_SITES_DATA_H

#include <string>

namespace aps {

  namespace apslib {
    class APSIStrFile;
  }

  namespace apslinoccult {

using apslib::APSIStrFile;

class LOData;
class LOPosData;
class LOSitesDataReaderSubModule;
class LOModuleSitesDataReader;

//======================= LOReadSitesData ==========================

class LOReadSitesData
{
  private:

    LOModuleSitesDataReader * pModule;
    APSIStrFile             * pInputFile;

    int GetCoord( const std::string & pStr, float & Coord ) const;

    bool ParseLine( const std::string & Str,
                    std::string & ObsName,
                    std::string & EMail,
                    std::string & sOutputFiles,
                    std::string & sSort,
                    std::string & sObserverLongitude,
                    std::string & sObserverLatitude,
                    std::string & sMaxDistance,
                    std::string & sMaxMv,
                    std::string & sMinDuration,
                    std::string & sSunElev,
                    std::string & sMinDrop,
                    std::string & sMinProb,
                    std::string & sMinCenterProb,
                    std::string & sMinStarElev ) const;

    int ReadSite( LOPosData * pLOPosData, const std::string & pStr, const int LineNumber ) const;

  public:

    LOReadSitesData( LOSitesDataReaderSubModule * pLOSitesDataReaderSubModule, const std::string & SitesDataFileName );

    virtual ~LOReadSitesData( void );

    int Read( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------



