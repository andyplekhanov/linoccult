//------------------------------------------------------------------------------
//
// File:    apsrwodefs.h
//
// Purpose: Fields definition in RWO file.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 02.01.2006 Initial version
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

#ifndef APS_RWO_DEFS_H
#define APS_RWO_DEFS_H

namespace aps {

  namespace apsastroio {

/* Asteroid ID number if available */
const unsigned int RWO_NUMBER_OFFSET = 1;
const unsigned int RWO_NUMBER_LENGTH = 9;
const unsigned int RWO_NUMBER_PAD    = 1;

/* Type of observation: O - OPTICAL S - SATELLITE */
const unsigned int RWO_TYPE_OFFSET = RWO_NUMBER_OFFSET + RWO_NUMBER_LENGTH + RWO_NUMBER_PAD;
const unsigned int RWO_TYPE_LENGTH = 1;
const unsigned int RWO_TYPE_PAD    = 1;

/* Tech */
const unsigned int RWO_TECH_OFFSET = RWO_TYPE_OFFSET + RWO_TYPE_LENGTH + RWO_TYPE_PAD;
const unsigned int RWO_TECH_LENGTH = 1;
const unsigned int RWO_TECH_PAD    = 1;

/* Note */
const unsigned int RWO_NOTE_OFFSET = RWO_TECH_OFFSET + RWO_TECH_LENGTH + RWO_TECH_PAD;
const unsigned int RWO_NOTE_LENGTH = 1;
const unsigned int RWO_NOTE_PAD    = 1;

/* Year */
const unsigned int RWO_YEAR_OFFSET = RWO_NOTE_OFFSET + RWO_NOTE_LENGTH + RWO_NOTE_PAD;
const unsigned int RWO_YEAR_LENGTH = 4;
const unsigned int RWO_YEAR_PAD    = 1;

/* Month */
const unsigned int RWO_MONTH_OFFSET = RWO_YEAR_OFFSET + RWO_YEAR_LENGTH + RWO_YEAR_PAD;
const unsigned int RWO_MONTH_LENGTH = 2;
const unsigned int RWO_MONTH_PAD    = 1;

/* Day */
const unsigned int RWO_DAY_OFFSET   = RWO_MONTH_OFFSET + RWO_MONTH_LENGTH + RWO_MONTH_PAD;
const unsigned int RWO_DAY_LENGTH   = 13;
const unsigned int RWO_DAY_PAD      = 1;

/* Time accuracy */
const unsigned int RWO_TIME_ACC_OFFSET = RWO_DAY_OFFSET + RWO_DAY_LENGTH + RWO_DAY_PAD;
const unsigned int RWO_TIME_ACC_LENGTH = 10;
const unsigned int RWO_TIME_ACC_PAD    = 1;

/* RA_Hour */
const unsigned int RWO_RA_HOUR_OFFSET = RWO_TIME_ACC_OFFSET + RWO_TIME_ACC_LENGTH + RWO_TIME_ACC_PAD;
const unsigned int RWO_RA_HOUR_LENGTH = 2;
const unsigned int RWO_RA_HOUR_PAD    = 1;

/* RA_Min */
const unsigned int RWO_RA_MIN_OFFSET = RWO_RA_HOUR_OFFSET + RWO_RA_HOUR_LENGTH + RWO_RA_HOUR_PAD;
const unsigned int RWO_RA_MIN_LENGTH = 2;
const unsigned int RWO_RA_MIN_PAD    = 1;

/* RA_Sec */
const unsigned int RWO_RA_SEC_OFFSET = RWO_RA_MIN_OFFSET + RWO_RA_MIN_LENGTH + RWO_RA_MIN_PAD;
const unsigned int RWO_RA_SEC_LENGTH = 6;
const unsigned int RWO_RA_SEC_PAD    = 1;

/* RA accuracy */
const unsigned int RWO_RA_ACC_OFFSET = RWO_RA_SEC_OFFSET + RWO_RA_SEC_LENGTH + RWO_RA_SEC_PAD;
const unsigned int RWO_RA_ACC_LENGTH = 10;
const unsigned int RWO_RA_ACC_PAD    = 1;

/* RA RMS */
const unsigned int RWO_RA_RMS_OFFSET = RWO_RA_ACC_OFFSET + RWO_RA_ACC_LENGTH + RWO_RA_ACC_PAD;
const unsigned int RWO_RA_RMS_LENGTH = 8;
const unsigned int RWO_RA_RMS_PAD    = 1;

/* RA force */
const unsigned int RWO_RA_FORCE_OFFSET = RWO_RA_RMS_OFFSET + RWO_RA_RMS_LENGTH + RWO_RA_RMS_PAD;
const unsigned int RWO_RA_FORCE_LENGTH = 1;
const unsigned int RWO_RA_FORCE_PAD    = 1;

/* RA bias */
const unsigned int RWO_RA_BIAS_OFFSET = RWO_RA_FORCE_OFFSET + RWO_RA_FORCE_LENGTH + RWO_RA_FORCE_PAD;
const unsigned int RWO_RA_BIAS_LENGTH = 8;
const unsigned int RWO_RA_BIAS_PAD    = 0;

/* RA resid */
const unsigned int RWO_RA_RESID_OFFSET = RWO_RA_BIAS_OFFSET + RWO_RA_BIAS_LENGTH + RWO_RA_BIAS_PAD;
const unsigned int RWO_RA_RESID_LENGTH = 9;
const unsigned int RWO_RA_RESID_PAD    = 1;

/* Dec_Deg */
const unsigned int RWO_DEC_DEG_OFFSET = RWO_RA_RESID_OFFSET + RWO_RA_RESID_LENGTH + RWO_RA_RESID_PAD;
const unsigned int RWO_DEC_DEG_LENGTH = 3;
const unsigned int RWO_DEC_DEG_PAD    = 1;

/* Dec_Min */
const unsigned int RWO_DEC_MIN_OFFSET = RWO_DEC_DEG_OFFSET + RWO_DEC_DEG_LENGTH + RWO_DEC_DEG_PAD;
const unsigned int RWO_DEC_MIN_LENGTH = 2;
const unsigned int RWO_DEC_MIN_PAD    = 1;

/* Dec_Sec */
const unsigned int RWO_DEC_SEC_OFFSET = RWO_DEC_MIN_OFFSET + RWO_DEC_MIN_LENGTH + RWO_DEC_MIN_PAD;
const unsigned int RWO_DEC_SEC_LENGTH = 5;
const unsigned int RWO_DEC_SEC_PAD    = 1;

/* Dec accuracy */
const unsigned int RWO_DEC_ACC_OFFSET = RWO_DEC_SEC_OFFSET + RWO_DEC_SEC_LENGTH + RWO_DEC_SEC_PAD;
const unsigned int RWO_DEC_ACC_LENGTH = 10;
const unsigned int RWO_DEC_ACC_PAD    = 1;

/* Dec RMS */
const unsigned int RWO_DEC_RMS_OFFSET = RWO_DEC_ACC_OFFSET + RWO_DEC_ACC_LENGTH + RWO_DEC_ACC_PAD;
const unsigned int RWO_DEC_RMS_LENGTH = 8;
const unsigned int RWO_DEC_RMS_PAD    = 1;

/* Dec force */
const unsigned int RWO_DEC_FORCE_OFFSET = RWO_DEC_RMS_OFFSET + RWO_DEC_RMS_LENGTH + RWO_DEC_RMS_PAD;
const unsigned int RWO_DEC_FORCE_LENGTH = 1;
const unsigned int RWO_DEC_FORCE_PAD    = 1;

/* Dec bias */
const unsigned int RWO_DEC_BIAS_OFFSET = RWO_DEC_FORCE_OFFSET + RWO_DEC_FORCE_LENGTH + RWO_DEC_FORCE_PAD;
const unsigned int RWO_DEC_BIAS_LENGTH = 8;
const unsigned int RWO_DEC_BIAS_PAD    = 0;

/* Dec resid */
const unsigned int RWO_DEC_RESID_OFFSET = RWO_DEC_BIAS_OFFSET + RWO_DEC_BIAS_LENGTH + RWO_DEC_BIAS_PAD;
const unsigned int RWO_DEC_RESID_LENGTH = 9;
const unsigned int RWO_DEC_RESID_PAD    = 1;

/* Magnitude */
const unsigned int RWO_MAG_OFFSET = RWO_DEC_RESID_OFFSET + RWO_DEC_RESID_LENGTH + RWO_DEC_RESID_PAD;
const unsigned int RWO_MAG_LENGTH = 19;
const unsigned int RWO_MAG_PAD    = 1;

/* Observatory code */
const unsigned int RWO_OBS_CODE_OFFSET = RWO_MAG_OFFSET + RWO_MAG_LENGTH + RWO_MAG_PAD;
const unsigned int RWO_OBS_CODE_LENGTH = 3;
const unsigned int RWO_OBS_CODE_PAD    = 1;

/* Chi */
const unsigned int RWO_CHI_OFFSET = RWO_OBS_CODE_OFFSET + RWO_OBS_CODE_LENGTH + RWO_OBS_CODE_PAD;
const unsigned int RWO_CHI_LENGTH = 9;
const unsigned int RWO_CHI_PAD    = 1;

/* Sel coord */
const unsigned int RWO_SEL_COORD_OFFSET = RWO_CHI_OFFSET + RWO_CHI_LENGTH + RWO_CHI_PAD;
const unsigned int RWO_SEL_COORD_LENGTH = 1;
const unsigned int RWO_SEL_COORD_PAD    = 1;

/* Sel mag */
const unsigned int RWO_SEL_MAG_OFFSET = RWO_SEL_COORD_OFFSET + RWO_SEL_COORD_LENGTH + RWO_SEL_COORD_PAD;
const unsigned int RWO_SEL_MAG_LENGTH = 1;
const unsigned int RWO_SEL_MAG_PAD    = 0;

const unsigned int RWO_RECORD_LENGTH = RWO_SEL_MAG_OFFSET + RWO_SEL_MAG_LENGTH + RWO_SEL_MAG_PAD;

}}

#endif

//---------------------------- End of file ---------------------------

