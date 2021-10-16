//------------------------------------------------------------------------------
//
// File:    testappl.cc
//
// Purpose: Test application
//          Main program
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

#include <iostream>

#include "testAppl.h"

int main( int argc, char * argv[] )
{
  int        RetCode = 0;

  if( argc == 2 ) {
    aps::testappl::TestAppl * pTestAppl = new aps::testappl::TestAppl( argv[ 1 ] );

    RetCode = pTestAppl->Run();

    if( RetCode ) {
      RetCode = 2;
    }

    delete pTestAppl;
  }
  else {
    std::cout << "Usage: " << argv[ 0 ] << " <project.config>" << std::endl;    
    RetCode = 1;
  }

  return( RetCode );
}
