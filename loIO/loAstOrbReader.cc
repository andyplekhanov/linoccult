//------------------------------------------------------------------------------
//
// File:    loAstOrbReader.cc
//
// Purpose: Asteroids ephemeris reader for LinOccult.
//          Read data from astorb.dat.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 31.01.2004
// version 0.2 11.04.2004 approcsimation asteroid diameter by D[km]=10**(3.52-0.2*H0)
// version 0.3 24.05.2004 OneAsteroid processing
// version 0.4 10.06.2004 Brigteness, EphemerisUncertainty have been added
// version 0.5 15.02.2005 Slope was added
// version 0.6 05.03.2005 StartAsteroidNumber, EndAsteroidNumber were added
// version 0.7 17.04.2005 Updates database was added
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
#include <iostream>
#include <iomanip>
#include <cmath>

#include "apsmathconst.h"
#include "apsangle.h"
#include "apstime.h"

#include "loAstOrbReader.h"
#include "loData.h"
#include "loAstOrbData.h"
#include "loUpdateData.h"
#include "loUpdate.h"
#include "loModuleAstOrbReader.h"
#include "loAstOrbReadSubModule.h"

namespace aps {

  namespace apslinoccult {

const int SHOW_AST_NUMBER = 1000;

LOAstOrbReader :: LOAstOrbReader( LOAstOrbReadSubModule * pLOAstOrbReadSubModule, const std::string & AstOrbFilePath ) :
                  AstOrbReader( AstOrbFilePath ), UpdatesNumber( 0 )
{
  pModule = new LOModuleAstOrbReader( pLOAstOrbReadSubModule );
}

LOAstOrbReader :: ~LOAstOrbReader( void )
{
  delete pModule;
}

int LOAstOrbReader :: ReadOneAsteroid( LOAstOrbData * pLOAstOrbData, LOUpdateData * pLOUpdateData, const int Count )
{
  const LOUpdate * pLOUpdate;
  int            AsteroidID;
  //bool           IfAsteroidID;
  std::string    AsteroidName;
  //bool           IfAsteroidName;
  std::string    OrbitComputer;
  //bool           IfOrbitComputer;
  double         Brigteness;
  bool           IfBrigteness;
  double         Slope;
  //bool           IfSlope;
  double         Color;
  //bool           IfColor;
  double         Diameter;
  bool           IfDiameter;
  std::string    Taxonomic;
  //bool           IfTaxonomic;
  int            Code1;
  //bool           IfCode1;
  int            Code2;
  //bool           IfCode2;
  int            Code3;
  //bool           IfCode3;
  int            Code4;
  //bool           IfCode4;    
  int            Code5;
  //bool           IfCode5;
  int            Code6;
  //bool           IfCode6;
  int            OrbitalArc;
  //bool           IfOrbitalArc;
  int            NumberOfObservations;
  //bool           IfNumberOfObservations;
  int            ObservationYear;
  bool           IfObservationYear;
  int            ObservationMonth;
  bool           IfObservationMonth;
  int            ObservationDay;
  bool           IfObservationDay;
  double         M;
  bool           IfM;
  double         W;
  bool           IfW;
  double         O;
  bool           IfO;
  double         I;
  bool           IfI;
  double         E;
  bool           IfE;
  double         A;
  bool           IfA;
  int            ComputationYear;
  //bool           IfComputationYear;
  int            ComputationMonth;
  //bool           IfComputationMonth;
  int            ComputationDay;
  //bool           IfComputationDay;
  double         EphemerisUncertainty;
  //bool           IfEphemerisUncertainty;
  double         EphemerisUncertaintyRate;
  //bool           IfEphemerisUncertaintyRate;
  int            CEUYear;
  //bool           IfCEUYear;
  int            CEUMonth;
  //bool           IfCEUMonth;
  int            CEUDay;
  //bool           IfCEUDay;
  double         NextPeakEphemerisUncertainty;
  //bool           IfNextPeakEphemerisUncertainty;
  int            PEUYear;
  //bool           IfPEUYear;
  int            PEUMonth;
  //bool           IfPEUMonth;
  int            PEUDay;
  //bool           IfPEUDay;
  double         GreatestPeakEphemerisUncertainty;
  //bool           IfGreatestPeakEphemerisUncertainty;
  int            GEUYear;
  //bool           IfGEUYear;
  int            GEUMonth;
  //bool           IfGEUMonth;
  int            GEUDay;
  //bool           IfGEUDay;
  double         GreatestPeak2EphemerisUncertainty;
  //bool           IfGreatestPeak2EphemerisUncertainty;
  int            GEU2Year;
  //bool           IfGEU2Year;
  int            GEU2Month;
  //bool           IfGEU2Month;
  int            GEU2Day;
  //bool           IfGEU2Day;
  double         ObservationEpoch;
  double         Tmp;
  double         TmpEU;
  int            RetCode = 0;

  if( !GetAsteroidID( AsteroidID ) ) {
    //IfAsteroidID = true;
  }
  else {
    //IfAsteroidID = false;
    AsteroidID = 0;  // Set AsteroidID = 0;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_ASTEROID_ID, Msg.str() );
  }

  if( !GetAsteroidName( AsteroidName ) ) {
    //IfAsteroidName = true;
  }
  else {
    //IfAsteroidName = false;
    AsteroidName = "NoName"; // Set AsteroidName "NoName"
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_ASTEROID_NAME, Msg.str() );
  }

  if( !GetOrbitComputer( OrbitComputer ) ) {
    //IfOrbitComputer = true;
  }
  else {
    //IfOrbitComputer = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_ORBIT_COMPUTER, Msg.str() );
  }

  if( !GetBrightness( Brigteness ) ) {
    IfBrigteness = true;
  }
  else {
    IfBrigteness = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_BRIGTENES, Msg.str() );
  }

  if( !GetSlope( Slope ) ) {
    //IfSlope = true;
  }
  else {
    //IfSlope = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_SLOPE, Msg.str() );
  }

  if( !GetColor( Color ) ) {
    //IfColor = true;
  }
  else {
    //IfColor = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_COLOR, Msg.str() );
  }

  if( !GetDiameter( Diameter ) ) {
    IfDiameter = true;
  }
  else {
    IfDiameter = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_DIAMETER, Msg.str() );
  }

  if( !GetTaxonomic( Taxonomic ) ) {
    //IfTaxonomic = true;
  }
  else {
    //IfTaxonomic = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_TAXONOMIC, Msg.str() );
  }

  if( !GetCode1( Code1 ) ) {
    //IfCode1 = true;
  }
  else {
    //IfCode1 = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CODE1, Msg.str() );
  }

  if( !GetCode2( Code2 ) ) {
    //IfCode2 = true;
  }
  else {
    //IfCode2 = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CODE2, Msg.str() );
  }

  if( !GetCode3( Code3 ) ) {
    //IfCode3 = true;
  }
  else {
    //IfCode3 = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CODE3, Msg.str() );
  }

  if( !GetCode4( Code4 ) ) {
    //IfCode4 = true;
  }
  else {
    //IfCode4 = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CODE4, Msg.str() );
  }

  if( !GetCode5( Code5 ) ) {
    //IfCode5 = true;
  }
  else {
    //IfCode5 = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CODE5, Msg.str() );
  }

  if( !GetCode6( Code6 ) ) {
    //IfCode6 = true;
  }
  else {
    //IfCode6 = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CODE6, Msg.str() );
  }

  if( !GetOrbitalArc( OrbitalArc ) ) {
    //IfOrbitalArc = true;
  }
  else {
    //IfOrbitalArc = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_ORBITAL_ARC, Msg.str() );
  }

  if( !GetNumberOfObservations( NumberOfObservations ) ) {
    //IfNumberOfObservations = true;
  }
  else {
    //IfNumberOfObservations = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_NUMBER_OF_OBSERVATIONS, Msg.str() );
  }

  if( !GetObservationYear( ObservationYear ) ) {
    IfObservationYear = true;
  }
  else {
    IfObservationYear = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_OBSERVATION_YEAR, Msg.str() );
  }

  if( !GetObservationMonth( ObservationMonth ) ) {
    IfObservationMonth = true;
  }
  else {
    IfObservationMonth = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_OBSERVATION_MONTH, Msg.str() );
  }

  if( !GetObservationDay( ObservationDay ) ) {
    IfObservationDay = true;
  }
  else {
    IfObservationDay = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_OBSERVATION_DAY, Msg.str() );
  }

  if( !GetM( M ) ) {
    IfM = true;
  }
  else {
    IfM = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_M, Msg.str() );
  }

  if( !GetW( W ) ) {
    IfW = true;
  }
  else {
    IfW = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_W, Msg.str() );
  }

  if( !GetO( O ) ) {
    IfO = true;
  }
  else {
    IfO = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_O, Msg.str() );
  }

  if( !GetI( I ) ) {
    IfI = true;
  }
  else {
    IfI = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_I, Msg.str() );
  }

  if( !GetE( E ) ) {
    IfE = true;
  }
  else {
    IfE = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_E, Msg.str() );
  }

  if( !GetA( A ) ) {
    IfA = true;
  }
  else {
    IfA = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_A, Msg.str() );
  }

  if( !GetComputationYear( ComputationYear ) ) {
    //IfComputationYear = true;
  }
  else {
    //IfComputationYear = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_COMPUTATION_YEAR, Msg.str() );
  }

  if( !GetComputationMonth( ComputationMonth ) ) {
    //IfComputationMonth = true;
  }
  else {
    //IfComputationMonth = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_COMPUTATION_MONTH, Msg.str() );
  }

  if( !GetComputationDay( ComputationDay ) ) {
    //IfComputationDay = true;
  }
  else {
    //IfComputationDay = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_COMPUTATION_DAY, Msg.str() );
  }

  if( !GetEphemerisUncertainty( EphemerisUncertainty ) ) {
    //IfEphemerisUncertainty = true;
  }
  else {
    //IfEphemerisUncertainty = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_EPHEMERIS_UNCERTAINTY, Msg.str() );
  }

  if( !GetEphemerisUncertaintyRate( EphemerisUncertaintyRate ) ) {
    //IfEphemerisUncertaintyRate = true;
  }
  else {
    //IfEphemerisUncertaintyRate = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_EPHEMERIS_UNCERTAINTY_RATE, Msg.str() );
  }

  if( !GetCEUYear( CEUYear ) ) {
    //IfCEUYear = true;
  }
  else {
    //IfCEUYear = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CEU_YEAR, Msg.str() );
  }

  if( !GetCEUMonth( CEUMonth ) ) {
    //IfCEUMonth = true;
  }
  else {
    //IfCEUMonth = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CEU_MONTH, Msg.str() ); 
  }

  if( !GetCEUDay( CEUDay ) ) {
    //IfCEUDay = true;
  }
  else {
    //IfCEUDay = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_CEU_DAY, Msg.str() );
  }

  if( !GetNextPeakEphemerisUncertainty( NextPeakEphemerisUncertainty ) ) {
    //IfNextPeakEphemerisUncertainty = true;
  }
  else {
    //IfNextPeakEphemerisUncertainty = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_NEXT_PEAK_EPHEMERIS_UNCERTAINTY, Msg.str() );
  }

  if( !GetPEUYear( PEUYear ) ) {
    //IfPEUYear = true;
  }
  else {
    //IfPEUYear = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_PEU_YEAR, Msg.str() );
  }

  if( !GetPEUMonth( PEUMonth ) ) {
    //IfPEUMonth = true;
  }
  else {
    //IfPEUMonth = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_PEU_MONTH, Msg.str() );
  }

  if( !GetPEUDay( PEUDay ) ) {
    //IfPEUDay = true;
  }
  else {
    //IfPEUDay = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_PEU_DAY, Msg.str() );
  }

  if( !GetGreatestPeakEphemerisUncertainty( GreatestPeakEphemerisUncertainty ) ) {
    //IfGreatestPeakEphemerisUncertainty = true;
  }
  else {
    //IfGreatestPeakEphemerisUncertainty = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GREATEST_PEAK_EPHEMERIS_UNCERTAINTY, Msg.str() );
  }

  if( !GetGEUYear( GEUYear ) ) {
    //IfGEUYear = true;
  }
  else {
    //IfGEUYear = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GEU_YEAR, Msg.str() );
  }

  if( !GetGEUMonth( GEUMonth ) ) {
    //IfGEUMonth = true;
  }
  else {
    //IfGEUMonth = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GEU_MONTH, Msg.str() );
  }

  if( !GetGEUDay( GEUDay ) ) {
    //IfGEUDay = true;
  }
  else {
    //IfGEUDay = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GEU_DAY, Msg.str() );
  }

  if( !GetGreatestPeak2EphemerisUncertainty( GreatestPeak2EphemerisUncertainty ) ) {
    //IfGreatestPeak2EphemerisUncertainty = true;  
  }
  else {
    //IfGreatestPeak2EphemerisUncertainty = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GREATEST_PEAK2_EPHEMERIS_UNCERTAINTY, Msg.str() );
  }

  if( !GetGEU2Year( GEU2Year ) ) {
    //IfGEU2Year = true;
  }
  else {
    //IfGEU2Year = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GEU2_YEAR, Msg.str() );
  }

  if( !GetGEU2Month( GEU2Month ) ) {
    //IfGEU2Month = true;
  }
  else {
    //IfGEU2Month = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GEU2_MONTH, Msg.str() );
  }

  if( !GetGEU2Day( GEU2Day ) ) {
    //IfGEU2Day= true;
  }
  else {
    //IfGEU2Day = false;
    std::ostringstream Msg;
    Msg << "Line " << Count + 1 << std::endl;
    pModule->WarningMessage( LO_AST_ORB_READER_GEU2_DAY, Msg.str() );
  }

  if( !( Count % SHOW_AST_NUMBER ) ) {
    pModule->StrMessage( LO_AST_ORB_READER_PROGRESS );
  }

  if( IfObservationYear && IfObservationMonth && IfObservationDay &&
      IfM && IfW && IfO && IfI && IfE && IfA ) {
    ObservationEpoch = apsastroalg::Mjd( ObservationYear, ObservationMonth, ObservationDay );

    if( !IfDiameter ) {
      if( IfBrigteness ) {
        Diameter = pow( 10.0, 3.52 - 0.2 * Brigteness );
      }
      else {
        pModule->WarningMessage( LO_AST_ORB_READER_NO_DIAMETER_AND_BRIGTHNESS );
      }
    }

    if( AsteroidID ) {
      pLOUpdate = pLOUpdateData->FindUpdate( AsteroidID, ObservationEpoch - pModule->GetUpdatesExpirePeriod() );

      if( pLOUpdate ) {
        ObservationEpoch = pLOUpdate->GetObservationEpoch();
        M                = pLOUpdate->GetM();
        W                = pLOUpdate->GetW();
        O                = pLOUpdate->GetO();
        I                = pLOUpdate->GetI();
        E                = pLOUpdate->GetE();
        A                = pLOUpdate->GetA();

        TmpEU = pLOUpdate->GetMajor();

        if( TmpEU < pLOUpdate->GetMinor() ) {
          TmpEU = pLOUpdate->GetMinor();
        }

        if( TmpEU != 0.0 ) {
          EphemerisUncertainty = TmpEU;
        }

        /*std::cout << "INFO: Updates for asteroid " << AsteroidID << " " << AsteroidName <<
                     " M = " << std::fixed << std::setprecision(6) << M << " W = " << std::fixed << std::setprecision(6) << W << " O = " << std::fixed << std::setprecision(6) << O <<
                     " I = " << std::fixed << std::setprecision(6) << I << " E = " << std::fixed << std::setprecision(6) << E << " A = " << std::fixed << std::setprecision(6) << A <<
                     " Epoch = " << std::fixed << std::setprecision(6) << ObservationEpoch << std::endl;*/

        UpdatesNumber++;
      }
      //else {
      //  return( 0 ); /* Only for asteroids with updates */
      //}
    }
    //else {
    //  return( 0 ); /* Only for asteroids with updates */
    //}

    if( pModule->GetIfOneAsteroid() ) {
      if( ( pModule->GetIfOneAsteroid() == AsteroidID ) || pModule->GetAsteroidNumber() ||
          ( pModule->GetStartAsteroidNumber() == pModule->GetEndAsteroidNumber() ) ) {
        ObservationEpoch = pModule->GetObservationEpoch();
        M                = pModule->GetOrbitM();
        W                = pModule->GetOrbitW();
        O                = pModule->GetOrbitO();
        I                = pModule->GetOrbitI();
        E                = pModule->GetOrbitE();
        A                = pModule->GetOrbitA();
        //EphemerisUncertainty = 0.047;

        /*std::cout << "INFO: Get orbit elements for asteroid " << AsteroidID << " " << AsteroidName << ":" <<
                     " M = " << std::fixed << std::setprecision(6) << M << " W = " << std::fixed << std::setprecision(6) << W << " O = " << std::fixed << std::setprecision(6) << O <<
                     " I = " << std::fixed << std::setprecision(6) << I << " E = " << std::fixed << std::setprecision(6) << E << " A = " << std::fixed << std::setprecision(6) << A <<
                     " Epoch = " << std::fixed << std::setprecision(6) << ObservationEpoch << std::endl;*/
      }
    }

    Tmp = apsmathlib::Ddd( 0, 0, EphemerisUncertainty );

    if( !pLOAstOrbData->CreateAsteroid( AsteroidID, AsteroidName, ObservationEpoch,
                         M * apsmathlib::Rad, W * apsmathlib::Rad,
                         O * apsmathlib::Rad, I * apsmathlib::Rad, E, A, Diameter,
                         Brigteness, Slope, apsmathlib::Rad * Tmp ) ) {
      pModule->WarningMessage( LO_AST_ORB_READER_TOO_MANY_ASTEROIDS );
      RetCode = 2;
    }
  }
  else {
    pModule->WarningMessage( LO_AST_ORB_READER_NOT_ENOUGH_DATA );
    RetCode = 1;
  }

  return( RetCode );
}

int LOAstOrbReader :: Read( LOData * pLOData )
{
  LOAstOrbData * pLOAstOrbData;
  LOUpdateData * pLOUpdateData;
  off_t          AsteroidsNumber;
  int            AsteroidNumber;
  int            Count;
  int            StartAsteroidNumber;
  int            EndAsteroidNumber;
  int            RetCode = LO_AST_ORB_READER_NO_ERROR;

  if( Open() ) {
    // Must be here to calculate RecordLength
    if( GetAsteroidsNumber( AsteroidsNumber ) ) {
      pModule->WarningMessage( LO_AST_ORB_READER_FILE_LENGTH );
    }

    pLOUpdateData = pLOData->GetUpdateData();

    AsteroidNumber = pModule->GetAsteroidNumber();

    UpdatesNumber = 0;

    if( !AsteroidNumber ) {
      Count = 0;

      StartAsteroidNumber = pModule->GetStartAsteroidNumber() - 1;
      EndAsteroidNumber   = pModule->GetEndAsteroidNumber();

      if( EndAsteroidNumber > AsteroidsNumber ) {
        EndAsteroidNumber = AsteroidsNumber;
      }

      pLOAstOrbData = pLOData->CreateAstOrbData( EndAsteroidNumber - StartAsteroidNumber );

      {
        std::ostringstream Msg;
        Msg << AsteroidsNumber << " records." << std::endl;
        pModule->InfoMessage( LO_AST_ORB_READER_START_READING, Msg.str() );
      }

      if( GoToRecord( StartAsteroidNumber ) ) {
        while( ReadStr() ) {
          Count++;

          ReadOneAsteroid( pLOAstOrbData, pLOUpdateData, Count );

          if( Count >= EndAsteroidNumber - StartAsteroidNumber ) {
            break;
          }
        }

        if( Count != EndAsteroidNumber - StartAsteroidNumber ) {
          pModule->WarningMessage( LO_AST_ORB_READER_WRONG_ASTEROIDS_NUMBER );
        }

        pModule->StrMessage( LO_AST_ORB_NEW_LINE );

        {
          std::ostringstream Msg;
          Msg << Count << " records." << std::endl;
          pModule->InfoMessage( LO_AST_ORB_READER_FINISH_READING, Msg.str() );
        }
      }
      else {
        pModule->ErrorMessage( LO_AST_ORB_SEEK );
        RetCode = LO_AST_ORB_SEEK;
      }
    }
    else {
      pModule->InfoMessage( LO_AST_ORB_READER_START_READ_ONE_ASTEROID );

      pLOAstOrbData = pLOData->CreateAstOrbData( 1 );

      if( GoToRecord( AsteroidNumber - 1 ) ) {
        if( ReadStr() ) {
          ReadOneAsteroid( pLOAstOrbData, pLOUpdateData, AsteroidNumber - 1 );
        }
        else {
          pModule->ErrorMessage( LO_AST_ORB_READ );
          RetCode = LO_AST_ORB_READ;
        }
      }
      else {
        pModule->ErrorMessage( LO_AST_ORB_SEEK );
        RetCode = LO_AST_ORB_SEEK;
      }

      pModule->InfoMessage( LO_AST_ORB_READER_FINISH_READ_ONE_ASTEROID );
    }

    std::cout << "INFO: UpdatesNumber = " << UpdatesNumber << std::endl;

    Close();
  }
  else {
    pModule->ErrorMessage( LO_AST_ORB_OPEN_FILE );
    RetCode = LO_AST_ORB_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
