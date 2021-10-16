//------------------------------------------------------------------------------
//
// File:    loPos.h
//
// Purpose: Data for storing observation position in LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 17.02.2005
//         version 0.2 24.02.2005 pEMail, OutputFiles, Sort, MinDrop, MinProb, MinCenterProb, MinStarElev were added
//         version 0.3 27.02.2005 LOPointEventList was added
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

#ifndef LO_POS_H
#define LO_POS_H

#include <string>

namespace aps {

  namespace apslinoccult {

class LOPointEventList;
class LOPointEventItem;
class LOPointEvent;

const int PE_TEXT_FILE = 1;
const int PE_PDF_FILE  = 2;
const int PE_HTML_FILE = 4;

const int PE_SORT_BY_DATE     = 1;
const int PE_SORT_BY_NUMBER   = 2;
const int PE_SORT_BY_DROP     = 4;
const int PE_SORT_BY_DISTANCE = 8;
const int PE_SORT_BY_DURATION = 16;
const int PE_SORT_BY_PROB     = 32;
const int PE_SORT_BY_CPROB    = 64;
const int PE_SORT_BY_MAG      = 128;
const int PE_SORT_BY_UNCERT   = 256;

//======================= LOPos ==========================

class LOPos
{
  private:

    LOPointEventList * pLOPointEventList;
    std::string        ObsName;
    std::string        EMail;
    unsigned int       OutputFiles;
    unsigned int       Sort;
    float              ObserverLongitude;
    float              ObserverLatitude;
    double             MaxDistance;
    float              MaxMv;
    double             MinDuration;
    double             SunElev;
    double             MinDrop;
    double             MinProb;
    double             MinCenterProb;
    double             MinStarElev;
    LOPos            * pNext;

  public:

    LOPos( const std::string & aObsName, const std::string & aEMail,
           const unsigned int aOutputFiles, const unsigned int aSort,
           const float aObserverLongitude, const float aObserverLatitude,
           const double aMaxDistance, const float aMaxMv,
           const double aMinDuration, const double aSunElev,
           const double aMinDrop, const double aMinProb,
           const double aMinCenterProb, const double aMinStarElev,
           LOPos * apNext );

    virtual ~LOPos( void );

    LOPos * GetNextPosPtr( void ) const
      { return( pNext ); }

    void AddPointEvent( const LOPointEvent * pLOPointEvent ) const;

    const LOPointEventItem * GetFirstPointEventItem( void ) const;

    const std::string & GetObsNamePtr( void ) const
      { return( ObsName ); }

    const std::string & GetEMail( void ) const
      { return( EMail ); }

    unsigned int GetOutputFiles( void ) const
      { return( OutputFiles ); }

    unsigned int GetSort( void ) const
      { return( Sort ); }

    float GetObserverLongitude( void ) const
      { return( ObserverLongitude ); }

    float GetObserverLatitude( void ) const
      { return( ObserverLatitude ); }

    double GetMaxDistance( void ) const
      { return( MaxDistance ); }

    float GetMaxMv( void ) const
      { return( MaxMv ); }

    double GetMinDuration( void ) const
      { return( MinDuration ); }

    double GetSunElev( void ) const
      { return( SunElev ); }

    double GetMinDrop( void ) const
      { return( MinDrop ); }

    double GetMinProb( void ) const
      { return( MinProb ); }

    double GetMinCenterProb( void ) const
      { return( MinCenterProb ); }

    double GetMinStarElev( void ) const
      { return( MinStarElev ); }

    //virtual void Print( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
