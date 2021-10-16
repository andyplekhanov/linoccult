//------------------------------------------------------------------------------
//
// File:    loPos.cc
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

#include "loPos.h"
#include "loPointEvent.h"

namespace aps {

  namespace apslinoccult {

LOPos :: LOPos( const std::string & aObsName, const std::string & aEMail,
                const unsigned int aOutputFiles, const unsigned int aSort,
                const float aObserverLongitude, const float aObserverLatitude,
                const double aMaxDistance, const float aMaxMv,
                const double aMinDuration, const double aSunElev,
                const double aMinDrop, const double aMinProb,
                const double aMinCenterProb, const double aMinStarElev,
                LOPos * apNext ) :
         ObsName( aObsName ), EMail( aEMail ),
         OutputFiles( aOutputFiles ), Sort( aSort ),
         ObserverLongitude( aObserverLongitude ),
         ObserverLatitude( aObserverLatitude ),
         MaxDistance( aMaxDistance ), MaxMv( aMaxMv ),
         MinDuration( aMinDuration ), SunElev( aSunElev ),
         MinDrop( aMinDrop ), MinProb( aMinProb ),
         MinCenterProb( aMinCenterProb ),
         MinStarElev( aMinStarElev ),
         pNext( apNext )

{
  pLOPointEventList = new LOPointEventList();
}

LOPos :: ~LOPos( void )
{
  delete pLOPointEventList;
}

void LOPos :: AddPointEvent( const LOPointEvent * pLOPointEvent ) const
{
  pLOPointEventList->AddPointEvent( pLOPointEvent );
}

const LOPointEventItem * LOPos :: GetFirstPointEventItem( void ) const
{
  return( pLOPointEventList->GetFirstPointEventItem() );
}

}}

//---------------------------- End of file ---------------------------
