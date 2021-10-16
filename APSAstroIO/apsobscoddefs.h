//------------------------------------------------------------------------------
//
// File:    apsobscoddefs.h
//
// Purpose: Fields definition in observatories codes file.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 23.02.2006 Initial version
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

#ifndef APS_OBSCOD_DEFS_H
#define APS_OBSCOD_DEFS_H

namespace aps {

  namespace apsastroio {

/* Observatory name */
const unsigned int OBSCOD_NAME_OFFSET = 0;
const unsigned int OBSCOD_NAME_LENGTH = 3;
const unsigned int OBSCOD_NAME_PAD    = 0;

/* Observatory longitude */
const unsigned int OBSCOD_LONGITUDE_OFFSET = OBSCOD_NAME_OFFSET + OBSCOD_NAME_LENGTH + OBSCOD_NAME_PAD;
const unsigned int OBSCOD_LONGITUDE_LENGTH = 10;
const unsigned int OBSCOD_LONGITUDE_PAD    = 0;

/* Observatory parallax constant rho*cos(phi') */
const unsigned int OBSCOD_COS_OFFSET = OBSCOD_LONGITUDE_OFFSET + OBSCOD_LONGITUDE_LENGTH + OBSCOD_LONGITUDE_PAD;
const unsigned int OBSCOD_COS_LENGTH = 8;
const unsigned int OBSCOD_COS_PAD    = 0;

/* Observatory parallax constant rho*sin(phi') */
const unsigned int OBSCOD_SIN_OFFSET = OBSCOD_COS_OFFSET + OBSCOD_COS_LENGTH + OBSCOD_COS_PAD;
const unsigned int OBSCOD_SIN_LENGTH = 9;
const unsigned int OBSCOD_SIN_PAD    = 0;

/* Comment */
const unsigned int OBSCOD_COMMENT_OFFSET = OBSCOD_SIN_OFFSET + OBSCOD_SIN_LENGTH + OBSCOD_SIN_PAD;

}}

#endif

//---------------------------- End of file ---------------------------
