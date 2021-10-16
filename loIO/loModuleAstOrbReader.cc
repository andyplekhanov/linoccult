//------------------------------------------------------------------------------
//
// File:    loModuleAstOrbReader.cc
//
// Purpose: Module for asteroids ephemeris reader.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 10.02.2004
// version 0.2 11.04.2004 LO_AST_ORB_READER_NO_DIAMETER_AND_BRIGTHNESS has been added
// version 0.3 24.05.2004 IfOneAsteroid, ObservationEpoch,
//                                OrbitM, OrbitW, OrbitO, OrbitI, OrbitE, OrbitA parameters were added
// version 0.4 05.03.2005 StartAsteroidNumber, EndAsteroidNumber were added
// version 0.5 17.04.2005 UpdatesExpirePeriod was added
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

#include "loModuleAstOrbReader.h"
#include "loAstOrbReadSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleAstOrbReader =================================

LOModuleAstOrbReader :: LOModuleAstOrbReader( LOAstOrbReadSubModule * pOwner ) :
                          APSModule( "LOAstOrbReader", pOwner )
{
}

LOModuleAstOrbReader :: ~LOModuleAstOrbReader( void )
{
}

int LOModuleAstOrbReader :: WarningMessage( const int MsgNumber, const std::string & Msg, const APSModule * pSubModule ) const
{
  switch( MsgNumber ) {
    case LO_AST_ORB_READER_ASTEROID_ID:
      if( !pSubModule && !GetOwnerPtr() ) 
        return( apslib::MODULE_CONTINUE );
    break;
    case LO_AST_ORB_READER_DIAMETER:
      if( !pSubModule && !GetOwnerPtr() ) 
        return( apslib::MODULE_CONTINUE );
    break;
    case LO_AST_ORB_READER_COLOR:
      if( !pSubModule && !GetOwnerPtr() ) 
        return( apslib::MODULE_CONTINUE );
    break;
    default:;
  }

  return( APSModule :: WarningMessage( MsgNumber, Msg, pSubModule ) );
}

const std::string LOModuleAstOrbReader :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_AST_ORB_READER_NO_ERROR:
      return("No error\n");
    case LO_AST_ORB_OPEN_FILE:
      return("Can't open asteroid orbits file.\n");
    case LO_AST_ORB_SEEK:
      return("Error in seek.\n");
    case LO_AST_ORB_READ:
      return("Read error.\n");
    case LO_AST_ORB_READER_FILE_LENGTH:
      return("Wrong file length\n");
    case LO_AST_ORB_READER_START_READING:
      return("Start reading asteroid orbits file.");
    case LO_AST_ORB_READER_FINISH_READING:
      return("Asteroid orbits file has been read.");
    case LO_AST_ORB_READER_START_READ_ONE_ASTEROID:
      return("Start reading one asteroid.\n");
    case LO_AST_ORB_READER_FINISH_READ_ONE_ASTEROID:
      return("One asteroid has been read.\n");
    case LO_AST_ORB_READER_TOO_MANY_ASTEROIDS:
      return("Too many asteroids\n");
    case LO_AST_ORB_READER_NOT_ENOUGH_DATA:
      return("Not enough data\n");
    case LO_AST_ORB_READER_WRONG_ASTEROIDS_NUMBER:
      return("Wrong asteroids number\n");
    case LO_AST_ORB_READER_NO_DIAMETER_AND_BRIGTHNESS:
      return("No diameter and brightness\n");
    case LO_AST_ORB_READER_ASTEROID_ID:
      return("Asteroid ID");
    case LO_AST_ORB_READER_ASTEROID_NAME:
      return("Asteroid Name");
    case LO_AST_ORB_READER_ORBIT_COMPUTER:
      return("Orbit computer");
    case LO_AST_ORB_READER_BRIGTENES:
      return("Brigtness");
    case LO_AST_ORB_READER_SLOPE:
      return("Slope");
    case LO_AST_ORB_READER_COLOR:
      return("Color");
    case LO_AST_ORB_READER_DIAMETER:
      return("Diameter");
    case LO_AST_ORB_READER_TAXONOMIC:
      return("Taxonomic");
    case LO_AST_ORB_READER_CODE1:
      return("Code1");
    case LO_AST_ORB_READER_CODE2:
      return("Code2");
    case LO_AST_ORB_READER_CODE3:
      return("Code3");
    case LO_AST_ORB_READER_CODE4:
      return("Code4");
    case LO_AST_ORB_READER_CODE5:
      return("Code5");
    case LO_AST_ORB_READER_CODE6:
      return("Code6");
    case LO_AST_ORB_READER_ORBITAL_ARC:
      return("Orbital Arc");
    case LO_AST_ORB_READER_NUMBER_OF_OBSERVATIONS:
      return("Number of observations");
    case LO_AST_ORB_READER_OBSERVATION_YEAR:
      return("Observation year");
    case LO_AST_ORB_READER_OBSERVATION_MONTH:
      return("Observation month");
    case LO_AST_ORB_READER_OBSERVATION_DAY:
      return("Observation day");
    case LO_AST_ORB_READER_M:
      return("M");
    case LO_AST_ORB_READER_W:
      return("W");
    case LO_AST_ORB_READER_O:
      return("O");
    case LO_AST_ORB_READER_I:
      return("I");
    case LO_AST_ORB_READER_E:
      return("E");
    case LO_AST_ORB_READER_A:
      return("A");
    case LO_AST_ORB_READER_COMPUTATION_YEAR:
      return("Computation year");
    case LO_AST_ORB_READER_COMPUTATION_MONTH:
      return("Computation month");
    case LO_AST_ORB_READER_COMPUTATION_DAY:
      return("Computation day");
    case LO_AST_ORB_READER_EPHEMERIS_UNCERTAINTY:
      return("Ephemeris uncertainty");
    case LO_AST_ORB_READER_EPHEMERIS_UNCERTAINTY_RATE:
      return("Ephemeris uncertainty rate");
    case LO_AST_ORB_READER_CEU_YEAR:
      return("CEU year");
    case LO_AST_ORB_READER_CEU_MONTH:
      return("CEU month");
    case LO_AST_ORB_READER_CEU_DAY:
      return("CEU day");
    case LO_AST_ORB_READER_NEXT_PEAK_EPHEMERIS_UNCERTAINTY:
      return("Next peak ephemeris uncertainty");
    case LO_AST_ORB_READER_PEU_YEAR:
      return("PEU year");
    case LO_AST_ORB_READER_PEU_MONTH:
      return("PEU month");
    case LO_AST_ORB_READER_PEU_DAY:
      return("PEU day");
    case LO_AST_ORB_READER_GREATEST_PEAK_EPHEMERIS_UNCERTAINTY:
      return("Greatest peak ephemeris uncertainty");
    case LO_AST_ORB_READER_GEU_YEAR:
      return("GEU year");
    case LO_AST_ORB_READER_GEU_MONTH:
      return("GEU month");
    case LO_AST_ORB_READER_GEU_DAY:
      return("GEU day");
    case LO_AST_ORB_READER_GREATEST_PEAK2_EPHEMERIS_UNCERTAINTY:
      return("Greatest peak2 ephemeris uncertainty");
    case LO_AST_ORB_READER_GEU2_YEAR:
      return("GEU2 year");
    case LO_AST_ORB_READER_GEU2_MONTH:
      return("GEU2 month");
    case LO_AST_ORB_READER_GEU2_DAY:
      return("GEU2 day");
    case LO_AST_ORB_READER_PROGRESS:
      return("*");
    case LO_AST_ORB_NEW_LINE:
      return("\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOAstOrbReadSubModule * LOModuleAstOrbReader :: GetLOAstOrbReadSubModulePtr( void ) const
{
  return( static_cast<const LOAstOrbReadSubModule *>( GetOwnerPtr() ) );
}

int LOModuleAstOrbReader :: GetAsteroidNumber( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetAsteroidNumber() );
}

int LOModuleAstOrbReader :: GetIfOneAsteroid( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetIfOneAsteroid() );
}

double LOModuleAstOrbReader :: GetObservationEpoch( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetObservationEpoch() );
}

double LOModuleAstOrbReader :: GetOrbitM( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetOrbitM() );
}

double LOModuleAstOrbReader :: GetOrbitW( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetOrbitW() );
}

double LOModuleAstOrbReader :: GetOrbitO( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetOrbitO() );
}

double LOModuleAstOrbReader :: GetOrbitI( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetOrbitI() );
}

double LOModuleAstOrbReader :: GetOrbitE( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetOrbitE() );
}

double LOModuleAstOrbReader :: GetOrbitA( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetOrbitA() );
}

int LOModuleAstOrbReader :: GetStartAsteroidNumber( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetStartAsteroidNumber() );
}

int LOModuleAstOrbReader :: GetEndAsteroidNumber( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetEndAsteroidNumber() );
}

int LOModuleAstOrbReader :: GetUpdatesExpirePeriod( void ) const
{
  return( GetLOAstOrbReadSubModulePtr()->GetUpdatesExpirePeriod() );
}

}}

//---------------------------- End of file ---------------------------
