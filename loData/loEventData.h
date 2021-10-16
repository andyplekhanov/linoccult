//------------------------------------------------------------------------------
//
// File:    loEventData.h
//
// Purpose: Base class for occultation events data base for LinOccult.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 28.12.2004
//         version 0.2 07.02.2005 Event processing was added.
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

#ifndef LO_EVENT_DATA_H
#define LO_EVENT_DATA_H

#include <string>

namespace aps {

  namespace apslinoccult {

class LOEvent;

//======================= LOEventData ==========================

class LOEventData
{
  private:

    LOEvent      ** ppLOEventsArray;
    LOEvent       * pFirstEvent;
    unsigned int    EventsNumber;

    bool IsEqual( const LOEvent * pLOEvent, const int AsteroidID, const unsigned char Catalog,
                 const int StarNumber, const double DateTime ) const;

  public:

    LOEventData( void );

    virtual ~LOEventData( void );

    const LOEvent * CreateEvent( const int AsteroidID, const std::string & AsteroidName,
                                 const double Diameter, const double EphemerisUncertainty,
                                 const double ObservationEpoch,
                                 const double M, const double W, const double O,
                                 const double I, const double E, const double A,
                                 const unsigned char Catalog, const int StarNumber,
                                 const short Mv, const short ChebOrder,
                                 const double * pcX, const double * pcY, const double * pcZ,
                                 const double ET_UT, const double BeginOccTime, const double EndOccTime,
                                 const int EarthFlag, const double MaxDuration,
                                 const double StarRA, const double StarDec, const double MoonPhase,
                                 const double SunDist, const double MoonDist,
                                 const double Brightness, const double BrightDelta,
                                 const double Uncertainty );

    unsigned int GetEventsNumber( void ) const
      { return( EventsNumber ); }

    LOEvent * GetEventPtr( const unsigned int EventNumber ) const;

    const LOEvent * FindEvent( const int AsteroidID, const unsigned char Catalog,
                               const int StarNumber, const double DateTime ) const;

    int Rebuild( void );

    void SortByDate( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
