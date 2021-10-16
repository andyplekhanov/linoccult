//------------------------------------------------------------------------------
//
// File:    loData.h
//
// Purpose: LinOccult data.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 02.02.2004
//         version 0.2 15.01.2005 BuildKDTree has been added
//         version 0.3 07.02.2005 Events were added
//         version 0.4 17.02.2005 Positions were added
//         version 0.5 27.02.2005 LOPointEventData was added
//         version 0.6 17.04.2005 LOUpdateData was added
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

#ifndef LO_DATA_H
#define LO_DATA_H

namespace aps {

  namespace apslinoccult {

class LOAstOrbData;
class LOStarData;
class LOEventData;
class LOPosData;
class LOPointEventData;
class LOUpdateData;

//======================= LOData ==========================

class LOData
{
  private:

    LOAstOrbData     * pLOAstOrbData;
    LOStarData       * pLOStarData;
    LOEventData      * pLOEventData;
    LOPosData        * pLOPosData;
    LOPointEventData * pLOPointEventData;
    LOUpdateData     * pLOUpdateData;

  public:

    LOData( void );

    virtual ~LOData( void );

    LOAstOrbData * CreateAstOrbData( const unsigned int AsteroidsNumber );

    LOStarData * CreateStarData( const unsigned int StarsNumber );

    LOEventData * CreateEventData( void );

    LOPosData * CreatePosData( void );

    LOPointEventData * CreatePointEventData( void );

    LOUpdateData * CreateUpdateData( void );

    const LOAstOrbData * GetAstOrbDataPtr( void ) const
      { return( pLOAstOrbData ); }

    const LOStarData * GetStarDataPtr( void ) const
      { return( pLOStarData ); }

    LOEventData * GetEventDataPtr( void ) const
      { return( pLOEventData ); }

    LOPosData * GetPosDataPtr( void ) const
      { return( pLOPosData ); }

    LOPointEventData * GetPointEventData( void ) const
      { return( pLOPointEventData ); }

    LOUpdateData * GetUpdateData( void ) const
      { return( pLOUpdateData ); }

    int BuildKDTree( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------

