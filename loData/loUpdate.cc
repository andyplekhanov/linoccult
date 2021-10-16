//------------------------------------------------------------------------------
//
// File:    loUpdate.cc
//
// Purpose: Data for storing update in LinOccult.
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

#include "loUpdate.h"

namespace aps {

  namespace apslinoccult {

//======================= LOUpdate ==========================

LOUpdate :: LOUpdate( const int aAsteroidID, const double aObservationEpoch,
                      const double aM, const double aW, const double aO,
                      const double aI, const double aE, const double aA,
                      const double aMajor, const double aMinor,
                      const double aPA, LOUpdate * apNext ) :
            AsteroidID( aAsteroidID ), ObservationEpoch( aObservationEpoch ),
            M( aM ), W( aW ), O( aO ), I( aI ), E( aE ), A( aA ),
            Major( aMajor ), Minor( aMinor ), PA( aPA ), pNext( apNext )
{
}

LOUpdate :: ~LOUpdate( void )
{
}

}}

//---------------------------- End of file ---------------------------
