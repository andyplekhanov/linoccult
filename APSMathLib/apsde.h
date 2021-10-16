//------------------------------------------------------------------------------
//
// File:    apsde.h
//
// Purpose: class for 'DE' integration method.
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

#ifndef APSDE_H
#define APSDE_H

#include "apsabsinteg.h"

namespace aps {

  namespace apsmathlib {

enum DE_STATE {
  DE_INIT                  = 1,    // Starting step
  DE_DONE                  = 2,    // Successful integration step
  DE_ACCURACY_NOT_ACHIEVED = 3,    // Too stringent accuracy requirements
  DE_TOO_MANY_STEPS        = 4,    // Too many steps required
  DE_STIFF                 = 5,    // Suspect of stiff differential equation
  DE_INVALID_PARAMS        = 6     // Invalid input
};

//========================== APSDE ========================

class APSDE : public APSAbsInteg
{
  private:

    // Data members
    double   *yy,*wt,*p,*yp,*ypout;
    double   **phi;
    double   alpha[13],beta[13],v[13],w[13],psi[13];
    double   sig[14],g[14];
    double   x,h,hold,told,delsgn;
    int      ns,k,kold;
    bool     OldPermit, phase1,start,nornd;
    
    // Interpolation
    void Intrp( const double x, const double y[], const double xout, 
                double yout[], double ypout[] );

    // Elementary integration step
    void Step( double& x, double y[], double& eps, bool& crash);

  public:

    APSDE( const APSAbsIntegFunction * afunc );

    virtual ~APSDE( void );

    void Integ ( 
      double y[],        // Solution vector; updated on output
      double& t,         // Value of independent variable; updated on output
      const double tout, // Value of independent variable to integrate to
      double& relerr,    // Desired relative accuracy of the solution; updated
      double& abserr,    // Desired absolute accuracy of the solution; updated
      DE_STATE& State,   // State code
      const bool PermitTOUT = true
    );
};

}}

#endif

//---------------------------- End of file ---------------------------
