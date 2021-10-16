//------------------------------------------------------------------------------
//
// File:    loPointEventData.cc
//
// Purpose: Base class for observation event and positions data base for LinOccult.
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

#include "loPointEventData.h"
#include "loPointEvent.h"

namespace aps {

  namespace apslinoccult {

//======================= LOPointEventData ==========================

LOPointEventData :: LOPointEventData( void )
{
  pLOPointEventList = new LOPointEventList();
}

LOPointEventData :: ~LOPointEventData( void )
{
  const LOPointEvent     * pLOPointEvent;
  const LOPointEventItem * pLOPointEventItem;

  pLOPointEventItem = pLOPointEventList->GetFirstPointEventItem();

  while( pLOPointEventItem ) {
    pLOPointEvent = pLOPointEventItem->GetPointEventPtr();
    delete pLOPointEvent;
    pLOPointEventItem = pLOPointEventItem->GetNextPointEventItemPtr();
  }

  delete pLOPointEventList;
}

const LOPointEvent * LOPointEventData :: CreatePointEvent( const LOPos * pLOPos, const LOEvent * pLOEvent,
                                                           const double Distance, const double Mjdate,
                                                           const double StarElev, const double SunElev,
                                                           const double MoonElev, const double MaxLongitude,
                                                           const double MaxLatitude, const double Probability,
                                                           const double MaxProbability, const double Az,
                                                           const double StarAz )
{
  const LOPointEvent * pLOPointEvent;

  pLOPointEvent = new LOPointEvent( pLOPos, pLOEvent, Distance, Mjdate,
                                    StarElev, SunElev, MoonElev, MaxLongitude, MaxLatitude,
                                    Probability, MaxProbability, Az, StarAz );

  pLOPointEventList->AddPointEvent( pLOPointEvent );

  return( pLOPointEvent );
}

}}

//---------------------------- End of file ---------------------------
