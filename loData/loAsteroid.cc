//------------------------------------------------------------------------------
//
// File:    loAsteroid.cc
//
// Purpose: Asteroid ephemeris data for LinOccult.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 02.02.2004
// version 0.2 11.04.2004 diameter has been added
// version 0.3 10.06.2004 Brigteness, EphemerisUncertainty have been added
// version 0.4 15.02.2005 Slope was added
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

#include <iostream>

#include "loAsteroid.h"

namespace aps {

  namespace apslinoccult {

LOAsteroid :: LOAsteroid( const int aAsteroidID, const std::string & aAsteroidName, const double aObservationEpoch,
                          const double aM, const double aW, const double aO, const double aI, const double aE, const double aA,
                          const double aDiameter, const double aBrigteness, const double aSlope, const double aEphemerisUncertainty ) :
              AsteroidID( aAsteroidID ),
              AsteroidName( aAsteroidName ),
              ObservationEpoch( aObservationEpoch ),
              M( aM ), W( aW ), O( aO ), I( aI ), E( aE ), A( aA ),
              Diameter( aDiameter ),
              Brigteness( aBrigteness ),
              Slope( aSlope ),
              EphemerisUncertainty( aEphemerisUncertainty )
{
}

LOAsteroid :: ~LOAsteroid( void )
{
}

void LOAsteroid :: Print( void ) const
{
  std::cout << "ID = " << AsteroidID << " Name = " << AsteroidName <<
               " ObservationEpoch = " <<  ObservationEpoch <<
               " M = " << M << " W = " << W << " O = " << O <<
               " I = " << I << " E = " << E << " A = " << A <<
               " Diameter = " << Diameter <<
               " Brigteness = " << Brigteness <<
               " Slope = " << Slope <<
               " EphemerisUncertainty = " << EphemerisUncertainty << std::endl;
}

}}

//---------------------------- End of file ---------------------------
