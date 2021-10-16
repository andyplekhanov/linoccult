//------------------------------------------------------------------------------
//
// File:    testModuleAppl.cc
//
// Purpose: Module for Test application.
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
#include <iostream>
#include <sstream>

#include "apsreadcfg.h"
#include "testModuleAppl.h"
#include "testImplementationSubModule.h"
#include "testConfigReadSubModule.h"
#include "testConfig.h"

namespace aps {

  namespace testappl {

using apslib::APSReadConfig;

const std::string MAIN_CONFIG_PATH = "test.config";

//======================= TestModuleAppl ==========================

TestModuleAppl :: TestModuleAppl( const std::string & aProjectFilePath,
                                  const std::string & aModuleName,
                                  const int X_Version,
                                  const int Y_Version,
                                  const int Z_Version,
                                  const int FirstCopyRightYear,
                                  const int CopyRightYear,
                                  const apslib::APS_PROGRAM_VERSION_TYPE VersionType ) :
                  APSMainModule( aModuleName, X_Version, Y_Version, Z_Version,
                                 FirstCopyRightYear, CopyRightYear, VersionType ),
                                 ProjectFilePath( aProjectFilePath )
{
  pTestImplementationSubModule = new TestImplementationSubModule( this );
  pTestConfigReadSubModule     = new TestConfigReadSubModule( this );

  IntValue1    = 1;
  DoubleValue1 = 10.0;
  StringValue1 = "DefaultString1";
  IntValue2    = 2;
  DoubleValue2 = 20.0;
  StringValue2 = "DefaultString2";
  IntValue3    = 3;
  DoubleValue3 = 30.0;
  StringValue3 = "DefaultString3";

  OriginIntValue1    = TEST_APPL_PARAM_DEFAULT;
  OriginDoubleValue1 = TEST_APPL_PARAM_DEFAULT;
  OriginStringValue1 = TEST_APPL_PARAM_DEFAULT;
  OriginIntValue2    = TEST_APPL_PARAM_DEFAULT;
  OriginDoubleValue2 = TEST_APPL_PARAM_DEFAULT;
  OriginStringValue2 = TEST_APPL_PARAM_DEFAULT;
  OriginIntValue3    = TEST_APPL_PARAM_DEFAULT;
  OriginDoubleValue3 = TEST_APPL_PARAM_DEFAULT;
  OriginStringValue3 = TEST_APPL_PARAM_DEFAULT;
}

TestModuleAppl :: ~TestModuleAppl( void )
{
  delete pTestConfigReadSubModule;
  delete pTestImplementationSubModule;
}

bool TestModuleAppl :: IfIntValue1( void ) const
{
  if( OriginIntValue1 == TEST_APPL_PARAM_DEFAULT ) {
    return( false );
  }

  return( true );
}

bool TestModuleAppl :: IfDoubleValue1( void ) const
{
  if( OriginDoubleValue1 == TEST_APPL_PARAM_DEFAULT ) {
    return( false );
  }

  return( true );
}

bool TestModuleAppl :: IfStringValue1( void ) const
{
  if( OriginStringValue1 == TEST_APPL_PARAM_DEFAULT ) {
    return( false );
  }

  return( true );
}

bool TestModuleAppl :: IfStringValue3( void ) const
{
  if( OriginStringValue3 == TEST_APPL_PARAM_DEFAULT ) {
    return( false );
  }

  return( true );
}

const std::string TestModuleAppl :: GetMessageText( const int MsgNumber ) const
{
  switch( MsgNumber ) {
    case TEST_APPL_NO_ERR:
      return("No error.\n");
    case TEST_APPL_IMPLEMENTATION:
      return("Error in implementation module.\n");
    case TEST_APPL_START:
      return("  Test program started.\n");
    case TEST_APPL_FINISH:
      return("  Test program finished.\n");
    case TEST_APPL_MODULE:
      return("Init module.\n");
    case TEST_APPL_SHOW_PARAM:
      return("");
    default:;
  }

  return( APSModule :: GetMessageText( MsgNumber ) );
}

void TestModuleAppl :: PrintParameters( void ) const
{
  if( OriginIntValue1 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IntValue1 from file " << MAIN_CONFIG_PATH << ": " << IntValue1 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginIntValue1 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IntValue1 from file " << ProjectFilePath << ": " << IntValue1 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginDoubleValue1 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter DoubleValue1 from file " << MAIN_CONFIG_PATH << ": " << DoubleValue1 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginDoubleValue1 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter DoubleValue1 from file " << ProjectFilePath << ": " << DoubleValue1 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStringValue1 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StringValue1 from file " << MAIN_CONFIG_PATH << ": " << StringValue1 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginStringValue1 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StringValue1 from file " << ProjectFilePath << ": " << StringValue1 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIntValue2 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IntValue2 from file " << MAIN_CONFIG_PATH << ": " << IntValue2 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginIntValue2 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IntValue2 from file " << ProjectFilePath << ": " << IntValue2 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginDoubleValue2 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter DoubleValue2 from file " << MAIN_CONFIG_PATH << ": " << DoubleValue2 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginDoubleValue2 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter DoubleValue2 from file " << ProjectFilePath << ": " << DoubleValue2 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStringValue2 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StringValue2 from file " << MAIN_CONFIG_PATH << ": " << StringValue2 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginStringValue2 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StringValue2 from file " << ProjectFilePath << ": " << StringValue2 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginIntValue3 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter IntValue3 from file " << MAIN_CONFIG_PATH << ": " << IntValue3 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginIntValue3 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter IntValue3 from file " << ProjectFilePath << ": " << IntValue3 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginDoubleValue3 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter DoubleValue3 from file " << MAIN_CONFIG_PATH << ": " << DoubleValue3 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginDoubleValue3 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter DoubleValue3 from file " << ProjectFilePath << ": " << DoubleValue3 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }

  if( OriginStringValue3 == TEST_APPL_PARAM_MAIN_CONFIG ) {
    std::ostringstream Msg;
    Msg << "Parameter StringValue3 from file " << MAIN_CONFIG_PATH << ": " << StringValue3 << std::endl;
    InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
  }
  else {
    if( OriginStringValue3 == TEST_APPL_PARAM_EXTRA_CONFIG ) {
      std::ostringstream Msg;
      Msg << "Parameter StringValue3 from file " << ProjectFilePath << ": " << StringValue3 << std::endl;
      InfoMessage( TEST_APPL_SHOW_PARAM, Msg.str() );
    }
  }
}

void TestModuleAppl :: UpdateParameters( void )
{
  if( IfStringValue1() && !IfStringValue3() ) {
    StringValue3 = StringValue1;

    OriginStringValue3 = TEST_APPL_PARAM_CALCULATED;
  }
}

int TestModuleAppl :: Run( void )
{
  APSReadConfig * pAPSReadConfig;
  TestConfig    * pTestConfig;
  APSReadConfig * pAPSReadConfig1;
  TestConfig    * pTestConfig1;
  int             RetCode = TEST_APPL_NO_ERR;

  ShowBanner();

  InfoMessage( TEST_APPL_START );

  pTestConfig = new TestConfig();

  pAPSReadConfig = new APSReadConfig( pTestConfigReadSubModule, MAIN_CONFIG_PATH );

  RetCode = pAPSReadConfig->Read( pTestConfig );

  if( !RetCode ) {
    if( !pTestConfig->GetInt1( IntValue1 ) ) {
      OriginIntValue1 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetDouble1( DoubleValue1 ) ) {
      OriginDoubleValue1 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetString1( StringValue1 ) ) {
      OriginStringValue1 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetInt2( IntValue2 ) ) {
      OriginIntValue2 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetDouble2( DoubleValue2 ) ) {
      OriginDoubleValue2 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetString2( StringValue2 ) ) {
      OriginStringValue2 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetInt3( IntValue3 ) ) {
      OriginIntValue3 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetDouble3( DoubleValue3 ) ) {
      OriginDoubleValue3 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    if( !pTestConfig->GetString3( StringValue3 ) ) {
      OriginStringValue3 = TEST_APPL_PARAM_MAIN_CONFIG;
    }

    pTestConfig1 = new TestConfig();

    pAPSReadConfig1 = new APSReadConfig( pTestConfigReadSubModule, ProjectFilePath );

    RetCode = pAPSReadConfig1->Read( pTestConfig1 );

    if( !RetCode ) {
      if( !pTestConfig1->GetInt1( IntValue1 ) ) {
        OriginIntValue1 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetDouble1( DoubleValue1 ) ) {
        OriginDoubleValue1 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetString1( StringValue1 ) ) {
        OriginStringValue1 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetInt2( IntValue2 ) ) {
        OriginIntValue2 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetDouble2( DoubleValue2 ) ) {
        OriginDoubleValue2 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetString2( StringValue2 ) ) {
        OriginStringValue2 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetInt3( IntValue3 ) ) {
        OriginIntValue3 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetDouble3( DoubleValue3 ) ) {
        OriginDoubleValue3 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      if( !pTestConfig1->GetString3( StringValue3 ) ) {
        OriginStringValue3 = TEST_APPL_PARAM_EXTRA_CONFIG;
      }

      UpdateParameters();

      PrintParameters();
    }

    delete pAPSReadConfig1;

    delete pTestConfig1;
  }

  delete pAPSReadConfig;

  delete pTestConfig;

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------


