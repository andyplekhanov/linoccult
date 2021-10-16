//------------------------------------------------------------------------------
//
// File:    testConfig.cc
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

#include "testConfig.h"

namespace aps {

  namespace testappl {

TestConfig :: TestConfig( void ) : APSConfig()
{
  AddParameter( "IntValue1", apslib::PARAM_INTEGER );
  AddParameter( "DoubleValue1", apslib::PARAM_DOUBLE );
  AddParameter( "StringValue1", apslib::PARAM_STRING );
  AddParameter( "IntValue2", apslib::PARAM_INTEGER );
  AddParameter( "DoubleValue2", apslib::PARAM_DOUBLE );
  AddParameter( "StringValue2", apslib::PARAM_STRING );
  AddParameter( "IntValue3", apslib::PARAM_INTEGER );
  AddParameter( "DoubleValue3", apslib::PARAM_DOUBLE );
  AddParameter( "StringValue3", apslib::PARAM_STRING );
}

TestConfig :: ~TestConfig( void )
{
}

int TestConfig :: GetInt1( int & IntValue ) const
{
  return( GetIntegerValue( "IntValue1", IntValue ) );
}

int TestConfig :: GetDouble1( double & DoubleValue ) const
{
  return( GetDoubleValue( "DoubleValue1", DoubleValue ) );
}

int TestConfig :: GetString1( std::string & StringValue ) const
{
  return( GetStringValue( "StringValue1", StringValue ) );
}

int TestConfig :: GetInt2( int & IntValue ) const
{
  return( GetIntegerValue( "IntValue2", IntValue ) );
}

int TestConfig :: GetDouble2( double & DoubleValue ) const
{
  return( GetDoubleValue( "DoubleValue2", DoubleValue ) );
}

int TestConfig :: GetString2( std::string & StringValue ) const
{
  return( GetStringValue( "StringValue2", StringValue ) );
}

int TestConfig :: GetInt3( int & IntValue ) const
{
  return( GetIntegerValue( "IntValue3", IntValue ) );
}

int TestConfig :: GetDouble3( double & DoubleValue ) const
{
  return( GetDoubleValue( "DoubleValue3", DoubleValue ) );
}

int TestConfig :: GetString3( std::string & StringValue ) const
{
  return( GetStringValue( "StringValue3", StringValue ) );
}

}}

//---------------------------- End of file ---------------------------

