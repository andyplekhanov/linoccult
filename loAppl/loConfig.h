//------------------------------------------------------------------------------
//
// File:    loConfig.h
//
// Purpose: Asteroids occultation programb config parameters
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 08.03.2004
//         version 0.2 24.05.2004 IfOneAsteroid, ObservationEpoch,
//                                OrbitM, OrbitW, OrbitO, OrbitI, OrbitE, OrbitA parameters were added
//         version 0.3 27.05.2004 OutputType parameter was added
//         version 0.4 31.01.2005 ResultsFilePath, SitesFilePath, CalculationMode, IfOutputFile,
//                                IfMySQL, IfPicture, IfPath parameters ware added
//         version 0.5 15.02.2005 InputEventsFilePath, OutputEventsFilePath, SunDist, MaxMv were added.
//                                ResultsFilePath, IfOutputFile were removed.
//         version 0.6 22.02.2005 SunDist -> SunElev
//         version 0.7 05.03.2005 UpdatesFilePath, UpdatesExpirePeriod, StartAsteroidNumber, EndAsteroidNumber,
//                                StartSQLNumber were added
//         version 0.8 31.07.2005 OneStarCatalog, OneStarMv were added
//         version 0.9 23.08.2005 OneStarParallax was added
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

#ifndef 	_LOCONFIG_H_
#define         _LOCONFIG_H_	1

#include <string>

#include "apsconfig.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSConfig;

//------------------------------- LOConfig ---------------------------------

class LOConfig : public APSConfig
{
  public:

    LOConfig( void );

    virtual ~LOConfig( void );

    int GetAstOrbFilePath( std::string & AstOrbFilePath ) const;

    int GetStarCatalogFilePath( std::string & StarCatalogFilePath ) const;

    int GetJPLEphemFilePath( std::string & JPLEphemFilePath ) const;

    int GetStartYear( int & StartYear ) const;

    int GetStartMonth( int & StartMonth ) const;

    int GetStartDay( int & StartDay ) const;

    int GetEndYear( int & EndYear ) const;

    int GetEndMonth( int & EndMonth ) const;

    int GetEndDay( int & EndDay ) const;

    int GetAsteroidNumber( int & AsteroidNumber ) const;

    int GetIfOneStar( int & IfOneStar ) const;

    int GetRA_Hour( int & RA_Hour ) const;

    int GetRA_Min( int & RA_Min ) const;

    int GetRA_Sec( double & RA_Sec ) const;

    int GetDec_Deg( int & Dec_Deg ) const;

    int GetDec_Min( int & Dec_Min ) const;

    int GetDec_Sec( double & Dec_Sec ) const;

    int GetpmRA( double & pmRA ) const;

    int GetpmDec( double & pmDec ) const;

    int GetOneStarCatalog( int & OneStarCatalog ) const;

    int GetOneStarMv( double & OneStarMv ) const;

    int GetOneStarParallax( double & OneStarParallax ) const;
    
    int GetVrad( double & Vrad ) const;
    
    int GetEpoch( double & Epoch ) const;

    int GetScanStep( int & ScanStep ) const;

    int GetIfExtraRadius( int & IfExtraRadius ) const;

    int GetExtraRadius( double & ExtraRadius ) const;

    int GetET_UT( double & ET_UT ) const;

    int GetUT_UTC( double & UT_UTC ) const;

    int GetMinA( double & MinA ) const;

    int GetMaxA( double & MaxA ) const;

    int GetMinDiameter( double & MinDiameter ) const;

    int GetMaxDiameter( double & MaxDiameter ) const;

    int GetIfOneAsteroid( int & IfOneAsteroid ) const;

    int GetObservationEpoch( double & ObservationEpoch ) const;

    int GetOrbitM( double & OrbitM ) const;

    int GetOrbitW( double & OrbitW ) const;

    int GetOrbitO( double & OrbitO ) const;

    int GetOrbitI( double & OrbitI ) const;

    int GetOrbitE( double & OrbitE ) const;

    int GetOrbitA( double & OrbitA ) const;

    int GetOutputType( int & OutputType ) const;

    int GetInputEventsFilePath( std::string & InputEventsFilePath ) const;

    int GetOutputEventsFilePath( std::string & OutputEventsFilePath ) const;

    int GetSitesFilePath( std::string & SitesFilePath ) const;

    int GetCalculationMode( int & CalculationMode ) const;

    int GetIfMySQL( int & IfMySQL ) const;

    int GetIfPicture( int & IfPicture ) const;

    int GetIfPath( int & IfPath ) const;

    int GetSunElev( double & SunElev ) const;

    int GetMaxMv( double & MaxMv ) const;

    int GetUpdatesFilePath( std::string & UpdatesFilePath ) const;

    int GetUpdatesExpirePeriod( int & UpdatesExpirePeriod ) const;

    int GetStartAsteroidNumber( int & StartAsteroidNumber ) const;

    int GetEndAsteroidNumber( int & EndAsteroidNumber ) const;

    int GetStartSQLNumber( int & StartSQLNumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------

