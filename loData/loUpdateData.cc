//------------------------------------------------------------------------------
//
// File:    loUpdateData.cc
//
// Purpose: Base class for updates data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 16.04.2005
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

#include "loUpdateData.h"
#include "loUpdate.h"

namespace aps {

  namespace apslinoccult {

//======================= LOUpdateData ==========================

LOUpdateData :: LOUpdateData( void ) :
                  pFirstUpdate( 0 ),
                  UpdatesNumber( 0 )
{
}

LOUpdateData :: ~LOUpdateData( void )
{
  const LOUpdate * pLOUpdate;
  const LOUpdate * pLONextUpdate;

  pLOUpdate = pFirstUpdate;

  while( pLOUpdate ) {
    pLONextUpdate = pLOUpdate->GetNextUpdatePtr();
    delete( pLOUpdate );
    pLOUpdate = pLONextUpdate;
  }
}

const LOUpdate * LOUpdateData :: CreateUpdate( const int AsteroidID, const double ObservationEpoch,
                                               const double M, const double W, const double O,
                                               const double I, const double E, const double A,
                                               const double Major, const double Minor, const double PA )
{
  LOUpdate * pLOUpdate;

  pLOUpdate = new LOUpdate( AsteroidID, ObservationEpoch, M, W, O, I, E, A, Major, Minor, PA, pFirstUpdate );

  pFirstUpdate = pLOUpdate;

  return( pLOUpdate );
}

bool LOUpdateData :: IsEqual( const LOUpdate * pLOUpdate, const int AsteroidID, const double LastDate ) const
{
  if( pLOUpdate->GetAsteroidID() == AsteroidID ) {
    if( LastDate <= pLOUpdate->GetObservationEpoch() ) {
      return( true );
    }
  }

  return( false );
}

const LOUpdate * LOUpdateData :: FindUpdate( const int AsteroidID, const double LastDate ) const
{
  const LOUpdate * pLOUpdate = pFirstUpdate;
  const LOUpdate * pLOLastUpdate = 0;

  while( pLOUpdate ) {
    if( IsEqual( pLOUpdate, AsteroidID, LastDate ) ) {

      if( pLOLastUpdate ) {
        if( pLOLastUpdate->GetObservationEpoch() < pLOUpdate->GetObservationEpoch() ) {
          pLOLastUpdate = pLOUpdate;
        }
      }
      else {
        pLOLastUpdate = pLOUpdate;
      }
    }

    pLOUpdate = pLOUpdate->GetNextUpdatePtr();
  }

  return( pLOLastUpdate );
}

}}

//---------------------------- End of file ---------------------------
