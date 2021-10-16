//------------------------------------------------------------------------------
//
// File:    apsreadcfg.cc
//
// Purpose: Class for reading config
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 06.03.2004
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

#include <sstream>

#include "apsreadcfg.h"
#include "apsconfig.h"
#include "apsistrfile.h"
#include "apsmodulecfgreader.h"

namespace aps {

  namespace apslib {

//------------------------------- APSReadConfig ---------------------------------

APSReadConfig :: APSReadConfig( APSSubModule * pSubModule, const std::string & ConfigFilePath )
{
  pModule = new APSModuleConfigReader( pSubModule );
  pFile   = new APSIStrFile( ConfigFilePath );
}

APSReadConfig :: ~APSReadConfig( void )
{
  delete pFile;
  delete pModule;
}

bool APSReadConfig :: ParseLine( const std::string & Str, std::string & ParamType,
                                 std::string & ParamName, std::string & ParamValue ) const
{
  std::stringstream istrstream( Str );
  std::string       NullParam;

  if( istrstream >> ParamType ) {
    if( istrstream >> ParamName ) {
      if( istrstream >> ParamValue ) {
        if( !( istrstream >> NullParam ) ) {
          return( true );
        }
      }
    }
  }

  return( false );
}

int APSReadConfig :: Read( APSConfig * pConfig )
{
  std::string          Str;
  std::string          ParamType;
  std::string          ParamName;
  std::string          ParamValue;
  int                  IntParam;
  double               DoubleParam;
  std::ostringstream   Msg;
  const APSParameter * pParameter;
  int                  RetCode = 0;

  if( pFile->Open() ) {
    while( pFile->GetStr( Str ) ) {
      if( ( Str[ 0 ] != '#') && ( !Str.empty() ) ) {
        if( ParseLine( Str, ParamType, ParamName, ParamValue ) ) {
          pParameter = pConfig->FindParameter( ParamName );

          if( pParameter ) {
            if( pConfig->IfExistsParameter( ParamName ) ) {
              Msg << "File " << pFile->GetFileName() << ". Parameter name `" << ParamName << "`" << std::endl;
              pModule->ErrorMessage( APS_MODULE_CFG_READER_EXISTS, Msg.str() );
              RetCode = APS_MODULE_CFG_READER_EXISTS;
              break;
            }
          }
          else {
            Msg << "File " << pFile->GetFileName() << ". Parameter name `" << ParamName << "`" << std::endl;
            pModule->ErrorMessage( APS_MODULE_CFG_READER_NOT_FOUND, Msg.str() );
            RetCode = APS_MODULE_CFG_READER_NOT_FOUND;
            break;
          }

          if( "int" == ParamType ) {
            if( pParameter->GetType() == PARAM_INTEGER ) {
              std::istringstream istrstream( ParamValue );

              if( istrstream >> IntParam ) {
                pConfig->AddIntegerParameter( ParamName, IntParam );
              }
              else {
                Msg << "File " << pFile->GetFileName() << ". Parameter name `" << ParamName << "` Value `" << ParamValue << "` is not integer." << std::endl;
                pModule->ErrorMessage( APS_MODULE_CFG_READER_VALUE, Msg.str() );
                RetCode = APS_MODULE_CFG_READER_VALUE;
                break;
              }
            }
            else {
              Msg << "File " << pFile->GetFileName() << ". Parameter name `" << ParamName << "` must be not integer." << std::endl;
              pModule->ErrorMessage( APS_MODULE_CFG_READER_TYPE, Msg.str() );
              RetCode = APS_MODULE_CFG_READER_TYPE;
              break;
            }
          }
          else {
            if( "double" == ParamType ) {
              if( pParameter->GetType() == PARAM_DOUBLE ) {
                std::istringstream istrstream( ParamValue );

                if( istrstream >> DoubleParam ) {
                  pConfig->AddDoubleParameter( ParamName, DoubleParam );
                }
                else {
                  Msg << "File " << pFile->GetFileName() << ". Parameter name `" << ParamName << "` Value `" << ParamValue << "` is not double." << std::endl;
                  pModule->ErrorMessage( APS_MODULE_CFG_READER_VALUE, Msg.str() );
                  RetCode = APS_MODULE_CFG_READER_VALUE;
                  break;
                }
              }
              else {
                Msg << "File " << pFile->GetFileName() << ". Parameter name `" << ParamName << "` must be not double." << std::endl;
                pModule->ErrorMessage( APS_MODULE_CFG_READER_TYPE, Msg.str() );
                RetCode = APS_MODULE_CFG_READER_TYPE;
                break;
              }
            }
            else {
              if( "string" == ParamType ) {
                if( pParameter->GetType() == PARAM_STRING ) {
                  pConfig->AddStringParameter( ParamName, ParamValue );
                }
                else {
                  Msg << "File " << pFile->GetFileName() << ". Parameter name `" << ParamName << "` must be not string." << std::endl;
                  pModule->ErrorMessage( APS_MODULE_CFG_READER_TYPE, Msg.str() );
                  RetCode = APS_MODULE_CFG_READER_TYPE;
                  break;
                }
              }
              else {
                Msg << "File " << pFile->GetFileName() << ". Parameter type `" << ParamType << "`" << std::endl;
                pModule->ErrorMessage( APS_MODULE_CFG_READER_WRONG_TYPE, Msg.str() );
                RetCode = APS_MODULE_CFG_READER_WRONG_TYPE;
                break;
              }
            }
          }
        }
        else {
          Msg << "File " << pFile->GetFileName() << ". String: " << Str << std::endl;
          pModule->ErrorMessage( APS_MODULE_CFG_READER_PARSE_LINE, Msg.str() );
          RetCode = APS_MODULE_CFG_READER_PARSE_LINE;
          break;
        }
      } // If comment or empty line
    } // while

    pFile->Close();
  }
  else {
    Msg << "File " << pFile->GetFileName() << " not found" << std::endl;
    pModule->ErrorMessage( APS_MODULE_CFG_READER_FILE_NOT_FOUND, Msg.str() );
    RetCode = APS_MODULE_CFG_READER_FILE_NOT_FOUND;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
