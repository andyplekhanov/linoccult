//------------------------------------------------------------------------------
//
// File:    apsibinastroio.cc
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

#include <cstring>

#include "apsibinastroio.h"

namespace aps {

  namespace apsastroio {

//=============================== APSIBinAstroIO =========================

APSIBinAstroIO :: APSIBinAstroIO( const int FileArchType, const std::string & FileName ) : APSIBinFile( FileName ),
                                  MaxRecordLength( 0 ), Record( 0 ), IfReady( false ), IfSwap( false )
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

APSIBinAstroIO :: ~APSIBinAstroIO( void )
{
  if( Record ) {
    delete [] Record;
  }

  delete pByteOrder;
}

int APSIBinAstroIO :: ReadRecord( const unsigned int aMaxRecordLength )
{
  if( MaxRecordLength != aMaxRecordLength ) {
    if( Record ) {
      delete [] Record;
    }

    MaxRecordLength = aMaxRecordLength;

    Record = new char[ aMaxRecordLength ];
  }

  bool RetCode = GetRecord( Record, aMaxRecordLength );

  if( RetCode ) {
    IfReady = true;
  }
  else {
    IfReady = false;
  }

  return( RetCode );  
}

int APSIBinAstroIO :: GetLong( int64_t & pLong, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( int64_t ) <= MaxRecordLength ) {
      int64_t TmpLong;

      memcpy( &TmpLong, Record + Offset, sizeof( int64_t ) );

      if( IfSwap ) {
        pLong = pByteOrder->SwapLong( TmpLong );
      }
      else {
        pLong = TmpLong;
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

int APSIBinAstroIO :: GetULong( uint64_t & pLong, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( uint64_t ) <= MaxRecordLength ) {
      uint64_t TmpLong;

      memcpy( &TmpLong, Record + Offset, sizeof( uint64_t ) );

      if( IfSwap ) {
        pLong = pByteOrder->SwapLong( TmpLong );
      }
      else {
        pLong = TmpLong;
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
    
int APSIBinAstroIO :: GetInteger( int32_t & pInt, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( int32_t ) <= MaxRecordLength ) {
      int32_t TmpInt;

      memcpy( &TmpInt, Record + Offset, sizeof( int32_t ) );

      if( IfSwap ) {
        pInt = pByteOrder->SwapInteger( TmpInt );
      }
      else {
        pInt = TmpInt;
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

int APSIBinAstroIO :: GetUInteger( uint32_t & pInt, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( uint32_t ) <= MaxRecordLength ) {
      uint32_t TmpInt;

      memcpy( &TmpInt, Record + Offset, sizeof( uint32_t ) );

      if( IfSwap ) {
        pInt = pByteOrder->SwapInteger( TmpInt );
      }
      else {
        pInt = TmpInt;
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

int APSIBinAstroIO :: GetShort( int16_t & pShort, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( int16_t ) <= MaxRecordLength ) {
      int16_t TmpShort;

      memcpy( &TmpShort, Record + Offset, sizeof( int16_t ) );

      if( IfSwap ) {
        pShort = pByteOrder->SwapShort( TmpShort );
      }
      else {
        pShort = TmpShort;
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

int APSIBinAstroIO :: GetUShort( uint16_t & pShort, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( uint16_t ) <= MaxRecordLength ) {
      uint16_t TmpShort;

      memcpy( &TmpShort, Record + Offset, sizeof( uint16_t ) );

      if( IfSwap ) {
        pShort = pByteOrder->SwapShort( TmpShort );
      }
      else {
        pShort = TmpShort;
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

int APSIBinAstroIO :: GetFloat( float & pFlt, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( float ) <= MaxRecordLength ) {
      float TmpFloat;

      memcpy( &TmpFloat, Record + Offset, sizeof( float ) );

      if( IfSwap ) {
        pFlt = pByteOrder->SwapFloat( TmpFloat );
      }
      else {
        pFlt = TmpFloat;
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

int APSIBinAstroIO :: GetDouble( double & pDbl, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( double ) <= MaxRecordLength ) {
      double TmpDouble;

      memcpy( &TmpDouble, Record + Offset, sizeof( double ) );

      if( IfSwap ) {
        pDbl = pByteOrder->SwapDouble( TmpDouble );
      }
      else {
        pDbl = TmpDouble;
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

int APSIBinAstroIO :: GetChar( unsigned char & pChar, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( char ) <= MaxRecordLength ) {
      pChar = Record[ Offset ];
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

int APSIBinAstroIO :: GetCharArray( unsigned char * pCharArray, const unsigned int Length, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + Length <= MaxRecordLength ) {
      if( pCharArray ) {
        memcpy( pCharArray, Record + Offset, Length );
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

int APSIBinAstroIO :: GetString( std::string & pString, const unsigned int Offset, unsigned int & NewOffset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( uint32_t ) <= MaxRecordLength ) {
      uint32_t StrLength;

      memcpy( &StrLength, Record + Offset, sizeof( uint32_t ) );

      if( IfSwap ) {
        StrLength = pByteOrder->SwapInteger( StrLength );
      }

      if( Offset + sizeof( uint32_t ) + StrLength <= MaxRecordLength ) {
        char * TmpStr = new char[ StrLength + 1 ];        

        memcpy( TmpStr, Record + Offset + sizeof( uint32_t ), StrLength );

        TmpStr[ StrLength ] = 0x00;

        NewOffset = Offset + sizeof( uint32_t ) + StrLength;

        pString = TmpStr;

        delete [] TmpStr;
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
