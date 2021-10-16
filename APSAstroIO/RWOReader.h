//------------------------------------------------------------------------------
//
// File:    RWOReader.h
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

#ifndef RWO_READER_H
#define RWO_READER_H

#include <map>
#include <string>

#include "apsistrastroio.h"

namespace aps {

  namespace apsastroio {

//======================= RWOReader ==========================

class RWOReader : protected APSIStrAstroIO
{
  private:

    int AddParam( std::map<const std::string,const std::string> & params,
                  const std::string & Buffer ) const;

  protected:

    int GetAsteroidName( std::string & AsteroidName ) const;

    int GetType( char & Type ) const;

    int GetTech( char & Tech ) const;

    int GetNote( char & Note ) const;

    int GetObservationYear( int & ObservationYear ) const;

    int GetObservationMonth( int & ObservationMonth ) const;

    int GetObservationDay( double & ObservationDay ) const;

    int GetObservationTimeAccuracy( double & ObservationTimeAccuracy ) const;

    int GetRA( double & RA ) const;

    int GetRAAccuracy( double & RAAccuracy ) const;

    int GetRARMS( std::string & RARMS ) const;

    int GetRAForce( char & RAForce ) const;

    int GetRABias( double & RABias ) const;

    int GetRAResid( std::string & RAResid ) const;

    int GetDec( double & Dec ) const;

    int GetDecAccuracy( double & DecAccuracy ) const;

    int GetDecRMS( std::string & DecRMS ) const;

    int GetDecForce( char & DecForce ) const;

    int GetDecBias( double & DecBias ) const;

    int GetDecResid( std::string & DecResid ) const;

    int GetMagnitude( std::string & Magnitude ) const;

    int GetObsCode( std::string & ObsCode ) const;

    int GetChi( std::string & Chi ) const;

    int GetSelCoord( int & SelCoord ) const;

    int GetSelMag( int & SelMag ) const;

    int GetIntFromHeader( const std::map<const std::string,const std::string> & params,
                          const std::string & key,
                          int & Value ) const;

    int GetDoubleFromHeader( const std::map<const std::string,const std::string> & params,
                             const std::string & key,
                             double & Value ) const;

    int GetCharFromHeader( const std::map<const std::string,const std::string> & params,
                           const std::string & key,
                           char & Value ) const;

    int GetStringFromHeader( const std::map<const std::string,const std::string> & params,
                             const std::string & key,
                             std::string & Value ) const;

    bool IfComment( void ) const;

    int ReadHeader( std::map<const std::string,const std::string> & params );

  public:

    RWOReader( const std::string & RWOFilePath );

    virtual ~RWOReader( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
