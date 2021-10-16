//------------------------------------------------------------------------------
//
// File:    loAstOrbData.cc
//
// Purpose: Asteroids ephemeris data base for LinOccult.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 31.01.2004
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

#include "loAstOrbData.h"
#include "loAsteroid.h"

namespace aps {

  namespace apslinoccult {

//======================= LOAstOrbData ==========================

LOAstOrbData :: LOAstOrbData( const unsigned int aAsteroidsNumber ) :
                              AsteroidsNumber( aAsteroidsNumber ),
                              CurrentNumber( 0 )
{
  ppLOAsteroidArray = new LOAsteroid * [ aAsteroidsNumber ];
}

LOAstOrbData :: ~LOAstOrbData( void )
{
  unsigned int i;

  for( i = 0; i < CurrentNumber; i++ ) {
    delete ppLOAsteroidArray[ i ];
  }

  delete ppLOAsteroidArray;
}

LOAsteroid * LOAstOrbData :: CreateAsteroid( const int AsteroidID,
                                             const std::string & AsteroidName,
                                             const double ObservationEpoch,
                                             const double M, const double W, const double O,
                                             const double I, const double E, const double A,
                                             const double Diameter, const double Brigteness,
                                             const double Slope, const double EphemerisUncertainty )
{
  LOAsteroid * pLOAsteroid = 0;

  if( CurrentNumber < AsteroidsNumber ) {
    pLOAsteroid = new LOAsteroid( AsteroidID, AsteroidName, ObservationEpoch,
                                  M, W, O, I, E, A, Diameter, Brigteness, Slope, EphemerisUncertainty );

    ppLOAsteroidArray[ CurrentNumber ] = pLOAsteroid;

    CurrentNumber++;
  }

  return( pLOAsteroid );
}

LOAsteroid * LOAstOrbData :: GetAsteroidPtr( const unsigned int AsteroidNumber ) const
{
  if( AsteroidNumber < CurrentNumber ) {
    return( ppLOAsteroidArray[ AsteroidNumber ] );
  }

  return( 0 );
}

}}

//---------------------------- End of file ---------------------------
