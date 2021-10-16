//------------------------------------------------------------------------------
//
// File:    testModuleImplementation.cc
//
// Purpose: Module test application.
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

#include "testModuleImplementation.h"
#include "testImplementationSubModule.h"

namespace aps {

  namespace testappl {

//================================== TestModuleImplementation =================================

TestModuleImplementation :: TestModuleImplementation( TestImplementationSubModule * pOwner ) :
                            APSModule( "TestImplementation", pOwner )
{
}

TestModuleImplementation :: ~TestModuleImplementation( void )
{
}

const std::string TestModuleImplementation :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case TEST_IMPLEMENTATION_NO_ERROR:
      return("No error.\n");
    case TEST_IMPLEMENTATION_HELLO:
      return("Hello world.\n");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

const TestImplementationSubModule * TestModuleImplementation :: GetTestImplementationSubModulePtr( void ) const
{
  return( static_cast<const TestImplementationSubModule *>( GetOwnerPtr() ) );
}

int TestModuleImplementation :: GetInt1( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetInt1() );
}

double TestModuleImplementation :: GetDouble1( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetDouble1() );
}

const std::string & TestModuleImplementation :: GetString1( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetString1() );
}

int TestModuleImplementation :: GetInt2( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetInt2() );
}

double TestModuleImplementation :: GetDouble2( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetDouble2() );
}

const std::string & TestModuleImplementation :: GetString2( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetString2() );
}

int TestModuleImplementation :: GetInt3( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetInt3() );
}

double TestModuleImplementation :: GetDouble3( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetDouble3() );
}

const std::string & TestModuleImplementation :: GetString3( void ) const
{
  return( GetTestImplementationSubModulePtr()->GetString3() );
}

}}

//---------------------------- End of file ---------------------------



