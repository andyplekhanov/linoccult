//------------------------------------------------------------------------------
//
// File:    loAbsEventDataIO.cc
//
// Purpose: Class for occultation events data base input/output for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 09.01.2005
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

#include "loAbsEventDataIO.h"

namespace aps {

  namespace apslinoccult {

DescriptorType LOAbsEventDataIO :: Descriptor = 0x0F0F0F0F;

LOAbsEventDataIO :: LOAbsEventDataIO( void )
{
}

LOAbsEventDataIO :: ~LOAbsEventDataIO( void )
{
}

int LOAbsEventDataIO :: IfInInterval( const double MjdStart, const double MjdEnd,
                                      const double BeginOccTime, const double EndOccTime ) const
{
  if( BeginOccTime > MjdEnd ) {
    return( 0 );
  }

  if( EndOccTime < MjdStart ) {
    return( 0 );
  }

  return( 1 );
}

}}

//---------------------------- End of file ---------------------------
