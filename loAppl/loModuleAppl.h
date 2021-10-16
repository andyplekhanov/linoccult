//------------------------------------------------------------------------------
//
// File:    loModuleAppl.h
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
//         version 0.5 08.02.2005 EventDataWriter was added
//         version 0.6 15.02.2005 InputEventsFilePath, OutputEventsFilePath, SunDist, MaxMv were added.
//                                ResultsFilePath, IfOutputFile were removed.
//         version 0.7 22.02.2005 SunDist -> SunElev
//         version 0.8 27.02.2005 LOEventPosWriterSubModule, LO_APPL_WRITE_POSITIONS_DATA were added
//         version 1.0 05.03.2005 UpdatesFilePath, UpdatesExpirePeriod, StartAsteroidNumber, EndAsteroidNumber,
//                                StartSQLNumber were added. LOSitesDataReaderSubModule was added.
//                                UpdatesParameters was added.
//         version 1.1 17.04.2005 LOUpdatesDataReaderSubModule was added.
//         version 1.2 31.07.2005 OneStarCatalog, OneStarMv were added
//         version 1.3 23.08.2005 OneStarParallax was added
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

#ifndef LO_MODULE_APPL_H
#define LO_MODULE_APPL_H

#include <string>

#include "apsmainmodule.h"
#include "loConfig.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSMainModule;

class LOAstOrbReadSubModule;
class LOTychoReadSubModule;
class LOGaiaReadSubModule;
class LOCalcSubModule;
class LOEventDataWriterSubModule;
class LOEventPosWriterSubModule;
class LOEventDataReaderSubModule;
class LOSitesDataReaderSubModule;
class LOUpdatesDataReaderSubModule;
class LOConfigReadSubModule;

enum {
  LO_APPL_NO_ERR = 0,
  LO_APPL_AST_ORB_READ,
  LO_APPL_GAIA_READ,
  LO_APPL_CALC,
  LO_APPL_WRITE_EVENT_DATA,
  LO_APPL_WRITE_POSITIONS_DATA,
  LO_APPL_READ_EVENT_DATA,
  LO_APPL_READ_SITES_DATA,
  LO_APPL_READ_UPDATES_DATA,
  LO_APPL_START,
  LO_APPL_MODULE,
  LO_APPL_SHOW_PARAM
};

enum {
  LO_APPL_PARAM_DEFAULT = 0,
  LO_APPL_PARAM_MAIN_CONFIG,
  LO_APPL_PARAM_EXTRA_CONFIG,
  LO_APPL_PARAM_CALCULATED
};

//======================= LOModuleAppl ==========================

class LOModuleAppl : public APSMainModule
{
  private:

    LOAstOrbReadSubModule        * pLOAstOrbReadSubModule;
    LOGaiaReadSubModule          * pLOGaiaReadSubModule;
    LOCalcSubModule              * pLOCalcSubModule;
    LOEventDataWriterSubModule   * pLOEventDataWriterSubModule;
    LOEventPosWriterSubModule    * pLOEventPosWriterSubModule;
    LOEventDataReaderSubModule   * pLOEventDataReaderSubModule;
    LOSitesDataReaderSubModule   * pLOSitesDataReaderSubModule;
    LOUpdatesDataReaderSubModule * pLOUpdatesDataReaderSubModule;
    LOConfigReadSubModule        * pLOConfigReadSubModule;

    std::string ProjectFilePath;

    std::string AstOrbFilePath;
    std::string StarCatalogFilePath;
    std::string JPLEphemFilePath;
    int         StartYear;
    int         StartMonth;
    int         StartDay;
    int         EndYear;
    int         EndMonth;
    int         EndDay;
    int         AsteroidNumber;
    int         IfOneStar;
    int         RA_Hour;
    int         RA_Min;
    double      RA_Sec;
    int         Dec_Deg;
    int         Dec_Min;
    double      Dec_Sec;
    double      pmRA;
    double      pmDec;
    int         OneStarCatalog;
    double      OneStarMv;
    double      OneStarParallax;
    double      Vrad;
    double      Epoch;
    int         ScanStep;
    int         IfExtraRadius;
    double      ExtraRadius;
    double      ET_UT;
    double      UT_UTC;
    double      MinA;
    double      MaxA;
    double      MinDiameter;
    double      MaxDiameter;
    int         IfOneAsteroid;
    double      ObservationEpoch;
    double      OrbitM;
    double      OrbitW;
    double      OrbitO;
    double      OrbitI;
    double      OrbitE;
    double      OrbitA;
    int         OutputType;
    std::string InputEventsFilePath;
    std::string OutputEventsFilePath;
    std::string SitesFilePath;
    int         CalculationMode;
    int         IfMySQL;
    int         IfPicture;
    int         IfPath;
    double      SunElev;
    double      MaxMv;
    std::string UpdatesFilePath;
    int         UpdatesExpirePeriod;
    int         StartAsteroidNumber;
    int         EndAsteroidNumber;
    int         StartSQLNumber;

    int OriginAstOrbFilePath;
    int OriginStarCatalogFilePath;
    int OriginJPLEphemFilePath;
    int OriginStartYear;
    int OriginStartMonth;
    int OriginStartDay;
    int OriginEndYear;
    int OriginEndMonth;
    int OriginEndDay;
    int OriginAsteroidNumber;
    int OriginIfOneStar;
    int OriginRA_Hour;
    int OriginRA_Min;
    int OriginRA_Sec;
    int OriginDec_Deg;
    int OriginDec_Min;
    int OriginDec_Sec;
    int OriginpmRA;
    int OriginpmDec;
    int OriginOneStarCatalog;
    int OriginOneStarMv;
    int OriginOneStarParallax;
    int OriginVrad;
    int OriginEpoch;
    int OriginScanStep;
    int OriginIfExtraRadius;
    int OriginExtraRadius;
    int OriginET_UT;
    int OriginUT_UTC;
    int OriginMinA;
    int OriginMaxA;
    int OriginMinDiameter;
    int OriginMaxDiameter;
    int OriginIfOneAsteroid;
    int OriginObservationEpoch;
    int OriginOrbitM;
    int OriginOrbitW;
    int OriginOrbitO;
    int OriginOrbitI;
    int OriginOrbitE;
    int OriginOrbitA;
    int OriginOutputType;
    int OriginInputEventsFilePath;
    int OriginOutputEventsFilePath;
    int OriginSitesFilePath;
    int OriginCalculationMode;
    int OriginIfMySQL;
    int OriginIfPicture;
    int OriginIfPath;
    int OriginSunElev;
    int OriginMaxMv;
    int OriginUpdatesFilePath;
    int OriginUpdatesExpirePeriod;
    int OriginStartAsteroidNumber;
    int OriginEndAsteroidNumber;
    int OriginStartSQLNumber;

  public:

    LOModuleAppl( const std::string & aProjectFilePath,
                  const std::string & ModuleName,
                  const int X_Version,
                  const int Y_Version,
                  const int Z_Version,
                  const int FirstCopyRightYear,
                  const int CopyRightYear,
                  const apslib::APS_PROGRAM_VERSION_TYPE VersionType = apslib::APS_NORMAL_VERSION );

    virtual ~LOModuleAppl( void );

    LOAstOrbReadSubModule * GetAstOrbReadSubModulePtr( void ) const
      { return( pLOAstOrbReadSubModule ); }

    LOGaiaReadSubModule * GetGaiaReadSubModulePtr( void ) const
      { return( pLOGaiaReadSubModule ); }

    LOCalcSubModule * GetCalcSubModulePtr( void ) const
      { return( pLOCalcSubModule ); }

    LOEventDataWriterSubModule * GetEventDataWriterSubModulePtr( void ) const
      { return( pLOEventDataWriterSubModule ); }

    LOEventPosWriterSubModule * GetEventPosWriterSubModulePtr( void ) const
      { return( pLOEventPosWriterSubModule ); }

    LOEventDataReaderSubModule * GetEventDataReaderSubModulePtr( void ) const
      { return( pLOEventDataReaderSubModule ); }

    LOSitesDataReaderSubModule * GetSitesDataReaderSubModulePtr( void ) const
      { return( pLOSitesDataReaderSubModule ); }

    LOUpdatesDataReaderSubModule * GetUpdatesDataReaderSubModulePtr( void ) const
      { return( pLOUpdatesDataReaderSubModule ); }

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    const std::string & GetAstOrbFilePath( void ) const
      { return( AstOrbFilePath ); }

    const std::string & GetStarCatalogFilePath( void ) const
      { return( StarCatalogFilePath ); }

    const std::string & GetJPLEphemFilePath( void ) const
      { return( JPLEphemFilePath ); }

    int GetStartYear( void ) const
      { return( StartYear ); }

    int GetStartMonth( void ) const
      { return( StartMonth ); }

    int GetStartDay( void ) const
      { return( StartDay ); }

    int GetEndYear( void ) const
      { return( EndYear ); }

    int IfEndYear( void ) const;

    int GetEndMonth( void ) const
      { return( EndMonth ); }

    int IfEndMonth( void ) const;

    int GetEndDay( void ) const
      { return( EndDay ); }

    int IfEndDay( void ) const;

    int GetAsteroidNumber( void ) const
      { return( AsteroidNumber ); }

    int GetIfOneStar( void ) const
      { return( IfOneStar ); }

    int GetRA_Hour( void ) const
      { return( RA_Hour ); }

    int GetRA_Min( void ) const
      { return( RA_Min ); }

    double GetRA_Sec( void ) const
      { return( RA_Sec ); }

    int GetDec_Deg( void ) const
      { return( Dec_Deg ); }

    int GetDec_Min( void ) const
      { return( Dec_Min ); }

    double GetDec_Sec( void ) const
      { return( Dec_Sec ); }

    double GetpmRA( void ) const
      { return( pmRA ); }

    double GetpmDec( void ) const
      { return( pmDec ); }

    int GetOneStarCatalog( void ) const
      { return( OneStarCatalog ); }

    double GetOneStarMv( void ) const
      { return( OneStarMv ); }

    double GetOneStarParallax( void ) const
      { return( OneStarParallax ); }
    
    double GetVrad( void ) const
      { return( Vrad ); }
    
    double GetEpoch( void ) const
      { return( Epoch ); }
    
    int GetScanStep( void ) const
      { return( ScanStep ); }

    int GetIfExtraRadius( void ) const
      { return( IfExtraRadius ); }

    double GetExtraRadius( void ) const
      { return( ExtraRadius ); }

    double GetET_UT( void ) const
      { return( ET_UT ); }

    double GetUT_UTC( void ) const
      { return( UT_UTC ); }

    double GetMinA( void ) const
      { return( MinA ); }

    double GetMaxA( void ) const
      { return( MaxA ); }

    double GetMinDiameter( void ) const
      { return( MinDiameter ); }

    double GetMaxDiameter( void ) const
      { return( MaxDiameter ); }

    int GetIfOneAsteroid( void ) const
      { return( IfOneAsteroid ); }

    double GetObservationEpoch( void ) const
      { return( ObservationEpoch ); }

    double GetOrbitM( void ) const
      { return( OrbitM ); }

    double GetOrbitW( void ) const
      { return( OrbitW ); }

    double GetOrbitO( void ) const
      { return( OrbitO ); }

    double GetOrbitI( void ) const
      { return( OrbitI ); }

    double GetOrbitE( void ) const
      { return( OrbitE ); }

    double GetOrbitA( void ) const
      { return( OrbitA ); }

    int GetOutputType( void ) const
      { return( OutputType ); }

    const std::string & GetInputEventsFilePath( void ) const
      { return( InputEventsFilePath ); }

    int IfInputEventsFilePath( void ) const;

    const std::string & GetOutputEventsFilePath( void ) const
      { return( OutputEventsFilePath ); }

    int IfOutputEventsFilePath( void ) const;

    const std::string & GetSitesFilePath( void ) const
      { return( SitesFilePath ); }

    int IfSitesFilePath( void ) const;

    int GetCalculationMode( void ) const
      { return( CalculationMode ); }

    int GetIfMySQL( void ) const
      { return( IfMySQL ); }

    int GetIfPicture( void ) const
      { return( IfPicture ); }

    int GetIfPath( void ) const
      { return( IfPath ); }

    double GetSunElev( void ) const
      { return( SunElev ); }

    double GetMaxMv( void ) const
      { return( MaxMv ); }

    const std::string & GetUpdatesFilePath( void ) const
      { return( UpdatesFilePath ); }

    int IfUpdatesFilePath( void ) const;

    int GetUpdatesExpirePeriod( void ) const
      { return( UpdatesExpirePeriod ); }

    int GetStartAsteroidNumber( void ) const
      { return( StartAsteroidNumber ); }

    int GetEndAsteroidNumber( void ) const
      { return( EndAsteroidNumber ); }

    int GetStartSQLNumber( void ) const
      { return( StartSQLNumber ); }

    void PrintParameters( void ) const;

    void UpdateParameters( void );

    virtual int Run( void );
};

}}

#endif

//---------------------------- End of file ---------------------------


