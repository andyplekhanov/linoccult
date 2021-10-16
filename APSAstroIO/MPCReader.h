//------------------------------------------------------------------------------
//
// File:    MPCReader.h
//
// Purpose: Read data from MPC observations file.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 23.02.2006
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

#ifndef MPC_READER_H
#define MPC_READER_H

#include <string>

#include "apsistrastroio.h"

namespace aps {

  namespace apsastroio {

//======================= MPCReader ==========================

class MPCReader : protected APSIStrAstroIO
{
  protected:

    int GetAsteroidID( std::string & AsteroidID ) const;

    int GetAsteroidName( std::string & AsteroidName ) const;

    int GetAsterisk( char & Asterisk ) const;

    int GetNote1( char & Note1 ) const;

    int GetNote2( char & Note2 ) const;

    int GetObservationYear( int & ObservationYear ) const;

    int GetObservationMonth( int & ObservationMonth ) const;

    int GetObservationDay( double & ObservationDay, double & Prec ) const;

    int GetRA( double & RA, double & Prec ) const;

    int GetDec( double & Dec, double & Prec ) const;

    int GetMagnitude( std::string & Magnitude ) const;

    int GetBand( char & Band ) const;

    int GetObsCode( std::string & ObsCode ) const;

  public:

    MPCReader( const std::string & MPCFilePath );

    virtual ~MPCReader( void );

    static int ConvertAsteroidID( const std::string & AsteroidID, int & AsteroidNumber );
};

}}

#endif

//---------------------------- End of file ---------------------------
