//------------------------------------------------------------------------------
//
// File:    RWOReader.cc
//
// Purpose: Read data from RWO observations file.
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

#include "RWOReader.h"
#include "apsrwodefs.h"

namespace aps {

  namespace apsastroio {

    const std::string END_OF_HEADER = "END_OF_HEADER";
    const char DELIM_SIGN           = '=';
    const char CHAR_DELIM           = '\'';

//======================= RWOReader ==========================

RWOReader :: RWOReader( const std::string & MPCFilePath ) : APSIStrAstroIO( MPCFilePath )
{
}

RWOReader :: ~RWOReader( void )
{
}

int RWOReader :: GetAsteroidName( std::string & AsteroidName ) const
{
  return( GetString( AsteroidName, RWO_NUMBER_OFFSET, RWO_NUMBER_LENGTH ) );
}

int RWOReader :: GetType( char & Type ) const
{
  return( GetChar( Type, RWO_TYPE_OFFSET ) );
}

int RWOReader :: GetTech( char & Tech ) const
{
  return( GetChar( Tech, RWO_TECH_OFFSET ) );
}

int RWOReader :: GetNote( char & Note ) const
{
  return( GetChar( Note, RWO_NOTE_OFFSET ) );
}

int RWOReader :: GetObservationYear( int & ObservationYear ) const
{
  return( GetInteger( ObservationYear, RWO_YEAR_OFFSET, RWO_YEAR_LENGTH ) );
}

int RWOReader :: GetObservationMonth( int & ObservationMonth ) const
{
  return( GetInteger( ObservationMonth, RWO_MONTH_OFFSET, RWO_MONTH_LENGTH ) );
}

int RWOReader :: GetObservationDay( double & ObservationDay ) const
{
  return( GetDouble( ObservationDay, RWO_DAY_OFFSET, RWO_DAY_LENGTH ) );
}

int RWOReader :: GetObservationTimeAccuracy( double & ObservationTimeAccuracy ) const
{
  return( GetDouble( ObservationTimeAccuracy, RWO_TIME_ACC_OFFSET, RWO_TIME_ACC_LENGTH ) );
}

int RWOReader :: GetRA( double & RA ) const
{
  double Prec;

  return( GetAngle( RA, Prec, RWO_RA_HOUR_OFFSET,
          RWO_RA_HOUR_LENGTH + RWO_RA_HOUR_PAD + RWO_RA_MIN_LENGTH + RWO_RA_MIN_PAD + RWO_RA_SEC_LENGTH ) );
}

int RWOReader :: GetRAAccuracy( double & RAAccuracy ) const
{
  return( GetDouble( RAAccuracy, RWO_RA_ACC_OFFSET, RWO_RA_ACC_LENGTH ) );
}

int RWOReader :: GetRARMS( std::string & RARMS ) const
{
  return( GetString( RARMS, RWO_RA_RMS_OFFSET, RWO_RA_RMS_LENGTH ) );
}

int RWOReader :: GetRAForce( char & RAForce ) const
{
  return( GetChar( RAForce, RWO_RA_FORCE_OFFSET ) );
}

int RWOReader :: GetRABias( double & RABias ) const
{
  return( GetDouble( RABias, RWO_RA_BIAS_OFFSET, RWO_RA_BIAS_LENGTH ) );
}

int RWOReader :: GetRAResid( std::string & RAResid ) const
{
  return( GetString( RAResid, RWO_RA_RESID_OFFSET, RWO_RA_RESID_LENGTH ) );
}

int RWOReader :: GetDec( double & Dec ) const
{
  double Prec;

  return( GetAngle( Dec, Prec, RWO_DEC_DEG_OFFSET,
          RWO_DEC_DEG_LENGTH + RWO_DEC_DEG_PAD + RWO_DEC_MIN_LENGTH + RWO_DEC_MIN_PAD + RWO_DEC_SEC_LENGTH ) );
}

int RWOReader :: GetDecAccuracy( double & DecAccuracy ) const
{
  return( GetDouble( DecAccuracy, RWO_DEC_ACC_OFFSET, RWO_DEC_ACC_LENGTH ) );
}

int RWOReader :: GetDecRMS( std::string & DecRMS ) const
{
  return( GetString( DecRMS, RWO_DEC_RMS_OFFSET, RWO_DEC_RMS_LENGTH ) );
}

int RWOReader :: GetDecForce( char & DecForce ) const
{
  return( GetChar( DecForce, RWO_DEC_FORCE_OFFSET ) );
}

int RWOReader :: GetDecBias( double & DecBias ) const
{
  return( GetDouble( DecBias, RWO_DEC_BIAS_OFFSET, RWO_DEC_BIAS_LENGTH ) );
}

int RWOReader :: GetDecResid( std::string & DecResid ) const
{
  return( GetString( DecResid, RWO_DEC_RESID_OFFSET, RWO_DEC_RESID_LENGTH ) );
}

int RWOReader :: GetMagnitude( std::string & Magnitude ) const
{
  return( GetString( Magnitude, RWO_MAG_OFFSET, RWO_MAG_LENGTH ) );
}

int RWOReader :: GetObsCode( std::string & ObsCode ) const
{
  return( GetString( ObsCode, RWO_OBS_CODE_OFFSET, RWO_OBS_CODE_LENGTH ) );
}

int RWOReader :: GetChi( std::string & Chi ) const
{
  return( GetString( Chi, RWO_CHI_OFFSET, RWO_CHI_LENGTH ) );
}

int RWOReader :: GetSelCoord( int & SelCoord ) const
{
  return( GetInteger( SelCoord, RWO_SEL_COORD_OFFSET, RWO_SEL_COORD_LENGTH ) );
}

int RWOReader :: GetSelMag( int & SelMag ) const
{
  return( GetInteger( SelMag, RWO_SEL_MAG_OFFSET, RWO_SEL_MAG_LENGTH ) );
}

int RWOReader :: GetIntFromHeader( const std::map<const std::string,const std::string> & params,
                                   const std::string & key,
                                   int & Value ) const
{
  int RetCode = 0;

  const std::map<const std::string,const std::string>::const_iterator p =
                 params.find( key );

  if( p != params.end() ) {
    std::stringstream istrstream( p->second );

    if( !( istrstream >> Value ) ) {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int RWOReader :: GetDoubleFromHeader( const std::map<const std::string,const std::string> & params,
                                      const std::string & key,
                                      double & Value ) const
{
  int RetCode = 0;

  const std::map<const std::string,const std::string>::const_iterator p =
                 params.find( key );

  if( p != params.end() ) {
    std::stringstream istrstream( p->second );

    if( !( istrstream >> Value ) ) {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int RWOReader :: GetCharFromHeader( const std::map<const std::string,const std::string> & params,
                                    const std::string & key,
                                    char & Value ) const
{
  int RetCode = 0;

  const std::map<const std::string,const std::string>::const_iterator p =
                 params.find( key );

  if( p != params.end() ) {
    std::string data = p->second;

    std::string::size_type pos = data.find( CHAR_DELIM );

    if( pos != std::string::npos ) {
      Value = data[ pos + sizeof( CHAR_DELIM ) ];
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int RWOReader :: GetStringFromHeader( const std::map<const std::string,const std::string> & params,
                                      const std::string & key,
                                      std::string & Value ) const
{
  int RetCode = 0;

  const std::map<const std::string,const std::string>::const_iterator p =
                 params.find( key );

  if( p != params.end() ) {
    std::stringstream istrstream( p->second );

    if( !( istrstream >> Value ) ) {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int RWOReader :: AddParam( std::map<const std::string,const std::string> & params,
                           const std::string & Buffer ) const
{
  int RetCode = 0;

  std::string::size_type pos = Buffer.find( DELIM_SIGN );

  if( pos != std::string::npos ) {
    std::string tmp  = Buffer.substr( 0, pos );
    std::string data = Buffer.substr( pos + sizeof( DELIM_SIGN ), std::string::npos );

    std::stringstream istrstream( tmp );
    std::string key;

    if( istrstream >> key ) {
      std::pair<const std::string,const std::string> newPair = std::make_pair( key, data );

      params.insert( newPair );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

bool RWOReader :: IfComment( void ) const
{
  char FirstChar;

  if( !GetChar( FirstChar, 0 ) ) {
    if( FirstChar == '!' ) {
      return( true );
    }
  }

  return( false );
}

int RWOReader :: ReadHeader( std::map<const std::string,const std::string> & params )
{
  params.clear();

  int  RetCode = 1;

  while( ReadStr() ) {
    std::string Buffer = GetBuffer();

    if( Buffer.length() > 0 ) {
      if( IfComment() ) {
        continue;
      }
      else {
        std::string str;

        if( !GetString( str, 0, END_OF_HEADER.length() ) ) {
          std::stringstream istrstream( str );
          std::string key;

          if( istrstream >> key ) {
            if( key == END_OF_HEADER ) {
              RetCode = 0;
              break;
            }
          }
        }

        if( AddParam( params, Buffer ) ) {
          RetCode = 3;
          break;
        }
      }
    }
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------

