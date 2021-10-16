//------------------------------------------------------------------------------
//
// File:    GaiaReader.cc
//
// Purpose: Gaia star catalog reader.
//          Read data from Gaia14.dat.
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

#include "GaiaReader.h"
#include "apsgaiadefs.h"

namespace aps {

  namespace apsastroio {

//======================= GaiaReader ==========================

GaiaReader :: GaiaReader( const std::string & pGaiaFilePath ) :
              APSIBinAstroIO( apslib::ABS_ARCH_LITTLE, pGaiaFilePath )
{
}

GaiaReader :: ~GaiaReader( void )
{
}

int GaiaReader :: ReadStar( void )
{
  return( ReadRecord( GAIA_RECORD_LENGTH ) );  
}

int GaiaReader :: GetStarsNumber( off_t & StarsNumber ) const
{
  off_t FileLength = 0;

  GetLength( FileLength );

  StarsNumber = FileLength / GAIA_RECORD_LENGTH;

  return( FileLength % GAIA_RECORD_LENGTH );
}

int GaiaReader :: GetRA( int32_t & pRA ) const
{
  return( GetInteger( pRA, GAIA_RA_OFFSET ) );
}

int GaiaReader :: GetRA2( unsigned char & pRA2 ) const
{
  return( GetChar( pRA2, GAIA_RA2_OFFSET ) );
} 

int GaiaReader :: GetDec( int32_t & pDec ) const
{
  return( GetInteger( pDec, GAIA_DEC_OFFSET ) );
}
    
int GaiaReader :: GetDec2( unsigned char & pDec2 ) const
{
  return( GetChar( pDec2, GAIA_DEC2_OFFSET ) );
}
    
int GaiaReader :: GetParallax( uint16_t & pParallax ) const
{
  return( GetUShort( pParallax, GAIA_PARALLAX_OFFSET ) );
}

int GaiaReader :: GetpmRA( int32_t & ppmRA ) const
{
  return( GetInteger( ppmRA, GAIA_PM_RA_OFFSET ) );
}

int GaiaReader :: GetpmDec( int32_t & ppmDec ) const
{
  return( GetInteger( ppmDec, GAIA_PM_DEC_OFFSET ) );
}

int GaiaReader :: GetVrad( int16_t & pVrad ) const
{
  return( GetShort( pVrad, GAIA_VRAD_OFFSET ) );
}

int GaiaReader :: GetepRA( uint16_t & pepRA ) const
{
  return( GetUShort( pepRA, GAIA_EPRA_OFFSET ) );
} 

int GaiaReader :: GetepDec( uint16_t & pepDec ) const
{
  return( GetUShort( pepDec, GAIA_EPDE_OFFSET ) );
}  

int GaiaReader :: GetMagBlue( int16_t & pMagBlue ) const
{
  return( GetShort( pMagBlue, GAIA_MAG_BLUE_OFFSET ) );
}  
    
int GaiaReader :: GetMagRed( int16_t & pMagRed ) const
{
  return( GetShort( pMagRed, GAIA_MAG_RED_OFFSET ) );
}
    
int GaiaReader :: GetRAerror( uint16_t & pRAerror ) const
{
  return( GetUShort( pRAerror, GAIA_ERROR_RA_OFFSET ) );
}
    
int GaiaReader :: GetDecerror( uint16_t & pDecerror ) const
{
  return( GetUShort( pDecerror, GAIA_ERROR_DEC_OFFSET ) );
}

int GaiaReader :: GetParallaxerror( uint16_t & pParallaxerror ) const
{
  return( GetUShort( pParallaxerror, GAIA_ERROR_PARALLAX_OFFSET ) );
}  
    
int GaiaReader :: GetpmRAerror( uint16_t & ppmRAerror ) const
{
  return( GetUShort( ppmRAerror, GAIA_ERROR_PM_RA_OFFSET ) );
}
    
int GaiaReader :: GetpmDecerror( uint16_t & ppmDecerror ) const
{
  return( GetUShort( ppmDecerror, GAIA_ERROR_PM_DEC_OFFSET ) );
}
    
int GaiaReader :: GetVraderror( unsigned char & pVraderror ) const
{
  return( GetChar( pVraderror, GAIA_ERROR_VRAD_OFFSET ) );
}

int GaiaReader :: GetSpecType( unsigned char & pSpecType ) const
{
  return( GetChar( pSpecType, GAIA_ERROR_SPEC_TYPE_OFFSET ) );
}  
    
int GaiaReader :: GetCatID( unsigned char & pCatID ) const
{
  return( GetChar( pCatID, GAIA_ERROR_CAT_ID_OFFSET ) );
}  
    
int GaiaReader :: GetCatNum( uint32_t & pCatNum ) const
{
  return( GetUInteger( pCatNum, GAIA_ERROR_CAT_NUM_OFFSET ) );
}
    
int GaiaReader :: GetSupNum( unsigned char & pSupNum ) const
{
  return( GetChar( pSupNum, GAIA_ERROR_SUP_NUM_OFFSET ) );
}

}}

//---------------------------- End of file ---------------------------
