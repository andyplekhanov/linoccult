//------------------------------------------------------------------------------
//
// File:    loPosData.h
//
// Purpose: Base class for observation positions data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 17.02.2005
//         version 0.2 24.02.2005 pEMail, OutputFiles, Sort, MinDrop, MinProb, MinCenterProb, MinStarElev were added
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

#ifndef LO_POS_DATA_H
#define LO_POS_DATA_H

#include <string>

namespace aps {

  namespace apslinoccult {

class LOPos;

//======================= LOPosData ==========================

class LOPosData
{
  private:

    LOPos        ** ppLOPosArray;
    LOPos         * pFirstPos;
    unsigned int    PositionsNumber;

  public:

    LOPosData( void );

    virtual ~LOPosData( void );

    const LOPos * CreatePosition( const std::string & ObsName, const std::string & pEMail,
                                  const unsigned int OutputFiles, const unsigned int Sort,
                                  const float ObserverLongitude, const float ObserverLatitude,
                                  const double MaxDistance, const float MaxMv,
                                  const double MinDuration, const double SunElev,
                                  const double MinDrop, const double MinProb,
                                  const double MinCenterProb, const double MinStarElev );

    unsigned int GetPositionsNumber( void ) const
      { return( PositionsNumber ); }

    LOPos * GetPositionPtr( const unsigned int PositionNumber ) const;

    int Rebuild( void );
};

}}

#endif

//---------------------------- End of file ---------------------------

