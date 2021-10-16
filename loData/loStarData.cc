//------------------------------------------------------------------------------
//
// File:    loStarData.cc
//
// Purpose: Stars data base for LinOccult.
//   
// (c) 2004-2021 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
//         version 0.2 10.06.2004 Mv has been added
//         version 0.3 13.01.2003 kdtree
//         version 0.4 11.01.2021 Gaia EDR3. SupNum was removed.
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

#include <cmath>
#include <iostream>
#include <sstream>

#include "loStarData.h"
#include "loStar.h"

namespace aps {

  namespace apslinoccult {

//======================= LOStarData ==========================

LOStarData :: LOStarData( const unsigned int aStarsNumber ) :
                          StarsNumber( aStarsNumber ),
                          CurrentNumber( 0 )
{
  ppLOStarsArray = new LOStar * [ aStarsNumber ];
}

LOStarData :: ~LOStarData( void )
{
  for( unsigned int i = 0; i < CurrentNumber; i++ ) {
    delete ppLOStarsArray[ i ];
  }

  delete ppLOStarsArray;
}

const LOStar * LOStarData :: CreateStar( const double RA, const float pmRA,
                                         const double Dec, const float pmDec,
                                         const float Parallax, const float Vrad,
					 const double Epoch, const unsigned char Catalogue,
                                         const int StarNumber, const short Mv )
{
  LOStar * pLOStar;

  if( CurrentNumber < StarsNumber ) {
    pLOStar = new LOStar( RA, pmRA, Dec, pmDec, Parallax, Vrad, Epoch, Catalogue, StarNumber, Mv );

    ppLOStarsArray[ CurrentNumber ] = pLOStar;

    CurrentNumber++;
  }
  else {
    pLOStar = 0;
  }

  return( pLOStar );
}

const LOStar * LOStarData :: GetStarPtr( const unsigned int StarNumber ) const
{
  if( StarNumber < CurrentNumber ) {
    return( ppLOStarsArray[ StarNumber ] );
  }

  return( 0 );
}

const LOStar * LOStarData :: FindStar( const unsigned char Catalogue, const int StarNumber ) const
{
  unsigned int   i;
  const LOStar * pLOStar;

  for( i = 0; i < GetStarsNumber(); i++ ) {
    pLOStar = GetStarPtr( i );

    //if( pLOStar->GetCatalogue() == Catalogue ) {
      if( pLOStar->GetStarNumber() == StarNumber ) {
        return( pLOStar );
      }
    //}
  }

  return( 0 );
}

int LOStarData :: BuildKDTree( void )
{
  const LOStar * pLOStar;
  int            RetCode = 0;

  for( unsigned int i = 0; i < GetCurrentNumber(); i++ ) {
    pLOStar = GetStarPtr( i );

    Vec2f p0 = Vec2f( pLOStar->GetRA(), pLOStar->GetDec() );

    tree.insert( p0, pLOStar );
  }

  tree.build();

  return( RetCode );
}

int LOStarData :: FastFindStars( const LOStar ** pLOStarsArray, unsigned int & StarNumber,
                                 const double RA1, const double Dec1,
                                 const double RA2, const double Dec2 ) const
{
  int                i;
  double             range;
  std::vector<Vec2f> keys;
  std::vector<const LOStar*> vals;
  const LOStar     * pLOStar;
  int                N;
  unsigned int       N_Max;
  int                RetCode = 0;

  N_Max = StarNumber;

  Vec2f p0 = Vec2f( ( RA1 + RA2 ) / 2.0, ( Dec1 + Dec2 ) / 2.0 );

  range = std::sqrt( ( RA1 - RA2 ) * ( RA1 - RA2 ) + ( Dec1 - Dec2 ) * ( Dec1 - Dec2 ) );

  N = tree.in_sphere( p0, range, keys, vals );

  StarNumber = 0;

  for( i = 0; i < N; i++ ) {
    pLOStar = vals[ i ];

    if( RA1 < pLOStar->GetRA() ) {
      if( RA2 > pLOStar->GetRA() ) {
        if( Dec1 < pLOStar->GetDec() ) {
          if( Dec2 > pLOStar->GetDec() ) {
            pLOStarsArray[ StarNumber ] = pLOStar;

            StarNumber++;

            if( StarNumber > N_Max ) {
              std::cout << "WARNING: LOStarData :: FastFindStars: too many stars." << std::endl;
              RetCode = 1;
              break;
            }
          }
        }
      }
    }
  }

  return( RetCode );
}

std::string LOStarData :: GetCatName( const unsigned char Catalogue )
{
  switch( Catalogue ) {
    case 2:     //Hipparcos
      return("HIP");              
    case 3:     //Tycho2
      return("TYC");              
    case 4:     //Tycho2
      return("TYC");             
    case 5:     //Tycho2
      return("TYC");             
    case 6:     // UCAC4
      return("UCAC4");             
    default:;
  }

  return("UNKNOWN");
}

std::string LOStarData :: GetStarName( const unsigned char Catalogue, const int StarNumber )
{
  std::ostringstream Msg;
  
  switch( Catalogue ) {
    case 2:     //Hipparcos
      Msg << StarNumber;
      return( Msg.str() );              
    case 3:     //Tycho2
      Msg << StarNumber / 100000 << "-" << StarNumber % 100000 << "-1";
      return( Msg.str() );
    case 4:     //Tycho2
      Msg << StarNumber / 100000 << "-" << StarNumber % 100000 << "-2";
      return( Msg.str() );
    case 5:     //Tycho2
      Msg << StarNumber / 100000 << "-" << StarNumber % 100000 << "-3";
      return( Msg.str() );								  
    case 6:     //UCAC4
      Msg << StarNumber / 1000000 << "-" << StarNumber % 1000000;
      return( Msg.str() );
    default:;
  }

  return("UNKNOWN");
}   

}}

//---------------------------- End of file ---------------------------
