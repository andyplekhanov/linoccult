//------------------------------------------------------------------------------
//
// File:    apsistrastroio.cc
//
// Purpose: Base class for text astro file input.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 05.02.2006
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
#include <sstream>

#include "apsistrastroio.h"

namespace aps {

  namespace apsastroio {

//=============================== APSIStrAstroIO =========================

APSIStrAstroIO :: APSIStrAstroIO( const std::string & FileName ) : APSIStrFile( FileName ),
                                  IfReady( false )
{
}

APSIStrAstroIO :: ~APSIStrAstroIO( void )
{
}

bool APSIStrAstroIO :: ReadStr( void )
{
  bool RetCode = true;

  if( GetStr( Str ) ) {
    IfReady = true;
  }
  else {
    IfReady = false;
    RetCode = false;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetInteger( int & pInt, const unsigned int Offset, const unsigned int Length ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + Length <= Str.length() ) {
      std::istringstream istrstream( Str.substr( Offset, Length ) );

      if( !( istrstream >> pInt ) ) {
        RetCode = 3;
      }
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetShort( short & pShort, const unsigned int Offset, const unsigned int Length ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + Length <= Str.length() ) {
      std::istringstream istrstream( Str.substr( Offset, Length ) );

      if( !( istrstream >> pShort ) ) {
        RetCode = 3;
      }
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetString( std :: string & pStr, const unsigned int Offset, const unsigned int Length ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + Length <= Str.length() ) {
      pStr = Str.substr( Offset, Length );
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetChar( char & pChar, const unsigned int Offset ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + sizeof( char ) <= Str.length() ) {
      pChar = Str[ Offset ];
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetFloat( float & pFlt, const unsigned int Offset, const unsigned int Length ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + Length <= Str.length() ) {
      std::istringstream istrstream( Str.substr( Offset, Length ) );

      if( !( istrstream >> pFlt ) ) {
        RetCode = 3;
      }
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetDouble( double & pDbl, const unsigned int Offset, const unsigned int Length ) const
{
  int  RetCode = 0;

  if( IfReady ) {
    if( Offset + Length <= Str.length() ) {
      std::istringstream istrstream( Str.substr( Offset, Length ) );

      if( !( istrstream >> pDbl ) ) {
        RetCode = 3;
      }
    }
    else {
      RetCode = 2;
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: ParseString( const std::string & Str, std::list<std::string> & List ) const
{
  std::stringstream istrstream( Str );
  std::string       TmpStr;
  int               Count = 0;

  while( istrstream >> TmpStr ) {
    List.push_back( TmpStr );
    Count++;
  }

  return( Count );
}

int APSIStrAstroIO :: ProcessString( const std::string & Str, std::list<std::string> & List,
                                     int & Number, double & sign ) const
{
  int RetCode = 0;

  sign = 1.0;

  std::string::size_type pos = Str.find_first_not_of( ' ' );

  if( pos != std::string::npos ) {
    std::string Str1 = Str.substr( pos );

    if( Str1[ 0 ] == '+' ) {
      Str1[ 0 ] = ' ';
    }
    else {
      if( Str1[ 0 ] == '-' ) {
        sign = -1.0;
        Str1[ 0 ] = ' ';
      }
    }

    Number = ParseString( Str1, List );
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetDoubleWithPrecision( const std::string & Str, double & Angle, double & Prec ) const
{
  int RetCode = 0;

  std::stringstream istrstream( Str );

  if( istrstream >> Angle ) {
    std::string::size_type pos = Str.find_last_of( '.' );

    Prec = 1.0;

    if( pos != std::string::npos ) {
      std::string::size_type pos1 = Str.find_last_not_of( ' ' );

      if( pos1 != std::string::npos ) {
        if( pos1 >= pos ) {
          for( int i = 0; i < static_cast<int>( pos1 - pos ); i++ ) {
            Prec = Prec * 0.1;
          }
        }
        else {
          RetCode = 3;
        }
      }
      else {
        RetCode = 2;
      }
    }
  }
  else {
    RetCode = 1;
  }

  return( RetCode );
}

int APSIStrAstroIO :: GetAngle( double & Angle, double & Prec, const unsigned int Offset, const unsigned int Length ) const
{
  std::string Str;
  double      Fact    = 1.0;
  int         RetCode = 0;

  Angle = 0.0;
  Prec  = 1.0;

  RetCode = GetString( Str, Offset, Length );

  if( !RetCode ) {
    std::list<std::string> List;
    int                    Number = 0;
    double                 sign   = 1.0;

    if( !ProcessString( Str, List, Number, sign ) ) {
      std::list<std::string>::const_iterator p = List.begin();

      switch( Number ) {
        case 3:
          {
            int TmpAngle = 0;
            std::stringstream istrstream( *p );

            if( istrstream >> TmpAngle ) {
              Angle = TmpAngle;

              Fact = Fact / 60.0;

              ++p;
            }
            else {
              RetCode = 7;
              break;
            }
          } // No break !
        case 2:
          {
            int TmpAngle = 0;
            std::stringstream istrstream( *p );

            if( istrstream >> TmpAngle ) {
              Angle = Angle + TmpAngle * Fact;

              Fact = Fact / 60.0;

              ++p;
            }
            else {
              RetCode = 6;
              break;
            }
          } // No break !
        case 1:
          {
            double TmpAngle = 0;

            if( !GetDoubleWithPrecision( *p, TmpAngle, Prec ) ) {
              Angle = Angle + TmpAngle * Fact;

              Prec = Prec * Fact;
            }
            else {
              RetCode = 5;
            }
          }
        break;
        default:
          RetCode = 4;
      }

      Angle = Angle * sign;
    }
    else {
      RetCode = 3;
    }
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
