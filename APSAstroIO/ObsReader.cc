//------------------------------------------------------------------------------
//
// File:    ObsReader.cc
//
// Purpose: Read data from observatories position file.
//   
// (c) Plekhanov Andrey
//
// Initial version 0.1
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

#include "ObsReader.h"
#include "apsobscoddefs.h"

namespace aps {

  namespace apsastroio {

//======================= ObsReader ==========================

ObsReader :: ObsReader( const std::string & pObsFilePath ) : APSIStrAstroIO( pObsFilePath )
{
}

ObsReader :: ~ObsReader( void )
{
}

int ObsReader :: ConvertObsCode( const std::string & ObsCodeName, int & ObsCode )
{
  char A = ObsCodeName[ 0 ];
  int  RetCode = 0;

  if( ( A == ' ' ) || ( ( A >= '0' ) && ( A <= '9' ) ) ) {
    std::stringstream istrstream( ObsCodeName );

    if( istrstream >> ObsCode ) {
      if( ObsCode < 0 ) {
        RetCode = 1;
      }
    }
    else {
      RetCode = 2;
    }
  }
  else {
    if( ( A >= 'A' ) && ( A <= 'Z' ) ) {
      std::stringstream istrstream( ObsCodeName.substr( 1 ) );

      if( istrstream >> ObsCode ) {
        ObsCode = ObsCode + ( A - 'A' + 10 ) * 100; 

        if( ObsCode < 0 ) {
          RetCode = 3;
        }
      }
      else {
        RetCode = 4;
      }
    }
    else {
      RetCode = 5;
    }
  }

  return( RetCode );
}

int ObsReader :: GetObsCodeName( std::string & pObsCodeName ) const
{
  return( GetString( pObsCodeName, OBSCOD_NAME_OFFSET, OBSCOD_NAME_LENGTH ) );
}

int ObsReader :: GetLongitude( double & pLongitude ) const
{
  return( GetDouble( pLongitude, OBSCOD_LONGITUDE_OFFSET, OBSCOD_LONGITUDE_LENGTH ) );
}

int ObsReader :: GetRhoCos( double & pRhoCos ) const
{
  return( GetDouble( pRhoCos, OBSCOD_COS_OFFSET, OBSCOD_COS_LENGTH ) );
}

int ObsReader :: GetRhoSin( double & pRhoSin ) const
{
  return( GetDouble( pRhoSin, OBSCOD_SIN_OFFSET, OBSCOD_SIN_LENGTH ) );
}

int ObsReader :: GetName( std::string & Name ) const
{
  return( GetString( Name, OBSCOD_COMMENT_OFFSET, GetBuffer().length() - OBSCOD_COMMENT_OFFSET ) );
}

}}

//---------------------------- End of file ---------------------------

