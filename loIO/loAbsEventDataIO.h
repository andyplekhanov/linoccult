//------------------------------------------------------------------------------
//
// File:    loAbsEventDataIO.h
//
// Purpose: Class for occultation events data base input/output for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 09.01.2005
//         version 0.2 10.02.2021 FILE_VERSION_1 2 -> 3
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

#ifndef LO_ABS_EVENT_DATA_IO_H
#define LO_ABS_EVENT_DATA_IO_H

namespace aps {

  namespace apslinoccult {

typedef unsigned int DescriptorType;

const int FILE_VERSION_1 = 3;

//======================= LOAbsEventDataIO ==========================

class LOAbsEventDataIO
{
  protected:

    static DescriptorType Descriptor;

    int IfInInterval( const double MjdStart, const double MjdEnd,
                      const double BeginOccTime, const double EndOccTime ) const;

  public:

    LOAbsEventDataIO( void );

    virtual ~LOAbsEventDataIO( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
