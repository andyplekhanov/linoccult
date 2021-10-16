//------------------------------------------------------------------------------
//
// File:    loModuleAppl.cc
//
// Purpose: Module for LinOccult application.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
//         version 0.2 24.05.2004 IfOneAsteroid, ObservationEpoch,
//                                OrbitM, OrbitW, OrbitO, OrbitI, OrbitE, OrbitA parameters were added
//         version 0.3 27.05.2004 OutputType parameter was added
//         version 0.4 31.01.2005 ResultsFilePath, SitesFilePath, CalculationMode, IfOutputFile,
//                                IfMySQL, IfPicture, IfPath parameters ware added
//         version 0.5 08.02.2005 ExtraRadius = 10.0, EventDataWriter was added
//         version 0.6 15.02.2005 InputEventsFilePath, OutputEventsFilePath, SunDist, MaxMv were added.
//                                ResultsFilePath, IfOutputFile were removed.
//         version 0.7 17.02.2005 ExtraRadius = 3.0
//         version 0.8 22.02.2005 SunDist -> SunElev
//         version 0.9 27.02.2005 LOEventPosWriterSubModule, LO_APPL_WRITE_POSITIONS_DATA were added
//         version 1.0 05.03.2005 UpdatesFilePath, UpdatesExpirePeriod, StartAsteroidNumber, EndAsteroidNumber,
//                                StartSQLNumber were added. LOSitesDataReaderSubModule was added.
//                                UpdatesParameters was added.
//         version 1.1 17.04.2005 LOUpdatesDataReaderSubModule was added.
//         version 1.2 24.04.2005 UpdatesExpirePeriod = 2 * 365
//         version 1.3 31.07.2005 OneStarCatalog, OneStarMv were added
//         version 1.4 23.08.2005 OneStarParallax was added
//         version 1.5 14.10.2005 UpdatesExpirePeriod = 4 * 365
//         version 1.6 24.04.2005 Back to UpdatesExpirePeriod = 2 * 365
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

#include <limits>
#include <sstream>
#include <iomanip>

#include "apsreadcfg.h"
#include "apsastroconst.h"
#include "loModuleAppl.h"
#include "loAstOrbReadSubModule.h"
#include "loGaiaReadSubModule.h"
#include "loEventDataWriterSubModule.h"
#include "loEventPosWriterSubModule.h"
#include "loEventDataReaderSubModule.h"
#include "loSitesDataReaderSubModule.h"
#include "loUpdatesDataReaderSubModule.h"
#include "loCalcSubModule.h"
#include "loConfigReadSubModule.h"
#include "loConfig.h"

namespace aps {

  namespace apslinoccult {

static const std::string MAIN_CONFIG_PATH = "linoccult.config";

//======================= LOModuleAppl ==========================

LOModuleAppl :: LOModuleAppl( const std::string & aProjectFilePath,
                              const std::string & ModuleName,
                              const int X_Version,
                              const int Y_Version,
                              const int Z_Version,
                              const int FirstCopyRightYear,
                              const int CopyRightYear,
                              const apslib::APS_PROGRAM_VERSION_TYPE VersionType ) :
                  APSMainModule( ModuleName, X_Version, Y_Version, Z_Version,
                                 FirstCopyRightYear, CopyRightYear, VersionType ),
                                 ProjectFilePath( aProjectFilePath )
{
  pLOAstOrbReadSubModule        = new LOAstOrbReadSubModule( this );
  pLOGaiaReadSubModule          = new LOGaiaReadSubModule( this );
  pLOEventDataWriterSubModule   = new LOEventDataWriterSubModule( this );
  pLOEventPosWriterSubModule    = new LOEventPosWriterSubModule( this );
  pLOEventDataReaderSubModule   = new LOEventDataReaderSubModule( this );
  pLOSitesDataReaderSubModule   = new LOSitesDataReaderSubModule( this );
  pLOUpdatesDataReaderSubModule = new LOUpdatesDataReaderSubModule( this );
  pLOCalcSubModule              = new LOCalcSubModule( this );
  pLOConfigReadSubModule        = new LOConfigReadSubModule( this );

  AstOrbFilePath      = "astorb.dat";
  StarCatalogFilePath = "Gaia14.bin";
  JPLEphemFilePath    = "unxp2000.405";
  StartYear           = 2004;
  StartMonth          = 1;
  StartDay            = 1;
  EndYear             = 2021;
  EndMonth            = 1;
  EndDay              = 1;
  AsteroidNumber      = 0;
  IfOneStar           = 0;
  RA_Hour             = 0;
  RA_Min              = 0;
  RA_Sec              = 0.0;
  Dec_Deg             = 0;
  Dec_Min             = 0;
  Dec_Sec             = 0.0;
  pmRA                = 0.0;
  pmDec               = 0.0;
  OneStarCatalog      = 0;
  OneStarMv           = 0.0;
  OneStarParallax     = 0.0;
  Vrad                = 0.0;
  Epoch               = apsastroalg::MJD_J2016;
  ScanStep            = 24 * 60;
  IfExtraRadius       = 0;
  ExtraRadius         = 3.0;
  ET_UT               = 69.364215; // December 2020
  UT_UTC              = 0.0;
  MinA                = std::numeric_limits<double>::min();
  MaxA                = std::numeric_limits<double>::max();
  MinDiameter         = std::numeric_limits<double>::min();
  MaxDiameter         = std::numeric_limits<double>::max();
  IfOneAsteroid       = 0;
  ObservationEpoch    = 0.0;
  OrbitM              = 0.0;
  OrbitW              = 0.0;
  OrbitO              = 0.0;
  OrbitI              = 0.0;
  OrbitE              = 0.0;
  OrbitA              = 0.0;
  OutputType          = 0;
  InputEventsFilePath = "results.bin";
  OutputEventsFilePath = "results.bin";
  SitesFilePath       = "Sites.txt";
  CalculationMode     = 1;
  IfMySQL             = 0;
  IfPicture           = 0;
  IfPath              = 1;
  SunElev             = 0.0;
  MaxMv               = std::numeric_limits<double>::max();
  UpdatesFilePath     = "Updates.txt";
  UpdatesExpirePeriod = 2 * 365;
  StartAsteroidNumber = 1;
  EndAsteroidNumber   = std::numeric_limits<int>::max();
  StartSQLNumber      = 1;

  OriginAstOrbFilePath       = LO_APPL_PARAM_DEFAULT;
  OriginStarCatalogFilePath  = LO_APPL_PARAM_DEFAULT;
  OriginJPLEphemFilePath     = LO_APPL_PARAM_DEFAULT;
  OriginStartYear            = LO_APPL_PARAM_DEFAULT;
  OriginStartMonth           = LO_APPL_PARAM_DEFAULT;
  OriginStartDay             = LO_APPL_PARAM_DEFAULT;
  OriginEndYear              = LO_APPL_PARAM_DEFAULT;
  OriginEndMonth             = LO_APPL_PARAM_DEFAULT;
  OriginEndDay               = LO_APPL_PARAM_DEFAULT;
  OriginAsteroidNumber       = LO_APPL_PARAM_DEFAULT;
  OriginIfOneStar            = LO_APPL_PARAM_DEFAULT;
  OriginRA_Hour              = LO_APPL_PARAM_DEFAULT;
  OriginRA_Min               = LO_APPL_PARAM_DEFAULT;
  OriginRA_Sec               = LO_APPL_PARAM_DEFAULT;
  OriginDec_Deg              = LO_APPL_PARAM_DEFAULT;
  OriginDec_Min              = LO_APPL_PARAM_DEFAULT;
  OriginDec_Sec              = LO_APPL_PARAM_DEFAULT;
  OriginpmRA                 = LO_APPL_PARAM_DEFAULT;
  OriginpmDec                = LO_APPL_PARAM_DEFAULT;
  OriginOneStarCatalog       = LO_APPL_PARAM_DEFAULT;
  OriginOneStarMv            = LO_APPL_PARAM_DEFAULT;
  OriginOneStarParallax      = LO_APPL_PARAM_DEFAULT;
  OriginVrad                 = LO_APPL_PARAM_DEFAULT;
  OriginEpoch                = LO_APPL_PARAM_DEFAULT;
  OriginScanStep             = LO_APPL_PARAM_DEFAULT;
  OriginIfExtraRadius        = LO_APPL_PARAM_DEFAULT;
  OriginExtraRadius          = LO_APPL_PARAM_DEFAULT;
  OriginET_UT                = LO_APPL_PARAM_DEFAULT;
  OriginUT_UTC               = LO_APPL_PARAM_DEFAULT;
  OriginMinA                 = LO_APPL_PARAM_DEFAULT;
  OriginMaxA                 = LO_APPL_PARAM_DEFAULT;
  OriginMinDiameter          = LO_APPL_PARAM_DEFAULT;
  OriginMaxDiameter          = LO_APPL_PARAM_DEFAULT;
  OriginIfOneAsteroid        = LO_APPL_PARAM_DEFAULT;
  OriginObservationEpoch     = LO_APPL_PARAM_DEFAULT;
  OriginOrbitM               = LO_APPL_PARAM_DEFAULT;
  OriginOrbitW               = LO_APPL_PARAM_DEFAULT;
  OriginOrbitO               = LO_APPL_PARAM_DEFAULT;
  OriginOrbitI               = LO_APPL_PARAM_DEFAULT;
  OriginOrbitE               = LO_APPL_PARAM_DEFAULT;
  OriginOrbitA               = LO_APPL_PARAM_DEFAULT;
  OriginOutputType           = LO_APPL_PARAM_DEFAULT;
  OriginInputEventsFilePath  = LO_APPL_PARAM_DEFAULT;
  OriginOutputEventsFilePath = LO_APPL_PARAM_DEFAULT;
  OriginSitesFilePath        = LO_APPL_PARAM_DEFAULT;
  OriginCalculationMode      = LO_APPL_PARAM_DEFAULT;
  OriginIfMySQL              = LO_APPL_PARAM_DEFAULT;
  OriginIfPicture            = LO_APPL_PARAM_DEFAULT;
  OriginIfPath               = LO_APPL_PARAM_DEFAULT;
  OriginSunElev              = LO_APPL_PARAM_DEFAULT;
  OriginMaxMv                = LO_APPL_PARAM_DEFAULT;
  OriginUpdatesFilePath      = LO_APPL_PARAM_DEFAULT;
  OriginUpdatesExpirePeriod  = LO_APPL_PARAM_DEFAULT;
  OriginStartAsteroidNumber  = LO_APPL_PARAM_DEFAULT;
  OriginEndAsteroidNumber    = LO_APPL_PARAM_DEFAULT;
  OriginStartSQLNumber       = LO_APPL_PARAM_DEFAULT;
}

LOModuleAppl :: ~LOModuleAppl( void )
{
  delete pLOAstOrbReadSubModule;
  delete pLOGaiaReadSubModule;
  delete pLOEventDataWriterSubModule;
  delete pLOEventPosWriterSubModule;
  delete pLOEventDataReaderSubModule;
  delete pLOSitesDataReaderSubModule;
  delete pLOUpdatesDataReaderSubModule;
  delete pLOCalcSubModule;
  delete pLOConfigReadSubModule;
}

int LOModuleAppl :: IfInputEventsFilePath( void ) const
{
  if( OriginInputEventsFilePath == LO_APPL_PARAM_DEFAULT ) {
    return( 0 );
  }

  return( 1 );
}

int LOModuleAppl :: IfOutputEventsFilePath( void ) const
{
  if( OriginOutputEventsFilePath == LO_APPL_PARAM_DEFAULT ) {
    return( 0 );
  }

  return( 1 );
}

int LOModuleAppl :: IfSitesFilePath( void ) const
{
  if( OriginSitesFilePath == LO_APPL_PARAM_DEFAULT ) {
    return( 0 );
  }

  return( 1 );
}

int LOModuleAppl :: IfUpdatesFilePath( void ) const
{
  if( OriginUpdatesFilePath == LO_APPL_PARAM_DEFAULT ) {
    return( 0 );
  }

  return( 1 );
}

int LOModuleAppl :: IfEndYear( void ) const
{
  if( OriginEndYear == LO_APPL_PARAM_DEFAULT ) {
    return( 0 );
  }

  return( 1 );
}

int LOModuleAppl :: IfEndMonth( void ) const
{
  if( OriginEndMonth == LO_APPL_PARAM_DEFAULT ) {
    return( 0 );
  }

  return( 1 );
}

int LOModuleAppl :: IfEndDay( void ) const
{
  if( OriginEndDay == LO_APPL_PARAM_DEFAULT ) {
    return( 0 );
  }

  return( 1 );
}

const std::string LOModuleAppl :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_APPL_NO_ERR:
      return("No error.\n");
    case LO_APPL_AST_ORB_READ:
      return("Asteroid orbits file reading error.\n");
    case LO_APPL_GAIA_READ:
      return("Gaia star catalog reading error.\n");
    case LO_APPL_CALC:
      return("Calculation error.\n");
    case LO_APPL_WRITE_EVENT_DATA:
      return("Events data writing error.\n");
    case LO_APPL_WRITE_POSITIONS_DATA:
      return("Positions data writing error.\n");
    case LO_APPL_READ_EVENT_DATA:
      return("Events data reading error.\n");
    case LO_APPL_READ_SITES_DATA:
      return("Sites data reading error.\n");
    case LO_APPL_READ_UPDATES_DATA:
      return("Updates data reading error.\n");
    case LO_APPL_START:
      return("  Asteroids occultation program.\n  (C) Plekhanov Andrey\n\n");
    case LO_APPL_MODULE:
      return("Init module.\n");
    case LO_APPL_SHOW_PARAM:
      return("");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

void LOModuleAppl :: PrintParameters( void ) const
{
  if( OriginAstOrbFilePath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter AstOrbFilePath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << AstOrbFilePath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginAstOrbFilePath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter AstOrbFilePath from file " << ProjectFilePath << ": " << std::fixed << AstOrbFilePath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStarCatalogFilePath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StarCatalogFilePath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << StarCatalogFilePath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginStarCatalogFilePath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StarCatalogFilePath from file " << ProjectFilePath << ": " << std::fixed << StarCatalogFilePath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginJPLEphemFilePath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter JPLEphemFilePath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << JPLEphemFilePath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginJPLEphemFilePath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter JPLEphemFilePath from file " << ProjectFilePath << ": " << std::fixed << JPLEphemFilePath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStartYear == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StartYear from file " << MAIN_CONFIG_PATH << ": " << std::fixed << StartYear << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginStartYear == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StartYear from file " << ProjectFilePath << ": " << std::fixed << StartYear << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStartMonth == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StartMonth from file " << MAIN_CONFIG_PATH << ": " << std::fixed << StartMonth << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginStartMonth == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StartMonth from file " << ProjectFilePath << ": " << std::fixed << StartMonth << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStartDay == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StartDay from file " << MAIN_CONFIG_PATH << ": " << std::fixed << StartDay << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginStartDay == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StartDay from file " << ProjectFilePath << ": " << std::fixed << StartDay << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginEndYear == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter EndYear from file " << MAIN_CONFIG_PATH << ": " << std::fixed << EndYear << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginEndYear == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter EndYear from file " << ProjectFilePath << ": " << std::fixed << EndYear << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
    else {
      if( OriginEndYear == LO_APPL_PARAM_CALCULATED ) {
        std::ostringstream Msg;
        Msg << "Parameter EndYear assigned " << std::fixed << EndYear << std::endl;
        InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
      }
    }
  }

  if( OriginEndMonth == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter EndMonth from file " << MAIN_CONFIG_PATH << ": " << std::fixed << EndMonth << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginEndMonth == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter EndMonth from file " << ProjectFilePath << ": " << std::fixed << EndMonth << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
    else {
      if( OriginEndMonth == LO_APPL_PARAM_CALCULATED ) {
        std::ostringstream Msg;
        Msg << "Parameter EndMonth assigned " << std::fixed << EndMonth << std::endl;
        InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
      }
    }
  }

  if( OriginEndDay == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter EndDay from file " << MAIN_CONFIG_PATH << ": " << std::fixed << EndDay << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginEndDay == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter EndDay from file " << ProjectFilePath << ": " << std::fixed << EndDay << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
    else {
      if( OriginEndDay == LO_APPL_PARAM_CALCULATED ) {
        std::ostringstream Msg;
        Msg << "Parameter EndDay assigned " << std::fixed << EndDay << std::endl;
        InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
      }
    }
  }

  if( OriginAsteroidNumber == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter AsteroidNumber from file " << MAIN_CONFIG_PATH << ": " << std::fixed << AsteroidNumber << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginAsteroidNumber == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter AsteroidNumber from file " << ProjectFilePath << ": " << std::fixed << AsteroidNumber << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIfOneStar == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IfOneStar from file " << MAIN_CONFIG_PATH << ": " << std::fixed << IfOneStar << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginIfOneStar == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IfOneStar from file " << ProjectFilePath << ": " << std::fixed << IfOneStar << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginRA_Hour == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter RA_Hour from file " << MAIN_CONFIG_PATH << ": " << std::fixed << RA_Hour << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginRA_Hour == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter RA_Hour from file " << ProjectFilePath << ": " << std::fixed << RA_Hour << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginRA_Min == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter RA_Min from file " << MAIN_CONFIG_PATH << ": " << std::fixed << RA_Min << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginRA_Min == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter RA_Min from file " << ProjectFilePath << ": " << std::fixed << RA_Min << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginRA_Sec == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter RA_Sec from file " << MAIN_CONFIG_PATH << ": " << std::fixed << RA_Sec << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginRA_Sec == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter RA_Sec from file " << ProjectFilePath << ": " << std::fixed << RA_Sec << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginDec_Deg == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter Dec_Deg from file " << MAIN_CONFIG_PATH << ": " << std::fixed << Dec_Deg << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginDec_Deg == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter Dec_Deg from file " << ProjectFilePath << ": " << std::fixed << Dec_Deg << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginDec_Min == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter Dec_Min from file " << MAIN_CONFIG_PATH << ": " << std::fixed << Dec_Min << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginDec_Min == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter Dec_Min from file " << ProjectFilePath << ": " << std::fixed << Dec_Min << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginDec_Sec == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter Dec_Sec from file " << MAIN_CONFIG_PATH << ": " << std::fixed << Dec_Sec << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginDec_Sec == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter Dec_Sec from file " << ProjectFilePath << ": " << std::fixed << Dec_Sec << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginpmRA == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter pmRA from file " << MAIN_CONFIG_PATH << ": " << std::fixed << pmRA << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginpmRA == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter pmRA from file " << ProjectFilePath << ": " << std::fixed << pmRA << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginpmDec == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter pmDec from file " << MAIN_CONFIG_PATH << ": " << std::fixed << pmDec << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginpmDec == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter pmDec from file " << ProjectFilePath << ": " << std::fixed << pmDec << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOneStarCatalog == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OneStarCatalog from file " << MAIN_CONFIG_PATH << ": " << std::fixed << OneStarCatalog << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOneStarCatalog == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OneStarCatalog from file " << ProjectFilePath << ": " << std::fixed << OneStarCatalog << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOneStarMv == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OneStarMv from file " << MAIN_CONFIG_PATH << ": " << std::fixed << OneStarMv << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOneStarMv == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OneStarMv from file " << ProjectFilePath << ": " << std::fixed << OneStarMv << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOneStarParallax == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OneStarParallax from file " << MAIN_CONFIG_PATH << ": " << std::fixed << OneStarParallax << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOneStarParallax == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OneStarParallax from file " << ProjectFilePath << ": " << std::fixed << OneStarParallax << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginVrad == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter Vrad from file " << MAIN_CONFIG_PATH << ": " << std::fixed << Vrad << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginVrad == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter Vrad from file " << ProjectFilePath << ": " << std::fixed << Vrad << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginEpoch == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter Epoch from file " << MAIN_CONFIG_PATH << ": " << std::fixed << Epoch << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginEpoch == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter Epoch from file " << ProjectFilePath << ": " << std::fixed << Epoch << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }  

  if( OriginScanStep == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter ScanStep from file " << MAIN_CONFIG_PATH << ": " << std::fixed << ScanStep << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginScanStep == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter ScanStep from file " << ProjectFilePath << ": " << std::fixed << ScanStep << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIfExtraRadius == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IfExtraRadius from file " << MAIN_CONFIG_PATH << ": " << std::fixed << IfExtraRadius << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginIfExtraRadius == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IfExtraRadius from file " << ProjectFilePath << ": " << std::fixed << IfExtraRadius << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginExtraRadius == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter ExtraRadius from file " << MAIN_CONFIG_PATH << ": " << std::fixed << ExtraRadius << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginExtraRadius == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter ExtraRadius from file " << ProjectFilePath << ": " << std::fixed << ExtraRadius << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginET_UT == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter ET_UT from file " << MAIN_CONFIG_PATH << ": " << std::fixed << ET_UT << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginET_UT == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter ET_UT from file " << ProjectFilePath << ": " << std::fixed << ET_UT << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginUT_UTC == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter UT_UTC from file " << MAIN_CONFIG_PATH << ": " << std::fixed << UT_UTC << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginUT_UTC == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter UT_UTC from file " << ProjectFilePath << ": " << std::fixed << UT_UTC << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginMinA == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter MinA from file " << MAIN_CONFIG_PATH << ": " << std::fixed << MinA << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginMinA == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter MinA from file " << ProjectFilePath << ": " << std::fixed << MinA << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginMaxA == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter MaxA from file " << MAIN_CONFIG_PATH << ": " << std::fixed << MaxA << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginMaxA == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter MaxA from file " << ProjectFilePath << ": " << std::fixed << MaxA << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginMinDiameter == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter MinDiameter from file " << MAIN_CONFIG_PATH << ": " << std::fixed << MinDiameter << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginMinDiameter == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter MinDiameter from file " << ProjectFilePath << ": " << std::fixed << MinDiameter << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginMaxDiameter == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter MaxDiameter from file " << MAIN_CONFIG_PATH << ": " << std::fixed << MaxDiameter << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginMaxDiameter == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter MaxDiameter from file " << ProjectFilePath << ": " << std::fixed << MaxDiameter << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIfOneAsteroid == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IfOneAsteroid from file " << MAIN_CONFIG_PATH << ": " << std::fixed << IfOneAsteroid << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginIfOneAsteroid == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IfOneAsteroid from file " << ProjectFilePath << ": " << std::fixed << IfOneAsteroid << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginObservationEpoch == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter ObservationEpoch from file " << MAIN_CONFIG_PATH << ": " << std::fixed << ObservationEpoch << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginObservationEpoch == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter ObservationEpoch from file " << ProjectFilePath << ": " << std::fixed << ObservationEpoch << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOrbitM == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OrbitM from file " << MAIN_CONFIG_PATH << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
            OrbitM << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOrbitM == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OrbitM from file " << ProjectFilePath << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
             OrbitM << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOrbitW == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OrbitW from file " << MAIN_CONFIG_PATH << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
           OrbitW << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOrbitW == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OrbitW from file " << ProjectFilePath << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
             OrbitW << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOrbitO == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OrbitO from file " << MAIN_CONFIG_PATH << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
           OrbitO << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOrbitO == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OrbitO from file " << ProjectFilePath << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
             OrbitO << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOrbitI == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OrbitI from file " << MAIN_CONFIG_PATH << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
           OrbitI << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOrbitI == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OrbitI from file " << ProjectFilePath << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
             OrbitI << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOrbitE == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OrbitE from file " << MAIN_CONFIG_PATH << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
           OrbitE << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOrbitE == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OrbitE from file " << ProjectFilePath << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
             OrbitE << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOrbitA == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OrbitA from file " << MAIN_CONFIG_PATH << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
           OrbitA << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOrbitA == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OrbitA from file " << ProjectFilePath << ": " << std::fixed << std::setw( 12 ) << std::setprecision( 8 ) <<
             OrbitA << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOutputType == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OutputType from file " << MAIN_CONFIG_PATH << ": " << std::fixed << OutputType << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOutputType == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OutputType from file " << ProjectFilePath << ": " << std::fixed << OutputType << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginInputEventsFilePath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter InputEventsFilePath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << InputEventsFilePath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginInputEventsFilePath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter InputEventsFilePath from file " << ProjectFilePath << ": " << std::fixed << InputEventsFilePath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginOutputEventsFilePath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter OutputEventsFilePath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << OutputEventsFilePath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginOutputEventsFilePath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter OutputEventsFilePath from file " << ProjectFilePath << ": " << std::fixed << OutputEventsFilePath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginSitesFilePath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter SitesFilePath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << SitesFilePath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginSitesFilePath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter SitesFilePath from file " << ProjectFilePath << ": " << std::fixed << SitesFilePath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginCalculationMode == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter CalculationMode from file " << MAIN_CONFIG_PATH << ": " << std::fixed << CalculationMode << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginCalculationMode == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter CalculationMode from file " << ProjectFilePath << ": " << std::fixed << CalculationMode << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIfMySQL == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IfMySQL from file " << MAIN_CONFIG_PATH << ": " << std::fixed << IfMySQL << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginIfMySQL == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IfMySQL from file " << ProjectFilePath << ": " << std::fixed << IfMySQL << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIfPicture == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IfPicture from file " << MAIN_CONFIG_PATH << ": " << std::fixed << IfPicture << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginIfPicture == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IfPicture from file " << ProjectFilePath << ": " << std::fixed << IfPicture << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIfPath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IfPath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << IfPath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginIfPath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IfPath from file " << ProjectFilePath << ": " << std::fixed << IfPath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginSunElev == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter SunElev from file " << MAIN_CONFIG_PATH << ": " << std::fixed << SunElev << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginSunElev == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter SunElev from file " << ProjectFilePath << ": " << std::fixed << SunElev << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginMaxMv == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter MaxMv from file " << MAIN_CONFIG_PATH << ": " << std::fixed << MaxMv << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginMaxMv == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter MaxMv from file " << ProjectFilePath << ": " << std::fixed << MaxMv << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginUpdatesFilePath == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter UpdatesFilePath from file " << MAIN_CONFIG_PATH << ": " << std::fixed << UpdatesFilePath << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginUpdatesFilePath == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter UpdatesFilePath from file " << ProjectFilePath << ": " << std::fixed << UpdatesFilePath << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginUpdatesExpirePeriod == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter UpdatesExpirePeriod from file " << MAIN_CONFIG_PATH << ": " << std::fixed << UpdatesExpirePeriod << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginUpdatesExpirePeriod == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter UpdatesExpirePeriod from file " << ProjectFilePath << ": " << std::fixed << UpdatesExpirePeriod << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStartAsteroidNumber == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StartAsteroidNumber from file " << MAIN_CONFIG_PATH << ": " << std::fixed << StartAsteroidNumber << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginStartAsteroidNumber == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StartAsteroidNumber from file " << ProjectFilePath << ": " << std::fixed << StartAsteroidNumber << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginEndAsteroidNumber == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter EndAsteroidNumber from file " << MAIN_CONFIG_PATH << ": " << std::fixed << EndAsteroidNumber << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginEndAsteroidNumber == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter EndAsteroidNumber from file " << ProjectFilePath << ": " << std::fixed << EndAsteroidNumber << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStartSQLNumber == LO_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StartSQLNumber from file " << MAIN_CONFIG_PATH << ": " << std::fixed << StartSQLNumber << std::endl;
    InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );    
  }
  else {
    if( OriginStartSQLNumber == LO_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StartSQLNumber from file " << ProjectFilePath << ": " << std::fixed << StartSQLNumber << std::endl;
      InfoMessage( LO_APPL_SHOW_PARAM, Msg.str() );
    }
  }
}

void LOModuleAppl :: UpdateParameters( void )
{
  if( !IfEndYear() && !IfEndMonth() && !IfEndDay() ) {
    EndYear  = StartYear;
    EndMonth = StartMonth;
    EndDay   = StartDay;

    OriginEndYear  = LO_APPL_PARAM_CALCULATED;
    OriginEndMonth = LO_APPL_PARAM_CALCULATED;
    OriginEndDay   = LO_APPL_PARAM_CALCULATED;
  }
}

int LOModuleAppl :: Run( void )
{
  apslib::APSReadConfig * pAPSReadConfig;
  LOConfig              * pLOConfig;
  apslib::APSReadConfig * pAPSReadConfig1;
  LOConfig              * pLOConfig1;
  int                     RetCode = LO_APPL_NO_ERR;

  ShowBanner();
  StrMessage( LO_APPL_START );

  pLOConfig = new LOConfig();

  pAPSReadConfig = new apslib::APSReadConfig( pLOConfigReadSubModule, MAIN_CONFIG_PATH );

  RetCode = pAPSReadConfig->Read( pLOConfig );

  if( !RetCode ) {
    if( !pLOConfig->GetAstOrbFilePath( AstOrbFilePath ) ) {
      OriginAstOrbFilePath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetStarCatalogFilePath( StarCatalogFilePath ) ) {
      OriginStarCatalogFilePath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetJPLEphemFilePath( JPLEphemFilePath ) ) {
      OriginJPLEphemFilePath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetStartYear( StartYear ) ) {
      OriginStartYear = LO_APPL_PARAM_MAIN_CONFIG;
    } 

    if( !pLOConfig->GetStartMonth( StartMonth ) ) {
      OriginStartMonth = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetStartDay( StartDay ) ) {
      OriginStartDay = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetEndYear( EndYear ) ) {
      OriginEndYear = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetEndMonth( EndMonth ) ) {
      OriginEndMonth = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetEndDay( EndDay ) ) {
      OriginEndDay = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetAsteroidNumber( AsteroidNumber ) ) {
      OriginAsteroidNumber = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetIfOneStar( IfOneStar ) ) {
      OriginIfOneStar = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetRA_Hour( RA_Hour ) ) {
      OriginRA_Hour = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetRA_Min( RA_Min ) ) {
      OriginRA_Min = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetRA_Sec( RA_Sec ) ) {
      OriginRA_Sec = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetDec_Deg( Dec_Deg ) ) {
      OriginDec_Deg = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetDec_Min( Dec_Min ) ) {
      OriginDec_Min = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetDec_Sec( Dec_Sec ) ) {
      OriginDec_Sec = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetpmRA( pmRA ) ) {
      OriginpmRA = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetpmDec( pmDec ) ) {
      OriginpmDec = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOneStarCatalog( OneStarCatalog ) ) {
      OriginOneStarCatalog = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOneStarMv( OneStarMv ) ) {
      OriginOneStarMv = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOneStarParallax( OneStarParallax ) ) {
      OriginOneStarParallax = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetVrad( Vrad ) ) {
      OriginVrad = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetEpoch( Epoch ) ) {
      OriginEpoch = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetScanStep( ScanStep ) ) {
      OriginScanStep = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetIfExtraRadius( IfExtraRadius ) ) {
      OriginIfExtraRadius = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetExtraRadius( ExtraRadius ) ) {
      OriginExtraRadius = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetET_UT( ET_UT ) ) {
      OriginET_UT = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetUT_UTC( UT_UTC ) ) {
      OriginUT_UTC = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetMinA( MinA ) ) {
      OriginMinA = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetMaxA( MaxA ) ) {
      OriginMaxA = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetMinDiameter( MinDiameter ) ) {
      OriginMinDiameter = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetMaxDiameter( MaxDiameter ) ) {
      OriginMaxDiameter = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetIfOneAsteroid( IfOneAsteroid ) ) {
      OriginIfOneAsteroid = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetObservationEpoch( ObservationEpoch ) ) {
      OriginObservationEpoch = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOrbitM( OrbitM ) ) {
      OriginOrbitM = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOrbitW( OrbitW ) ) {
      OriginOrbitW = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOrbitO( OrbitO ) ) {
      OriginOrbitO = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOrbitI( OrbitI ) ) {
      OriginOrbitI = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOrbitE( OrbitE ) ) {
      OriginOrbitE = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOrbitA( OrbitA ) ) {
      OriginOrbitA = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOutputType( OutputType ) ) {
      OriginOutputType = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetInputEventsFilePath( InputEventsFilePath ) ) {
      OriginInputEventsFilePath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetOutputEventsFilePath( OutputEventsFilePath ) ) {
      OriginOutputEventsFilePath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetSitesFilePath( SitesFilePath ) ) {
      OriginSitesFilePath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetCalculationMode( CalculationMode ) ) {
      OriginCalculationMode = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetIfMySQL( IfMySQL ) ) {
      OriginIfMySQL = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetIfPicture( IfPicture ) ) {
      OriginIfPicture = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetIfPath( IfPath ) ) {
      OriginIfPath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetSunElev( SunElev ) ) {
      OriginSunElev = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetMaxMv( MaxMv ) ) {
      OriginMaxMv = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetUpdatesFilePath( UpdatesFilePath ) ) {
      OriginUpdatesFilePath = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetUpdatesExpirePeriod( UpdatesExpirePeriod ) ) {
      OriginUpdatesExpirePeriod = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetStartAsteroidNumber( StartAsteroidNumber ) ) {
      OriginStartAsteroidNumber = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetEndAsteroidNumber( EndAsteroidNumber ) ) {
      OriginEndAsteroidNumber = LO_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pLOConfig->GetStartSQLNumber( StartSQLNumber ) ) {
      OriginStartSQLNumber = LO_APPL_PARAM_MAIN_CONFIG;
    }

    pLOConfig1 = new LOConfig();

    pAPSReadConfig1 = new apslib::APSReadConfig( pLOConfigReadSubModule, ProjectFilePath );

    RetCode = pAPSReadConfig1->Read( pLOConfig1 );

    if( !RetCode ) {
      if( !pLOConfig1->GetAstOrbFilePath( AstOrbFilePath ) ) {
        OriginAstOrbFilePath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetStarCatalogFilePath( StarCatalogFilePath ) ) {
        OriginStarCatalogFilePath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetJPLEphemFilePath( JPLEphemFilePath ) ) {
        OriginJPLEphemFilePath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetStartYear( StartYear ) ) {
        OriginStartYear = LO_APPL_PARAM_EXTRA_CONFIG;
      } 

      if( !pLOConfig1->GetStartMonth( StartMonth ) ) {
        OriginStartMonth = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetStartDay( StartDay ) ) {
        OriginStartDay = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetEndYear( EndYear ) ) {
        OriginEndYear = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetEndMonth( EndMonth ) ) {
        OriginEndMonth = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetEndDay( EndDay ) ) {
        OriginEndDay = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetAsteroidNumber( AsteroidNumber ) ) {
        OriginAsteroidNumber = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetIfOneStar( IfOneStar ) ) {
        OriginIfOneStar = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetRA_Hour( RA_Hour ) ) {
        OriginRA_Hour = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetRA_Min( RA_Min ) ) {
        OriginRA_Min = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetRA_Sec( RA_Sec ) ) {
        OriginRA_Sec = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetDec_Deg( Dec_Deg ) ) {
        OriginDec_Deg = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetDec_Min( Dec_Min ) ) {
        OriginDec_Min = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetDec_Sec( Dec_Sec ) ) {
        OriginDec_Sec = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetpmRA( pmRA ) ) {
        OriginpmRA = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetpmDec( pmDec ) ) {
        OriginpmDec = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOneStarCatalog( OneStarCatalog ) ) {
        OriginOneStarCatalog = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOneStarMv( OneStarMv ) ) {
        OriginOneStarMv = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOneStarParallax( OneStarParallax ) ) {
        OriginOneStarParallax = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetVrad( Vrad ) ) {
        OriginVrad = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetEpoch( Epoch ) ) {
        OriginEpoch = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetScanStep( ScanStep ) ) {
        OriginScanStep = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetIfExtraRadius( IfExtraRadius ) ) {
        OriginIfExtraRadius = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetExtraRadius( ExtraRadius ) ) {
        OriginExtraRadius = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetET_UT( ET_UT ) ) {
        OriginET_UT = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetUT_UTC( UT_UTC ) ) {
        OriginUT_UTC = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetMinA( MinA ) ) {
        OriginMinA = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetMaxA( MaxA ) ) {
        OriginMaxA = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetMinDiameter( MinDiameter ) ) {
        OriginMinDiameter = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetMaxDiameter( MaxDiameter ) ) {
        OriginMaxDiameter = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetIfOneAsteroid( IfOneAsteroid ) ) {
        OriginIfOneAsteroid = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetObservationEpoch( ObservationEpoch ) ) {
        OriginObservationEpoch = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOrbitM( OrbitM ) ) {
        OriginOrbitM = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOrbitW( OrbitW ) ) {
        OriginOrbitW = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOrbitO( OrbitO ) ) {
        OriginOrbitO = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOrbitI( OrbitI ) ) {
        OriginOrbitI = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOrbitE( OrbitE ) ) {
        OriginOrbitE = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOrbitA( OrbitA ) ) {
        OriginOrbitA = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOutputType( OutputType ) ) {
        OriginOutputType = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetInputEventsFilePath( InputEventsFilePath ) ) {
        OriginInputEventsFilePath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetOutputEventsFilePath( OutputEventsFilePath ) ) {
        OriginOutputEventsFilePath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetSitesFilePath( SitesFilePath ) ) {
        OriginSitesFilePath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetCalculationMode( CalculationMode ) ) {
        OriginCalculationMode = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetIfMySQL( IfMySQL ) ) {
        OriginIfMySQL = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetIfPicture( IfPicture ) ) {
        OriginIfPicture = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetIfPath( IfPath ) ) {
        OriginIfPath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetSunElev( SunElev ) ) {
        OriginSunElev = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetMaxMv( MaxMv ) ) {
        OriginMaxMv = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetUpdatesFilePath( UpdatesFilePath ) ) {
        OriginUpdatesFilePath = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetUpdatesExpirePeriod( UpdatesExpirePeriod ) ) {
        OriginUpdatesExpirePeriod = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetStartAsteroidNumber( StartAsteroidNumber ) ) {
        OriginStartAsteroidNumber = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetEndAsteroidNumber( EndAsteroidNumber ) ) {
        OriginEndAsteroidNumber = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pLOConfig1->GetStartSQLNumber( StartSQLNumber ) ) {
        OriginStartSQLNumber = LO_APPL_PARAM_EXTRA_CONFIG;
      }

      UpdateParameters();

      PrintParameters();
    }

    delete pAPSReadConfig1;

    delete pLOConfig1;
  }

  delete pAPSReadConfig;

  delete pLOConfig;

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
