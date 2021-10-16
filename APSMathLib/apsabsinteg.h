//------------------------------------------------------------------------------
//
// File:    apsabsinteg.h
//
// Purpose: base class for integration methods.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 05.11.2005
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

#ifndef APSABSINTEG_H
#define APSABSINTEG_H

namespace aps {

  namespace apsmathlib {

//=================== APSAbsIntegFunction ======================

class APSAbsIntegFunction
{
  private:

    int                         neqn;

  protected:

    APSAbsIntegFunction( const int Neqn ) : neqn( Neqn ) {}

    virtual ~APSAbsIntegFunction( void ) {}

  public:

    unsigned int GetNeqn( void ) const
      { return( neqn ); }

    virtual void Run( const double X, const double Y[], double dYdX[] ) const = 0;

};

//======================= APSAbsInteg ==========================

class APSAbsInteg
{
  private:

    const APSAbsIntegFunction * func;

  protected:

    APSAbsInteg( const APSAbsIntegFunction * afunc ) : func( afunc ) {}

    virtual ~APSAbsInteg( void ) {}

  public:

    const APSAbsIntegFunction * GetIntegFunction( void ) const
      { return( func ); }
};

}}

#endif

//---------------------------- End of file ---------------------------

