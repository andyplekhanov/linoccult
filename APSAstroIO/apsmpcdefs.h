//------------------------------------------------------------------------------
//
// File:    apsmpcdefs.h
//
// Purpose: Fields definition in MPC observation file.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 26.12.2005 Initial version
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

#ifndef APS_MPC_DEFS_H
#define APS_MPC_DEFS_H

namespace aps {

  namespace apsastroio {

/* Asteroid ID number if available */
const unsigned int MPC_NUMBER_OFFSET = 0;
const unsigned int MPC_NUMBER_LENGTH = 5;
const unsigned int MPC_NUMBER_PAD    = 0;

/* Provisional or temporary designation */
const unsigned int MPC_NAME_OFFSET   = MPC_NUMBER_OFFSET + MPC_NUMBER_LENGTH + MPC_NUMBER_PAD;
const unsigned int MPC_NAME_LENGTH   = 7;
const unsigned int MPC_NAME_PAD      = 0;

/* Discovery asterisk */
const unsigned int MPC_ASTERISK_OFFSET = MPC_NAME_OFFSET + MPC_NAME_LENGTH + MPC_NAME_PAD;
const unsigned int MPC_ASTERISK_LENGTH = 1;
const unsigned int MPC_ASTERISK_PAD    = 0;

/* Note 1 */
const unsigned int MPC_NOTE1_OFFSET   = MPC_ASTERISK_OFFSET + MPC_ASTERISK_LENGTH + MPC_ASTERISK_PAD;
const unsigned int MPC_NOTE1_LENGTH   = 1;
const unsigned int MPC_NOTE1_PAD      = 0;

/* Note 2 */
const unsigned int MPC_NOTE2_OFFSET   = MPC_NOTE1_OFFSET + MPC_NOTE1_LENGTH + MPC_NOTE1_PAD;
const unsigned int MPC_NOTE2_LENGTH   = 1;
const unsigned int MPC_NOTE2_PAD      = 0;

/* Year */
const unsigned int MPC_YEAR_OFFSET    = MPC_NOTE2_OFFSET + MPC_NOTE2_LENGTH + MPC_NOTE2_PAD;
const unsigned int MPC_YEAR_LENGTH    = 4;
const unsigned int MPC_YEAR_PAD       = 1;

/* Month */
const unsigned int MPC_MONTH_OFFSET   = MPC_YEAR_OFFSET + MPC_YEAR_LENGTH + MPC_YEAR_PAD;
const unsigned int MPC_MONTH_LENGTH   = 2;
const unsigned int MPC_MONTH_PAD      = 1;

/* Day */
const unsigned int MPC_DAY_OFFSET     = MPC_MONTH_OFFSET + MPC_MONTH_LENGTH + MPC_MONTH_PAD;
const unsigned int MPC_DAY_LENGTH     = 9;
const unsigned int MPC_DAY_PAD        = 0;

/* RA_Hour */
const unsigned int MPC_RA_HOUR_OFFSET = MPC_DAY_OFFSET + MPC_DAY_LENGTH + MPC_DAY_PAD;
const unsigned int MPC_RA_HOUR_LENGTH = 2;
const unsigned int MPC_RA_HOUR_PAD    = 1;

/* RA_Min */
const unsigned int MPC_RA_MIN_OFFSET = MPC_RA_HOUR_OFFSET + MPC_RA_HOUR_LENGTH + MPC_RA_HOUR_PAD;
const unsigned int MPC_RA_MIN_LENGTH = 2;
const unsigned int MPC_RA_MIN_PAD    = 1;

/* RA_Sec */
const unsigned int MPC_RA_SEC_OFFSET = MPC_RA_MIN_OFFSET + MPC_RA_MIN_LENGTH + MPC_RA_MIN_PAD;
const unsigned int MPC_RA_SEC_LENGTH = 6;
const unsigned int MPC_RA_SEC_PAD    = 0;

/* Dec_Deg */
const unsigned int MPC_DEC_DEG_OFFSET = MPC_RA_SEC_OFFSET + MPC_RA_SEC_LENGTH + MPC_RA_SEC_PAD;
const unsigned int MPC_DEC_DEG_LENGTH = 3;
const unsigned int MPC_DEC_DEG_PAD    = 1;

/* Dec_Min */
const unsigned int MPC_DEC_MIN_OFFSET = MPC_DEC_DEG_OFFSET + MPC_DEC_DEG_LENGTH + MPC_DEC_DEG_PAD;
const unsigned int MPC_DEC_MIN_LENGTH = 2;
const unsigned int MPC_DEC_MIN_PAD    = 1;

/* Dec_Sec */
const unsigned int MPC_DEC_SEC_OFFSET = MPC_DEC_MIN_OFFSET + MPC_DEC_MIN_LENGTH + MPC_DEC_MIN_PAD;
const unsigned int MPC_DEC_SEC_LENGTH = 5;
const unsigned int MPC_DEC_SEC_PAD    = 0;

/* Blank 1 */
const unsigned int MPC_BLANK1_OFFSET  = MPC_DEC_SEC_OFFSET + MPC_DEC_SEC_LENGTH + MPC_DEC_SEC_PAD;
const unsigned int MPC_BLANK1_LENGTH  = 9;
const unsigned int MPC_BLANK1_PAD     = 0;

/* Magnitude */
const unsigned int MPC_MAGNITUDE_OFFSET = MPC_BLANK1_OFFSET + MPC_BLANK1_LENGTH + MPC_BLANK1_PAD;
const unsigned int MPC_MAGNITUDE_LENGTH = 5;
const unsigned int MPC_MAGNITUDE_PAD    = 0;

/* Band */
const unsigned int MPC_BAND_OFFSET    = MPC_MAGNITUDE_OFFSET + MPC_MAGNITUDE_LENGTH + MPC_MAGNITUDE_PAD;
const unsigned int MPC_BAND_LENGTH    = 1;
const unsigned int MPC_BAND_PAD       = 0;

/* Blank 2 */
const unsigned int MPC_BLANK2_OFFSET  = MPC_BAND_OFFSET + MPC_BAND_LENGTH + MPC_BAND_PAD;
const unsigned int MPC_BLANK2_LENGTH  = 6;
const unsigned int MPC_BLANK2_PAD     = 0;

/* Observatory code */
const unsigned int MPC_OBS_CODE_OFFSET = MPC_BLANK2_OFFSET + MPC_BLANK2_LENGTH + MPC_BLANK2_PAD;
const unsigned int MPC_OBS_CODE_LENGTH = 3;
const unsigned int MPC_OBS_CODE_PAD    = 0;

const unsigned int MPC_RECORD_LENGTH = MPC_OBS_CODE_OFFSET + MPC_OBS_CODE_LENGTH + MPC_OBS_CODE_PAD;

}}

#endif

//---------------------------- End of file ---------------------------

