//------------------------------------------------------------------------------
//
// File:    loEvent.h
//
// Purpose: Data for storing occultation event in LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 06.02.2005
//         version 0.2 27.02.2005 LOPointEventList was added
//         version 0.3 24.03.2005 GetFirstPointEventItem was added
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

#ifndef LO_EVENT_H
#define LO_EVENT_H

#include <string>

namespace aps {

  namespace apslinoccult {

class LOPointEventList;
class LOPointEventItem;
class LOPointEvent;

//======================= LOEvent ==========================

class LOEvent
{
  private:

    LOPointEventList * pLOPointEventList;
    int                AsteroidID;
    std::string        AsteroidName;
    double             Diameter;
    double             EphemerisUncertainty;
    double             ObservationEpoch;
    double             M;
    double             W;
    double             O;
    double             I;
    double             E;
    double             A;
    unsigned char      Catalog;
    int                StarNumber;
    short              Mv;
    short              ChebOrder;
    double           * pcX;
    double           * pcY;
    double           * pcZ;
    double             ET_UT;
    double             BeginOccTime;
    double             EndOccTime;
    int                EarthFlag;
    double             MaxDuration;
    double             StarRA;
    double             StarDec;
    double             MoonPhase;
    double             SunDist;
    double             MoonDist;
    double             Brightness;
    double             BrightDelta;
    double             Uncertainty;
    LOEvent          * pNext;

  public:

    LOEvent( const int aAsteroidID, const std::string & aAsteroidName,
             const double aDiameter, const double aEphemerisUncertainty,
             const double aObservationEpoch,
             const double aM, const double aW, const double aO,
             const double aI, const double aE, const double aA,
             const unsigned char aCatalog, const int aStarNumber,
             const short aMv, const short aChebOrder,
             const double * apcX, const double * apcY, const double * apcZ,
             const double aET_UT,
             const double aBeginOccTime, const double aEndOccTime,
             const int aEarthFlag, const double aMaxDuration,
             const double aStarRA, const double aStarDec,
             const double aMoonPhase, const double aSunDist,
             const double aMoonDist, const double aBrightness,
             const double aBrightDelta, const double aUncertainty,
             LOEvent * apNext );

    virtual ~LOEvent( void );

    LOEvent * GetNextEventPtr( void ) const
      { return( pNext ); }

    void AddPointEvent( const LOPointEvent * pLOPointEvent ) const;

    const LOPointEventItem * GetFirstPointEventItem( void ) const;

    int GetAsteroidID( void ) const
      { return( AsteroidID ); }

    const std::string & GetAsteroidNamePtr( void ) const
      { return( AsteroidName ); }

    double GetDiameter( void ) const
      { return( Diameter ); }

    double GetEphemerisUncertainty( void ) const
      { return( EphemerisUncertainty ); }

    double GetObservationEpoch( void ) const
      { return( ObservationEpoch ); }

    double GetM( void ) const
      { return( M ); }

    double GetW( void ) const
      { return( W ); }

    double GetO( void ) const
      { return( O ); }

    double GetI( void ) const
      { return( I ); }

    double GetE( void ) const
      { return( E ); }

    double GetA( void ) const
      { return( A ); }

    unsigned char GetCatalog( void ) const
      { return( Catalog ); }

    int GetStarNumber( void ) const
      { return( StarNumber ); }

    short GetMv( void ) const
      { return( Mv ); }

    short GetChebOrder( void ) const
      { return( ChebOrder ); }

    const double * GetcX( void ) const
      { return( pcX ); }

    const double * GetcY( void ) const
      { return( pcY ); }

    const double * GetcZ( void ) const
      { return( pcZ ); }

    double GetET_UT( void ) const
      { return( ET_UT ); }

    double GetBeginOccTime( void ) const
      { return( BeginOccTime ); }

    double GetEndOccTime( void ) const
      { return( EndOccTime ); }

    int GetEarthFlag( void ) const
      { return( EarthFlag ); }

    double GetMaxDuration( void ) const
      { return( MaxDuration ); }

    double GetStarRA( void ) const
      { return( StarRA ); }

    double GetStarDec( void ) const
      { return( StarDec ); }

    double GetMoonPhase( void ) const
      { return( MoonPhase ); }

    double GetSunDist( void ) const
      { return( SunDist ); }

    double GetMoonDist( void ) const
      { return( MoonDist ); }

    double GetBrightness( void ) const
      { return( Brightness ); }

    double GetBrightDelta( void ) const
      { return( BrightDelta ); }

    double GetUncertainty( void ) const
      { return( Uncertainty ); }

    //virtual void Print( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
