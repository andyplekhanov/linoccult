//------------------------------------------------------------------------------
//
// File:    apsmodule.cc
//
// Purpose: Module support
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.04.2004
//         version 0.2 16.12.2004 Check ( apOwner == 0 )
//         version 0.3 12.02.2005 FindMainModule was added
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

#include <sstream>
#include <iostream>

#include "apsmodule.h"
#include "apssubmodule.h"
#include "apsmainmodule.h"

namespace aps {

  namespace apslib {

APSModule :: APSModule( const std::string & aModuleName, APSSubModule * apOwner ) :
                        APSAbsModule(), ModuleName( aModuleName ), pOwner( apOwner )
{
  if( apOwner ) {
    apOwner->SetSubModule( this );
  }
}

APSModule :: ~APSModule( void )
{
  if( pOwner ) {
    pOwner->SetSubModule( 0 );
  }
}

const APSMainModule * APSModule :: FindMainModule( void ) const
{
  const APSModule     * pModule;
  const APSSubModule  * pSubModule;
  const APSMainModule * pMainModule;

  pModule    = this;
  pSubModule = GetOwnerPtr();

  while( pSubModule ) {
    pModule    = pSubModule->GetOwnerPtr();
    pSubModule = pModule->GetOwnerPtr();
  }

  pMainModule = dynamic_cast<const APSMainModule *>( pModule );

  return( pMainModule );
}

const std::string & APSModule :: GetModuleName( void ) const
{
  return( ModuleName );
}

int APSModule :: InfoMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  std::ostringstream MsgText;
  int                RetCode = MODULE_CONTINUE;

  if( pOwner ) {
    if( pSubModule ) {
      RetCode = pOwner->InfoMessage( MsgNumber, Msg, pSubModule );
    }
    else {
      RetCode = pOwner->InfoMessage( MsgNumber, Msg, this );
    }
  }
  else {
    if( pSubModule ) {
      if( Msg == "" ) {
        MsgText << "INFO: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber );
      }
      else {
        MsgText << "INFO: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
    else {
      if( Msg == "" ) {
        MsgText << "INFO: " << GetModuleName() << " " << GetMessageText( MsgNumber );
      }
      else {
        MsgText << "INFO: " << GetModuleName() << " " << GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
  }

  return( RetCode );
}

int APSModule :: WarningMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  std::ostringstream MsgText;
  int                RetCode = MODULE_CONTINUE;

  if( pOwner ) {
    if( pSubModule ) {
      RetCode = pOwner->WarningMessage( MsgNumber, Msg, pSubModule );
    }
    else {
      RetCode = pOwner->WarningMessage( MsgNumber, Msg, this );
    }
  }
  else {
    if( pSubModule ) {
      if( Msg == "" ) {
        MsgText << "WARNING: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber );
      }
      else {
        MsgText << "WARNING: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
    else {
      if( Msg == "" ) {
        MsgText << "WARNING: " << GetModuleName() << " " << GetMessageText( MsgNumber );
      }
      else {
        MsgText << "WARNING: " << GetModuleName() << " " << GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
  }

  return( RetCode );
}

int APSModule :: ErrorMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  std::ostringstream MsgText;
  int                RetCode = MODULE_STOP;

  if( pOwner ) {
    if( pSubModule ) {
      RetCode = pOwner->ErrorMessage( MsgNumber, Msg, pSubModule );
    }
    else {
      RetCode = pOwner->ErrorMessage( MsgNumber, Msg, this );
    }
  }
  else {
    if( pSubModule ) {
      if( Msg == "" ) {
        MsgText << "ERROR: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber );
      }
      else {
        MsgText << "ERROR: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
    else {
      if( Msg == "" ) {
        MsgText << "ERROR: " << GetModuleName() << " " << GetMessageText( MsgNumber );
      }
      else {
        MsgText << "ERROR: " << GetModuleName() << " " << GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
  }

  return( RetCode );
}

int APSModule :: DebugMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  std::ostringstream MsgText;
  int                RetCode = MODULE_CONTINUE;

  if( pOwner ) {
    if( pSubModule ) {
      RetCode = pOwner->DebugMessage( MsgNumber, Msg, pSubModule );
    }
    else {
      RetCode = pOwner->DebugMessage( MsgNumber, Msg, this );
    }
  }
  else {
    if( pSubModule ) {
      if( Msg == "" ) {
        MsgText << "DEBUG: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber );
      }
      else {
        MsgText << "DEBUG: " << pSubModule->GetModuleName() << " " << pSubModule->GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
    else {
      if( Msg == "" ) {
        MsgText << "DEBUG: " << GetModuleName() << " " << GetMessageText( MsgNumber );
      }
      else {
        MsgText << "DEBUG: " << GetModuleName() << " " << GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
  }

  return( RetCode );
}

int APSModule :: StrMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  std::ostringstream MsgText;
  int                RetCode = MODULE_CONTINUE;

  if( pOwner ) {
    if( pSubModule ) {
      RetCode = pOwner->StrMessage( MsgNumber, Msg, pSubModule );
    }
    else {
      RetCode = pOwner->StrMessage( MsgNumber, Msg, this );
    }
  }
  else {
    if( pSubModule ) {
      if( Msg == "" ) {
        MsgText << pSubModule->GetMessageText( MsgNumber );
      }
      else {
        MsgText << pSubModule->GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
    else {
      if( Msg == "" ) {
        MsgText << GetMessageText( MsgNumber );
      }
      else {
        MsgText << GetMessageText( MsgNumber ) << " " << Msg;
      }

      PutMessage( MsgText.str() );
    }
  }

  return( RetCode );
}

const std::string APSModule :: GetMessageText( const int MsgNumber ) const
{
  std::ostringstream MsgText;

  MsgText << MsgNumber << std::endl;

  return( MsgText.str() );
}

void APSModule :: PutMessage( const std::string & Msg ) const
{
  std::cout << Msg;
  std::cout.flush();
}

}}

//---------------------------- End of file ---------------------------
