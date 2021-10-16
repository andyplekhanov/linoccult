//------------------------------------------------------------------------------
//
// File:    loConfig.cc
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

#include "loConfig.h"

namespace aps {

  namespace apslinoccult {

LOConfig :: LOConfig( void ) : APSConfig()
{
  AddParameter( "AstOrbFilePath", apslib::PARAM_STRING );
  AddParameter( "StarCatalogFilePath", apslib::PARAM_STRING );
  AddParameter( "JPLEphemFilePath", apslib::PARAM_STRING );
  AddParameter( "StartYear", apslib::PARAM_INTEGER );
  AddParameter( "StartMonth", apslib::PARAM_INTEGER );
  AddParameter( "StartDay", apslib::PARAM_INTEGER );
  AddParameter( "EndYear", apslib::PARAM_INTEGER );
  AddParameter( "EndMonth", apslib::PARAM_INTEGER );
  AddParameter( "EndDay", apslib::PARAM_INTEGER );
  AddParameter( "AsteroidNumber", apslib::PARAM_INTEGER );
  AddParameter( "IfOneStar", apslib::PARAM_INTEGER );
  AddParameter( "RA_Hour", apslib::PARAM_INTEGER );
  AddParameter( "RA_Min", apslib::PARAM_INTEGER );
  AddParameter( "RA_Sec", apslib::PARAM_DOUBLE );
  AddParameter( "Dec_Deg", apslib::PARAM_INTEGER );
  AddParameter( "Dec_Min", apslib::PARAM_INTEGER );
  AddParameter( "Dec_Sec", apslib::PARAM_DOUBLE );
  AddParameter( "pmRA", apslib::PARAM_DOUBLE );
  AddParameter( "pmDec", apslib::PARAM_DOUBLE );
  AddParameter( "OneStarCatalog", apslib::PARAM_INTEGER );
  AddParameter( "OneStarMv", apslib::PARAM_DOUBLE );
  AddParameter( "OneStarParallax", apslib::PARAM_DOUBLE );
  AddParameter( "Vrad", apslib::PARAM_DOUBLE );
  AddParameter( "Epoch", apslib::PARAM_DOUBLE );  
  AddParameter( "ScanStep", apslib::PARAM_INTEGER );
  AddParameter( "IfExtraRadius", apslib::PARAM_INTEGER );
  AddParameter( "ExtraRadius", apslib::PARAM_DOUBLE );
  AddParameter( "ET_UT", apslib::PARAM_DOUBLE );
  AddParameter( "UT_UTC", apslib::PARAM_DOUBLE );
  AddParameter( "MinA", apslib::PARAM_DOUBLE );
  AddParameter( "MaxA", apslib::PARAM_DOUBLE );
  AddParameter( "MinDiameter", apslib::PARAM_DOUBLE );
  AddParameter( "MaxDiameter", apslib::PARAM_DOUBLE );
  AddParameter( "IfOneAsteroid", apslib::PARAM_INTEGER );
  AddParameter( "ObservationEpoch", apslib::PARAM_DOUBLE );
  AddParameter( "OrbitM", apslib::PARAM_DOUBLE );
  AddParameter( "OrbitW", apslib::PARAM_DOUBLE );
  AddParameter( "OrbitO", apslib::PARAM_DOUBLE );
  AddParameter( "OrbitI", apslib::PARAM_DOUBLE );
  AddParameter( "OrbitE", apslib::PARAM_DOUBLE );
  AddParameter( "OrbitA", apslib::PARAM_DOUBLE );
  AddParameter( "OutputType", apslib::PARAM_INTEGER );
  AddParameter( "InputEventsFilePath", apslib::PARAM_STRING );
  AddParameter( "OutputEventsFilePath", apslib::PARAM_STRING );
  AddParameter( "SitesFilePath", apslib::PARAM_STRING );
  AddParameter( "CalculationMode", apslib::PARAM_INTEGER );
  AddParameter( "IfMySQL", apslib::PARAM_INTEGER );
  AddParameter( "IfPicture", apslib::PARAM_INTEGER );
  AddParameter( "SunElev", apslib::PARAM_DOUBLE );
  AddParameter( "MaxMv", apslib::PARAM_DOUBLE );
  AddParameter( "UpdatesFilePath", apslib::PARAM_STRING );
  AddParameter( "UpdatesExpirePeriod", apslib::PARAM_INTEGER );
  AddParameter( "StartAsteroidNumber", apslib::PARAM_INTEGER );
  AddParameter( "EndAsteroidNumber", apslib::PARAM_INTEGER );
  AddParameter( "StartSQLNumber", apslib::PARAM_INTEGER );
}

LOConfig :: ~LOConfig( void )
{
}

int LOConfig :: GetAstOrbFilePath( std::string & AstOrbFilePath ) const
{
  return( GetStringValue( "AstOrbFilePath", AstOrbFilePath ) );
}

int LOConfig :: GetStarCatalogFilePath( std::string & StarCatalogFilePath ) const
{
  return( GetStringValue( "StarCatalogFilePath", StarCatalogFilePath ) );
}

int LOConfig :: GetJPLEphemFilePath( std::string & JPLEphemFilePath ) const
{
  return( GetStringValue( "JPLEphemFilePath", JPLEphemFilePath ) );
}

int LOConfig :: GetStartYear( int & StartYear ) const
{
  return( GetIntegerValue( "StartYear", StartYear ) );
}

int LOConfig :: GetStartMonth( int & StartMonth ) const
{
  return( GetIntegerValue( "StartMonth", StartMonth ) );
}

int LOConfig :: GetStartDay( int & StartDay ) const
{
  return( GetIntegerValue( "StartDay", StartDay ) );
}

int LOConfig :: GetEndYear( int & EndYear ) const
{
  return( GetIntegerValue( "EndYear", EndYear ) );
}

int LOConfig :: GetEndMonth( int & EndMonth ) const
{
  return( GetIntegerValue( "EndMonth", EndMonth ) );
}

int LOConfig :: GetEndDay( int & EndDay ) const
{
  return( GetIntegerValue( "EndDay", EndDay ) );
}

int LOConfig :: GetAsteroidNumber( int & AsteroidNumber ) const
{
  return( GetIntegerValue( "AsteroidNumber", AsteroidNumber ) );
}

int LOConfig :: GetIfOneStar( int & IfOneStar ) const
{
  return( GetIntegerValue( "IfOneStar", IfOneStar ) );
}

int LOConfig :: GetRA_Hour( int & RA_Hour ) const
{
  return( GetIntegerValue( "RA_Hour", RA_Hour ) );
}

int LOConfig :: GetRA_Min( int & RA_Min ) const
{
  return( GetIntegerValue( "RA_Min", RA_Min ) );
}

int LOConfig :: GetRA_Sec( double & RA_Sec ) const
{
  return( GetDoubleValue( "RA_Sec", RA_Sec ) );
}

int LOConfig :: GetDec_Deg( int & Dec_Deg ) const
{
  return( GetIntegerValue( "Dec_Deg", Dec_Deg ) );
}

int LOConfig :: GetDec_Min( int & Dec_Min ) const
{
  return( GetIntegerValue( "Dec_Min", Dec_Min ) );
}

int LOConfig :: GetDec_Sec( double & Dec_Sec ) const
{
  return( GetDoubleValue( "Dec_Sec", Dec_Sec ) );
}

int LOConfig :: GetpmRA( double & pmRA ) const
{
  return( GetDoubleValue( "pmRA", pmRA ) );
}

int LOConfig :: GetpmDec( double & pmDec ) const
{
  return( GetDoubleValue( "pmDec", pmDec ) );
}

int LOConfig :: GetOneStarCatalog( int & OneStarCatalog ) const
{
  return( GetIntegerValue( "OneStarCatalog", OneStarCatalog ) );
}

int LOConfig :: GetOneStarMv( double & OneStarMv ) const
{
  return( GetDoubleValue( "OneStarMv", OneStarMv ) );
}

int LOConfig :: GetOneStarParallax( double & OneStarParallax ) const
{
  return( GetDoubleValue( "OneStarParallax", OneStarParallax ) );
}
    
int LOConfig :: GetVrad( double & Vrad ) const
{
  return( GetDoubleValue( "Vrad", Vrad ) );
}
    
int LOConfig :: GetEpoch( double & Epoch ) const
{
  return( GetDoubleValue( "Epoch", Epoch ) );
}
   
int LOConfig :: GetScanStep( int & ScanStep ) const
{
  return( GetIntegerValue( "ScanStep", ScanStep ) );
}

int LOConfig :: GetIfExtraRadius( int & IfExtraRadius ) const
{
  return( GetIntegerValue( "IfExtraRadius", IfExtraRadius ) );
}

int LOConfig :: GetExtraRadius( double & ExtraRadius ) const
{
  return( GetDoubleValue( "ExtraRadius", ExtraRadius ) );
}

int LOConfig :: GetET_UT( double & ET_UT ) const
{
  return( GetDoubleValue( "ET_UT", ET_UT ) );
}

int LOConfig :: GetUT_UTC( double & UT_UTC ) const
{
  return( GetDoubleValue( "UT_UTC", UT_UTC ) );
}

int LOConfig :: GetMinA( double & MinA ) const
{
  return( GetDoubleValue( "MinA", MinA ) );
}

int LOConfig :: GetMaxA( double & MaxA ) const
{
  return( GetDoubleValue( "MaxA", MaxA ) );
}

int LOConfig :: GetMinDiameter( double & MinDiameter ) const
{
  return( GetDoubleValue( "MinDiameter", MinDiameter ) );
}

int LOConfig :: GetMaxDiameter( double & MaxDiameter ) const
{
  return( GetDoubleValue( "MaxDiameter", MaxDiameter ) );
}

int LOConfig :: GetIfOneAsteroid( int & IfOneAsteroid ) const
{
  return( GetIntegerValue( "IfOneAsteroid", IfOneAsteroid ) );
}

int LOConfig :: GetObservationEpoch( double & ObservationEpoch ) const
{
  return( GetDoubleValue( "ObservationEpoch", ObservationEpoch ) );
}

int LOConfig :: GetOrbitM( double & OrbitM ) const
{
  return( GetDoubleValue( "OrbitM", OrbitM ) );
}

int LOConfig :: GetOrbitW( double & OrbitW ) const
{
  return( GetDoubleValue( "OrbitW", OrbitW ) );
}

int LOConfig :: GetOrbitO( double & OrbitO ) const
{
  return( GetDoubleValue( "OrbitO", OrbitO ) );
}

int LOConfig :: GetOrbitI( double & OrbitI ) const
{
  return( GetDoubleValue( "OrbitI", OrbitI ) );
}

int LOConfig :: GetOrbitE( double & OrbitE ) const
{
  return( GetDoubleValue( "OrbitE", OrbitE ) );
}

int LOConfig :: GetOrbitA( double & OrbitA ) const
{
  return( GetDoubleValue( "OrbitA", OrbitA ) );
}

int LOConfig :: GetOutputType( int & OutputType ) const
{
  return( GetIntegerValue( "OutputType", OutputType ) );
}

int LOConfig :: GetInputEventsFilePath( std::string & InputEventsFilePath ) const
{
  return( GetStringValue( "InputEventsFilePath", InputEventsFilePath ) );
}

int LOConfig :: GetOutputEventsFilePath( std::string & OutputEventsFilePath ) const
{
  return( GetStringValue( "OutputEventsFilePath", OutputEventsFilePath ) );
}

int LOConfig :: GetSitesFilePath( std::string & SitesFilePath ) const
{
  return( GetStringValue( "SitesFilePath", SitesFilePath ) );
}

int LOConfig :: GetCalculationMode( int & CalculationMode ) const
{
  return( GetIntegerValue( "CalculationMode", CalculationMode ) );
}

int LOConfig :: GetIfMySQL( int & IfMySQL ) const
{
  return( GetIntegerValue( "IfMySQL", IfMySQL ) );
}

int LOConfig :: GetIfPicture( int & IfPicture ) const
{
  return( GetIntegerValue( "IfPicture", IfPicture ) );
}

int LOConfig :: GetIfPath( int & IfPath ) const
{
  return( GetIntegerValue( "IfPath", IfPath ) );
}

int LOConfig :: GetSunElev( double & SunElev ) const
{
  return( GetDoubleValue( "SunElev", SunElev ) );
}

int LOConfig :: GetMaxMv( double & MaxMv ) const
{
  return( GetDoubleValue( "MaxMv", MaxMv ) );
}

int LOConfig :: GetUpdatesFilePath( std::string & UpdatesFilePath ) const
{
  return( GetStringValue( "UpdatesFilePath", UpdatesFilePath ) );
}

int LOConfig :: GetUpdatesExpirePeriod( int & UpdatesExpirePeriod ) const
{
  return( GetIntegerValue( "UpdatesExpirePeriod", UpdatesExpirePeriod ) );
}

int LOConfig :: GetStartAsteroidNumber( int & StartAsteroidNumber ) const
{
  return( GetIntegerValue( "StartAsteroidNumber", StartAsteroidNumber ) );
}

int LOConfig :: GetEndAsteroidNumber( int & EndAsteroidNumber ) const
{
  return( GetIntegerValue( "EndAsteroidNumber", EndAsteroidNumber ) );
}

int LOConfig :: GetStartSQLNumber( int & StartSQLNumber ) const
{
  return( GetIntegerValue( "StartSQLNumber", StartSQLNumber ) );
}

}}

//---------------------------- End of file ---------------------------

