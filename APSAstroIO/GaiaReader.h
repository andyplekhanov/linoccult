//------------------------------------------------------------------------------
//
// File:    GaiaReader.h
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

        /*  FILE RECORD FORMAT
         * 
         Byte-by-byte Description of file: 
        ----------------------------------------------------------------------------------
           Bytes Format   Units   Label      Explanations
        ----------------------------------------------------------------------------------
           1-  4  int32     mas   RA         Right ascension - truncated to 1 mas precision.
               5  byte     4µas   RA2        RA. component <1mas. Units of 4 µas
                                                Add to the right ascension
           6-  9  int32     mas   Dec        Declination - truncated (round towards -infinity) to 1 mas precision:
										        truncation:  +10.123 = +10; -10.123 = -11
              10  byte     4µas   Dec2       Dec component <1mas. Units of 4 µas. 
                                                Value is always added to the signed value of declination. 
										        e.g.  +10 + .124 = +10.124; -10 + .124 = -9.876
          11- 12 uint16 12.5µas   Parx       Parallax. Stored in units of 12.5 µas (to include Proxima within range)
          13- 16  int32   µas/yr  PM_RA      Annual proper motion in RA
          17- 20  int32   µas/yr  PM_Dec     Annual proper motion in Dec
          21- 22  int16     km/s  RV         Radial velocity
          23- 24 uint16     ---   EpRA-2000  Epoch for RA, units 0.001 yr
          25- 26 uint16     ---   EpDe-2000  Epoch for Declination, units 0.001 yr
          27- 28  int16     mMag  Mag G      Magnitude from Blue photometer
          29- 30  int16     mMag  Mag        Magnitude from Red photometer
          31- 32 uint16   10µas   e_RA       Uncertainty in RA units of 10 µas
          33- 34 uint16   10µas   e_Dec      Uncertainty in Dec units of 10 µas
          35- 36 uint16   10µas   e_Parx     Uncertainty in Parallax units of 10 µas
          37- 38 uint16   µas/yr  e_PM_RA    Uncertainty in Proper motion in RA
          39- 40 uint16   µas/yr  e_PM_Dec   Uncertainty in Proper motion in Dec
              41  byte      km/s  e_RV       Uncertainty in Radial Velocity 
              42  byte      ---   Spec       Spectral type. High nibble = class, low nibble = subclass (****)
              43  byte      ---   CatID      Catalogue identifier  2 = Hipparcos, 3 = Tycho2, 4 = UCAC4, 5 = UCAC2, 6 = USNO-B1, 7 = NOMAD
          44- 47 uint32     ---   CatNum     Sequential number in catalogue zone (or number in catalogue)
              48  byte      ---   SupNum     Supplemental digit for Cat ID:
                                                Hipparcos, UCAC2, UCAC4 - zero
                                                For Tycho-2 : the digit of the third field
                                                For USNO-B1 and NOMAD - the digits before the last 2 digits of the zone number
         --------------------------------------------------------------------------------
         Star number coding
            Hipparcos:  nnnnnnn
			            CatNum = nnnnnnn, SupNum = 0
            Tycho2: aaaa-bbbbb-c  
			            CatNum = aaaabbbbb, SupNum = c
            UCAC4: zzz-nnnnnn
			            CatNum = zzznnnnnn, SupNum = 0
            UCAC2: nnnnnnnn
			            CatNum = nnnnnnnn, SupNum = 0
            USNO-B1, NOMAD: ZZzz-nnnnnnn  
			            CatNum = zznnnnnnn, SupNum = ZZ
         */

#ifndef GAIA_READER_H
#define GAIA_READER_H

#include <string>

#include "apsibinastroio.h"

namespace aps {

  namespace apsastroio {

//======================= GaiaReader ==========================

class GaiaReader : protected APSIBinAstroIO
{
  protected:

    int ReadStar( void );

    int GetStarsNumber( off_t & StarsNumber ) const;

    int GetRA( int32_t & pRA ) const;

    int GetRA2( unsigned char & pRA2 ) const;

    int GetDec( int32_t & pDec ) const;

    int GetDec2( unsigned char & pDec2 ) const;
    
    int GetParallax( uint16_t & pParallax ) const;

    int GetpmRA( int32_t & ppmRA ) const;

    int GetpmDec( int32_t & ppmDec ) const; 

    int GetVrad( int16_t & pVrad ) const;

    int GetepRA( uint16_t & pepRA ) const;

    int GetepDec( uint16_t & pepDec ) const;

    int GetMagBlue( int16_t & pMagBlue ) const;
    
    int GetMagRed( int16_t & pMagRed ) const;
    
    int GetRAerror( uint16_t & pRAerror ) const;
    
    int GetDecerror( uint16_t & pDecerror ) const;

    int GetParallaxerror( uint16_t & pParallaxerror ) const;
    
    int GetpmRAerror( uint16_t & ppmRAerror ) const;
    
    int GetpmDecerror( uint16_t & ppmDecerror ) const;
    
    int GetVraderror( unsigned char & pVraderror ) const;

    int GetSpecType( unsigned char & pSpecType ) const;
    
    int GetCatID( unsigned char & pCatID ) const;
    
    int GetCatNum( uint32_t & pCatNum ) const;
    
    int GetSupNum( unsigned char & pSupNum ) const;

  public:

    GaiaReader( const std::string & pGaiaFilePath );

    virtual ~GaiaReader( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
