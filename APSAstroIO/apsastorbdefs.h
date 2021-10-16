//------------------------------------------------------------------------------
//
// File:    apsastorbdefs.h
//
// Purpose: Fields definition in asteroids ephemeris astorb.dat file.
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

#ifndef APS_ASTORB_DEFS_H
#define APS_ASTORB_DEFS_H

namespace aps {

  namespace apsastroio {

// astorb.dat fields

/* Asteroid ID number if available */
const unsigned int ASTER_NUMBER_OFFSET = 0;
const unsigned int ASTER_NUMBER_LENGTH = 6;  /* New astorb format */
const unsigned int ASTER_NUMBER_PAD    = 1;

/* Asteroid MPC Name or Designation if available */
const unsigned int ASTER_NAME_OFFSET   = ASTER_NUMBER_OFFSET + ASTER_NUMBER_LENGTH + ASTER_NUMBER_PAD;
const unsigned int ASTER_NAME_LENGTH   = 18;
const unsigned int ASTER_NAME_PAD      = 1;

/* Orbit computor */
const unsigned int ASTER_AUTHOR_OFFSET = ASTER_NAME_OFFSET + ASTER_NAME_LENGTH + ASTER_NAME_PAD;
const unsigned int ASTER_AUTHOR_LENGTH = 15;
const unsigned int ASTER_AUTHOR_PAD    = 1;

/* Absolute magnitude */
const unsigned int ASTER_BRIGHTNESS_OFFSET = ASTER_AUTHOR_OFFSET + ASTER_AUTHOR_LENGTH + ASTER_AUTHOR_PAD;
const unsigned int ASTER_BRIGHTNESS_LENGTH = 5;
const unsigned int ASTER_BRIGHTNESS_PAD    = 1;

/* Slope parameter */
const unsigned int ASTER_SLOPE_OFFSET = ASTER_BRIGHTNESS_OFFSET + ASTER_BRIGHTNESS_LENGTH + ASTER_BRIGHTNESS_PAD;
const unsigned int ASTER_SLOPE_LENGTH      = 5;
const unsigned int ASTER_SLOPE_PAD         = 1;

/* Colour Index */
const unsigned int ASTER_COLOR_OFFSET = ASTER_SLOPE_OFFSET + ASTER_SLOPE_LENGTH + ASTER_SLOPE_PAD;
const unsigned int ASTER_COLOR_LENGTH = 4;
const unsigned int ASTER_COLOR_PAD    = 1;

/* IRAS Diameter */
const unsigned int ASTER_DIAM_OFFSET = ASTER_COLOR_OFFSET + ASTER_COLOR_LENGTH + ASTER_COLOR_PAD;
const unsigned int ASTER_DIAM_LENGTH = 5;
const unsigned int ASTER_DIAM_PAD    = 1;

/* Taxonomic class */
const unsigned int ASTER_TAXON_OFFSET = ASTER_DIAM_OFFSET + ASTER_DIAM_LENGTH + ASTER_DIAM_PAD;
const unsigned int ASTER_TAXON_LENGTH = 4;
const unsigned int ASTER_TAXON_PAD    = 1;

/* Codes */
const unsigned int ASTER_CODE1_OFFSET = ASTER_TAXON_OFFSET + ASTER_TAXON_LENGTH + ASTER_TAXON_PAD;
const unsigned int ASTER_CODE1_LENGTH = 4;
const unsigned int ASTER_CODE1_PAD    = 0;

const unsigned int ASTER_CODE2_OFFSET = ASTER_CODE1_OFFSET + ASTER_CODE1_LENGTH + ASTER_CODE1_PAD;
const unsigned int ASTER_CODE2_LENGTH = 4;
const unsigned int ASTER_CODE2_PAD    = 0;

const unsigned int ASTER_CODE3_OFFSET = ASTER_CODE2_OFFSET + ASTER_CODE2_LENGTH + ASTER_CODE2_PAD;
const unsigned int ASTER_CODE3_LENGTH = 4;
const unsigned int ASTER_CODE3_PAD    = 0;

const unsigned int ASTER_CODE4_OFFSET = ASTER_CODE3_OFFSET + ASTER_CODE3_LENGTH + ASTER_CODE3_PAD;
const unsigned int ASTER_CODE4_LENGTH = 4;
const unsigned int ASTER_CODE4_PAD    = 0;

const unsigned int ASTER_CODE5_OFFSET = ASTER_CODE4_OFFSET + ASTER_CODE4_LENGTH + ASTER_CODE4_PAD;
const unsigned int ASTER_CODE5_LENGTH = 4;
const unsigned int ASTER_CODE5_PAD    = 0;

const unsigned int ASTER_CODE6_OFFSET = ASTER_CODE5_OFFSET + ASTER_CODE5_LENGTH + ASTER_CODE5_PAD;
const unsigned int ASTER_CODE6_LENGTH = 4;
const unsigned int ASTER_CODE6_PAD    = 1;

/* Orbital arc */
const unsigned int ASTER_ARC_OFFSET = ASTER_CODE6_OFFSET + ASTER_CODE6_LENGTH + ASTER_CODE6_PAD;
const unsigned int ASTER_ARC_LENGTH = 5; 
const unsigned int ASTER_ARC_PAD    = 0;

/* Number of observations */
const unsigned int ASTER_OBSERV_OFFSET = ASTER_ARC_OFFSET + ASTER_ARC_LENGTH + ASTER_ARC_PAD;
const unsigned int ASTER_OBSERV_LENGTH = 5;
const unsigned int ASTER_OBSERV_PAD    = 1;

/* Epoch of observation */
const unsigned int ASTER_OBS_YEAR_OFFSET = ASTER_OBSERV_OFFSET + ASTER_OBSERV_LENGTH + ASTER_OBSERV_PAD;
const unsigned int ASTER_OBS_YEAR_LENGTH = 4;
const unsigned int ASTER_OBS_YEAR_PAD    = 0;

const unsigned int ASTER_OBS_MONTH_OFFSET = ASTER_OBS_YEAR_OFFSET + ASTER_OBS_YEAR_LENGTH + ASTER_OBS_YEAR_PAD;
const unsigned int ASTER_OBS_MONTH_LENGTH = 2; 
const unsigned int ASTER_OBS_MONTH_PAD    = 0;

const unsigned int ASTER_OBS_DAY_OFFSET = ASTER_OBS_MONTH_OFFSET + ASTER_OBS_MONTH_LENGTH + ASTER_OBS_MONTH_PAD;
const unsigned int ASTER_OBS_DAY_LENGTH = 2;
const unsigned int ASTER_OBS_DAY_PAD    = 1;

/* Orbit elements */
const unsigned int ASTER_ORBIT_M_OFFSET = ASTER_OBS_DAY_OFFSET + ASTER_OBS_DAY_LENGTH + ASTER_OBS_DAY_PAD;
const unsigned int ASTER_ORBIT_M_LENGTH = 10;
const unsigned int ASTER_ORBIT_M_PAD    = 1;

const unsigned int ASTER_ORBIT_W_OFFSET = ASTER_ORBIT_M_OFFSET + ASTER_ORBIT_M_LENGTH + ASTER_ORBIT_M_PAD;
const unsigned int ASTER_ORBIT_W_LENGTH = 10;
const unsigned int ASTER_ORBIT_W_PAD    = 1;

const unsigned int ASTER_ORBIT_O_OFFSET = ASTER_ORBIT_W_OFFSET + ASTER_ORBIT_W_LENGTH + ASTER_ORBIT_W_PAD;
const unsigned int ASTER_ORBIT_O_LENGTH = 10;
const unsigned int ASTER_ORBIT_O_PAD    = 0;

const unsigned int ASTER_ORBIT_I_OFFSET = ASTER_ORBIT_O_OFFSET + ASTER_ORBIT_O_LENGTH + ASTER_ORBIT_O_PAD;
const unsigned int ASTER_ORBIT_I_LENGTH = 10;
const unsigned int ASTER_ORBIT_I_PAD    = 1;

const unsigned int ASTER_ORBIT_E_OFFSET = ASTER_ORBIT_I_OFFSET + ASTER_ORBIT_I_LENGTH + ASTER_ORBIT_I_PAD;
const unsigned int ASTER_ORBIT_E_LENGTH = 10;
const unsigned int ASTER_ORBIT_E_PAD    = 1;

const unsigned int ASTER_ORBIT_A_OFFSET = ASTER_ORBIT_E_OFFSET + ASTER_ORBIT_E_LENGTH + ASTER_ORBIT_E_PAD;
const unsigned int ASTER_ORBIT_A_LENGTH = 12;
const unsigned int ASTER_ORBIT_A_PAD    = 1;

/* Epoch of Orbit computation */
const unsigned int ASTER_CMP_YEAR_OFFSET = ASTER_ORBIT_A_OFFSET + ASTER_ORBIT_A_LENGTH + ASTER_ORBIT_A_PAD;
const unsigned int ASTER_CMP_YEAR_LENGTH = 4;
const unsigned int ASTER_CMP_YEAR_PAD    = 0;

const unsigned int ASTER_CMP_MONTH_OFFSET = ASTER_CMP_YEAR_OFFSET + ASTER_CMP_YEAR_LENGTH + ASTER_CMP_YEAR_PAD;
const unsigned int ASTER_CMP_MONTH_LENGTH = 2; 
const unsigned int ASTER_CMP_MONTH_PAD    = 0;

const unsigned int ASTER_CMP_DAY_OFFSET = ASTER_CMP_MONTH_OFFSET + ASTER_CMP_MONTH_LENGTH + ASTER_CMP_MONTH_PAD;
const unsigned int ASTER_CMP_DAY_LENGTH = 2;
const unsigned int ASTER_CMP_DAY_PAD    = 1;

/* Current Ephemeris Uncertainty */
const unsigned int ASTER_UNCERT_OFFSET = ASTER_CMP_DAY_OFFSET + ASTER_CMP_DAY_LENGTH + ASTER_CMP_DAY_PAD;
const unsigned int ASTER_UNCERT_LENGTH = 7;
const unsigned int ASTER_UNCERT_PAD    = 1;

/* Rate of change of Current Ephemeris Uncertainty */
const unsigned int ASTER_UNCERT_RATE_OFFSET = ASTER_UNCERT_OFFSET + ASTER_UNCERT_LENGTH + ASTER_UNCERT_PAD;
const unsigned int ASTER_UNCERT_RATE_LENGTH = 8;
const unsigned int ASTER_UNCERT_RATE_PAD    = 1;

/* Epoch of CEU */
const unsigned int ASTER_CEU_YEAR_OFFSET = ASTER_UNCERT_RATE_OFFSET + ASTER_UNCERT_RATE_LENGTH + ASTER_UNCERT_RATE_PAD;
const unsigned int ASTER_CEU_YEAR_LENGTH = 4;
const unsigned int ASTER_CEU_YEAR_PAD    = 0;

const unsigned int ASTER_CEU_MONTH_OFFSET = ASTER_CEU_YEAR_OFFSET + ASTER_CEU_YEAR_LENGTH + ASTER_CEU_YEAR_PAD;
const unsigned int ASTER_CEU_MONTH_LENGTH = 2; 
const unsigned int ASTER_CEU_MONTH_PAD    = 0;

const unsigned int ASTER_CEU_DAY_OFFSET = ASTER_CEU_MONTH_OFFSET + ASTER_CEU_MONTH_LENGTH + ASTER_CEU_MONTH_PAD;
const unsigned int ASTER_CEU_DAY_LENGTH = 2;
const unsigned int ASTER_CEU_DAY_PAD    = 1;

/* Next Peak Ephemeris Uncertainty */
const unsigned int ASTER_UNCERT_NEXT_OFFSET = ASTER_CEU_DAY_OFFSET + ASTER_CEU_DAY_LENGTH + ASTER_CEU_DAY_PAD;
const unsigned int ASTER_UNCERT_NEXT_LENGTH = 7;
const unsigned int ASTER_UNCERT_NEXT_PAD    = 1;

/* Epoch of PEU */
const unsigned int ASTER_PEU_YEAR_OFFSET = ASTER_UNCERT_NEXT_OFFSET + ASTER_UNCERT_NEXT_LENGTH + ASTER_UNCERT_NEXT_PAD;
const unsigned int ASTER_PEU_YEAR_LENGTH = 4;
const unsigned int ASTER_PEU_YEAR_PAD    = 0;

const unsigned int ASTER_PEU_MONTH_OFFSET = ASTER_PEU_YEAR_OFFSET + ASTER_PEU_YEAR_LENGTH + ASTER_PEU_YEAR_PAD;
const unsigned int ASTER_PEU_MONTH_LENGTH = 2; 
const unsigned int ASTER_PEU_MONTH_PAD    = 0;

const unsigned int ASTER_PEU_DAY_OFFSET = ASTER_PEU_MONTH_OFFSET + ASTER_PEU_MONTH_LENGTH + ASTER_PEU_MONTH_PAD;
const unsigned int ASTER_PEU_DAY_LENGTH = 2;
const unsigned int ASTER_PEU_DAY_PAD    = 1;

/* Greatest Peak Ephemeris Uncertainty */
const unsigned int ASTER_UNCERT_GREAT_OFFSET = ASTER_PEU_DAY_OFFSET + ASTER_PEU_DAY_LENGTH + ASTER_PEU_DAY_PAD;
const unsigned int ASTER_UNCERT_GREAT_LENGTH = 7;
const unsigned int ASTER_UNCERT_GREAT_PAD    = 1;

/* Epoch of GEU */
const unsigned int ASTER_GEU_YEAR_OFFSET = ASTER_UNCERT_GREAT_OFFSET + ASTER_UNCERT_GREAT_LENGTH + ASTER_UNCERT_GREAT_PAD;
const unsigned int ASTER_GEU_YEAR_LENGTH = 4;
const unsigned int ASTER_GEU_YEAR_PAD    = 0;

const unsigned int ASTER_GEU_MONTH_OFFSET = ASTER_GEU_YEAR_OFFSET + ASTER_GEU_YEAR_LENGTH + ASTER_GEU_YEAR_PAD;
const unsigned int ASTER_GEU_MONTH_LENGTH = 2; 
const unsigned int ASTER_GEU_MONTH_PAD    = 0;

const unsigned int ASTER_GEU_DAY_OFFSET = ASTER_GEU_MONTH_OFFSET + ASTER_GEU_MONTH_LENGTH + ASTER_GEU_MONTH_PAD;
const unsigned int ASTER_GEU_DAY_LENGTH = 2;
const unsigned int ASTER_GEU_DAY_PAD    = 1;

/* Greatest Peak 2 Ephemeris Uncertainty */
const unsigned int ASTER_UNCERT_GREAT2_OFFSET = ASTER_GEU_DAY_OFFSET + ASTER_GEU_DAY_LENGTH + ASTER_GEU_DAY_PAD;
const unsigned int ASTER_UNCERT_GREAT2_LENGTH = 7;
const unsigned int ASTER_UNCERT_GREAT2_PAD    = 1;

/* Epoch of GEU2 */
const unsigned int ASTER_GEU2_YEAR_OFFSET = ASTER_UNCERT_GREAT2_OFFSET + ASTER_UNCERT_GREAT2_LENGTH + ASTER_UNCERT_GREAT2_PAD;
const unsigned int ASTER_GEU2_YEAR_LENGTH = 4;
const unsigned int ASTER_GEU2_YEAR_PAD    = 0;

const unsigned int ASTER_GEU2_MONTH_OFFSET = ASTER_GEU2_YEAR_OFFSET + ASTER_GEU2_YEAR_LENGTH + ASTER_GEU2_YEAR_PAD;
const unsigned int ASTER_GEU2_MONTH_LENGTH = 2; 
const unsigned int ASTER_GEU2_MONTH_PAD    = 0;

const unsigned int ASTER_GEU2_DAY_OFFSET = ASTER_GEU2_MONTH_OFFSET + ASTER_GEU2_MONTH_LENGTH + ASTER_GEU2_MONTH_PAD;
const unsigned int ASTER_GEU2_DAY_LENGTH = 2;

const unsigned int ASTER_NEW_STRING1    = 2; // For Dos & Windows
const unsigned int ASTER_NEW_STRING2    = 1; // For UNIX
const unsigned int ASTER_RECORD_LENGTH1 = ASTER_GEU2_DAY_OFFSET + ASTER_GEU2_DAY_LENGTH + ASTER_NEW_STRING1;
const unsigned int ASTER_RECORD_LENGTH2 = ASTER_GEU2_DAY_OFFSET + ASTER_GEU2_DAY_LENGTH + ASTER_NEW_STRING2;

}}

#endif

//---------------------------- End of file ---------------------------
