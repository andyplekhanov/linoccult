//------------------------------------------------------------------------------
//
// File:    testConfig.h
//
// Purpose: Test application config parameters
//   
// (c) 2004 Plekhanov Andrey
//
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

#ifndef 	_TESTCONFIG_H_
#define         _TESTCONFIG_H_	1

#include "apsconfig.h"

namespace aps {

  namespace testappl {

using apslib::APSConfig;

//------------------------------- TestConfig ---------------------------------

class TestConfig : public APSConfig
{
  public:

    TestConfig( void );

    virtual ~TestConfig( void );

    int GetInt1( int & IntValue ) const;

    int GetDouble1( double & DoubleValue ) const;

    int GetString1( std::string & StringValue ) const;

    int GetInt2( int & IntValue ) const;

    int GetDouble2( double & DoubleValue ) const;

    int GetString2( std::string & StringValue ) const;

    int GetInt3( int & IntValue ) const;

    int GetDouble3( double & DoubleValue ) const;

    int GetString3( std::string & StringValue ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------


