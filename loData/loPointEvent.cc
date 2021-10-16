//------------------------------------------------------------------------------
//
// File:    loPointEvent.cc
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

#include "loPointEvent.h"

namespace aps {

  namespace apslinoccult {

//======================= LOPointEvent ==========================

LOPointEvent :: LOPointEvent( const LOPos * apLOPos, const LOEvent * apLOEvent,
                              const double aDistance, const double aMjdate,
                              const double aStarElev, const double aSunElev,
                              const double aMoonElev, const double aMaxLongitude,
                              const double aMaxLatitude, const double aProbability,
                              const double aMaxProbability, const double aAz, 
                              const double aStarAz ) :
                pLOPos( apLOPos ), pLOEvent( apLOEvent ), Distance( aDistance ),
                Mjdate( aMjdate ), StarElev( aStarElev ), SunElev( aSunElev ),
                MoonElev( aMoonElev ), MaxLongitude( aMaxLongitude ),
                MaxLatitude( aMaxLatitude ), Probability( aProbability ),
                MaxProbability( aMaxProbability ), Az( aAz ), StarAz( aStarAz )
{
}

LOPointEvent :: ~LOPointEvent( void )
{
}

//======================= LOPointEventItem ==========================

LOPointEventItem :: LOPointEventItem( LOPointEventItem * apLOPointEventItem,
                                      const LOPointEvent * apLOPointEvent ) :
                    pLONextPointEventItem( apLOPointEventItem ),
                    pLOPointEvent( apLOPointEvent )
{
}

LOPointEventItem :: ~LOPointEventItem( void )
{
}

//======================= LOPointEventList ==========================

LOPointEventList :: LOPointEventList( void ) : pFirstPointEventItem( 0 )
{
}

LOPointEventList :: ~LOPointEventList( void )
{
  LOPointEventItem * pLOPointEventItem;
  LOPointEventItem * pLONextPointEventItem;

  pLOPointEventItem = pFirstPointEventItem;

  while( pLOPointEventItem ) {
    pLONextPointEventItem = pLOPointEventItem->GetNextPointEventItemPtr();
    delete( pLOPointEventItem );
    pLOPointEventItem = pLONextPointEventItem;
  }
}

void LOPointEventList :: AddPointEvent( const LOPointEvent * pLOPointEvent )
{
  LOPointEventItem * pLOPointEventItem;

  pLOPointEventItem = new LOPointEventItem( pFirstPointEventItem, pLOPointEvent );

  pFirstPointEventItem = pLOPointEventItem;
}

}}

//---------------------------- End of file ---------------------------
