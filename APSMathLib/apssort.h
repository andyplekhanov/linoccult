//------------------------------------------------------------------------------
//
// File:    apssort.h
//
// Purpose: Class for quick sorting
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 01.03.2004
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

#ifndef 	_APSSORT_H_
#define         _APSSORT_H_	1

namespace aps {

  namespace apsmathlib {

//------------------------------- APSSort ------------------------------

class APSSort
{
  private:

    void QuickSort( const void ** ppArr, const int d, const int h, const int Type ) const;

  public:

    APSSort( void );

    virtual ~APSSort( void );

    // return 1 if *pPtr1 > *pPtr2, -1 if *pPtr1 < *pPtr2, 0 if *pPtr1 == *pPtr2
    virtual int Compare( const void * pPtr1, const void * pPtr2, const int Type ) const = 0;

    void Sort( const void ** ppArr, const int Size, const int Type ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------

