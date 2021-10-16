//------------------------------------------------------------------------------
//
// File:    loAsteroid.h
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

#ifndef LO_ASTEROID_H
#define LO_ASTEROID_H

#include <string>

namespace aps {

  namespace apslinoccult {

//======================= LOAsteroid ==========================

class LOAsteroid
{
  private:

    int    AsteroidID;
    std::string AsteroidName;
    double ObservationEpoch;
    double M;
    double W;
    double O;
    double I;
    double E;
    double A;
    double Diameter;
    double Brigteness;
    double Slope;
    double EphemerisUncertainty;

  public:

    LOAsteroid( const int aAsteroidID, const std::string & aAsteroidName, const double aObservationEpoch,
                const double aM, const double aW, const double aO, const double aI, const double aE, const double aA,
                const double aDiameter, const double aBrigteness, const double aSlope, const double aEphemerisUncertainty );

    virtual ~LOAsteroid( void );

    int GetAsteroidID( void ) const
      { return( AsteroidID ); }

    const std::string & GetAsteroidNamePtr( void ) const
      { return( AsteroidName ); }

    double GetObservationEpoch( void ) const
      { return( ObservationEpoch ); }

    double GetM( void ) const
      { return( M ); }

    double GetW( void ) const
      { return( W ); }

    double GetO( void ) const
      { return( O ); }

    double GetI( void ) const
      { return( I ); }

    double GetE( void ) const
      { return( E ); }

    double GetA( void ) const
      { return( A ); }

    double GetDiameter( void ) const
      { return( Diameter ); }

    double GetBrigteness( void ) const
      { return( Brigteness ); }

    double GetSlope( void ) const
      { return( Slope ); }

    double GetEphemerisUncertainty( void ) const
      { return( EphemerisUncertainty ); }

    virtual void Print( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------




