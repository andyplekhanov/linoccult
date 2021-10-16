//------------------------------------------------------------------------------
//
// File:    loModuleCalc.cc
//
// Purpose: Module for linux asteroid occultations calculation.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 16.02.2004
//         version 0.2 27.05.2004 OutputType parameter was added
//         version 0.3 15.01.2005 kdtree
//         version 0.4 31.01.2005 ResultsFilePath, SitesFilePath, IfOutputFile,
//                                IfMySQL, IfPicture, IfPath parameters ware added
//         version 0.5 15.02.2005 GetResultsFilePath, GetIfOutputFile were removed.
//                                SunDist was added.
//         version 0.6 22.02.2005 SunDist -> SunElev
//         version 0.7 05.03.2005 StartSQLNumber was added.
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

#include "loModuleCalc.h"
#include "loCalcSubModule.h"
#include "loChebMakerSubModule.h"
#include "loChebSubModule.h"
#include "loAstOrbSubModule.h"

namespace aps {

  namespace apslinoccult {

//================================== LOModuleCalc =================================

LOModuleCalc :: LOModuleCalc( LOCalcSubModule * pOwner ) :
                              APSModule( "LOCalc", pOwner )
{
  pLOChebMakerSubModule = new LOChebMakerSubModule( this );
  pLOAstOrbSubModule    = new LOAstOrbSubModule( this );
  pLOChebSubModule      = new LOChebSubModule( this );
}

LOModuleCalc :: ~LOModuleCalc( void )
{
  delete pLOChebSubModule;
  delete pLOAstOrbSubModule;
  delete pLOChebMakerSubModule;
}

const std::string LOModuleCalc :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case LO_CALC_NO_ERROR:
      return("No error.\n");
    case LO_CALC_ASTEROID_ERROR:
      return("Process asteroid.\n");
    case LO_CALC_INTEGRATION:
      return("Integration.\n");
    case LO_CALC_STAR_PROCESSING:
      return("Star processing.\n");
    case LO_CALC_ET_UT:
      return("ET_UT processing.\n");
    case LO_CALC_START:
      return("Start calculation.\n");
    case LO_CALC_START_ASTEROID_PROCESSING:
      return("Start processing asteroid\n");
    case LO_CALC_FINISH:
      return("Calculation has been finished.\n");
    case LO_CALC_START_KDTREE:
      return("Start building kdtree.\n");
    case LO_CALC_FINISH_KDTREE:
      return("Building kdtree has been finished.\n");
    case LO_CALC_KDTREE_BUILD_ERROR:
      return("Building kdtree.\n");
    case LO_CALC_JPL_INIT:
      return("Init jpl file.\n");
    case LO_CALC_TRANSFORM_EPOCH:
      return("Error in transform epoch.");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const LOCalcSubModule * LOModuleCalc :: GetLOCalcSubModuleApplPtr( void ) const
{
  return( static_cast<const LOCalcSubModule *>( GetOwnerPtr() ) );
}

const std::string & LOModuleCalc :: GetJPLEphemFilePath( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetJPLEphemFilePath() );
}

int LOModuleCalc :: GetStartYear( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetStartYear() );
}

int LOModuleCalc :: GetStartMonth( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetStartMonth() );
}

int LOModuleCalc :: GetStartDay( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetStartDay() );
}

int LOModuleCalc :: GetEndYear( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetEndYear() );
}

int LOModuleCalc :: GetEndMonth( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetEndMonth() );
}

int LOModuleCalc :: GetEndDay( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetEndDay() );
}

int LOModuleCalc :: GetAsteroidNumber( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetAsteroidNumber() );
}

int LOModuleCalc :: GetScanStep( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetScanStep() );
}

int LOModuleCalc :: GetIfExtraRadius( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetIfExtraRadius() );
}

double LOModuleCalc :: GetExtraRadius( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetExtraRadius() );
}

double LOModuleCalc :: GetET_UT( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetET_UT() );
}

double LOModuleCalc :: GetUT_UTC( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetUT_UTC() );
}

double LOModuleCalc :: GetMinA( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetMinA() );
}

double LOModuleCalc :: GetMaxA( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetMaxA() );
}

double LOModuleCalc :: GetMinDiameter( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetMinDiameter() );
}

double LOModuleCalc :: GetMaxDiameter( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetMaxDiameter() );
}

int LOModuleCalc :: GetOutputType( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetOutputType() );
}

const std::string & LOModuleCalc :: GetSitesFilePath( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetSitesFilePath() );
}

int LOModuleCalc :: GetIfMySQL( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetIfMySQL() );
}

int LOModuleCalc :: GetIfPicture( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetIfPicture() );
}

int LOModuleCalc :: GetIfPath( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetIfPath() );
}

double LOModuleCalc :: GetSunElev( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetSunElev() );
}

int LOModuleCalc :: GetStartSQLNumber( void ) const
{
  return( GetLOCalcSubModuleApplPtr()->GetStartSQLNumber() );
}

}}

//---------------------------- End of file ---------------------------
