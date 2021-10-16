//------------------------------------------------------------------------------
//
// File:    loGaiaReadSubModule.h
//
// Purpose: Submodule for Gaia catalog reader.
//   
// (c) 2004-2021 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
// Gaia EDR3       0.2 10.01.2021
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

#ifndef LO_GAIA_READ_SUB_MODULE_H
#define LO_GAIA_READ_SUB_MODULE_H

#include "apssubmodule.h"

namespace aps {

  namespace apslinoccult {

using apslib::APSSubModule;

class LOModuleAppl;

//======================= LOGaiaReadSubModule ==========================

class LOGaiaReadSubModule : public APSSubModule
{
  private:

    const LOModuleAppl * GetLOModuleApplPtr( void ) const;

  public:

    LOGaiaReadSubModule( LOModuleAppl * pOwner );

    virtual ~LOGaiaReadSubModule( void );

    double GetMaxMv( void ) const;

    int GetIfOneStar( void ) const;

    int GetRA_Hour( void ) const;

    int GetRA_Min( void ) const;

    double GetRA_Sec( void ) const;

    int GetDec_Deg( void ) const;

    int GetDec_Min( void ) const;

    double GetDec_Sec( void ) const;

    double GetpmRA( void ) const;

    double GetpmDec( void ) const;

    int GetOneStarCatalog( void ) const;

    double GetOneStarMv( void ) const;

    double GetOneStarParallax( void ) const;
    
    double GetVrad( void ) const;
    
    double GetEpoch( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
