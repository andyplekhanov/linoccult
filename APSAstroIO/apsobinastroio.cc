//------------------------------------------------------------------------------
//
// File:    apsobinastroio.cc
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

#include <cstring>

#include "apsobinastroio.h"

namespace aps {

  namespace apsastroio {

//=============================== APSOBinAstroIO =========================

APSOBinAstroIO :: APSOBinAstroIO( const int FileArchType, const std::string & FileName ) :
                  APSOBinFile( FileName ), RecordLength( 0 ), Record( 0 ), IfReady( false ), IfSwap( false )
{
  Init( FileArchType );
}

APSOBinAstroIO :: APSOBinAstroIO( const int FileArchType, const std::string & FileName, const bool IfAppend ) :
                  APSOBinFile( FileName, 1 ), RecordLength( 0 ), Record( 0 ), IfReady( false ), IfSwap( false )
{
  Init( FileArchType );
}

void APSOBinAstroIO :: Init( const int FileArchType )
{
  pByteOrder = new APSByteOrder();

  IfSwap = false;

  if( ( pByteOrder->GetArchType() == apslib::ABS_ARCH_LITTLE ) && ( FileArchType == apslib::ABS_ARCH_BIG ) ) {
    IfSwap = true;
  }

  if( ( pByteOrder->GetArchType() == apslib::ABS_ARCH_BIG ) && ( FileArchType == apslib::ABS_ARCH_LITTLE ) ) {
    IfSwap = true;
  }
}

APSOBinAstroIO :: ~APSOBinAstroIO( void )
{
  if( Record ) {
    delete [] Record;
  }

  delete pByteOrder;
}

int APSOBinAstroIO :: PrepareRecord( const unsigned int aRecordLength )
{
  int RetCode = 0;  

  if( !IfReady ) {
    if( Record ) {
      delete [] Record;
    }

    RecordLength = aRecordLength;

    Record = new char[ aRecordLength ];

    IfReady = true;
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSOBinAstroIO :: WriteRecord( void )
{
  int RetCode = 0;  

  if( IfReady ) {
    RetCode = PutRecord( Record, RecordLength );

    delete [] Record;

    IfReady = false;
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSOBinAstroIO :: PutInteger( int32_t Int, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( int32_t ) <= RecordLength ) {
      if( IfSwap ) {
        Int = pByteOrder->SwapInteger( Int );
      }

      memcpy( Record + Offset, &Int, sizeof( int32_t ) );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode ); 
}

int APSOBinAstroIO :: PutShort( int16_t Short, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( int16_t ) <= RecordLength ) {
      if( IfSwap ) {
        Short = pByteOrder->SwapShort( Short );
      }

      memcpy( Record + Offset, &Short, sizeof( int16_t ) );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSOBinAstroIO :: PutFloat( float Flt, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( float ) <= RecordLength ) {
      if( IfSwap ) {
        Flt = pByteOrder->SwapFloat( Flt );
      }

      memcpy( Record + Offset, &Flt, sizeof( float ) );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSOBinAstroIO :: PutDouble( double Dbl, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( double ) <= RecordLength ) {
      if( IfSwap ) {
        Dbl = pByteOrder->SwapDouble( Dbl );
      }

      memcpy( Record + Offset, &Dbl, sizeof( double ) );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSOBinAstroIO :: PutChar( const unsigned char Char, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( unsigned char ) <= RecordLength ) {
      memcpy( Record + Offset, &Char, sizeof( unsigned char ) );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSOBinAstroIO :: PutCharArray( const unsigned char * pCharArray, const unsigned int Length, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + Length <= RecordLength ) {
      memcpy( Record + Offset, pCharArray, Length );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSOBinAstroIO :: PutString( const std::string & pString, unsigned int Offset ) const
{
  uint32_t StrLength;
  int      RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( uint32_t ) <= RecordLength ) {
      StrLength = pString.length();

      if( IfSwap ) {
        StrLength = pByteOrder->SwapInteger( StrLength );
      }

      memcpy( Record + Offset, &StrLength, sizeof( uint32_t ) );

      if( Offset + sizeof( uint32_t ) + StrLength <= RecordLength ) {
        memcpy( Record + Offset + sizeof( uint32_t ), pString.c_str(), StrLength );
      }
      else {
        RetCode = 3;
      }
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------

