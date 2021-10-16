//------------------------------------------------------------------------------
//
// File:    testAppl.cc
//
// Purpose: Implementation of the test application
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.01.2004
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

#include "testAppl.h"
#include "testModuleAppl.h"
#include "testImplementation.h"

namespace aps {

  namespace testappl {

const int X_Version          = 1;
const int Y_Version          = 0;
const int Z_Version          = 0;
const int FirstCopyRightYear = 2004;
const int CopyRightYear      = 2006;
const apslib::APS_PROGRAM_VERSION_TYPE VersionType = apslib::APS_BETA_VERSION; //APS_NORMAL_VERSION;

//======================= TestAppl ==========================

TestAppl :: TestAppl( const std::string & ProjectFilePath )
{
  pModule = new TestModuleAppl( ProjectFilePath, "TestApplication", X_Version, Y_Version, Z_Version, FirstCopyRightYear, CopyRightYear, VersionType );
}

TestAppl :: ~TestAppl( void )
{
  delete pModule;
}

int TestAppl :: Run( void )
{
  TestImplementation * pTestImplementation;
  int                  RetCode;

  RetCode = pModule->Run();

  if( !RetCode ) {
    pTestImplementation = new TestImplementation( pModule->GetTestImplementationSubModulePtr() );

    RetCode = pTestImplementation->Run();

    if( !RetCode ) {

    }
    else {
      RetCode = TEST_APPL_IMPLEMENTATION;
    }

    delete pTestImplementation;

  }
  else {
    RetCode = TEST_APPL_MODULE;    
  }

  pModule->InfoMessage( TEST_APPL_FINISH );

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------

