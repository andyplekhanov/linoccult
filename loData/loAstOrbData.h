//------------------------------------------------------------------------------
//
// File:    loAstOrbData.h
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

#ifndef LO_ASTORB_DATA_H
#define LO_ASTORB_DATA_H

#include <string>

namespace aps {

  namespace apslinoccult {

class LOAsteroid;

//======================= LOAstOrbData ==========================

class LOAstOrbData
{
  private:

    LOAsteroid   ** ppLOAsteroidArray;
    unsigned int    AsteroidsNumber;
    unsigned int    CurrentNumber;

  public:

    LOAstOrbData( const unsigned int aAsteroidsNumber );

    virtual ~LOAstOrbData( void );

    LOAsteroid * CreateAsteroid( const int AsteroidID, const std::string & AsteroidName,
                                 const double ObservationEpoch,
                                 const double M, const double W, const double O,
                                 const double I, const double E, const double A,
                                 const double Diameter, const double Brigteness,
                                 const double Slope, const double EphemerisUncertainty );

    unsigned int GetAsteroidsNumber( void ) const
      { return( AsteroidsNumber ); }

    unsigned int GetCurrentNumber( void ) const
      { return( CurrentNumber ); }

    LOAsteroid * GetAsteroidPtr( const unsigned int AsteroidNumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
