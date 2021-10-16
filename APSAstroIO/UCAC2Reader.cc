//------------------------------------------------------------------------------
//
// File:    UCAC2Reader.cc
//
// Purpose: UCAC2 star catalog reader.
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

#include "UCAC2Reader.h"
#include "apsucac2defs.h"

namespace aps {

  namespace apsastroio {

//======================= UCAC2Reader ==========================

UCAC2Reader :: UCAC2Reader( const std::string & pUCAC2FilePath ) :
                 APSIBinAstroIO( apslib::ABS_ARCH_LITTLE, pUCAC2FilePath )
{
}

UCAC2Reader :: ~UCAC2Reader( void )
{
}

int UCAC2Reader :: GetStarsNumber( off_t & StarsNumber ) const
{
  off_t FileLength;

  GetLength( FileLength );

  StarsNumber = FileLength / UCAC2_RECORD_LENGTH;

  return( FileLength % UCAC2_RECORD_LENGTH );
}

int UCAC2Reader :: GetRA( int & pRA ) const
{
  return( GetInteger( pRA, UCAC2_RA_OFFSET ) );
}

int UCAC2Reader :: GetDec( int & pDec ) const
{
  return( GetInteger( pDec, UCAC2_DEC_OFFSET ) );
}

int UCAC2Reader :: GetU2Rmag( short & pU2Rmag ) const
{
  return( GetShort( pU2Rmag, UCAC2_U2RMAG_OFFSET ) );
}

int UCAC2Reader :: GetERAm( unsigned char & pERAm ) const
{
  return( GetChar( pERAm, UCAC2_E_RAM_OFFSET ) );
}

int UCAC2Reader :: GetEDEm( unsigned char & pEDEm ) const
{
  return( GetChar( pEDEm, UCAC2_E_DEM_OFFSET ) );
}

int UCAC2Reader :: GetNObs( unsigned char & pNObs ) const
{
  return( GetChar( pNObs, UCAC2_NOBS_OFFSET ) );
}

int UCAC2Reader :: GetEPos( unsigned char & pEPos ) const
{
  return( GetChar( pEPos, UCAC2_EPOS_OFFSET ) );
}

int UCAC2Reader :: GetNCat( unsigned char & pNCat ) const
{
  return( GetChar( pNCat, UCAC2_NCAT_OFFSET ) );
}

int UCAC2Reader :: GetCFLG( unsigned char & pCFLG ) const
{
  return( GetChar( pCFLG, UCAC2_CFLG_OFFSET ) );
}

int UCAC2Reader :: GetEpRAm( short & pEpRAm ) const
{
  return( GetShort( pEpRAm, UCAC2_EPRAM_OFFSET ) );
}

int UCAC2Reader :: GetEpDEm( short & pEpDEm ) const
{
  return( GetShort( pEpDEm, UCAC2_EPDEM_OFFSET ) );
}

int UCAC2Reader :: GetpmRA( int & ppmRA ) const
{
  return( GetInteger( ppmRA, UCAC2_PM_RA_OFFSET ) );
}

int UCAC2Reader :: GetpmDec( int & ppmDec ) const
{
  return( GetInteger( ppmDec, UCAC2_PM_DE_OFFSET ) );
}

int UCAC2Reader :: GetEpmRA( unsigned char & pEpmRA ) const
{
  return( GetChar( pEpmRA, UCAC2_EPMRA_OFFSET ) );
}

int UCAC2Reader :: GetEpmDE( unsigned char & pEpmDE ) const
{
  return( GetChar( pEpmDE, UCAC2_EPMDE_OFFSET ) );
}

int UCAC2Reader :: GetQpmRA( unsigned char & pQpmRA ) const
{
  return( GetChar( pQpmRA, UCAC2_QPMRA_OFFSET ) );
}

int UCAC2Reader :: GetQpmDE( unsigned char & pQpmDE ) const
{
  return( GetChar( pQpmDE, UCAC2_QPMDE_OFFSET ) );
}

int UCAC2Reader :: GetStarCatalogNumber( int & pNumber ) const
{
  return( GetInteger( pNumber, UCAC2_2MID_OFFSET ) );
}

int UCAC2Reader :: Get2mJ( short & p2mJ ) const
{
  return( GetShort( p2mJ, UCAC2_2MJ_OFFSET ) );
}

int UCAC2Reader :: Get2mH( short & p2mH ) const
{
  return( GetShort( p2mH, UCAC2_2MH_OFFSET ) );
}

int UCAC2Reader :: Get2mKs( short & p2mKs ) const
{
  return( GetShort( p2mKs, UCAC2_2MKS_OFFSET ) );
}

int UCAC2Reader :: Get2mPh( unsigned char & p2mPh ) const
{
  return( GetChar( p2mPh, UCAC2_2MPH_OFFSET ) );
}

int UCAC2Reader :: Get2mCc( unsigned char & p2mCc ) const
{
  return( GetChar( p2mCc, UCAC2_2MCC_OFFSET ) );
}

}}

//---------------------------- End of file ---------------------------
