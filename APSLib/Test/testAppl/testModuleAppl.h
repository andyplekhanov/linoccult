//------------------------------------------------------------------------------
//
// File:    testModuleAppl.h
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

#ifndef TEST_MODULE_APPL_H
#define TEST_MODULE_APPL_H

#include "apsmainmodule.h"
#include "testConfig.h"

namespace aps {

  namespace testappl {

class TestImplementationSubModule;
class TestConfigReadSubModule;

using apslib::APSMainModule;

enum {
  TEST_APPL_NO_ERR = 0,
  TEST_APPL_IMPLEMENTATION,
  TEST_APPL_MODULE,
  TEST_APPL_START,
  TEST_APPL_FINISH,
  TEST_APPL_SHOW_PARAM
};

enum {
  TEST_APPL_PARAM_DEFAULT = 0,
  TEST_APPL_PARAM_MAIN_CONFIG,
  TEST_APPL_PARAM_EXTRA_CONFIG,
  TEST_APPL_PARAM_CALCULATED
};

//======================= TestModuleAppl ==========================

class TestModuleAppl : public APSMainModule
{
  private:

    TestImplementationSubModule * pTestImplementationSubModule;
    TestConfigReadSubModule     * pTestConfigReadSubModule;

    std::string ProjectFilePath;

    int         IntValue1;
    double      DoubleValue1;
    std::string StringValue1;
    int         IntValue2;
    double      DoubleValue2;
    std::string StringValue2;
    int         IntValue3;
    double      DoubleValue3;
    std::string StringValue3;

    int OriginIntValue1;
    int OriginDoubleValue1;
    int OriginStringValue1;
    int OriginIntValue2;
    int OriginDoubleValue2;
    int OriginStringValue2;
    int OriginIntValue3;
    int OriginDoubleValue3;
    int OriginStringValue3;

  protected:

    void UpdateParameters( void );

  public:

    TestModuleAppl( const std::string & aProjectFilePath,
                    const std::string & aModuleName,
                    const int X_Version,
                    const int Y_Version,
                    const int Z_Version,
                    const int FirstCopyRightYear,
                    const int CopyRightYear,
                    const apslib::APS_PROGRAM_VERSION_TYPE VersionType = apslib::APS_NORMAL_VERSION );

    virtual ~TestModuleAppl( void );

    TestImplementationSubModule * GetTestImplementationSubModulePtr( void ) const
      { return( pTestImplementationSubModule ); }

    virtual const std::string GetMessageText( const int MsgNumber ) const;

    int GetInt1( void ) const
      { return( IntValue1 ); }

    double GetDouble1( void ) const
      { return( DoubleValue1 ); }

    const std::string & GetString1( void ) const
      { return( StringValue1 ); }

    int GetInt2( void ) const
      { return( IntValue2 ); }

    double GetDouble2( void ) const
      { return( DoubleValue2 ); }

    const std::string & GetString2( void ) const
      { return( StringValue2 ); }

    int GetInt3( void ) const
      { return( IntValue3 ); }

    double GetDouble3( void ) const
      { return( DoubleValue3 ); }

    const std::string & GetString3( void ) const
      { return( StringValue3 ); }

    bool IfIntValue1( void ) const;

    bool IfDoubleValue1( void ) const;

    bool IfStringValue1( void ) const;

    bool IfStringValue3( void ) const;

    void PrintParameters( void ) const;

    virtual int Run( void );
};

}}

#endif

//---------------------------- End of file ---------------------------



