//------------------------------------------------------------------------------
//
// File:    AstOrbReader.cc
//
// Purpose: Asteroids ephemeris reader.
//          Read data from astorb.dat.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.01.2004
//         version 0.2 26.05.2004 GoToRecord procedure has been added
//         version 1.0 09.11.2005 New astorb.dat format with 6 didits for asteroid number
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

#include "AstOrbReader.h"
#include "apsastorbdefs.h"

namespace aps {

  namespace apsastroio {

//======================= AstOrbReader ==========================

AstOrbReader :: AstOrbReader( const std::string & pAstOrbFilePath ) : APSIStrAstroIO( pAstOrbFilePath )
{
  RecordLength = 0;
}

AstOrbReader :: ~AstOrbReader( void )
{
}

bool AstOrbReader :: GoToRecord( const int RecordNumber )
{
  bool RetCode = true;

  if( RecordLength ) {
    if( !Seek( RecordNumber * RecordLength, std::ios::beg ) ) {
      RetCode = false;
    }
  }
  else {
    RetCode = false;
  }

  return( RetCode );
}

int AstOrbReader :: GetAsteroidsNumber( off_t & AsteroidsNumber )
{
  off_t Remainder;
  off_t FileLength = 0;

  GetLength( FileLength );

  Remainder = FileLength % ASTER_RECORD_LENGTH1;

  RecordLength = ASTER_RECORD_LENGTH1;

  if( Remainder ) {
    Remainder = FileLength % ASTER_RECORD_LENGTH2;

    AsteroidsNumber = FileLength / ASTER_RECORD_LENGTH2;

    RecordLength = ASTER_RECORD_LENGTH2;
  }
  else {
    AsteroidsNumber = FileLength / ASTER_RECORD_LENGTH1;
  }

  return( Remainder );
}

int AstOrbReader :: GetAsteroidID( int & pAsteroidID ) const
{
  return( GetInteger( pAsteroidID, ASTER_NUMBER_OFFSET, ASTER_NUMBER_LENGTH ) );
}

int AstOrbReader :: GetAsteroidName( std::string & pAsteroidName ) const
{
  return( GetString( pAsteroidName, ASTER_NAME_OFFSET, ASTER_NAME_LENGTH ) );
}

int AstOrbReader :: GetOrbitComputer( std::string & pOrbitComputer ) const
{
  return( GetString( pOrbitComputer, ASTER_AUTHOR_OFFSET, ASTER_AUTHOR_LENGTH ) );
}

int AstOrbReader :: GetBrightness( double & pBriteness ) const
{
  return( GetDouble( pBriteness, ASTER_BRIGHTNESS_OFFSET, ASTER_BRIGHTNESS_LENGTH ) );
}

int AstOrbReader :: GetSlope( double & pSlope ) const
{
  return( GetDouble( pSlope, ASTER_SLOPE_OFFSET, ASTER_SLOPE_LENGTH ) );
}

int AstOrbReader :: GetColor( double & pColor ) const
{
  return( GetDouble( pColor, ASTER_COLOR_OFFSET, ASTER_COLOR_LENGTH ) );
}

int AstOrbReader :: GetDiameter( double & pDiameter ) const
{
  return( GetDouble( pDiameter, ASTER_DIAM_OFFSET, ASTER_DIAM_LENGTH ) );
}

int AstOrbReader :: GetTaxonomic( std::string & pTaxonomic ) const
{
  return( GetString( pTaxonomic, ASTER_TAXON_OFFSET, ASTER_TAXON_LENGTH ) );
}

int AstOrbReader :: GetCode1( int & pCode1 ) const
{
  return( GetInteger( pCode1, ASTER_CODE1_OFFSET, ASTER_CODE1_LENGTH ) );
}

int AstOrbReader :: GetCode2( int & pCode2 ) const
{
  return( GetInteger( pCode2, ASTER_CODE2_OFFSET, ASTER_CODE2_LENGTH ) );
}

int AstOrbReader :: GetCode3( int & pCode3 ) const
{
  return( GetInteger( pCode3, ASTER_CODE3_OFFSET, ASTER_CODE3_LENGTH ) );
}

int AstOrbReader :: GetCode4( int & pCode4 ) const
{
  return( GetInteger( pCode4, ASTER_CODE4_OFFSET, ASTER_CODE4_LENGTH ) );
}

int AstOrbReader :: GetCode5( int & pCode5 ) const
{
  return( GetInteger( pCode5, ASTER_CODE5_OFFSET, ASTER_CODE5_LENGTH ) );
}

int AstOrbReader :: GetCode6( int & pCode6 ) const
{
  return( GetInteger( pCode6, ASTER_CODE6_OFFSET, ASTER_CODE6_LENGTH ) );
}

int AstOrbReader :: GetOrbitalArc( int & pOrbitalArc ) const
{
  return( GetInteger( pOrbitalArc, ASTER_ARC_OFFSET, ASTER_ARC_LENGTH ) );
}

int AstOrbReader :: GetNumberOfObservations( int & pNumberOfObservations ) const
{
  return( GetInteger( pNumberOfObservations, ASTER_OBSERV_OFFSET, ASTER_OBSERV_LENGTH ) );
}

int AstOrbReader :: GetObservationYear( int & pObservationYear ) const
{
  return( GetInteger( pObservationYear, ASTER_OBS_YEAR_OFFSET, ASTER_OBS_YEAR_LENGTH ) );
}

int AstOrbReader :: GetObservationMonth( int & pObservationMonth ) const
{
  return( GetInteger( pObservationMonth, ASTER_OBS_MONTH_OFFSET, ASTER_OBS_MONTH_LENGTH ) );
}

int AstOrbReader :: GetObservationDay( int & pObservationDay ) const
{
  return( GetInteger( pObservationDay, ASTER_OBS_DAY_OFFSET, ASTER_OBS_DAY_LENGTH ) );
}

int AstOrbReader :: GetM( double & pM ) const
{
  return( GetDouble( pM, ASTER_ORBIT_M_OFFSET, ASTER_ORBIT_M_LENGTH ) );
}

int AstOrbReader :: GetW( double & pW ) const
{
  return( GetDouble( pW, ASTER_ORBIT_W_OFFSET, ASTER_ORBIT_W_LENGTH ) );
}

int AstOrbReader :: GetO( double & pO ) const
{
  return( GetDouble( pO, ASTER_ORBIT_O_OFFSET, ASTER_ORBIT_O_LENGTH ) );
}

int AstOrbReader :: GetI( double & pI ) const
{
  return( GetDouble( pI, ASTER_ORBIT_I_OFFSET, ASTER_ORBIT_I_LENGTH ) );
}

int AstOrbReader :: GetE( double & pE ) const
{
  return( GetDouble( pE, ASTER_ORBIT_E_OFFSET, ASTER_ORBIT_E_LENGTH ) );
}

int AstOrbReader :: GetA( double & pA ) const
{
  return( GetDouble( pA, ASTER_ORBIT_A_OFFSET, ASTER_ORBIT_A_LENGTH ) );
}

int AstOrbReader :: GetComputationYear( int & pComputationYear ) const
{
  return( GetInteger( pComputationYear, ASTER_CMP_YEAR_OFFSET, ASTER_CMP_YEAR_LENGTH ) );
}

int AstOrbReader :: GetComputationMonth( int & pComputationMonth ) const
{
  return( GetInteger( pComputationMonth, ASTER_CMP_MONTH_OFFSET, ASTER_CMP_MONTH_LENGTH ) );
}

int AstOrbReader :: GetComputationDay( int & pComputationDay ) const
{
  return( GetInteger( pComputationDay, ASTER_CMP_DAY_OFFSET, ASTER_CMP_DAY_LENGTH ) );
}

int AstOrbReader :: GetEphemerisUncertainty( double & pEphemerisUncertainty ) const
{
  return( GetDouble( pEphemerisUncertainty, ASTER_UNCERT_OFFSET, ASTER_UNCERT_LENGTH ) );
}

int AstOrbReader :: GetEphemerisUncertaintyRate( double & pEphemerisUncertaintyRate ) const
{
  return( GetDouble( pEphemerisUncertaintyRate, ASTER_UNCERT_RATE_OFFSET, ASTER_UNCERT_RATE_LENGTH ) );
}

int AstOrbReader :: GetCEUYear( int & pCEUYear ) const
{
  return( GetInteger( pCEUYear, ASTER_CEU_YEAR_OFFSET, ASTER_CEU_YEAR_LENGTH ) );
}

int AstOrbReader :: GetCEUMonth( int & pCEUMonth ) const
{
  return( GetInteger( pCEUMonth, ASTER_CEU_MONTH_OFFSET, ASTER_CEU_MONTH_LENGTH ) );
}

int AstOrbReader :: GetCEUDay( int & pCEUDay ) const
{
  return( GetInteger( pCEUDay, ASTER_CEU_DAY_OFFSET, ASTER_CEU_DAY_LENGTH ) );
}

int AstOrbReader :: GetNextPeakEphemerisUncertainty( double & pNextPeakEphemerisUncertainty ) const
{
  return( GetDouble( pNextPeakEphemerisUncertainty, ASTER_UNCERT_NEXT_OFFSET, ASTER_UNCERT_NEXT_LENGTH ) );
}

int AstOrbReader :: GetPEUYear( int & pPEUYear ) const
{
  return( GetInteger( pPEUYear, ASTER_PEU_YEAR_OFFSET, ASTER_PEU_YEAR_LENGTH ) );
}

int AstOrbReader :: GetPEUMonth( int & pPEUMonth ) const
{
  return( GetInteger( pPEUMonth, ASTER_PEU_MONTH_OFFSET, ASTER_PEU_MONTH_LENGTH ) );
}

int AstOrbReader :: GetPEUDay( int & pPEUDay ) const
{
  return( GetInteger( pPEUDay, ASTER_PEU_DAY_OFFSET, ASTER_PEU_DAY_LENGTH ) );
}

int AstOrbReader :: GetGreatestPeakEphemerisUncertainty( double & pGreatestPeakEphemerisUncertainty ) const
{
  return( GetDouble( pGreatestPeakEphemerisUncertainty, ASTER_UNCERT_GREAT_OFFSET, ASTER_UNCERT_GREAT_LENGTH ) );
}

int AstOrbReader :: GetGEUYear( int & pGEUYear ) const
{
  return( GetInteger( pGEUYear, ASTER_GEU_YEAR_OFFSET, ASTER_GEU_YEAR_LENGTH ) );
}

int AstOrbReader :: GetGEUMonth( int & pGEUMonth ) const
{
  return( GetInteger( pGEUMonth, ASTER_GEU_MONTH_OFFSET, ASTER_GEU_MONTH_LENGTH ) );
}

int AstOrbReader :: GetGEUDay( int & pGEUDay ) const
{
  return( GetInteger( pGEUDay, ASTER_GEU_DAY_OFFSET, ASTER_GEU_DAY_LENGTH ) );
}

int AstOrbReader :: GetGreatestPeak2EphemerisUncertainty( double & pGreatestPeak2EphemerisUncertainty ) const
{
  return( GetDouble( pGreatestPeak2EphemerisUncertainty, ASTER_UNCERT_GREAT2_OFFSET, ASTER_UNCERT_GREAT2_LENGTH ) );
}

int AstOrbReader :: GetGEU2Year( int & pGEU2Year ) const
{
  return( GetInteger( pGEU2Year, ASTER_GEU2_YEAR_OFFSET, ASTER_GEU2_YEAR_LENGTH ) );
}

int AstOrbReader :: GetGEU2Month( int & pGEU2Month ) const
{
  return( GetInteger( pGEU2Month, ASTER_GEU2_MONTH_OFFSET, ASTER_GEU2_MONTH_LENGTH ) );
}

int AstOrbReader :: GetGEU2Day( int & pGEU2Day ) const
{
  return( GetInteger( pGEU2Day, ASTER_GEU2_DAY_OFFSET, ASTER_GEU2_DAY_LENGTH ) );
}

}}

//---------------------------- End of file ---------------------------
