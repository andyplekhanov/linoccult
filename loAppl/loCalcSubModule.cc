//------------------------------------------------------------------------------
//
// File:    loCalcSubModule.cc
//
// Purpose: Submodule for linux occultation calculations.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 16.02.2004
//         version 0.2 27.05.2004 OutputType parameter was added
//         version 0.3 31.01.2005 ResultsFilePath, SitesFilePath, IfOutputFile,
//                                IfMySQL, IfPicture, IfPath parameters ware added
//         version 0.4 15.02.2005 GetResultsFilePath, GetIfOutputFile were removed.
//                                SunDist was added.
//         version 0.5 22.02.2005 SunDist -> SunElev
//         version 0.6 05.03.2005 StartSQLNumber was added.
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

#include "loModuleAppl.h"
#include "loCalcSubModule.h"
#include "loModuleCalc.h"

namespace aps {

  namespace apslinoccult {

//======================= LOCalcSubModule ==========================

LOCalcSubModule :: LOCalcSubModule( LOModuleAppl * pOwner ) :
                              APSSubModule( pOwner )
{
}

LOCalcSubModule :: ~LOCalcSubModule( void )
{
}

int LOCalcSubModule :: WarningMessage( const int MsgNumber, const std::string & pMsg, const APSAbsModule * pSubModule ) const
{
  switch( MsgNumber ) {
    case LO_CALC_ET_UT: 
      return( apslib::MODULE_CONTINUE );
    default:;
  }

  return( APSSubModule :: WarningMessage( MsgNumber, pMsg, pSubModule ) );
}

const LOModuleAppl * LOCalcSubModule :: GetLOModuleApplPtr( void ) const
{
  return( static_cast<const LOModuleAppl *>( GetOwnerPtr() ) );
}

const std::string & LOCalcSubModule :: GetJPLEphemFilePath( void ) const
{
  return( GetLOModuleApplPtr()->GetJPLEphemFilePath() );
}

int LOCalcSubModule :: GetStartYear( void ) const
{
  return( GetLOModuleApplPtr()->GetStartYear() );
}

int LOCalcSubModule :: GetStartMonth( void ) const
{
  return( GetLOModuleApplPtr()->GetStartMonth() );
}

int LOCalcSubModule :: GetStartDay( void ) const
{
  return( GetLOModuleApplPtr()->GetStartDay() );
}

int LOCalcSubModule :: GetEndYear( void ) const
{
  return( GetLOModuleApplPtr()->GetEndYear() );
}

int LOCalcSubModule :: GetEndMonth( void ) const
{
  return( GetLOModuleApplPtr()->GetEndMonth() );
}

int LOCalcSubModule :: GetEndDay( void ) const
{
  return( GetLOModuleApplPtr()->GetEndDay() );
}

int LOCalcSubModule :: GetAsteroidNumber( void ) const
{
  return( GetLOModuleApplPtr()->GetAsteroidNumber() );
}

int LOCalcSubModule :: GetScanStep( void ) const
{
  return( GetLOModuleApplPtr()->GetScanStep() );
}

int LOCalcSubModule :: GetIfExtraRadius( void ) const
{
  return( GetLOModuleApplPtr()->GetIfExtraRadius() );
}

double LOCalcSubModule :: GetExtraRadius( void ) const
{
  return( GetLOModuleApplPtr()->GetExtraRadius() );
}

double LOCalcSubModule :: GetET_UT( void ) const
{
  return( GetLOModuleApplPtr()->GetET_UT() );
}

double LOCalcSubModule :: GetUT_UTC( void ) const
{
  return( GetLOModuleApplPtr()->GetUT_UTC() );
}

double LOCalcSubModule :: GetMinA( void ) const
{
  return( GetLOModuleApplPtr()->GetMinA() );
}

double LOCalcSubModule :: GetMaxA( void ) const
{
  return( GetLOModuleApplPtr()->GetMaxA() );
}

double LOCalcSubModule :: GetMinDiameter( void ) const
{
  return( GetLOModuleApplPtr()->GetMinDiameter() );
}

double LOCalcSubModule :: GetMaxDiameter( void ) const
{
  return( GetLOModuleApplPtr()->GetMaxDiameter() );
}

int LOCalcSubModule :: GetOutputType( void ) const
{
  return( GetLOModuleApplPtr()->GetOutputType() );
}

const std::string & LOCalcSubModule :: GetSitesFilePath( void ) const
{
  return( GetLOModuleApplPtr()->GetSitesFilePath() );
}

int LOCalcSubModule :: GetIfMySQL( void ) const
{
  return( GetLOModuleApplPtr()->GetIfMySQL() );
}

int LOCalcSubModule :: GetIfPicture( void ) const
{
  return( GetLOModuleApplPtr()->GetIfPicture() );
}

int LOCalcSubModule :: GetIfPath( void ) const
{
  return( GetLOModuleApplPtr()->GetIfPath() );
}

double LOCalcSubModule :: GetSunElev( void ) const
{
  return( GetLOModuleApplPtr()->GetSunElev() );
}

int LOCalcSubModule :: GetStartSQLNumber( void ) const
{
  return( GetLOModuleApplPtr()->GetStartSQLNumber() );
}

}}

//---------------------------- End of file ---------------------------
