//------------------------------------------------------------------------------
//
// File:    apsgaiaedr3defs.h
//
// Purpose: Fields definition in Gaia stars data base file.
//   
// (c) 2006-2020 Plekhanov Andrey
//
// Initial version 0.1 9.01.2020 Initial version
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

#ifndef APS_GAIA_EDR3_DEFS_H
#define APS_GAIA_EDR3_DEFS_H

namespace aps {

  namespace apsastroio {

// Gaia EDR3 fields

/* Right ascension - truncated to 1 mas precision. */
const unsigned int GAIA_EDR3_RA_OFFSET = 0;

/* RA. component <1mas. Units of 4 µas. Add to the right ascension */
const unsigned int GAIA_EDR3_RA2_OFFSET = 4;

/* Dec truncated to 1 mas precision */
const unsigned int GAIA_EDR3_DEC_OFFSET = 5;

/* Dec component <1mas. Units of 4 µas. Value is always added to the signed value of declination. */
const unsigned int GAIA_EDR3_DEC2_OFFSET = 9;

/* Parallax. Stored in units of 12.5 µas */
const unsigned int GAIA_EDR3_PARALLAX_OFFSET = 10;

/* Annual proper motion in RA µas/yr */
const unsigned int GAIA_EDR3_PM_RA_OFFSET = 12;

/* Annual proper motion in Dec */
const unsigned int GAIA_EDR3_PM_DEC_OFFSET = 16;

/* Radial velocity */
const unsigned int GAIA_EDR3_VRAD_OFFSET = 20;

/* Epoch of the positions from 2000.0, in units 0.001 yr. */
/* For stars sourced from Hipparcos, Epoch = 1991.25 (coded as -8750) */
const unsigned int GAIA_EDR3_EPOCH_OFFSET = 22;

/* Magnitude from Blue photometer */
const unsigned int GAIA_EDR3_MAG_BLUE_OFFSET = 24;

/* Magnitude from Green photometer */
const unsigned int GAIA_EDR3_MAG_GREEN_OFFSET = 26;

/* Magnitude from Red photometer */
const unsigned int GAIA_EDR3_MAG_RED_OFFSET = 28;

/* Uncertainty in RA units of 10 µas */
const unsigned int GAIA_EDR3_ERROR_RA_OFFSET = 30;

/* Uncertainty in Dec units of 10 µas */
const unsigned int GAIA_EDR3_ERROR_DEC_OFFSET = 32;

/* Uncertainty in Parallax units of 10 µas */
const unsigned int GAIA_EDR3_ERROR_PARALLAX_OFFSET = 34; 

/* Uncertainty in Proper motion in RA */
const unsigned int GAIA_EDR3_ERROR_PM_RA_OFFSET = 36;

/* Uncertainty in Proper motion in Dec */
const unsigned int GAIA_EDR3_ERROR_PM_DEC_OFFSET = 38;

/* Uncertainty in Radial Velocity */
const unsigned int GAIA_EDR3_ERROR_VRAD_OFFSET = 40;

/* Reliability indicator */
const unsigned int GAIA_EDR3_RELIABILITY_OFFSET = 41;

/* Flags */
const unsigned int GAIA_EDR3_FLAGS_OFFSET = 42;

/* Star diameter */
const unsigned int GAIA_EDR3_STAR_DIAMETER_OFFSET = 43;

/* G_Version */
const unsigned int GAIA_EDR3_GVERSION_OFFSET = 44;

/* Source_ID */
const unsigned int GAIA_EDR3_SOURCE_ID_OFFSET = 45;
 
/* Catalogue identifier */
const unsigned int GAIA_EDR3_CAT_ID_OFFSET = 53;

/* Sequential number in catalogue zone (or number in catalogue) */
const unsigned int GAIA_EDR3_CAT_NUM_OFFSET = 54;

/* Record length */
const unsigned int GAIA_EDR3_RECORD_LENGTH = 58;
 
}}

#endif

//---------------------------- End of file ---------------------------
