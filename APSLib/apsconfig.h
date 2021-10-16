//------------------------------------------------------------------------------
//
// File:    apsconfig.h
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

#ifndef 	_APSCONFIG_H_
#define         _APSCONFIG_H_	1

#include <string>

namespace aps {

  namespace apslib {

typedef enum {
  PARAM_INTEGER = 0,
  PARAM_DOUBLE,
  PARAM_STRING
} PARAM_TYPE;

//------------------------------- APSAbsParameter ------------------------------

class APSAbsParameter
{
  friend class APSConfig;

  private:

    std::string Name;

  protected:

    APSAbsParameter( const std::string & aName );

    virtual ~APSAbsParameter( void );

  public:

    virtual PARAM_TYPE GetType( void ) const = 0;

    const std::string & GetName( void ) const
      { return( Name ); }
};

//------------------------------- APSParameter ---------------------------------

class APSParameter : public APSAbsParameter
{
  friend class APSConfig;

  private:

    PARAM_TYPE           Type;
    const APSParameter * pNextParameter;

  protected:

    APSParameter( const std::string & aName, const PARAM_TYPE aType,
                  const APSParameter * apNextParameter );

    virtual ~APSParameter( void );

  public:

    virtual PARAM_TYPE GetType( void ) const
      { return( Type ); }

    const APSParameter * GetNextParameterPtr( void ) const
      { return( pNextParameter ); }
};

//------------------------------- APSIntegerParameter -------------------------

class APSIntegerParameter : public APSAbsParameter
{
  friend class APSConfig;

  private:

    int                         Value;
    const APSIntegerParameter * pNextParameter;

  protected:

    APSIntegerParameter( const std::string & aName, const int aValue,
                         const APSIntegerParameter * apNextParameter );

    virtual ~APSIntegerParameter( void );

  public:

    int GetValue( void ) const
      { return( Value ); }

    virtual PARAM_TYPE GetType( void ) const
      { return( PARAM_INTEGER ); }

    const APSIntegerParameter * GetNextParameterPtr( void ) const
      { return( pNextParameter ); }
};

//------------------------------- APSDoubleParameter -------------------------

class APSDoubleParameter : public APSAbsParameter
{
  friend class APSConfig;

  private:

    double                     Value;
    const APSDoubleParameter * pNextParameter;

  protected:

    APSDoubleParameter( const std::string & aName, const double aValue,
                        const APSDoubleParameter * apNextParameter );

    virtual ~APSDoubleParameter( void );

  public:

    double GetValue( void ) const
      { return( Value ); }

    virtual PARAM_TYPE GetType( void ) const
      { return( PARAM_DOUBLE ); }

    const APSDoubleParameter * GetNextParameterPtr( void ) const
      { return( pNextParameter ); }
};

//------------------------------- APSStringParameter -------------------------

class APSStringParameter : public APSAbsParameter
{
  friend class APSConfig;

  private:

    std::string                Value;
    const APSStringParameter * pNextParameter;

  protected:

    APSStringParameter( const std::string & aName, const std::string & aValue,
                        const APSStringParameter * apNextParameter );

    virtual ~APSStringParameter( void );

  public:

    const std::string & GetValue( void ) const
      { return( Value ); }

    virtual PARAM_TYPE GetType( void ) const
      { return( PARAM_STRING ); }

    const APSStringParameter * GetNextParameterPtr( void ) const
      { return( pNextParameter ); }
};

//------------------------------- APSConfig ---------------------------------

class APSConfig
{
  friend class APSReadConfig;

  private:

    APSParameter        * pFirstParameter;

    APSIntegerParameter * pIntegerFirstParameter;

    APSDoubleParameter  * pDoubleFirstParameter;

    APSStringParameter  * pStringFirstParameter;

  protected:

    void AddIntegerParameter( const std::string & Name, const int Value );

    void AddDoubleParameter( const std::string & Name, const double Value );

    void AddStringParameter( const std::string & Name, const std::string & Value );

    const APSIntegerParameter * FindIntegerParameter( const std::string & Name ) const;

    const APSDoubleParameter * FindDoubleParameter( const std::string & Name ) const;

    const APSStringParameter * FindStringParameter( const std::string & Name ) const;

    int IfExistsParameter( const std::string & Name ) const;

  protected:

    int AddParameter( const std::string & Name, const PARAM_TYPE Type );  

    const APSParameter * FindParameter( const std::string & Name ) const;

  public:

    APSConfig( void );

    virtual ~APSConfig( void );

    int GetIntegerValue( const std::string & Name, int & Value ) const;

    int GetDoubleValue( const std::string & Name, double & Value ) const;

    int GetStringValue( const std::string & Name, std::string & Value ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------

