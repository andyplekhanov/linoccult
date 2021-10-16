//------------------------------------------------------------------------------
//
// File:    apsmat3d.h
//
// Purpose: 3D matrix for double elements.
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

#ifndef APSMAT3D_H
#define APSMAT3D_H

#include "apsabsmat.h"

namespace aps {

  namespace apsmathlib {

class APSVec3d;

//======================= APSMat3d ==========================

class APSMat3d : public APSAbsMat
{
  private:

    double m_Mat[ 3 ][ 3 ];  // matrix elements

  public:

    APSMat3d( void );
    
    APSMat3d( const APSVec3d & e_1, const APSVec3d & e_2, const APSVec3d & e_3 );

    // component access
    friend APSVec3d Col( const APSMat3d & Mat, const int Index );
    friend APSVec3d Row( const APSMat3d & Mat, const int Index );

    // identity matrix
    friend APSMat3d Id3D( void );

    // elementary rotations
    friend APSMat3d R_x( const double RotAngle );
    friend APSMat3d R_y( const double RotAngle );
    friend APSMat3d R_z( const double RotAngle );

    // transposed matrix
    friend APSMat3d Transp( const APSMat3d & Mat );

    bool operator == ( const APSMat3d & Mat ) const;

    bool operator != ( const APSMat3d & Mat ) const;

    friend APSMat3d operator * ( const double fScalar, const APSMat3d & Mat );
    friend APSMat3d operator * ( const APSMat3d & Mat, const double fScalar );
    
    friend APSMat3d operator / ( const APSMat3d & Mat, const double fScalar );

    friend APSVec3d operator * ( const APSMat3d & Mat, const APSVec3d & Vec );
    
    friend APSVec3d operator * ( const APSVec3d & Vec, const APSMat3d & Mat );

    friend APSMat3d operator - ( const APSMat3d & Mat );

    friend APSMat3d operator + ( const APSMat3d & left, const APSMat3d & right );
    
    friend APSMat3d operator - ( const APSMat3d & left, const APSMat3d & right );    

    friend APSMat3d operator * ( const APSMat3d & left, const APSMat3d & right );
};

APSVec3d Col( const APSMat3d & Mat, const int Index );

APSVec3d Row( const APSMat3d & Mat, const int Index );

APSMat3d R_x( const double RotAngle );

APSMat3d R_y( const double RotAngle );

APSMat3d R_z( const double RotAngle );

APSMat3d Transp( const APSMat3d & Mat );

}}

#endif

//---------------------------- End of file ---------------------------

