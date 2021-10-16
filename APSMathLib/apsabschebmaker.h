//------------------------------------------------------------------------------
//
// File:    apsabschebmaker.h
//
// Purpose: Abstract class for creating three dimensional Chebyshev approximation.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 17.05.2004
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

#ifndef APSABSCHEBMAKER_H
#define APSABSCHEBMAKER_H

namespace aps {

  namespace apsmathlib {

class APSCheb;
class APSVec3d;

//======================= APSAbsChebMaker ==========================

class APSAbsChebMaker
{
  protected:

    virtual APSVec3d GetValue( const double t ) = 0;

  public:

    APSAbsChebMaker( void );

    virtual ~APSAbsChebMaker( void );

    int Create( const unsigned int Order, const double ta, const double tb,
                double cX[], double cY[], double cZ[] );
};

}}

#endif

//---------------------------- End of file ---------------------------

