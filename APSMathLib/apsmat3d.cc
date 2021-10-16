//------------------------------------------------------------------------------
//
// File:    apsmat3d.cc
//
// Purpose: 3D matrix for double elements.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 09.10.2005
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

#include <math.h>

#include "apsmat3d.h"
#include "apsvec3d.h"

namespace aps {

  namespace apsmathlib {

//======================= APSMat3d ==========================

APSMat3d :: APSMat3d( void ) : APSAbsMat( 3, 3 )
{
  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      m_Mat[ i ][ j ] = 0.0;
    }
  }
}

APSMat3d :: APSMat3d( const APSVec3d & e_1, const APSVec3d & e_2, const APSVec3d & e_3 ) : APSAbsMat( 3, 3 )
{
  for( int i = 0; i < 3; i++ ) {
    m_Mat[ i ][ 0 ] = e_1[ (r_index)i ];
    m_Mat[ i ][ 1 ] = e_2[ (r_index)i ];
    m_Mat[ i ][ 2 ] = e_3[ (r_index)i ];
  }
}

APSVec3d Col( const APSMat3d & Mat, const int Index )
{
  double Res[ 3 ];

  for( int i = 0; i < 3; i++ ) {
    Res[ i ] = Mat.m_Mat[ i ][ Index ];
  }

  return( APSVec3d( Res[ 0 ], Res[ 1 ], Res[ 2 ] ) );
}

APSVec3d Row( const APSMat3d & Mat, const int Index )
{
  double Res[ 3 ];

  for( int j = 0; j < 3; j++ ) {
    Res[ j ] = Mat.m_Mat[ Index ][ j ];
  }
  
  return( APSVec3d( Res[ 0 ], Res[ 1 ], Res[ 2 ] ) );
}

APSMat3d Id3D( void )
{
  APSMat3d Id;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      Id.m_Mat[ i ][ j ] = ( i == j ) ? 1 : 0;
    }
  }
   
  return( Id );
}

APSMat3d R_x( const double RotAngle )
{
  const double S = sin( RotAngle );
  const double C = cos( RotAngle );

  APSMat3d U;
  
  U.m_Mat[ 0 ][ 0 ] = 1.0;  U.m_Mat[ 0 ][ 1 ] = 0.0;  U.m_Mat[ 0 ][ 2 ] = 0.0;
  U.m_Mat[ 1 ][ 0 ] = 0.0;  U.m_Mat[ 1 ][ 1 ] =  +C;  U.m_Mat[ 1 ][ 2 ] =  +S;
  U.m_Mat[ 2 ][ 0 ] = 0.0;  U.m_Mat[ 2 ][ 1 ] =  -S;  U.m_Mat[ 2 ][ 2 ] =  +C;

  return( U );
}

APSMat3d R_y( const double RotAngle )
{
  const double S = sin( RotAngle );
  const double C = cos( RotAngle );

  APSMat3d U;
  
  U.m_Mat[ 0 ][ 0 ] =  +C;  U.m_Mat[ 0 ][ 1 ] = 0.0;  U.m_Mat[ 0 ][ 2 ] =  -S;
  U.m_Mat[ 1 ][ 0 ] = 0.0;  U.m_Mat[ 1 ][ 1 ] = 1.0;  U.m_Mat[ 1 ][ 2 ] = 0.0;
  U.m_Mat[ 2 ][ 0 ] =  +S;  U.m_Mat[ 2 ][ 1 ] = 0.0;  U.m_Mat[ 2 ][ 2 ] =  +C;

  return( U );
}

APSMat3d R_z( const double RotAngle )
{
  const double S = sin( RotAngle );
  const double C = cos( RotAngle );

  APSMat3d U;

  U.m_Mat[ 0 ][ 0 ] =  +C;  U.m_Mat[ 0 ][ 1 ] =  +S;  U.m_Mat[ 0 ][ 2 ] = 0.0;
  U.m_Mat[ 1 ][ 0 ] =  -S;  U.m_Mat[ 1 ][ 1 ] =  +C;  U.m_Mat[ 1 ][ 2 ] = 0.0;
  U.m_Mat[ 2 ][ 0 ] = 0.0;  U.m_Mat[ 2 ][ 1 ] = 0.0;  U.m_Mat[ 2 ][ 2 ] = 1.0;

  return( U );
}

APSMat3d Transp( const APSMat3d & Mat )
{
  APSMat3d T;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      T.m_Mat[ i ][ j ] = Mat.m_Mat[ j ][ i ];
    }
  }
    
  return( T );
}

bool APSMat3d :: operator == ( const APSMat3d & Mat ) const
{
  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      if( m_Mat[ i ][ j ] != Mat.m_Mat[ i ][ j ] ) {
        return( false );
      }
    }
  }

  return( true );
}

bool APSMat3d :: operator != ( const APSMat3d & Mat ) const
{
  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      if( m_Mat[ i ][ j ] != Mat.m_Mat[ i ][ j ] ) {
        return( true );
      }
    }
  }

  return( false );
}

APSMat3d operator * ( const double fScalar, const APSMat3d & Mat )
{
  APSMat3d Result;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      Result.m_Mat[ i ][ j ] = fScalar * Mat.m_Mat[ i ][ j ];
    }
  }

  return( Result );
}

APSMat3d operator * ( const APSMat3d & Mat, const double fScalar )
{
  return( fScalar * Mat );
}

APSMat3d operator / ( const APSMat3d & Mat, const double fScalar )
{
  APSMat3d Result;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      Result.m_Mat[ i ][ j ] = Mat.m_Mat[ i ][ j ] / fScalar;
    }
  }
  
  return( Result );
}

APSVec3d operator * ( const APSMat3d & Mat, const APSVec3d & Vec )
{
  double Result[ 3 ];

  for( int i = 0; i < 3; i++ ) {
    double Scalp = 0.0;

    for( int j = 0; j < 3; j++ ) {
      Scalp += Mat.m_Mat[ i ][ j ] * Vec[ (r_index)j ];
    }

    Result[ i ] = Scalp;
  }

  return( APSVec3d( Result[ 0 ], Result[ 1 ], Result[ 2 ] ) );
}

APSVec3d operator * ( const APSVec3d & Vec, const APSMat3d & Mat )
{
  double Result[ 3 ];

  for( int j = 0; j < 3; j++ ) {
    double Scalp = 0.0;

    for( int i = 0; i < 3; i++ ) {
      Scalp += Vec[ (r_index)i ] * Mat.m_Mat[ i ][ j ];
    }

    Result[ j ] = Scalp;
  }

  return( APSVec3d( Result[ 0 ], Result[ 1 ], Result[ 2 ] ) );
}

APSMat3d operator - ( const APSMat3d & Mat )
{
  APSMat3d Result;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      Result.m_Mat[ i ][ j ] = -Mat.m_Mat[ i ][ j ];
    }
  }

  return( Result );
}

APSMat3d operator + ( const APSMat3d & left, const APSMat3d & right )
{
  APSMat3d Result;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      Result.m_Mat[ i ][ j ] = left.m_Mat[ i ][ j ] + right.m_Mat[ i ][ j ];
    }
  }
    
  return( Result );
}

APSMat3d operator - ( const APSMat3d & left, const APSMat3d & right )
{
  APSMat3d Result;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      Result.m_Mat[ i ][ j ] = left.m_Mat[ i ][ j ] - right.m_Mat[ i ][ j ];
    }
  }
    
  return( Result );
}

APSMat3d operator * ( const APSMat3d & left, const APSMat3d & right )
{
  APSMat3d Result;

  for( int i = 0; i < 3; i++ ) {
    for( int j = 0; j < 3; j++ ) {
      double Scalp = 0.0;

      for( int k = 0; k < 3; k++ ) {
        Scalp += left.m_Mat[ i ][ k ] * right.m_Mat[ k ][ j ];
      }

      Result.m_Mat[ i ][ j ] = Scalp;
    }
  }
    
  return( Result );
}

}}

//---------------------------- End of file ---------------------------

