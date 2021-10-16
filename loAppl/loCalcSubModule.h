//------------------------------------------------------------------------------
//
// File:    loCalcSubModule.h
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

#ifndef LO_CALC_SUB_MODULE_H
#define LO_CALC_SUB_MODULE_H

#include <string>

#include "apssubmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSSubModule;

class LOModuleAppl;

//======================= LOCalcSubModule ==========================

class LOCalcSubModule : public APSSubModule
{
  private:

    const LOModuleAppl * GetLOModuleApplPtr( void ) const;

  public:

    LOCalcSubModule( LOModuleAppl * pOwner );

    virtual ~LOCalcSubModule( void );

    virtual int WarningMessage( const int MsgNumber, const std::string & pMsg, const APSAbsModule * pSubModule ) const;

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
