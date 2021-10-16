//------------------------------------------------------------------------------
//
// File:    apstycho2defs.h
//
// Purpose: Fields definition in Tycho2 stars data base file.
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

#ifndef APS_TYCHO2_DEFS_H
#define APS_TYCHO2_DEFS_H

namespace aps {

  namespace apsastroio {

// Tycho.dat fields

/* RA in deg */
const unsigned int TYCHO_RA_OFFSET = 0;

/* Annual Proper motion in RA */
const unsigned int TYCHO_PM_RA_OFFSET = 4;

/* Dec in deg */
const unsigned int TYCHO_DEC_OFFSET = 8;

/* Annual Proper motion in Dec */
const unsigned int TYCHO_PM_DEC_OFFSET = 12;

/* Parallax */
const unsigned int TYCHO_PARALLAX_OFFSET = 16;

/* Mv */
const unsigned int TYCHO_MV_OFFSET = 18;

/* Mp */
const unsigned int TYCHO_MP_OFFSET = 20;

/* Catalogue */
const unsigned int TYCHO_CATALOGUE_OFFSET = 22;

/* Catalogue number */
const unsigned int TYCHO_NUMBER_OFFSET = 23;

/* Record length */
const unsigned int TYCHO_RECORD_LENGTH = 27;

}}

#endif

//---------------------------- End of file ---------------------------
