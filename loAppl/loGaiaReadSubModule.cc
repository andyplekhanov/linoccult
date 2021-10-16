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

#include "loModuleAppl.h"
#include "loGaiaReadSubModule.h"

namespace aps {

  namespace apslinoccult {

//======================= LOGaiaReadSubModule ==========================

LOGaiaReadSubModule :: LOGaiaReadSubModule( LOModuleAppl * pOwner ) :
                       APSSubModule( pOwner )
{
}

LOGaiaReadSubModule :: ~LOGaiaReadSubModule( void )
{
}

const LOModuleAppl * LOGaiaReadSubModule :: GetLOModuleApplPtr( void ) const
{
  return( static_cast<const LOModuleAppl *>( GetOwnerPtr() ) );
}

double LOGaiaReadSubModule :: GetMaxMv( void ) const
{
  return( GetLOModuleApplPtr()->GetMaxMv() );
}

int LOGaiaReadSubModule :: GetIfOneStar( void ) const
{
  return( GetLOModuleApplPtr()->GetIfOneStar() );
}

int LOGaiaReadSubModule :: GetRA_Hour( void ) const
{
  return( GetLOModuleApplPtr()->GetRA_Hour() );
}

int LOGaiaReadSubModule :: GetRA_Min( void ) const
{
  return( GetLOModuleApplPtr()->GetRA_Min() );
}

double LOGaiaReadSubModule :: GetRA_Sec( void ) const
{
  return( GetLOModuleApplPtr()->GetRA_Sec() );
}

int LOGaiaReadSubModule :: GetDec_Deg( void ) const
{
  return( GetLOModuleApplPtr()->GetDec_Deg() );
}

int LOGaiaReadSubModule :: GetDec_Min( void ) const
{
  return( GetLOModuleApplPtr()->GetDec_Min() );
}

double LOGaiaReadSubModule :: GetDec_Sec( void ) const
{
  return( GetLOModuleApplPtr()->GetDec_Sec() );
}

double LOGaiaReadSubModule :: GetpmRA( void ) const
{
  return( GetLOModuleApplPtr()->GetpmRA() );
}

double LOGaiaReadSubModule :: GetpmDec( void ) const
{
  return( GetLOModuleApplPtr()->GetpmDec() );
}

int LOGaiaReadSubModule :: GetOneStarCatalog( void ) const
{
  return( GetLOModuleApplPtr()->GetOneStarCatalog() );
}

double LOGaiaReadSubModule :: GetOneStarMv( void ) const
{
  return( GetLOModuleApplPtr()->GetOneStarMv() );
}

double LOGaiaReadSubModule :: GetOneStarParallax( void ) const
{
  return( GetLOModuleApplPtr()->GetOneStarParallax() );
}
    
double LOGaiaReadSubModule :: GetVrad( void ) const
{
  return( GetLOModuleApplPtr()->GetVrad() );
}
    
double LOGaiaReadSubModule :: GetEpoch( void ) const
{
  return( GetLOModuleApplPtr()->GetEpoch() );
}
    
}}

//---------------------------- End of file ---------------------------
