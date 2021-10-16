//------------------------------------------------------------------------------
//
// File:    testImplementationSubModule.cc
//
// Purpose: Submodule for test program implementation.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 16.02.2004
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

#include "testModuleAppl.h"
#include "testImplementationSubModule.h"

namespace aps {

  namespace testappl {

//======================= TestImplementationSubModule ==========================

TestImplementationSubModule :: TestImplementationSubModule( TestModuleAppl * pOwner ) :
                                                            APSSubModule( pOwner )
{
}

TestImplementationSubModule :: ~TestImplementationSubModule( void )
{
}

int TestImplementationSubModule :: WarningMessage( const int MsgNumber, const std::string & Msg, const APSAbsModule * pSubModule ) const
{
  switch( MsgNumber ) {
    default:;
  }

  return( APSSubModule :: WarningMessage( MsgNumber, Msg, pSubModule ) );
}

const TestModuleAppl * TestImplementationSubModule :: GetTestModuleApplPtr( void ) const
{
  return( static_cast<const TestModuleAppl *>( GetOwnerPtr() ) );
}

int TestImplementationSubModule :: GetInt1( void ) const
{
  return( GetTestModuleApplPtr()->GetInt1() );
}

double TestImplementationSubModule :: GetDouble1( void ) const
{
  return( GetTestModuleApplPtr()->GetDouble1() );
}

const std::string & TestImplementationSubModule :: GetString1( void ) const
{
  return( GetTestModuleApplPtr()->GetString1() );
}

int TestImplementationSubModule :: GetInt2( void ) const
{
  return( GetTestModuleApplPtr()->GetInt2() );
}

double TestImplementationSubModule :: GetDouble2( void ) const
{
  return( GetTestModuleApplPtr()->GetDouble2() );
}

const std::string & TestImplementationSubModule :: GetString2( void ) const
{
  return( GetTestModuleApplPtr()->GetString2() );
}

int TestImplementationSubModule :: GetInt3( void ) const
{
  return( GetTestModuleApplPtr()->GetInt3() );
}

double TestImplementationSubModule :: GetDouble3( void ) const
{
  return( GetTestModuleApplPtr()->GetDouble3() );
}

const std::string & TestImplementationSubModule :: GetString3( void ) const
{
  return( GetTestModuleApplPtr()->GetString3() );
}

}}

//---------------------------- End of file ---------------------------

