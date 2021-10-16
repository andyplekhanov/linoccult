//------------------------------------------------------------------------------
//
// File:    apstimetaiutcsubmodule.cc
//
// Purpose: Submodule for TAI-UTC for time module.
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

namespace aps {

  namespace apsastroalg {

//======================= APSTimeTaiUtcSubModule ==========================

APSTimeTaiUtcSubModule :: APSTimeTaiUtcSubModule( APSModuleTime * pOwner ) :
                          APSSubModule( pOwner )
{
}

APSTimeTaiUtcSubModule :: ~APSTimeTaiUtcSubModule( void )
{
}

const APSModuleTime * APSTimeTaiUtcSubModule :: GetAPSModuleTimePtr( void ) const
{
  return( static_cast<const APSModuleTime *>( GetOwnerPtr() ) );
}

}}

//---------------------------- End of file ---------------------------
