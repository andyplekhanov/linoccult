//------------------------------------------------------------------------------
//
// File:    loAstOrbReadSubModule.cc
//
// Purpose: Submodule for asteroid orbits reader.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
//         version 0.2 26.05.2004 AsteroidNumber parameter
//         version 0.3 05.03.2005  StartAsteroidNumber, EndAsteroidNumber were added
//         version 0.4 17.04.2005 UpdatesExpirePeriod was added
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
#include "loAstOrbReadSubModule.h"
#include "loModuleAstOrbReader.h"

namespace aps {

  namespace apslinoccult {

//======================= LOAstOrbReadSubModule ==========================

LOAstOrbReadSubModule :: LOAstOrbReadSubModule( LOModuleAppl * pOwner ) :
                              APSSubModule( pOwner )
{
}

LOAstOrbReadSubModule :: ~LOAstOrbReadSubModule( void )
{
}

int LOAstOrbReadSubModule :: WarningMessage( const int MsgNumber, const std::string & pMsg, const APSAbsModule * pSubModule ) const
{
  switch( MsgNumber ) {
    case LO_AST_ORB_READER_ASTEROID_ID: 
      return( apslib::MODULE_CONTINUE );
    case LO_AST_ORB_READER_DIAMETER: 
      return( apslib::MODULE_CONTINUE );
    case LO_AST_ORB_READER_COLOR: 
      return( apslib::MODULE_CONTINUE );
    default:;
  }

  return( APSSubModule :: WarningMessage( MsgNumber, pMsg, pSubModule ) );
}

const LOModuleAppl * LOAstOrbReadSubModule :: GetLOModuleApplPtr( void ) const
{
  return( static_cast<const LOModuleAppl *>( GetOwnerPtr() ) );
}

int LOAstOrbReadSubModule :: GetAsteroidNumber( void ) const
{
  return( GetLOModuleApplPtr()->GetAsteroidNumber() );
}

int LOAstOrbReadSubModule :: GetIfOneAsteroid( void ) const
{
  return( GetLOModuleApplPtr()->GetIfOneAsteroid() );
}

double LOAstOrbReadSubModule :: GetObservationEpoch( void ) const
{
  return( GetLOModuleApplPtr()->GetObservationEpoch() );
}

double LOAstOrbReadSubModule :: GetOrbitM( void ) const
{
  return( GetLOModuleApplPtr()->GetOrbitM() );
}

double LOAstOrbReadSubModule :: GetOrbitW( void ) const
{
  return( GetLOModuleApplPtr()->GetOrbitW() );
}

double LOAstOrbReadSubModule :: GetOrbitO( void ) const
{
  return( GetLOModuleApplPtr()->GetOrbitO() );
}

double LOAstOrbReadSubModule :: GetOrbitI( void ) const
{
  return( GetLOModuleApplPtr()->GetOrbitI() );
}

double LOAstOrbReadSubModule :: GetOrbitE( void ) const
{
  return( GetLOModuleApplPtr()->GetOrbitE() );
}

double LOAstOrbReadSubModule :: GetOrbitA( void ) const
{
  return( GetLOModuleApplPtr()->GetOrbitA() );
}

int LOAstOrbReadSubModule :: GetStartAsteroidNumber( void ) const
{
  return( GetLOModuleApplPtr()->GetStartAsteroidNumber() );
}

int LOAstOrbReadSubModule :: GetEndAsteroidNumber( void ) const
{
  return( GetLOModuleApplPtr()->GetEndAsteroidNumber() );
}

int LOAstOrbReadSubModule :: GetUpdatesExpirePeriod( void ) const
{
  return( GetLOModuleApplPtr()->GetUpdatesExpirePeriod() );
}

}}

//---------------------------- End of file ---------------------------
