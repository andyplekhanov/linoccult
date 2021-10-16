//------------------------------------------------------------------------------
//
// File:    loPosData.cc
//
// Purpose: Base class for observation positions data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 17.02.2005
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

#include "loPosData.h"
#include "loPos.h"

namespace aps {

  namespace apslinoccult {

//======================= LOPosData ==========================

LOPosData :: LOPosData( void ) : ppLOPosArray( 0 ),
                                 pFirstPos( 0 ),
                                 PositionsNumber( 0 )
{
}

LOPosData :: ~LOPosData( void )
{
  const LOPos  * pLOPos;
  const LOPos  * pLONextPos;

  if( ppLOPosArray ) {
    for( unsigned int i = 0; i < PositionsNumber; i++ ) {
      delete ppLOPosArray[ i ];
    }

    delete ppLOPosArray;
  }

  pLOPos = pFirstPos;

  while( pLOPos ) {
    pLONextPos = pLOPos->GetNextPosPtr();
    delete( pLOPos );
    pLOPos = pLONextPos;
  }
}

const LOPos * LOPosData :: CreatePosition( const std::string & ObsName, const std::string & EMail,
                                           const unsigned int OutputFiles, const unsigned int Sort,
                                           const float ObserverLongitude, const float ObserverLatitude,
                                           const double MaxDistance, const float MaxMv,
                                           const double MinDuration, const double SunElev,
                                           const double MinDrop, const double MinProb,
                                           const double MinCenterProb, const double MinStarElev )
{
  LOPos * pLOPos;

  pLOPos = new LOPos( ObsName, EMail, OutputFiles, Sort,
                      ObserverLongitude, ObserverLatitude, MaxDistance, MaxMv, MinDuration, SunElev,
                      MinDrop, MinProb, MinCenterProb, MinStarElev, pFirstPos );

  pFirstPos = pLOPos;

  return( pLOPos );
}

LOPos * LOPosData :: GetPositionPtr( const unsigned int PositionNumber ) const
{
  if( PositionNumber < PositionsNumber ) {
    return( ppLOPosArray[ PositionNumber ] );
  }

  return( 0 );
}

int LOPosData :: Rebuild( void )
{
  LOPos        * pLOPos;
  unsigned int   CurrentNumber;
  int            RetCode = 0;

  pLOPos = pFirstPos;

  while( pLOPos ) {
    PositionsNumber++;

    pLOPos = pLOPos->GetNextPosPtr();
  }

  if( PositionsNumber ) {
    ppLOPosArray = new LOPos * [ PositionsNumber ];  

    pLOPos = pFirstPos;

    CurrentNumber = 0;

    while( pLOPos ) {
      if( CurrentNumber < PositionsNumber ) {
        ppLOPosArray[ CurrentNumber ] = pLOPos;

        CurrentNumber++;
      }
      else {
        RetCode = 1;
        break;
      }

      pLOPos = pLOPos->GetNextPosPtr();
    }

    pFirstPos = 0;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
