//------------------------------------------------------------------------------
//
// File:    loEvent.cc
//
// Purpose: Data for storing occultation event in LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 06.02.2005
//         version 0.2 27.02.2005 LOPointEventList was added
//         version 0.3 24.03.2005 GetFirstPointEventItem was added
// 
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

#include "loEvent.h"
#include "loPointEvent.h"

namespace aps {

  namespace apslinoccult {

LOEvent :: LOEvent( const int aAsteroidID, const std::string & aAsteroidName,
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
                    LOEvent * apNext ) :
           AsteroidID( aAsteroidID ), AsteroidName( aAsteroidName ),
           Diameter( aDiameter ), EphemerisUncertainty( aEphemerisUncertainty ),
           ObservationEpoch( aObservationEpoch ),
           M( aM ), W( aW ), O( aO ), I( aI ), E( aE ), A( aA ),
           Catalog( aCatalog ), StarNumber( aStarNumber ),
           Mv( aMv ), ChebOrder( aChebOrder ),
           ET_UT( aET_UT ), BeginOccTime( aBeginOccTime ),
           EndOccTime( aEndOccTime ), EarthFlag( aEarthFlag ),
           MaxDuration( aMaxDuration ), StarRA( aStarRA ),
           StarDec( aStarDec ), MoonPhase( aMoonPhase ),
           SunDist( aSunDist ), MoonDist( aMoonDist ),
           Brightness( aBrightness ), BrightDelta( aBrightDelta ),
           Uncertainty( aUncertainty ), pNext( apNext )
{
  pLOPointEventList    = new LOPointEventList();

  pcX = new double[ aChebOrder + 1 ];
  pcY = new double[ aChebOrder + 1 ];
  pcZ = new double[ aChebOrder + 1 ];

  for( int i = 0; i <= aChebOrder; i++ ) {
    pcX[ i ] = apcX[ i ];
    pcY[ i ] = apcY[ i ];
    pcZ[ i ] = apcZ[ i ];
  }
}

LOEvent :: ~LOEvent( void )
{
  delete pLOPointEventList;

  delete [] pcX;
  delete [] pcY;
  delete [] pcZ;
}

void LOEvent :: AddPointEvent( const LOPointEvent * pLOPointEvent ) const
{
  pLOPointEventList->AddPointEvent( pLOPointEvent );
}

const LOPointEventItem * LOEvent :: GetFirstPointEventItem( void ) const
{
  return( pLOPointEventList->GetFirstPointEventItem() );
}

}}

//---------------------------- End of file ---------------------------
