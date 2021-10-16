//------------------------------------------------------------------------------
//
// File:    apsangle.h
//
// Purpose: Functions to work with angles.
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

#ifndef APSANGLE_H
#define APSANGLE_H

#include <iostream>

namespace aps {

  namespace apsmathlib {

// Format tag for Angle output (used by Angle class output operator)
enum APSAngleFormat { 
  Dd,    // decimal representation
  DMM,   // degrees and whole minutes of arc
  DMMm,  // degrees and minutes of arc in decimal representation
  DMMSS, // degrees, minutes of arc and whole seconds of arc
  DMMSSs // degrees, minutes, and seconds of arc in decimal representation
};


// Frac: Gives the fractional part of a number
double Frac( const double x );


// Modulo: calculates x mod y
double Modulo( const double x, const double y );

//------------------------------------------------------------------------------
//
// Ddd: Conversion of angular degrees, minutes and seconds of arc to decimal
//      representation of an angle 
//
// Input:
//
//   D         Angular degrees
//   M         Minutes of arc
//   S         Seconds of arc
//
//   <return>  Angle in decimal representation
//
//------------------------------------------------------------------------------

double Ddd( const int D, const int M, const double S );


//------------------------------------------------------------------------------
//
// DMS: Finds degrees, minutes and seconds of arc for a given angle 
//
// Input:
//
//   Dd        Angle in degrees in decimal representation
//
// Output:
//
//   D         Angular degrees
//   M         Minutes of arc
//   S         Seconds of arc
//
//------------------------------------------------------------------------------

void DMS( const double Dd, int & D, int & M, double & S );

//============================ APSAngle ==============================

class APSAngle 
{
  public:
  
    // Constructor
    APSAngle( const double alpha, const APSAngleFormat Format = Dd ); 
    
    // Modifiers
    void Set( const APSAngleFormat Format=Dd );

    // Angle output
    friend std::ostream& operator << (std::ostream& os, const APSAngle & alpha );

  private:

    double         m_angle;
    APSAngleFormat m_Format;
};

}}

#endif   // include blocker

//---------------------------- End of file ---------------------------
