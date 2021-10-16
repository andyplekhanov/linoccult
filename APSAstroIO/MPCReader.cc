//------------------------------------------------------------------------------
//
// File:    MPCReader.cc
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

#include <sstream>

#include "MPCReader.h"
#include "apsmpcdefs.h"

namespace aps {

  namespace apsastroio {

//======================= MPCReader ==========================

MPCReader :: MPCReader( const std::string & MPCFilePath ) : APSIStrAstroIO( MPCFilePath )
{
}

MPCReader :: ~MPCReader( void )
{
}

int MPCReader :: ConvertAsteroidID( const std::string & AsteroidID, int & AsteroidNumber )
{
  char A = AsteroidID[ 0 ];
  int  RetCode = 0;

  if( ( A == ' ' ) || ( ( A >= '0' ) && ( A <= '9' ) ) ) {
    std::stringstream istrstream( AsteroidID );

    if( istrstream >> AsteroidNumber ) {
      if( AsteroidNumber < 0 ) {
        RetCode = 1;
      }
    }
    else {
      RetCode = 2;
    }
  }
  else {
    if( ( A >= 'A' ) && ( A <= 'Z' ) ) {
      std::stringstream istrstream( AsteroidID.substr( 1 ) );

      if( istrstream >> AsteroidNumber ) {
        AsteroidNumber = AsteroidNumber + ( A - 'A' + 10 ) * 10000; 

        if( AsteroidNumber < 0 ) {
          RetCode = 3;
        }
      }
      else {
        RetCode = 4;
      }
    }
    else {
      RetCode = 5;
    }
  }

  return( RetCode );
}

int MPCReader :: GetAsteroidID( std::string & AsteroidID ) const
{
  return( GetString( AsteroidID, MPC_NUMBER_OFFSET, MPC_NUMBER_LENGTH ) );
}

int MPCReader :: GetAsteroidName( std::string & AsteroidName ) const
{
  return( GetString( AsteroidName, MPC_NAME_OFFSET, MPC_NAME_LENGTH ) );
}

int MPCReader :: GetAsterisk( char & Asterisk ) const
{
  return( GetChar( Asterisk, MPC_ASTERISK_OFFSET ) );
}

int MPCReader :: GetNote1( char & Note1 ) const
{
  return( GetChar( Note1, MPC_NOTE1_OFFSET ) );
}

int MPCReader :: GetNote2( char & Note2 ) const
{
  return( GetChar( Note2, MPC_NOTE2_OFFSET ) );
}

int MPCReader :: GetObservationYear( int & ObservationYear ) const
{
  return( GetInteger( ObservationYear, MPC_YEAR_OFFSET, MPC_YEAR_LENGTH ) );
}

int MPCReader :: GetObservationMonth( int & ObservationMonth ) const
{
  return( GetInteger( ObservationMonth, MPC_MONTH_OFFSET, MPC_MONTH_LENGTH ) );
}

int MPCReader :: GetObservationDay( double & ObservationDay, double & Prec ) const
{
  std::string TmpStr;
  int         RetCode = GetString( TmpStr, MPC_DAY_OFFSET, MPC_DAY_LENGTH );

  if( !RetCode ) {
    RetCode = GetDoubleWithPrecision( TmpStr, ObservationDay, Prec );
  }

  return( RetCode );
}

int MPCReader :: GetRA( double & RA, double & Prec ) const
{
  return( GetAngle( RA, Prec, MPC_RA_HOUR_OFFSET,
          MPC_RA_HOUR_LENGTH + MPC_RA_HOUR_PAD + MPC_RA_MIN_LENGTH + MPC_RA_MIN_PAD + MPC_RA_SEC_LENGTH ) );
}

int MPCReader :: GetDec( double & Dec, double & Prec ) const
{
  return( GetAngle( Dec, Prec, MPC_DEC_DEG_OFFSET,
          MPC_DEC_DEG_LENGTH + MPC_DEC_DEG_PAD + MPC_DEC_MIN_LENGTH + MPC_DEC_MIN_PAD + MPC_DEC_SEC_LENGTH ) );
}

int MPCReader :: GetMagnitude( std::string & Magnitude ) const
{
  return( GetString( Magnitude, MPC_MAGNITUDE_OFFSET, MPC_MAGNITUDE_LENGTH ) );
}

int MPCReader :: GetBand( char & Band ) const
{
  return( GetChar( Band, MPC_BAND_OFFSET ) );
}

int MPCReader :: GetObsCode( std::string & ObsCode ) const
{
  return( GetString( ObsCode, MPC_OBS_CODE_OFFSET, MPC_OBS_CODE_LENGTH ) );
}

}}

//---------------------------- End of file ---------------------------

