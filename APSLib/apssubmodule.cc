//------------------------------------------------------------------------------
//
// File:    apssubmodule.cc
//
// Purpose: Submodule support
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.04.2004
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

#include "apssubmodule.h"
#include "apsmodule.h"

namespace aps {

  namespace apslib {

const static std::string UnknownName = "Unknown";

APSSubModule :: APSSubModule( APSModule * apOwner ) : APSAbsModule(),
                pOwner( apOwner ), pSubModule( 0 )
{
}

APSSubModule :: ~APSSubModule( void )
{
}

const std::string & APSSubModule :: GetModuleName( void ) const
{
  if( pSubModule ) {
    return( pSubModule->GetModuleName() );
  }
  else {
    return( UnknownName );
  }
}

int APSSubModule :: InfoMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  return( pOwner->InfoMessage( MsgNumber, Msg, pSubModule ) );
}

int APSSubModule :: WarningMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  return( pOwner->WarningMessage( MsgNumber, Msg, pSubModule ) );
}

int APSSubModule :: ErrorMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  return( pOwner->ErrorMessage( MsgNumber, Msg, pSubModule ) );
}

int APSSubModule :: DebugMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  return( pOwner->DebugMessage( MsgNumber, Msg, pSubModule ) );
}

int APSSubModule :: StrMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  return( pOwner->StrMessage( MsgNumber, Msg, pSubModule ) );
}

const std::string APSSubModule :: GetMessageText( const int MsgNumber ) const
{
  if( pSubModule ) {
    return( pSubModule->GetMessageText( MsgNumber ) );
  }
  else {
    return("Unknown message");
  }
}

}}

//---------------------------- End of file ---------------------------
