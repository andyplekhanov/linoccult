//------------------------------------------------------------------------------
//
// File:    apscheb.h
//
// Purpose: Three dimensional Chebyshev approximation.
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

#ifndef APSCHEB_H
#define APSCHEB_H

namespace aps {

  namespace apslib {
    class APSModule;
    class APSSubModule;
  }

  namespace apsmathlib {

using apslib::APSModule;
using apslib::APSSubModule;

class APSVec3d;

//======================= APSCheb ==========================

class APSCheb
{
  private:

    APSModule    * pModule;
    unsigned int   Order;
    double       * cX;
    double       * cY;
    double       * cZ;
    double         ta;
    double         tb;

  public:

    APSCheb( APSSubModule * pSubModule, const unsigned int aOrder,
             const double * acX, const double * acY, const double * acZ,
             const double ata, const double atb );

    virtual ~APSCheb( void );

    int Value( const double t, APSVec3d & Val );

    unsigned int GetOrder( void ) const
      { return( Order ); }

    double Getta( void ) const
      { return( ta ); }

    double Gettb( void ) const
      { return( tb ); }
};

}}

#endif

//---------------------------- End of file ---------------------------
