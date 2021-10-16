//------------------------------------------------------------------------------
//
// File:    GaiaEDR3Reader.cc
//
// Purpose: Gaia star catalog reader.
//          Read data from Gaia EDR3
//   
// (c) 2004-2020 Plekhanov Andrey
//
// Initial version 0.1 24.02.2020
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

#include "GaiaEDR3Reader.h"
#include "apsgaiaedr3defs.h"

namespace aps {

  namespace apsastroio {

//======================= GaiaReader ==========================

GaiaEDR3Reader :: GaiaEDR3Reader( const std::string & pGaiaFilePath ) :
                  APSIBinAstroIO( apslib::ABS_ARCH_LITTLE, pGaiaFilePath )
{
}

GaiaEDR3Reader :: ~GaiaEDR3Reader( void )
{
}

int GaiaEDR3Reader :: ReadStar( void )
{
  return( ReadRecord( GAIA_EDR3_RECORD_LENGTH ) );  
}

int GaiaEDR3Reader :: GetStarsNumber( off_t & StarsNumber ) const
{
  off_t FileLength = 0;

  GetLength( FileLength );

  StarsNumber = FileLength / GAIA_EDR3_RECORD_LENGTH;

  return( FileLength % GAIA_EDR3_RECORD_LENGTH );
}

int GaiaEDR3Reader :: GetRA( int32_t & pRA ) const
{
  return( GetInteger( pRA, GAIA_EDR3_RA_OFFSET ) );
}

int GaiaEDR3Reader :: GetRA2( unsigned char & pRA2 ) const
{
  return( GetChar( pRA2, GAIA_EDR3_RA2_OFFSET ) );
} 

int GaiaEDR3Reader :: GetDec( int32_t & pDec ) const
{
  return( GetInteger( pDec, GAIA_EDR3_DEC_OFFSET ) );
}
    
int GaiaEDR3Reader :: GetDec2( unsigned char & pDec2 ) const
{
  return( GetChar( pDec2, GAIA_EDR3_DEC2_OFFSET ) );
}
    
int GaiaEDR3Reader :: GetParallax( uint16_t & pParallax ) const
{
  return( GetUShort( pParallax, GAIA_EDR3_PARALLAX_OFFSET ) );
}

int GaiaEDR3Reader :: GetpmRA( int32_t & ppmRA ) const
{
  return( GetInteger( ppmRA, GAIA_EDR3_PM_RA_OFFSET ) );
}

int GaiaEDR3Reader :: GetpmDec( int32_t & ppmDec ) const
{
  return( GetInteger( ppmDec, GAIA_EDR3_PM_DEC_OFFSET ) );
}

int GaiaEDR3Reader :: GetVrad( int16_t & pVrad ) const
{
  return( GetShort( pVrad, GAIA_EDR3_VRAD_OFFSET ) );
}

int GaiaEDR3Reader :: GetEpoch( uint16_t & pEpoch ) const
{
  return( GetUShort( pEpoch, GAIA_EDR3_EPOCH_OFFSET ) );
} 

int GaiaEDR3Reader :: GetMagBlue( int16_t & pMagBlue ) const
{
  return( GetShort( pMagBlue, GAIA_EDR3_MAG_BLUE_OFFSET ) );
}

int GaiaEDR3Reader :: GetMagGreen( int16_t & pMagGreen ) const
{
  return( GetShort( pMagGreen, GAIA_EDR3_MAG_GREEN_OFFSET ) );
} 
    
int GaiaEDR3Reader :: GetMagRed( int16_t & pMagRed ) const
{
  return( GetShort( pMagRed, GAIA_EDR3_MAG_RED_OFFSET ) );
}
    
int GaiaEDR3Reader :: GetRAerror( uint16_t & pRAerror ) const
{
  return( GetUShort( pRAerror, GAIA_EDR3_ERROR_RA_OFFSET ) );
}
    
int GaiaEDR3Reader :: GetDecerror( uint16_t & pDecerror ) const
{
  return( GetUShort( pDecerror, GAIA_EDR3_ERROR_DEC_OFFSET ) );
}

int GaiaEDR3Reader :: GetParallaxerror( uint16_t & pParallaxerror ) const
{
  return( GetUShort( pParallaxerror, GAIA_EDR3_ERROR_PARALLAX_OFFSET ) );
}  
    
int GaiaEDR3Reader :: GetpmRAerror( uint16_t & ppmRAerror ) const
{
  return( GetUShort( ppmRAerror, GAIA_EDR3_ERROR_PM_RA_OFFSET ) );
}
    
int GaiaEDR3Reader :: GetpmDecerror( uint16_t & ppmDecerror ) const
{
  return( GetUShort( ppmDecerror, GAIA_EDR3_ERROR_PM_DEC_OFFSET ) );
}
    
int GaiaEDR3Reader :: GetVraderror( unsigned char & pVraderror ) const
{
  return( GetChar( pVraderror, GAIA_EDR3_ERROR_VRAD_OFFSET ) );
}

int GaiaEDR3Reader :: GetReliability( unsigned char & pReliability ) const
{
  return( GetChar( pReliability, GAIA_EDR3_RELIABILITY_OFFSET ) );
}  

int GaiaEDR3Reader :: GetFlags( unsigned char & pFlags ) const
{
  return( GetChar( pFlags, GAIA_EDR3_FLAGS_OFFSET ) );
}

int GaiaEDR3Reader :: GetStarDiameter( unsigned char & pStarDiameter ) const
{
  return( GetChar( pStarDiameter, GAIA_EDR3_STAR_DIAMETER_OFFSET ) );
} 

int GaiaEDR3Reader :: GetGVersion( unsigned char & pGVersion ) const
{
  return( GetChar( pGVersion, GAIA_EDR3_GVERSION_OFFSET ) );
} 

int GaiaEDR3Reader :: GetSourceID( uint64_t & pSourceID ) const
{
  return( GetULong( pSourceID, GAIA_EDR3_SOURCE_ID_OFFSET ) );
}
    
int GaiaEDR3Reader :: GetCatID( unsigned char & pCatID ) const
{
  return( GetChar( pCatID, GAIA_EDR3_CAT_ID_OFFSET ) );
}  
    
int GaiaEDR3Reader :: GetCatNum( uint32_t & pCatNum ) const
{
  return( GetUInteger( pCatNum, GAIA_EDR3_CAT_NUM_OFFSET ) );
}

}}

//---------------------------- End of file ---------------------------
