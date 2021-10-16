//------------------------------------------------------------------------------
//
// File:    apsabsvec.h
//
// Purpose: base class for vectors.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 04.11.2005
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

#ifndef APSABSVEC_H
#define APSABSVEC_H

namespace aps {

  namespace apsmathlib {

//======================= APSAbsVec ==========================

class APSAbsVec
{
  private:

    unsigned int Dim;

  protected:

    APSAbsVec( const unsigned int aDim ) : Dim( aDim ) {}

  public:

    unsigned int GetDim( void ) const
      { return( Dim ); }
};

}}

#endif

//---------------------------- End of file ---------------------------


