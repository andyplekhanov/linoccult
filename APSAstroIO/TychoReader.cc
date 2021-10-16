//------------------------------------------------------------------------------
//
// File:    TychoReader.cc
//
// Purpose: Tycho2 star catalog reader.
//          Read data from Tycho2.dat.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 24.02.2004
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

#include "TychoReader.h"
#include "apstycho2defs.h"

namespace aps {

  namespace apsastroio {

//======================= TychoReader ==========================

TychoReader :: TychoReader( const std::string & pTychoFilePath ) :
                 APSIBinAstroIO( apslib::ABS_ARCH_LITTLE, pTychoFilePath )
{
}

TychoReader :: ~TychoReader( void )
{
}

int TychoReader :: ReadStar( void )
{
  return( ReadRecord( TYCHO_RECORD_LENGTH ) );  
}

int TychoReader :: GetStarsNumber( off_t & StarsNumber ) const
{
  off_t FileLength = 0;

  GetLength( FileLength );

  StarsNumber = FileLength / TYCHO_RECORD_LENGTH;

  return( FileLength % TYCHO_RECORD_LENGTH );
}

int TychoReader :: GetRA( int & pRA ) const
{
  return( GetInteger( pRA, TYCHO_RA_OFFSET ) );
}

int TychoReader :: GetpmRA( float & ppmRA ) const
{
  return( GetFloat( ppmRA, TYCHO_PM_RA_OFFSET ) );
}

int TychoReader :: GetDec( int & pDec ) const
{
  return( GetInteger( pDec, TYCHO_DEC_OFFSET ) );
}

int TychoReader :: GetpmDec( float & ppmDec ) const
{
  return( GetFloat( ppmDec, TYCHO_PM_DEC_OFFSET ) );
}

int TychoReader :: GetParallax( short & pParallax ) const
{
  return( GetShort( pParallax, TYCHO_PARALLAX_OFFSET ) );
}

int TychoReader :: GetMv( short & pMv ) const
{
  return( GetShort( pMv, TYCHO_MV_OFFSET ) );
}

int TychoReader :: GetMp( short & pMp ) const
{
  return( GetShort( pMp, TYCHO_MP_OFFSET ) );
}

int TychoReader :: GetCatalogue( unsigned char & pCatalogue ) const
{
  return( GetChar( pCatalogue, TYCHO_CATALOGUE_OFFSET ) );
}

int TychoReader :: GetStarCatalogNumber( int & pNumber ) const
{
  return( GetInteger( pNumber, TYCHO_NUMBER_OFFSET ) );
}

}}

//---------------------------- End of file ---------------------------
