//------------------------------------------------------------------------------
//
// File:    apsfile.h
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

#ifndef 	_APSFILE_H_
#define         _APSFILE_H_	1

#include <string>
#include <fstream>

#include <sys/types.h>

namespace aps {

  namespace apslib {

class APSFile
{
  private:

    std::string        FileName;
    std::ios::openmode OpenMode;
    std::fstream       File;

  public:

    APSFile( const std::string & aFileName, const std::ios::openmode aOpenMode );

    virtual ~APSFile( void );

    const std::string & GetFileName( void ) const
      { return( FileName ); }

    std::ios::openmode GetOpenMode( void ) const
      { return( OpenMode ); }

    std::fstream & GetFile( void )
      { return( File ); }

    const std::fstream & GetFile( void ) const
      { return( File ); }

    bool IfOpened( void );

    bool Open( void );

    bool Close( void );

    virtual std::streampos Pos( void ) = 0;

    virtual bool Seek( const std::streamoff Offset,
                       const std::ios::seekdir dir ) = 0;

    bool IfExists( void ) const;

    /* device file resides on */
    bool GetDevice( dev_t & p_dev ) const;

    /* the file serial number */
    bool GetSerialNumber( ino_t & ino )	const;

    /* file mode */
    bool GetMode( mode_t & mode ) const;

    /* number of hard links to the file */
    bool GetLinkNumber( nlink_t & p_nlink ) const;

    /* user ID of owner */
    bool GetUserID( uid_t & p_uid ) const;

    /* group ID of owner */
    bool GetGroupID( gid_t & p_gid ) const;

    /* the device identifier (special files only)*/
    bool GetDevID( dev_t & p_dev ) const;

    /* total size of file, in bytes */
    bool GetLength( off_t & length ) const;

    /* file last access time */
    bool GetLastAccess( time_t & atime ) const;

    /* file last modify time */
    bool GetLastModify( time_t & mtime ) const;

    /* file last status change time */
    bool GetLastStatus( time_t & ctime ) const;

    /* preferred blocksize for file system I/O*/
    bool GetBlockSize( long & bsize )	const;

    /* actual number of blocks allocated */
    bool GetBlockNumber( long & bnumber ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------

