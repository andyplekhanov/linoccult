//------------------------------------------------------------------------------
//
// File:    apsobinastroio.h
//
// Purpose: Base class for binary astro file output.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 05.02.2006
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

#ifndef APS_OBIN_ASTRO_IO_H
#define APS_OBIN_ASTRO_IO_H

#include <string>

#include "apsobinfile.h"
#include "apsbyteorder.h"

namespace aps {

  namespace apslib {
    class APSByteOrder;
  }

  namespace apsastroio {

using apslib :: APSOBinFile;
using apslib :: APSByteOrder;

//=============================== APSOBinAstroIO =========================

class APSOBinAstroIO : public APSOBinFile
{
  private:

    APSByteOrder * pByteOrder;
    unsigned int   RecordLength;
    char         * Record;
    bool           IfReady;
    bool           IfSwap;

    void Init( const int FileArchType );

  protected:

    int PrepareRecord( const unsigned int aRecordLength );

    int WriteRecord( void );

    int PutInteger( int32_t Int, const unsigned int Offset ) const;

    int PutShort( int16_t Short, const unsigned int Offset ) const;

    int PutFloat( float Flt, const unsigned int Offset ) const;

    int PutDouble( double Dbl, const unsigned int Offset ) const;

    int PutChar( const unsigned char Char, const unsigned int Offset ) const;

    int PutCharArray( const unsigned char * pCharArray, const unsigned int Length, const unsigned int Offset ) const;

    int PutString( const std::string & pString, const unsigned int Offset ) const;

  public:

    APSOBinAstroIO( const int FileArchType, const std::string & FileName );

    APSOBinAstroIO( const int FileArchType, const std::string & FileName, const bool IfAppend );

    virtual ~APSOBinAstroIO( void );
};

}}

#endif

//---------------------------- End of file ---------------------------

