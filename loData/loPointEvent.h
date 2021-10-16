//------------------------------------------------------------------------------
//
// File:    loPointEvent.h
//
// Purpose: Data for storing occultation event near one observation point in LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 25.02.2005
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

#ifndef LO_POINT_EVENT_H
#define LO_POINT_EVENT_H

namespace aps {

  namespace apslinoccult {

class LOPos;
class LOEvent;

//======================= LOPointEvent ==========================

class LOPointEvent
{
  private:
    const LOPos   * pLOPos;
    const LOEvent * pLOEvent;
    double          Distance;
    double          Mjdate;
    double          StarElev;
    double          SunElev;
    double          MoonElev;
    double          MaxLongitude;
    double          MaxLatitude;
    double          Probability;
    double          MaxProbability;
    double          Az;
    double          StarAz;

  public:

    LOPointEvent( const LOPos * apLOPos, const LOEvent * apLOEvent,
                  const double aDistance, const double aMjdate,
                  const double aStarElev, const double aSunElev,
                  const double aMoonElev, const double aMaxLongitude,
                  const double aMaxLatitude, const double aProbability,
                  const double aMaxProbability, const double aAz,
                  const double aStarAz );

    virtual ~LOPointEvent( void );

    const LOPos * GetLOPosPtr( void ) const
      { return( pLOPos ); }

    const LOEvent * GetLOEventPtr( void ) const
      { return( pLOEvent ); }

    double GetDistance( void ) const
      { return( Distance ); }

    double GetMjdate( void ) const
      { return( Mjdate ); }

    double GetStarElev( void ) const
      { return( StarElev ); }

    double GetSunElev( void ) const
      { return( SunElev ); }

    double GetMoonElev( void ) const
      { return( MoonElev ); }

    double GetMaxLongitude( void ) const
      { return( MaxLongitude ); }

    double GetMaxLatitude( void ) const
      { return( MaxLatitude ); }

    double GetProbability( void ) const
      { return( Probability ); }

    double GetMaxProbability( void ) const
      { return( MaxProbability ); }

    double GetAz( void ) const
      { return( Az ); }

    double GetStarAz( void ) const
      { return( StarAz ); }
};

//======================= LOPointEventItem ==========================

class LOPointEventItem
{
  private:

    LOPointEventItem   * pLONextPointEventItem;
    const LOPointEvent * pLOPointEvent;

  public:

    LOPointEventItem( LOPointEventItem * apLONextPointEventItem, const LOPointEvent * apLOPointEvent );

    virtual ~LOPointEventItem( void );

    LOPointEventItem * GetNextPointEventItemPtr( void ) const
      { return( pLONextPointEventItem ); }

    const LOPointEvent * GetPointEventPtr( void ) const
      { return( pLOPointEvent ); }
};

//======================= LOPointEventList ==========================

class LOPointEventList
{
  private:

    LOPointEventItem * pFirstPointEventItem;

  public:

    LOPointEventList( void );

    virtual ~LOPointEventList( void );

    void AddPointEvent( const LOPointEvent * pLOPointEvent );

    const LOPointEventItem * GetFirstPointEventItem( void ) const
      { return( pFirstPointEventItem ); }
};

}}

#endif

//---------------------------- End of file ---------------------------
