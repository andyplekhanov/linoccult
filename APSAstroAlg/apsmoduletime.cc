//------------------------------------------------------------------------------
//
// File:    apsmoduletime.cc
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

#include "apsmoduletime.h"
#include "apstimetaiutcsubmodule.h"
#include "apstimeetutsubmodule.h"

namespace aps {

  namespace apsastroalg {

//================================== APSModuleTime =================================

APSModuleTime :: APSModuleTime( APSSubModule * pAPSSubModule ) :
                 APSModule( "APSModuleTime", pAPSSubModule )
{
  pAPSTimeTaiUtcSubModule = new APSTimeTaiUtcSubModule( this );
  pAPSTimeEtUtSubModule = new APSTimeEtUtSubModule( this );
}

APSModuleTime :: ~APSModuleTime( void )
{
  delete pAPSTimeEtUtSubModule;
  delete pAPSTimeTaiUtcSubModule;
}

const std::string APSModuleTime :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case APS_TIME_NO_ERROR:
      return("No error.\n");
    case APS_TIME_NITUTC:
      return("timnf: Duration in seconds of the previous day conversion error\n.");
    case APS_TIME_RENOM:
      return("timnf: Renormalization of time error.\n");
    case APS_TIME_NITMAX:
      return("timnf: Trivial case conversion error.\n");
    case APS_TIME_CVTTIM1:
      return("cnvtim: timnf( mjd2, sec2, scale )\n");
    case APS_TIME_CVTTIM2:
      return("cnvtim: delta_t1\n");
    case APS_TIME_CVTTIM3:
      return("cnvtim: delta_t2\n");
    case APS_TIME_CVTTIM4:
      return("cnvtim: ET -> UT1 error\n");
    case APS_TIME_CVTTIM5:
      return("cnvtim: TAI -> UTC error1\n");
    case APS_TIME_CVTTIM6:
      return("cnvtim: UTC -> TAI error\n");
    case APS_TIME_CVTTIM7:
      return("cnvtim: wrong scale.\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

}}

//---------------------------- End of file ---------------------------
