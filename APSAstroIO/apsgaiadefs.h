//------------------------------------------------------------------------------
//
// File:    apsgaiadefs.h
//
// Purpose: Fields definition in Gaia stars data base file.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 11.02.2006 Initial version
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

#ifndef APS_GAIA_DEFS_H
#define APS_GAIA_DEFS_H

namespace aps {

  namespace apsastroio {

// Gaia.dat fields

/* Right ascension - truncated to 1 mas precision. */
const unsigned int GAIA_RA_OFFSET = 0;

/* RA. component <1mas. Units of 4 µas. Add to the right ascension */
const unsigned int GAIA_RA2_OFFSET = 4;

/* Dec truncated to 1 mas precision */
const unsigned int GAIA_DEC_OFFSET = 5;

/* Dec component <1mas. Units of 4 µas. Value is always added to the signed value of declination. */
const unsigned int GAIA_DEC2_OFFSET = 9;

/* Parallax. Stored in units of 12.5 µas */
const unsigned int GAIA_PARALLAX_OFFSET = 10;

/* Annual proper motion in RA µas/yr */
const unsigned int GAIA_PM_RA_OFFSET = 12;

/* Annual proper motion in Dec */
const unsigned int GAIA_PM_DEC_OFFSET = 16;

/* Radial velocity */
const unsigned int GAIA_VRAD_OFFSET = 20;

/* Epoch for RA, units 0.001 yr */
const unsigned int GAIA_EPRA_OFFSET = 22;

/* Epoch for Declination, units 0.001 yr */
const unsigned int GAIA_EPDE_OFFSET = 24;

/* Magnitude from Blue photometer */
const unsigned int GAIA_MAG_BLUE_OFFSET = 26;

/* Magnitude from Red photometer */
const unsigned int GAIA_MAG_RED_OFFSET = 28;

/* Uncertainty in RA units of 10 µas */
const unsigned int GAIA_ERROR_RA_OFFSET = 30;

/* Uncertainty in Dec units of 10 µas */
const unsigned int GAIA_ERROR_DEC_OFFSET = 32;

/* Uncertainty in Parallax units of 10 µas */
const unsigned int GAIA_ERROR_PARALLAX_OFFSET = 34; 

/* Uncertainty in Proper motion in RA */
const unsigned int GAIA_ERROR_PM_RA_OFFSET = 36;

/* Uncertainty in Proper motion in Dec */
const unsigned int GAIA_ERROR_PM_DEC_OFFSET = 38;

/* Uncertainty in Radial Velocity */
const unsigned int GAIA_ERROR_VRAD_OFFSET = 40;

/* Spectral type. High nibble = class, low nibble = subclass */
const unsigned int GAIA_ERROR_SPEC_TYPE_OFFSET = 41;

/* Catalogue identifier  2 = Hipparcos, 3 = Tycho2, 4 = UCAC4, 5 = UCAC2, 6 = USNO-B1, 7 = NOMAD */
const unsigned int GAIA_ERROR_CAT_ID_OFFSET = 42;

/* Sequential number in catalogue zone (or number in catalogue) */
const unsigned int GAIA_ERROR_CAT_NUM_OFFSET = 43;

/* Supplemental digit for Cat ID: Hipparcos, UCAC2, UCAC4 - zero For Tycho-2 : the digit of the third field
   For USNO-B1 and NOMAD - the digits before the last 2 digits of the zone number */
const unsigned int GAIA_ERROR_SUP_NUM_OFFSET = 47;

/* Record length */
const unsigned int GAIA_RECORD_LENGTH = 48;
 
}}

#endif

//---------------------------- End of file ---------------------------
