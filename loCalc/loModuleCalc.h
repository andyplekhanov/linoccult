//------------------------------------------------------------------------------
//
// File:    loModuleCalc.h
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
//         version 0.7 05.03.2005 StartAsteroidNumber, EndAsteroidNumber, StartSQLNumber were added.
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

#ifndef LO_MODULE_CALC_H
#define LO_MODULE_CALC_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSModule;

class LOCalcSubModule;
class LOChebMakerSubModule;
class LOChebSubModule;
class LOAstOrbSubModule;

enum {
  LO_CALC_NO_ERROR = 0,
  LO_CALC_ASTEROID_ERROR,
  LO_CALC_INTEGRATION,
  LO_CALC_STAR_PROCESSING,
  LO_CALC_ET_UT,
  LO_CALC_START,
  LO_CALC_START_ASTEROID_PROCESSING,
  LO_CALC_FINISH,
  LO_CALC_START_KDTREE,
  LO_CALC_FINISH_KDTREE,
  LO_CALC_KDTREE_BUILD_ERROR,
  LO_CALC_JPL_INIT,
  LO_CALC_TRANSFORM_EPOCH
};

//======================= LOModuleCalc ==========================

class LOModuleCalc : public APSModule
{
  private:

    LOChebMakerSubModule  * pLOChebMakerSubModule;

    LOChebSubModule       * pLOChebSubModule;

    LOAstOrbSubModule     * pLOAstOrbSubModule;

    const LOCalcSubModule * GetLOCalcSubModuleApplPtr( void ) const;

  public:

    LOModuleCalc( LOCalcSubModule * pOwner );

    virtual ~LOModuleCalc( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    LOChebMakerSubModule * GetChebMakerSubModulePtr( void ) const
      { return( pLOChebMakerSubModule ); }

    LOChebSubModule * GetChebSubModulePtr( void ) const
      { return( pLOChebSubModule ); }

    LOAstOrbSubModule * GetAstOrbSubModulePtr( void ) const
      { return( pLOAstOrbSubModule ); }

    const std::string & GetJPLEphemFilePath( void ) const;

    int GetStartYear( void ) const;

    int GetStartMonth( void ) const;

    int GetStartDay( void ) const;

    int GetEndYear( void ) const;

    int GetEndMonth( void ) const;

    int GetEndDay( void ) const;

    int GetAsteroidNumber( void ) const;

    int GetScanStep( void ) const;

    int GetIfExtraRadius( void ) const;

    double GetExtraRadius( void ) const;

    double GetET_UT( void ) const;

    double GetUT_UTC( void ) const;

    double GetMinA( void ) const;

    double GetMaxA( void ) const;

    double GetMinDiameter( void ) const;

    double GetMaxDiameter( void ) const;

    int GetOutputType( void ) const;

    const std::string & GetSitesFilePath( void ) const;

    int GetIfMySQL( void ) const;

    int GetIfPicture( void ) const;

    int GetIfPath( void ) const;

    double GetSunElev( void ) const;

    int GetStartSQLNumber( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------


