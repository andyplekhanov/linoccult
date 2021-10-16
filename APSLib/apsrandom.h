//------------------------------------------------------------------------------
//
// File:    apsrandom.h
//
// Purpose: Random number generator based on Galua fields
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 27.05.2004
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

#ifndef APS_RANDOM_H
#define APS_RANDOM_H 1

#include <stdint.h>

namespace aps {

  namespace apslib {

class APSRandom
{
  private:

    const uint64_t poly_;

    const uint64_t mask_;
  
    uint64_t current_;

  public:

     APSRandom( const uint64_t startValue = 1 ) :
                poly_( 0x58a2791a6e3615db ),
		mask_( 0x8000000000000000 ),
                current_( startValue ) {}

    ~APSRandom( void ) {}

    void setCurrent( const uint64_t newCurrent )
      { current_ = newCurrent; }

    uint64_t getCurrent( void ) const
      { return( current_ ); }

    uint64_t nextNumber( void )
      {
        const bool flag = mask_ & current_;

        current_ = current_ + current_;

        if( flag ) {
          current_ = current_ ^ poly_;
        }

        return( current_ );
      }

    uint64_t getRandomNumber( const uint64_t module )
      {
	if( module ) {
          return( ( nextNumber() - 1 ) % module );
	}

        return( 0 );
      }

};
    

void SetCurrent( const uint32_t NewCurrent );

uint32_t GetCurrent( void );

uint32_t GetRandomNumber( const uint32_t Module );

}}

#endif

//---------------------------- End of file ---------------------------

