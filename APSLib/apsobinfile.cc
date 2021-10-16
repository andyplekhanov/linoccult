//------------------------------------------------------------------------------
//
// File:    apsobinfile.cc
//
// Purpose: General purpose procedures for output binary file processing
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.04.2004
//         version 0.2 12.02.2005 PutRecord was corrected
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

#include "apsobinfile.h"

namespace aps {

  namespace apslib {

APSOBinFile :: APSOBinFile( const std::string & aFileName ) :
APSOFile( aFileName, std::ios::out | std::ios::binary )
{
}

APSOBinFile :: APSOBinFile( const std::string & aFileName, int /*Append*/ ) :
APSOFile( aFileName, std::ios::out | std::ios::binary | std::ios::app )
{
}

APSOBinFile :: ~APSOBinFile( void )
{
}

bool APSOBinFile :: PutRecord( const void * pRecord, const unsigned int RecordLength )
{
 if( IfOpened() ) {
    GetFile().write( static_cast<const char *>( pRecord ), RecordLength );

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

