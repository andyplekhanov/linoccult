//------------------------------------------------------------------------------
//
// File:    TychoWriter.cc
//
// Purpose: Tycho2 star catalog writer.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 12.02.2006
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

#include "TychoWriter.h"
#include "apstycho2defs.h"

namespace aps {

  namespace apsastroio {

//======================= TychoWriter ==========================

TychoWriter :: TychoWriter( const std::string & pTychoFilePath ) :
                 APSOBinAstroIO( apslib::ABS_ARCH_LITTLE, pTychoFilePath )
{
}

TychoWriter :: ~TychoWriter( void )
{
}

int TychoWriter :: PutRA( int RA ) const
{
  return( PutInteger( RA, TYCHO_RA_OFFSET ) );
}

int TychoWriter :: PutpmRA( float pmRA ) const
{
  return( PutFloat( pmRA, TYCHO_PM_RA_OFFSET ) );
}

int TychoWriter :: PutDec( int Dec ) const
{
  return( PutInteger( Dec, TYCHO_DEC_OFFSET ) );
}

int TychoWriter :: PutpmDec( float pmDec ) const
{
  return( PutFloat( pmDec, TYCHO_PM_DEC_OFFSET ) );
}

int TychoWriter :: PutParallax( short Parallax ) const
{
  return( PutShort( Parallax, TYCHO_PARALLAX_OFFSET ) );
}

int TychoWriter :: PutMv( short Mv ) const
{
  return( PutShort( Mv, TYCHO_MV_OFFSET ) );
}

int TychoWriter :: PutMp( short Mp ) const
{
  return( PutShort( Mp, TYCHO_MP_OFFSET ) );
}

int TychoWriter :: PutCatalogue( unsigned char Catalogue ) const
{
  return( PutChar( Catalogue, TYCHO_CATALOGUE_OFFSET ) );
}

int TychoWriter :: PutStarCatalogNumber( int Number ) const
{
  return( PutInteger( Number, TYCHO_NUMBER_OFFSET ) );
}

}}

//---------------------------- End of file ---------------------------
