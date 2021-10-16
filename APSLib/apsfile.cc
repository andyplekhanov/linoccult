//------------------------------------------------------------------------------
//
// File:    apsfile.cc
//
// Purpose: General purpose procedures for file processing
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

#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>

#include "apsfile.h"

namespace aps {

  namespace apslib {

APSFile :: APSFile( const std::string & aFileName, const std::ios::openmode aOpenMode ) :
                    FileName( aFileName ), OpenMode( aOpenMode )
{
}

APSFile :: ~APSFile( void )
{
  if( IfOpened() ) {
    Close();
  }
}

bool APSFile :: IfOpened( void )
{
  return( GetFile().is_open() ? true : false );
}

bool APSFile :: Open( void )
{
  if( !IfOpened() ) {
    GetFile().open( GetFileName().c_str(), GetOpenMode() );

    if( !GetFile() ) {
      return( false );
    }

    return( true );
  }

  return( false );
}

bool APSFile :: Close( void )
{
  if( IfOpened() ) {
    GetFile().close();
    return( true );
  }

  return( false );
}

bool APSFile :: IfExists( void ) const
{
  struct stat statBuffer;

  return( stat( GetFileName().c_str(), &statBuffer ) == 0 );
}

bool APSFile :: GetDevice( dev_t & p_dev ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 )
    return( false );

  p_dev = statBuffer.st_dev;

  return( true );
}

bool APSFile :: GetSerialNumber( ino_t & ino ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }  

  ino = statBuffer.st_ino;

  return( true );
}

bool APSFile :: GetMode( mode_t & mode ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  mode = statBuffer.st_mode;

  return( true );
}

bool APSFile :: GetLinkNumber( nlink_t & p_nlink ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  p_nlink = statBuffer.st_nlink;

  return( true );
}

bool APSFile :: GetUserID( uid_t & p_uid ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  p_uid = statBuffer.st_uid;

  return( true );
}

bool APSFile :: GetGroupID( gid_t & p_gid ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  p_gid = statBuffer.st_gid;

  return( true );
}

bool APSFile :: GetDevID( dev_t & p_dev ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  p_dev = statBuffer.st_rdev;

  return( true );
}

bool APSFile :: GetLength( off_t & length ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  length = statBuffer.st_size;

  return( true );
}

bool APSFile :: GetLastAccess( time_t & atime )	const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  atime = statBuffer.st_atime;

  return( true );
}

bool APSFile :: GetLastModify( time_t & mtime ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  mtime = statBuffer.st_mtime;

  return( true );
}

bool APSFile :: GetLastStatus( time_t & ctime )	const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  ctime = statBuffer.st_ctime;

  return( true );
}

bool APSFile :: GetBlockSize( long & bsize ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  bsize = statBuffer.st_blksize;

  return( true );
}

bool APSFile :: GetBlockNumber( long & bnumber ) const
{
  struct stat statBuffer;

  if( stat( GetFileName().c_str(), &statBuffer ) == -1 ) {
    return( false );
  }

  bnumber = statBuffer.st_blocks;

  return( true );
}

}}

//---------------------------- End of file ---------------------------

