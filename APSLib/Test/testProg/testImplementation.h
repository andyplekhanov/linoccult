//------------------------------------------------------------------------------
//
// File:    testImplementation.h
//
// Purpose: Main test program
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

#ifndef TEST_IMPLEMENTATION_H
#define TEST_IMPLEMENTATION_H

namespace aps {

  namespace testappl {

class TestModuleImplementation;
class TestImplementationSubModule;

//======================= TestImplementation ==========================

class TestImplementation
{
  private:

    TestModuleImplementation * pModule;

  public:

    TestImplementation( TestImplementationSubModule * pTestImplementationSubModule );

    virtual ~TestImplementation( void );

    int Run( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
