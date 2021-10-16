//------------------------------------------------------------------------------
//
// File:    apsmoduletime.h
//
// Purpose: Module for time processing.
//   
// (c) Plekhanov Andrey
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

#ifndef APS_MODULE_TIME_H
#define APS_MODULE_TIME_H

#include <string>

#include "apsmodule.h"

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apsastroalg {

using apslib::APSModule;
using apslib::APSSubModule;

class APSTimeTaiUtcSubModule;
class APSTimeEtUtSubModule;

enum {
  APS_TIME_NO_ERROR = 0,
  APS_TIME_NITUTC,
  APS_TIME_RENOM,
  APS_TIME_NITMAX,
  APS_TIME_CVTTIM1,
  APS_TIME_CVTTIM2,
  APS_TIME_CVTTIM3,
  APS_TIME_CVTTIM4,
  APS_TIME_CVTTIM5,
  APS_TIME_CVTTIM6,
  APS_TIME_CVTTIM7,
  APS_TIME_CVTTIM8
};

//======================= APSModuleTime ==========================

class APSModuleTime : public APSModule
{
  private:

    APSTimeTaiUtcSubModule * pAPSTimeTaiUtcSubModule;
    APSTimeEtUtSubModule   * pAPSTimeEtUtSubModule;

  public:

    APSModuleTime( APSSubModule * pAPSSubModule );

    virtual ~APSModuleTime( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    APSTimeTaiUtcSubModule * GetTimeTaiUtcSubModulePtr( void ) const
      { return( pAPSTimeTaiUtcSubModule ); }

    APSTimeEtUtSubModule * GetTimeEtUtSubModulePtr( void ) const
      { return( pAPSTimeEtUtSubModule ); }
};

}}

#endif

//---------------------------- End of file ---------------------------
