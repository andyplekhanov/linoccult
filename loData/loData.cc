//------------------------------------------------------------------------------
//
// File:    loData.cc
//
// Purpose: LinOccult data.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 02.02.2004
//         version 0.2 15.01.2005 BuildKDTree has been added
//         version 0.3 07.02.2005 Events were added
//         version 0.4 17.02.2005 Positions were added
//         version 0.5 27.02.2005 LOPointEventData was added
//         version 0.6 17.04.2005 LOUpdateData was added
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

#include "loData.h"
#include "loAstOrbData.h"
#include "loStarData.h"
#include "loEventData.h"
#include "loPosData.h"
#include "loPointEventData.h"
#include "loUpdateData.h"

namespace aps {

  namespace apslinoccult {

//======================= LOData ==========================

LOData :: LOData( void ) : pLOAstOrbData( 0 ),
                           pLOStarData( 0 ),
                           pLOEventData( 0 ),
                           pLOPosData( 0 ),
                           pLOPointEventData( 0 ),
                           pLOUpdateData( 0 )
{
}

LOData :: ~LOData( void )
{
  if( pLOAstOrbData ) {
    delete pLOAstOrbData;
  }

  if( pLOStarData ) {
    delete pLOStarData;
  }

  if( pLOEventData ) {
    delete pLOEventData;
  }

  if( pLOPosData ) {
    delete pLOPosData;
  }

  if( pLOPointEventData ) {
    delete pLOPointEventData;
  }

  if( pLOUpdateData ) {
    delete pLOUpdateData;
  }
}

LOAstOrbData * LOData :: CreateAstOrbData( const unsigned int AsteroidsNumber )
{
  if( !pLOAstOrbData ) {
    pLOAstOrbData = new LOAstOrbData( AsteroidsNumber );
  }

  return( pLOAstOrbData );
}

LOStarData * LOData :: CreateStarData( const unsigned int StarsNumber )
{
  if( !pLOStarData ) {
    pLOStarData = new LOStarData( StarsNumber );
  }

  return( pLOStarData );
}

LOEventData * LOData :: CreateEventData( void )
{
  if( !pLOEventData ) {
    pLOEventData = new LOEventData();
  }

  return( pLOEventData );
}

LOPosData * LOData :: CreatePosData( void )
{
  if( !pLOPosData ) {
    pLOPosData = new LOPosData();
  }

  return( pLOPosData );
}

LOPointEventData * LOData :: CreatePointEventData( void )
{
  if( !pLOPointEventData ) {
    pLOPointEventData = new LOPointEventData();
  }

  return( pLOPointEventData );
}

LOUpdateData * LOData :: CreateUpdateData( void )
{
  if( !pLOUpdateData ) {
    pLOUpdateData = new LOUpdateData();
  }

  return( pLOUpdateData );
}

int LOData :: BuildKDTree( void ) const
{
  int RetCode;

  RetCode = 0;

  if( pLOStarData ) {
    if( pLOStarData->BuildKDTree() ) {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
