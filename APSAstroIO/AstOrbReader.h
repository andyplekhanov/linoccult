//------------------------------------------------------------------------------
//
// File:    AstOrbReader.h
//
// Purpose: Asteroids ephemeris reader.
//          Read data from astorb.dat.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.01.2004
//         version 0.2 26.05.2004 GoToRecord procedure has been added
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

#ifndef ASTORB_READER_H
#define ASTORB_READER_H

#include <string>

#include "apsistrastroio.h"

namespace aps {

  namespace apsastroio {

//======================= AstOrbReader ==========================

class AstOrbReader : protected APSIStrAstroIO
{
  private:

    int           RecordLength;

  protected:

    bool GoToRecord( const int RecordNumber );

    int GetAsteroidsNumber( off_t & AsteroidsNumber );

    int GetAsteroidID( int & pAsteroidID ) const;

    int GetAsteroidName( std::string & pAsteroidName ) const;

    int GetOrbitComputer( std::string & pOrbitComputer ) const;

    int GetBrightness( double & pBriteness ) const;

    int GetSlope( double & pSlope ) const;

    int GetColor( double & pColor ) const;

    int GetDiameter( double & pDiameter ) const;

    int GetTaxonomic( std::string & pTaxonomic ) const;

    int GetCode1( int & pCode1 ) const;

    int GetCode2( int & pCode2 ) const;

    int GetCode3( int & pCode3 ) const;

    int GetCode4( int & pCode4 ) const;

    int GetCode5( int & pCode5 ) const;

    int GetCode6( int & pCode6 ) const;

    int GetOrbitalArc( int & pOrbitalArc ) const;

    int GetNumberOfObservations( int & pNumberOfObservations ) const;

    int GetObservationYear( int & pObservationYear ) const;

    int GetObservationMonth( int & pObservationMonth ) const;

    int GetObservationDay( int & pObservationDay ) const;

    int GetM( double & pM ) const;

    int GetW( double & pW ) const;

    int GetO( double & pO ) const;

    int GetI( double & pI ) const;

    int GetE( double & pE ) const;

    int GetA( double & pA ) const;

    int GetComputationYear( int & pComputationYear ) const;

    int GetComputationMonth( int & pComputationMonth ) const;

    int GetComputationDay( int & pComputationDay ) const;

    int GetEphemerisUncertainty( double & pEphemerisUncertainty ) const;

    int GetEphemerisUncertaintyRate( double & pEphemerisUncertaintyRate ) const;

    int GetCEUYear( int & pCEUYear ) const;

    int GetCEUMonth( int & pCEUMonth ) const;

    int GetCEUDay( int & pCEUDay ) const;

    int GetNextPeakEphemerisUncertainty( double & pNextPeakEphemerisUncertainty ) const;

    int GetPEUYear( int & pPEUYear ) const;

    int GetPEUMonth( int & pPEUMonth ) const;

    int GetPEUDay( int & pPEUDay ) const;

    int GetGreatestPeakEphemerisUncertainty( double & pGreatestPeakEphemerisUncertainty ) const;

    int GetGEUYear( int & pGEUYear ) const;

    int GetGEUMonth( int & pGEUMonth ) const;

    int GetGEUDay( int & pGEUDay ) const;

    int GetGreatestPeak2EphemerisUncertainty( double & pGreatestPeak2EphemerisUncertainty ) const;

    int GetGEU2Year( int & pGEU2Year ) const;

    int GetGEU2Month( int & pGEU2Month ) const;

    int GetGEU2Day( int & pGEU2Day ) const;

  public:

    AstOrbReader( const std::string & pAstOrbFilePath );

    virtual ~AstOrbReader( void );
};

}}

#endif

//---------------------------- End of file ---------------------------

