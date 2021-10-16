//------------------------------------------------------------------------------
//
// File:    apsmathconst.h
//
// Purpose: Math constants.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 17.05.2004
//                 0.2 05.02.2006 Several new constants were added
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

#ifndef APSMATHCONST_H
#define APSMATHCONST_H

namespace aps {

  namespace apsmathlib {

const double pi        = 3.14159265358979324;
const double pi2       = 2.0 * pi;
const double Rad       = pi / 180.0;
const double Deg       = 180.0 / pi;
const double Arcs      = 3600.0 * 180.0 / pi;

}}

#endif

//---------------------------- End of file ---------------------------
