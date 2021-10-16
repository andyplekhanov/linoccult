//------------------------------------------------------------------------------
//
// File:    apsconfig.cc
//
// Purpose: Config parameters
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 06.03.2004
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

#include "apsconfig.h"

namespace aps {

  namespace apslib {

//------------------------------- APSAbsParameter ------------------------------

APSAbsParameter :: APSAbsParameter( const std::string & aName ) :
                                    Name( aName )
{
}

APSAbsParameter :: ~APSAbsParameter( void )
{
}

//------------------------------- APSParameter ---------------------------------

APSParameter :: APSParameter( const std::string & aName, const PARAM_TYPE aType,
                              const APSParameter * apNextParameter ) :
                APSAbsParameter( aName ), Type( aType ), pNextParameter( apNextParameter )
{
}

APSParameter :: ~APSParameter( void )
{
}

//------------------------------- APSIntegerParameter ---------------------------------

APSIntegerParameter :: APSIntegerParameter( const std::string & aName, const int aValue,
                                            const APSIntegerParameter * apNextParameter ) :
                       APSAbsParameter( aName ), Value( aValue ), pNextParameter( apNextParameter )
{
}

APSIntegerParameter :: ~APSIntegerParameter( void )
{
}

//------------------------------- APSDoubleParameter ---------------------------------

APSDoubleParameter :: APSDoubleParameter( const std::string & aName, const double aValue,
                                          const APSDoubleParameter * apNextParameter ) :
                        APSAbsParameter( aName ), Value( aValue ), pNextParameter( apNextParameter )
{
}

APSDoubleParameter :: ~APSDoubleParameter( void )
{
}

//------------------------------- APSStringParameter ---------------------------------

APSStringParameter :: APSStringParameter( const std::string & aName, const std::string & aValue,
                                          const APSStringParameter * apNextParameter ) :
                        APSAbsParameter( aName ), Value( aValue ), pNextParameter( apNextParameter )
{
}

APSStringParameter :: ~APSStringParameter( void )
{
}

//------------------------------- APSConfig ---------------------------------

APSConfig :: APSConfig( void ) : pFirstParameter( 0 ), pIntegerFirstParameter( 0 ),
                                 pDoubleFirstParameter( 0 ), pStringFirstParameter( 0 )
{
}

APSConfig :: ~APSConfig( void )
{
  const APSParameter        * pTmpParameter;
  const APSParameter        * pNextParameter;
  const APSIntegerParameter * pTmpIntegerParameter;
  const APSIntegerParameter * pNextIntegerParameter;
  const APSDoubleParameter  * pTmpDoubleParameter;
  const APSDoubleParameter  * pNextDoubleParameter;
  const APSStringParameter  * pTmpStringParameter;
  const APSStringParameter  * pNextStringParameter;

  pTmpParameter = pFirstParameter;

  while( pTmpParameter ) {
    pNextParameter = pTmpParameter->GetNextParameterPtr();

    delete pTmpParameter;

    pTmpParameter = pNextParameter;
  }

  pTmpIntegerParameter = pIntegerFirstParameter;

  while( pTmpIntegerParameter ) {
    pNextIntegerParameter = pTmpIntegerParameter->GetNextParameterPtr();

    delete pTmpIntegerParameter;

    pTmpIntegerParameter = pNextIntegerParameter;
  }

  pTmpDoubleParameter = pDoubleFirstParameter;

  while( pTmpDoubleParameter ) {
    pNextDoubleParameter = pTmpDoubleParameter->GetNextParameterPtr();

    delete pTmpDoubleParameter;

    pTmpDoubleParameter = pNextDoubleParameter;
  }

  pTmpStringParameter = pStringFirstParameter;

  while( pTmpStringParameter ) {
    pNextStringParameter = pTmpStringParameter->GetNextParameterPtr();

    delete pTmpStringParameter;

    pTmpStringParameter = pNextStringParameter;
  }
}

void APSConfig :: AddIntegerParameter( const std::string & Name, const int Value )
{
  APSIntegerParameter * pNewParameter = new APSIntegerParameter( Name, Value, pIntegerFirstParameter );

  pIntegerFirstParameter = pNewParameter;
}

void APSConfig :: AddDoubleParameter( const std::string & Name, const double Value )
{
  APSDoubleParameter * pNewParameter = new APSDoubleParameter( Name, Value, pDoubleFirstParameter );

  pDoubleFirstParameter = pNewParameter;
}

void APSConfig :: AddStringParameter( const std::string & Name, const std::string & Value )
{
  APSStringParameter * pNewParameter = new APSStringParameter( Name, Value, pStringFirstParameter );

  pStringFirstParameter = pNewParameter;
}

const APSIntegerParameter * APSConfig :: FindIntegerParameter( const std::string & Name ) const
{
  const APSIntegerParameter * pTmpParameter = pIntegerFirstParameter;

  while( pTmpParameter ) {
    if( pTmpParameter->GetName() == Name ) {
      return( pTmpParameter );
    }

    pTmpParameter = pTmpParameter->GetNextParameterPtr();
  }

  return( 0 );
}

const APSDoubleParameter * APSConfig :: FindDoubleParameter( const std::string & Name ) const
{
  const APSDoubleParameter * pTmpParameter = pDoubleFirstParameter;

  while( pTmpParameter ) {
    if( pTmpParameter->GetName() == Name ) {
      return( pTmpParameter );
    }

    pTmpParameter = pTmpParameter->GetNextParameterPtr();
  }

  return( 0 );
}

const APSStringParameter * APSConfig :: FindStringParameter( const std::string & Name ) const
{
  const APSStringParameter * pTmpParameter = pStringFirstParameter;

  while( pTmpParameter ) {
    if( pTmpParameter->GetName() == Name ) {
      return( pTmpParameter );
    }

    pTmpParameter = pTmpParameter->GetNextParameterPtr();
  }

  return( 0 );
}

int APSConfig :: IfExistsParameter( const std::string & Name ) const
{
  if( FindIntegerParameter( Name ) ) {
    return( 1 );
  }
  else {
    if( FindDoubleParameter( Name ) ) {
      return( 1 );
    }
    else {
      if( FindStringParameter( Name ) ) {
        return( 1 );
      }
    }
  }

  return( 0 );
}

int APSConfig :: AddParameter( const std::string & Name, const PARAM_TYPE Type )
{
  APSParameter * pNewParameter;
  int            RetCode = 0;

  if( ( Type == PARAM_INTEGER ) || ( Type == PARAM_DOUBLE ) || ( Type == PARAM_STRING ) ) {
    if( !FindParameter( Name ) ) {
      pNewParameter = new APSParameter( Name, Type, pFirstParameter );

      pFirstParameter = pNewParameter;
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

const APSParameter * APSConfig :: FindParameter( const std::string & Name ) const
{
  const APSParameter * pTmpParameter = pFirstParameter;

  while( pTmpParameter ) {
    if( pTmpParameter->GetName() == Name ) {
      return( pTmpParameter );
    }

    pTmpParameter = pTmpParameter->GetNextParameterPtr();
  }

  return( 0 );
}

int APSConfig :: GetIntegerValue( const std::string & Name, int & Value ) const
{
  const APSIntegerParameter * pTmpParameter = pIntegerFirstParameter;

  while( pTmpParameter ) {
    if( pTmpParameter->GetName() == Name ) {
      Value = pTmpParameter->GetValue();
      return( 0 );
    }

    pTmpParameter = pTmpParameter->GetNextParameterPtr();
  }

  return( 1 );
}

int APSConfig :: GetDoubleValue( const std::string & Name, double & Value ) const
{
  const APSDoubleParameter * pTmpParameter = pDoubleFirstParameter;

  while( pTmpParameter ) {
    if( pTmpParameter->GetName() == Name ) {
      Value = pTmpParameter->GetValue();
      return( 0 );
    }

    pTmpParameter = pTmpParameter->GetNextParameterPtr();
  }

  return( 1 );
}

int APSConfig :: GetStringValue( const std::string & Name, std::string & Value ) const
{
  const APSStringParameter * pTmpParameter = pStringFirstParameter;

  while( pTmpParameter ) {
    if( pTmpParameter->GetName() == Name ) {
      Value = pTmpParameter->GetValue();
      return( 0 );
    }

    pTmpParameter = pTmpParameter->GetNextParameterPtr();
  }

  return( 1 );
}

}}

//---------------------------- End of file ---------------------------
