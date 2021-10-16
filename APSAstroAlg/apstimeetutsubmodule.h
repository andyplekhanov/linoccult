//------------------------------------------------------------------------------
//
// File:    apstimeetutsubmodule.h
//
// Purpose: Submodule for ET-UT for time module.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1
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

#ifndef APS_TIME_ET_UT_SUB_MODULE_H
#define APS_TIME_ET_UT_SUB_MODULE_H

#include <string>

#include "apssubmodule.h"

namespace aps {

  namespace apsastroalg {

using apslib::APSSubModule;

class APSModuleTime;

//======================= APSTimeEtUtSubModule ==========================

class APSTimeEtUtSubModule : public APSSubModule
{
  public:

    APSTimeEtUtSubModule( APSModuleTime * pOwner );

    virtual ~APSTimeEtUtSubModule( void );

    const APSModuleTime * GetAPSModuleTimePtr( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
