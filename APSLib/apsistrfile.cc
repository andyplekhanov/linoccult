//------------------------------------------------------------------------------
//
// File:    apsistrfile.cc
//
// Purpose: General purpose procedures for input text file processing
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.04.2004
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

#include "apsistrfile.h"

namespace aps {

  namespace apslib {

APSIStrFile :: APSIStrFile( const std::string & aFileName ) :
APSIFile( aFileName, std::ios::in )
{
}

APSIStrFile :: ~APSIStrFile( void )
{
}

bool APSIStrFile :: GetStr( std::string & Str )
{
 if( IfOpened() ) {
    std::getline( GetFile(), Str );

    if( !GetFile() ) {
      return( false );
    }
  }
  else {
    return( false );
  }

  return( true );
}

}}

//---------------------------- End of file ---------------------------
