//------------------------------------------------------------------------------
//
// File:    loEventData.cc
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

#include "loEventData.h"
#include "loEvent.h"

namespace aps {

  namespace apslinoccult {

//======================= LOEventData ==========================

LOEventData :: LOEventData( void ) : ppLOEventsArray( 0 ),
                                     pFirstEvent( 0 ),
                                     EventsNumber( 0 )
{
}

LOEventData :: ~LOEventData( void )
{
  const LOEvent * pLOEvent;
  const LOEvent * pLONextEvent;

  if( ppLOEventsArray ) {
    for( unsigned int i = 0; i < EventsNumber; i++ ) {
      delete ppLOEventsArray[ i ];
    }

    delete ppLOEventsArray;
  }

  pLOEvent = pFirstEvent;

  while( pLOEvent ) {
    pLONextEvent = pLOEvent->GetNextEventPtr();
    delete( pLOEvent );
    pLOEvent = pLONextEvent;
  }
}

const LOEvent * LOEventData :: CreateEvent( const int AsteroidID, const std::string & AsteroidName,
                                            const double Diameter, const double EphemerisUncertainty,
                                            const double ObservationEpoch,
                                            const double M, const double W, const double O,
                                            const double I, const double E, const double A,
                                            const unsigned char Catalog, const int StarNumber,
                                            const short Mv, const short ChebOrder,
                                            const double * pcX, const double * pcY, const double * pcZ,
                                            const double ET_UT, const double BeginOccTime,
                                            const double EndOccTime, const int EarthFlag,
                                            const double MaxDuration, const double StarRA,
                                            const double StarDec, const double MoonPhase,
                                            const double SunDist, const double MoonDist,
                                            const double Brightness, const double BrightDelta,
                                            const double Uncertainty )
{
  LOEvent * pLOEvent;

  pLOEvent = new LOEvent( AsteroidID, AsteroidName, Diameter, EphemerisUncertainty,
                          ObservationEpoch, M, W, O, I, E, A,
                          Catalog, StarNumber, Mv, ChebOrder,
                          pcX, pcY, pcZ, ET_UT,
                          BeginOccTime, EndOccTime, EarthFlag, MaxDuration,
                          StarRA, StarDec, MoonPhase, SunDist, MoonDist,
                          Brightness, BrightDelta, Uncertainty, pFirstEvent );

  pFirstEvent = pLOEvent;

  return( pLOEvent );
}

LOEvent * LOEventData :: GetEventPtr( const unsigned int EventNumber ) const
{
  if( EventNumber < EventsNumber ) {
    return( ppLOEventsArray[ EventNumber ] );
  }

  return( 0 );
}

bool LOEventData :: IsEqual( const LOEvent * pLOEvent, const int AsteroidID, const unsigned char Catalog,
                             const int StarNumber, const double DateTime ) const
{
  if( pLOEvent->GetAsteroidID() == AsteroidID ) {
    if( pLOEvent->GetCatalog() == Catalog ) {
      if( pLOEvent->GetStarNumber() == StarNumber ) {
        if( ( DateTime >= pLOEvent->GetBeginOccTime() ) && ( DateTime <= pLOEvent->GetEndOccTime() ) ) {
          return( true );
        }
      }
    }
  }

  return( false );
}

const LOEvent * LOEventData :: FindEvent( const int AsteroidID, const unsigned char Catalog,
                                          const int StarNumber, const double DateTime ) const
{
  const LOEvent * pLOEvent = pFirstEvent;

  while( pLOEvent ) {
    if( IsEqual( pLOEvent, AsteroidID, Catalog, StarNumber, DateTime ) ) {
      return( pLOEvent );
    }

    pLOEvent = pLOEvent->GetNextEventPtr();
  }

  return( 0 );
}

int LOEventData :: Rebuild( void )
{
  LOEvent      * pLOEvent;
  unsigned int   CurrentNumber;
  int            RetCode = 0;

  pLOEvent = pFirstEvent;

  while( pLOEvent ) {
    EventsNumber++;

    pLOEvent = pLOEvent->GetNextEventPtr();
  }

  if( EventsNumber ) {
    ppLOEventsArray = new LOEvent * [ EventsNumber ];  

    pLOEvent = pFirstEvent;

    CurrentNumber = 0;

    while( pLOEvent ) {
      if( CurrentNumber < EventsNumber ) {
        ppLOEventsArray[ CurrentNumber ] = pLOEvent;

        CurrentNumber++;
      }
      else {
        RetCode = 1;
        break;
      }

      pLOEvent = pLOEvent->GetNextEventPtr();
    }

    pFirstEvent = 0;
  }

  return( RetCode );
}

void LOEventData :: SortByDate( void )
{

}

}}

//---------------------------- End of file ---------------------------
