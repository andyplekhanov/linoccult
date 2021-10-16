//------------------------------------------------------------------------------
//
// File:    apsastroconst.h
//
// Purpose: Astronomical constants.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 05.02.2006
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

#ifndef APSASTROCONST_H
#define APSASTROCONST_H   1

namespace aps {

  namespace apsastroalg {

// Radii of Earth, Sun and Moon
const double R_Earth   =   6378.137;     // [km]
const double R_Sun     = 696000.0;       // [km]
const double R_Moon    =   1738.0;       // [km]

const double MJD_J2000 = 51544.5;        // MJD of Epoch J2000.0
const double MJD_J2015 = 57023.5;        // MJD of Epoch J2015.0
const double MJD_J2016 = 57388.5;        // MJD of Epoch J2016.0
const double T_J2000   =  0.0;           // Epoch J2000.0
const double T_B1950   = -0.500002108;   // Epoch B1950

const double kGauss    = 0.01720209895;  // gravitational constant
const double GM_Sun    = kGauss*kGauss;  // [AU^3/d^2]

const double AU        = 149597870.0;    // Astronomical unit [km]

const double c_light   = 173.14;         // speed of light [AU/d]

const double EQU2ECL   = 23.43929111;

const double JYEAR     = 365.25; // Julian days in Julian year

}}

#endif

//---------------------------- End of file ---------------------------

