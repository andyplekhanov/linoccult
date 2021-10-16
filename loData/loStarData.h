//------------------------------------------------------------------------------
//
// File:    loStarData.h
//
// Purpose: Stars data base for LinOccult.
//   
// (c) 2004-2021 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
//         version 0.2 10.06.2004 Mv has been added
//         version 0.3 13.01.2005 kdtree
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

#ifndef LO_TYCHO_DATA_H
#define LO_TYCHO_DATA_H

#include <string>

#include "KDTree.h"
#include "Vec2f.h"

namespace aps {

  namespace apslinoccult {

class LOStar;

using namespace CGLA;

//======================= LOStarData ==========================

class LOStarData
{
  private:

    LOStar         ** ppLOStarsArray;
    unsigned int      StarsNumber;
    unsigned int      CurrentNumber;
    KDTree<Vec2f,const LOStar*> tree;

  public:

    LOStarData( const unsigned int aStarsNumber );

    virtual ~LOStarData( void );

    const LOStar * CreateStar( const double RA, const float pmRA,
                               const double Dec, const float pmDec,
                               const float Parallax, const float Vrad,
			       const double Epoch, const unsigned char Catalogue,
                               const int StarNumber, const short Mv );

    unsigned int GetStarsNumber( void ) const
      { return( StarsNumber ); }

    unsigned int GetCurrentNumber( void ) const
      { return( CurrentNumber ); }

    const LOStar * GetStarPtr( const unsigned int StarNumber ) const;

    const LOStar * FindStar( const unsigned char Catalogue, const int StarNumber ) const;

    int BuildKDTree( void );

    int FastFindStars( const LOStar ** pLOStarsArray, unsigned int & StarNumber,
                       const double RA1, const double Dec1,
                       const double RA2, const double Dec2 ) const;

    static std::string GetCatName( const unsigned char Catalogue );

    static std::string GetStarName( const unsigned char Catalogue, const int StarNumber );
};

}}

#endif

//---------------------------- End of file ---------------------------



