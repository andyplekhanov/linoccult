//------------------------------------------------------------------------------
//
// File:    testAppl.h
//
// Purpose: Header for test application
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

#ifndef TEST_APPL_H
#define TEST_APPL_H

#include <string>

namespace aps {

  namespace testappl {

class TestModuleAppl;

//======================= TestAppl ==========================

class TestAppl
{
  private:

    TestModuleAppl * pModule;

  public:

    TestAppl( const std::string & ProjectFilePath );

    virtual ~TestAppl( void );

    int Run( void );
};

}}

#endif

//---------------------------- End of file ---------------------------


