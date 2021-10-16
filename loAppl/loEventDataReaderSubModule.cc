//------------------------------------------------------------------------------
//
// File:    loEventDataReaderSubModule.h
//
// Purpose: Submodule for reading occultation events data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 13.02.2005
//         version 0.2 15.02.2005 InputEventsFilePath was added
//         version 0.3 22.02.2005 InputEventsFilePath was removed.
//                                StartYear, StartMonth, StartDay, EndYear, EndMonth, EndDay
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
#include "loEventDataReaderSubModule.h"

namespace aps {

  namespace apslinoccult {

//======================= LOEventDataReaderSubModule ==========================

LOEventDataReaderSubModule :: LOEventDataReaderSubModule( LOModuleAppl * pOwner ) :
                              APSSubModule( pOwner )
{
}

LOEventDataReaderSubModule :: ~LOEventDataReaderSubModule( void )
{
}

const LOModuleAppl * LOEventDataReaderSubModule :: GetLOModuleApplPtr( void ) const
{
  return( static_cast<const LOModuleAppl *>( GetOwnerPtr() ) );
}

int LOEventDataReaderSubModule :: GetStartYear( void ) const
{
  return( GetLOModuleApplPtr()->GetStartYear() );
}

int LOEventDataReaderSubModule :: GetStartMonth( void ) const
{
  return( GetLOModuleApplPtr()->GetStartMonth() );
}

int LOEventDataReaderSubModule :: GetStartDay( void ) const
{
  return( GetLOModuleApplPtr()->GetStartDay() );
}

int LOEventDataReaderSubModule :: GetEndYear( void ) const
{
  return( GetLOModuleApplPtr()->GetEndYear() );
}

int LOEventDataReaderSubModule :: GetEndMonth( void ) const
{
  return( GetLOModuleApplPtr()->GetEndMonth() );
}

int LOEventDataReaderSubModule :: GetEndDay( void ) const
{
  return( GetLOModuleApplPtr()->GetEndDay() );
}

}}

//---------------------------- End of file ---------------------------
