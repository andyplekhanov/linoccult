//------------------------------------------------------------------------------
//
// File:    apsibinastroio.h
//
// Purpose: Base class for binary astro file input.
//   
// (c) 2006-2020 Plekhanov Andrey
//
// Initial version 0.1 05.02.2006
// int64, uint64   0.2 09.01.2020
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

#ifndef APS_IBIN_ASTRO_IO_H
#define APS_IBIN_ASTRO_IO_H

#include <string>

#include "apsibinfile.h"
#include "apsbyteorder.h"

namespace aps {

  namespace apslib {
    class APSByteOrder;
  }

  namespace apsastroio {

using apslib :: APSIBinFile;
using apslib :: APSByteOrder;

//=============================== APSIBinAstroIO =========================

class APSIBinAstroIO : protected APSIBinFile
{
  private:

    APSByteOrder * pByteOrder;
    unsigned int   MaxRecordLength;
    char         * Record;
    bool           IfReady;
    bool           IfSwap;

  protected:

    int ReadRecord( const unsigned int aMaxRecordLength );

    int GetLong( int64_t & pLong, const unsigned int Offset ) const;

    int GetULong( uint64_t & pLong, const unsigned int Offset ) const;

    int GetInteger( int32_t & pInt, const unsigned int Offset ) const;

    int GetUInteger( uint32_t & pInt, const unsigned int Offset ) const;
    
    int GetShort( int16_t & pShort, const unsigned int Offset ) const;

    int GetUShort( uint16_t & pShort, const unsigned int Offset ) const;

    int GetFloat( float & pFlt, const unsigned int Offset ) const;

    int GetDouble( double & pDbl, const unsigned int Offset ) const;

    int GetChar( unsigned char & pChar, const unsigned int Offset ) const;

    int GetCharArray( unsigned char * pCharArray, const unsigned int Length, const unsigned int Offset ) const;

    int GetString( std :: string & pString, const unsigned int Offset, unsigned int & NewOffset ) const;

  public:

    APSIBinAstroIO( const int FileArchType, const std::string & FileName );

    virtual ~APSIBinAstroIO( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
