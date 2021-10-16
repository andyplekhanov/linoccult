//------------------------------------------------------------------------------
//
// File:    GaiaEDR3Reader.h
//
// Purpose: Gaia star catalog reader.
//          Read data from Gaia EDR3
//   
// (c) 2004-2020 Plekhanov Andrey
//
// Initial version 0.1 9.01.2020
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
         Bytes 	Units 	Format 	Label 	Explanations

        1-4 	int32 	mas 	RA 	Right ascension - truncated to 1 mas precision.
        5 	byte 	4µas 	RA2 	RA. component <1mas. Units of 4 µas. Add to the right ascension
        6-9 	int32 	mas 	Dec 	Declination - truncated (round towards -infinity) to 1 mas precision
                                        truncation: +10.123 = 10; -10.123 = -11
        10 	byte 	4µas 	Dec2 	Dec component <1mas. Units of 4 µas. Value is always added to the signed value of declination.
                                        e.g. +10 + .124 = +10.124; -10 + .124 = -9.876
        11-12 	uint16 	12.5µas 	Parallax. 	Stored in units of 12.5 µas (to include Proxima within range)
        13-16 	int32 	µas/yr 	PM_RA 	Annual proper motion in RA. Value has been multiplied by Cos(declination)
        17-20 	int32 	µas/yr 	PM_Dec 	Annual proper motion in Dec
        21-22 	int16 	km/s 	RV 	Radial velocity
        23-24 	int16 	--- 	Epoch 	Epoch of the positions from 2000.0, in units 0.001 yr.
                                        For stars sourced from Hipparcos, Epoch = 1991.25 (coded as -8750)
        25-26 	int16 	mMag 	Magbp 	Magnitude from the Blue photometer. Available for the majority of stars
        27-28 	int16 	mMag 	Mag G 	Magnitude from Green photometer (essentially, the Visual magnitude). Available for all stars
        29-30 	int16 	mMag 	Magrp 	Magnitude from Red photometer. Available for the majority of stars
        31-32 	uint16 	10µas 	e_RA 	Uncertainty in RA units of 10 µas
        33-34 	uint16 	10µas 	e_Dec 	Uncertainty in Dec units of 10 µas
        35-36 	uint16 	10µas 	e_Parx 	Uncertainty in Parallax units of 10 µas
        37-38 	uint16 	µas/yr 	e_PM_RA 	Uncertainty in Proper motion in RA
        39-40 	uint16 	µas/yr 	e_PM_Dec 	Uncertainty in Proper motion in Dec
        41 	byte 	km/s 	e_RV 	Uncertainty in Radial Velocity
        42 	byte 	--- 	Reliability indicator 	The reliability indicator provides a broad indicator of whether there are issues of concern
                                                        that may affect the accuracy of the star's position beyond the formal standard deviation measure.
                                                        The range of the indicator as provided is 0.0 to 12.6.

                                                        For stars where the position has come from Gaia DR3, the reliability indicator is the Gaia 'RUWE' value.
                                                        Values of RUWE in Gaia range from about 0.3 to over 100; values greater than 12.6 are all coded as 12.6 in this field.
                                                        Values of RUWE greater than 1.4 indicate reduced reliability of the position. Values of zero can also exist;
                                                        in such instances the position is of poor reliability.

                                                        For the approximately 1000 star positions obtained from TGAS (Gaia DR1), the 'astrometric_excess_noise'
                                                        element of that catalogue has been used as the reliability indicator.
                                                        This is described in 'Gaia Data Release 2 - the astrometric solution' A&A, 616, A2 (2018).
                                                        Also in the presentation "Astrometry in Gaia DR1' at the Gaia DR1 workshop, ESAC, 2016 Nov 3.

                                                        For the small number of stars where the position is taken from Hipparcos,
                                                        the indicator is derived using Eqns B1-B4 on page 15 of Daniel Michalik et al:
                                                        Joint astrometric solution of Hipparcos & Gaia, A&A, Vol 571 (Nov 2014).
                                                        These give the chi statistic for the star position, 'which is expected to be around 1.0 for a "good" solution'.

        43 	byte 	--- 	Flags 	The bits in this field are used to flag a range of situations:
                                                        Bit 1 - set if  the Gaia Duplicate Source flag has been set
                                                        Bit 2 - set if there is no Gaia proper motion for the star.
                                                        Bit 3 - when bit 2 set, the proper motion has been derived using the UCAC4 position at 2000.0
                                                        Bit 4 - UCAC4 identifier based on a poor match
        44 	byte 	mas 	Star diameter 	Apparent angular diameter of the star, in mas. Value has been multiplied by 5 (that is, the coding resolution is 0.2 mas)
        45 	byte 	  	G_Version 	The Gaia version used for the positions and Source_ID.
                                                        0 = Hipparcos2 of 2008
                                                        1 = TGAS (DR1)
                                                        2 = DR2
                                                        3 = EDR3
                                                        4 = DR3  ??
                                                        5 = DR4  ??
        46-53 	uint64 	--- 	Source_ID 	The Source ID in the relevant version of Gaia (see G_Version). For stars from Hipparcos, the Hipparcos number is specified.
        54 	byte 	--- 	CatID 	Catalogue identifier (to identify the star using a traditional catalogue entry)
                                                        0 = Not matched. Use star coords to identify  Ghhmmss.s±ddmmss
                                                        2 = Hipparcos.
                                                        3 = Tycho2, '-1' stars
                                                        4 = Tycho2, '-2' stars
                                                        5 = Tycho2, '-3' stars
                                                        6 = UCAC4
        55-58 	uint32 	--- 	CatNum 	Sequential number in catalogue zone (or number in catalogue)
                                                        Star number coding
                                                        Catalogue: 	Number format 	Contents of CatNum 	Extra details
                                                        Hipparcos 	nnnnnnn 	nnnnnnn 	0
                                                        Tycho2 	aaaa-bbbbb-c 	aaaabbbbb 	The last digit (c) is indicated via the CatID
                                                        UCAC4 	zzz-nnnnnn 	zzznnnnnn 	Issues regarding the source of proper motion, and reliability
                                                                                                of the UCAC4 designation, are indicated via the CatID
	 */

#ifndef GAIA_READER_EDR3_H
#define GAIA_READER_EDR3_H

#include <string>

#include "apsibinastroio.h"

namespace aps {

  namespace apsastroio {

//======================= GaiaEDR3Reader ==========================

class GaiaEDR3Reader : protected APSIBinAstroIO
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

    int GetEpoch( uint16_t & pEpoch ) const;

    int GetMagBlue( int16_t & pMagBlue ) const;

    int GetMagGreen( int16_t & pMagGreen ) const;  
    
    int GetMagRed( int16_t & pMagRed ) const;
    
    int GetRAerror( uint16_t & pRAerror ) const;
    
    int GetDecerror( uint16_t & pDecerror ) const;

    int GetParallaxerror( uint16_t & pParallaxerror ) const;
    
    int GetpmRAerror( uint16_t & ppmRAerror ) const;
    
    int GetpmDecerror( uint16_t & ppmDecerror ) const;
    
    int GetVraderror( unsigned char & pVraderror ) const;

    int GetReliability( unsigned char & pReliability ) const;

    int GetFlags( unsigned char & pFlags ) const;  

    int GetStarDiameter( unsigned char & pStarDiameter ) const;

    int GetGVersion( unsigned char & pGVersion ) const;

    int GetSourceID( uint64_t & pSourceID ) const;
    
    int GetCatID( unsigned char & pCatID ) const;
    
    int GetCatNum( uint32_t & pCatNum ) const;

  public:

    GaiaEDR3Reader( const std::string & pGaiaFilePath );

    virtual ~GaiaEDR3Reader( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
