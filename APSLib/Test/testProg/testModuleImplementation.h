//------------------------------------------------------------------------------
//
// File:    testModuleImplementation.h
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

#ifndef TEST_MODULE_IMPLEMENTATION_H
#define TEST_MODULE_IMPLEMENTATION_H

#include "apsmodule.h"

namespace aps {

  namespace testappl {

class TestImplementationSubModule;

enum {
  TEST_IMPLEMENTATION_NO_ERROR = 0,
  TEST_IMPLEMENTATION_HELLO
};

using apslib::APSModule;

//======================= TestModuleImplementation ==========================

class TestModuleImplementation : public APSModule
{
  private:

    const TestImplementationSubModule * GetTestImplementationSubModulePtr( void ) const;

  public:

    TestModuleImplementation( TestImplementationSubModule * pOwner );

    virtual ~TestModuleImplementation( void );

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    int GetInt1( void ) const;

    double GetDouble1( void ) const;

    const std::string & GetString1( void ) const;

    int GetInt2( void ) const;

    double GetDouble2( void ) const;

    const std::string & GetString2( void ) const;

    int GetInt3( void ) const;

    double GetDouble3( void ) const;

    const std::string & GetString3( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
