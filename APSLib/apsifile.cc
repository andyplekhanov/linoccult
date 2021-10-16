//------------------------------------------------------------------------------
//
// File:    apsifile.cc
//
// Purpose: General purpose procedures for binary file processing
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

#include "apsifile.h"

namespace aps {

  namespace apslib {

APSIFile :: APSIFile( const std::string & aFileName, const std::ios::openmode aMode ) :
APSFile( aFileName, aMode )
{
}

APSIFile :: ~APSIFile( void )
{
}

std::streampos APSIFile :: Pos( void )
{
  return( GetFile().tellg() );
}

bool APSIFile :: Seek( const std::streamoff Offset,
                       const std::ios::seekdir dir )
{
  if( IfOpened() ) {
    GetFile().seekg( Offset, dir );

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
