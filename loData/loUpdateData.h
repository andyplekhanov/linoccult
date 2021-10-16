//------------------------------------------------------------------------------
//
// File:    loUpdateData.h
//
// Purpose: Base class for updates data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 16.04.2005
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

#ifndef LO_UPDATE_DATA_H
#define LO_UPDATE_DATA_H

namespace aps {

  namespace apslinoccult {

class LOUpdate;

//======================= LOUpdateData ==========================

class LOUpdateData
{
  private:

    LOUpdate     * pFirstUpdate;
    unsigned int   UpdatesNumber;

    bool IsEqual( const LOUpdate * pLOUpdate, const int AsteroidID, const double LastDate ) const;

  public:

    LOUpdateData( void );

    virtual ~LOUpdateData( void );

    const LOUpdate * CreateUpdate( const int AsteroidID, const double ObservationEpoch,
                                   const double M, const double W, const double O,
                                   const double I, const double E, const double A,
                                   const double Major, const double Minor, const double PA );

    unsigned int GetUpdatesNumber( void ) const
      { return( UpdatesNumber ); }

    const LOUpdate * FindUpdate( const int AsteroidID, const double LastDate ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
