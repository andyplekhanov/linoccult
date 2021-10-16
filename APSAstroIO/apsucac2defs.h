//------------------------------------------------------------------------------
//
// File:    apsucac2defs.h
//
// Purpose: Fields definition in UCAC2 stars data base file.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 08.02.2006 Initial version
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

#ifndef APS_UCAC2_DEFS_H
#define APS_UCAC2_DEFS_H

namespace aps {

  namespace apsastroio {

/* Right Ascension at epoch J2000.0 (ICRS) */
const unsigned int UCAC2_RA_OFFSET = 0;

/* Declination at epoch J2000.0 (ICRS) */
const unsigned int UCAC2_DEC_OFFSET = 4;

/* Internal UCAC magnitude (red bandpass) */
const unsigned int UCAC2_U2RMAG_OFFSET = 8;

/* s.e. at central epoch in RA (*cos DEm) */
const unsigned int UCAC2_E_RAM_OFFSET = 10;

/* s.e. at central epoch in Dec */
const unsigned int UCAC2_E_DEM_OFFSET = 11;

/* Number of UCAC observations of this star */
const unsigned int UCAC2_NOBS_OFFSET = 12;

/* Error of original UCAC observ. (mas) */
const unsigned int UCAC2_EPOS_OFFSET = 13;

/* # of catalog positions used for pmRA, pmDC */
const unsigned int UCAC2_NCAT_OFFSET = 14;

/* ID of major catalogs used in pmRA, pmDE */
const unsigned int UCAC2_CFLG_OFFSET = 15;

/* Central epoch for mean RA, minus 1975 */
const unsigned int UCAC2_EPRAM_OFFSET = 16;

/* Central epoch for mean DE, minus 1975 */
const unsigned int UCAC2_EPDEM_OFFSET = 18;

/* Proper motion in RA (no cos DE) */
const unsigned int UCAC2_PM_RA_OFFSET = 20;

/* Proper motion in DE */
const unsigned int UCAC2_PM_DE_OFFSET = 24;

/* s.e. of pmRA (*cos DEm) */
const unsigned int UCAC2_EPMRA_OFFSET = 28;

/* s.e. of pmDE */
const unsigned int UCAC2_EPMDE_OFFSET = 29;

/* Goodness of fit for pmRA */
const unsigned int UCAC2_QPMRA_OFFSET = 30;

/* Goodness of fit for pmDE */
const unsigned int UCAC2_QPMDE_OFFSET = 31;

/* 2MASS pts_key star identifier */
const unsigned int UCAC2_2MID_OFFSET = 32;

/* 2MASS J  magnitude */
const unsigned int UCAC2_2MJ_OFFSET = 36;

/* 2MASS H  magnitude */
const unsigned int UCAC2_2MH_OFFSET = 38;

/* 2MASS K_s magnitude */
const unsigned int UCAC2_2MKS_OFFSET = 40;

/* 2MASS modified ph_qual flag */
const unsigned int UCAC2_2MPH_OFFSET = 42;

/* 2MASS modified cc_flg */
const unsigned int UCAC2_2MCC_OFFSET = 43;

const unsigned int UCAC2_RECORD_LENGTH = 44;

}}

#endif

//---------------------------- End of file ---------------------------
