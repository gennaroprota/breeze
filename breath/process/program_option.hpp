// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#ifndef BREATH_GUARD_4FikLg5aHTVI1mWG6jpHTJWskJUVVUMy
#define BREATH_GUARD_4FikLg5aHTVI1mWG6jpHTJWskJUVVUMy

#include "breath/top_level_namespace.hpp"
#include "breath/process/command_line.hpp"
#include "breath/text/from_string.hpp"
#include "breath/text/to_string.hpp"
#include "breath/type_identification/readable_type_name.hpp"

#include <algorithm> // gps temp?
#include <string>
#include <vector>

namespace breath_ns {

template< typename T >
class option_reader
{
public:
    virtual T           operator()( std::string const & s ) const = 0 ;
    virtual             ~option_reader() noexcept = default ;
} ;

template< typename T >
class default_reader
    :   public option_reader< T >
{
public:
    virtual T           operator()( std::string const & str ) const override
    {
        auto const &        m = breath::from_string< T >( str ) ;
        if ( ! m.is_valid() ) {
            throw breath::command_line_error( "invalid string" ) ;
        }

        return m.value() ;
    }

    virtual             ~default_reader() noexcept override = default ;
} ;

template< typename T >
class range_reader
    :   public option_reader< T >
{
public:
                        range_reader( T const & low, T const & high )
                            : m_low( low ), m_high( high )
    {
    }

    virtual T           operator()( std::string const & s ) const override
    {
        T const         ret = default_reader< T >()( s ) ;
        if ( ret < m_low || ret > m_high ) {
            throw breath::command_line_error( "range_error" ) ;
        }
        return ret;
    }

private:
  T                     m_low ;
  T                     m_high ;
} ;

template< typename T >
range_reader< T >
range( T const & low, T const & high )
{
    return range_reader< T >( low, high ) ;
}

template< typename T >
class oneof_reader
    :   public option_reader< T >
{
public:
    virtual T           operator()( std::string const & s ) const override
    {
        T const         ret = default_reader< T >()( s ) ;
        if ( std::find( m_alt.cbegin(), m_alt.cend(), ret ) == m_alt.cend() ) {
            throw command_line_error( "" ) ; // gps ""?
        }
        return ret ;
    }

    void add( T const & v )
    {
        m_alt.push_back( v ) ;
    }

private:
  std::vector< T >      m_alt ;
};

template< typename T >
oneof_reader< T > oneof( T a1 )
{
    oneof_reader< T >   ret ;
    ret.add( a1 ) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2)
{
    oneof_reader< T >   ret ;
    ret.add(a1) ;
    ret.add(a2) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2, T a3)
{
    oneof_reader< T >   ret ;
    ret.add( a1 ) ;
    ret.add( a2 ) ;
    ret.add( a3 ) ;
    return ret ;
}

template< typename T >
oneof_reader< T > oneof( T a1, T a2, T a3, T a4 )
{
    oneof_reader< T >   ret ;
    ret.add( a1 ) ;
    ret.add( a2 ) ;
    ret.add( a3 ) ;
    ret.add( a4 ) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2, T a3, T a4, T a5)
{
    oneof_reader< T >   ret ;
    ret.add(a1) ;
    ret.add(a2) ;
    ret.add(a3) ;
    ret.add(a4) ;
    ret.add(a5) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2, T a3, T a4, T a5, T a6)
{
    oneof_reader< T >   ret ;
    ret.add(a1) ;
    ret.add(a2) ;
    ret.add(a3) ;
    ret.add(a4) ;
    ret.add(a5) ;
    ret.add(a6) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2, T a3, T a4, T a5, T a6, T a7)
{
    oneof_reader< T >   ret ;
    ret.add(a1) ;
    ret.add(a2) ;
    ret.add(a3) ;
    ret.add(a4) ;
    ret.add(a5) ;
    ret.add(a6) ;
    ret.add(a7) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2, T a3, T a4, T a5, T a6, T a7, T a8)
{
    oneof_reader< T >   ret ;
    ret.add(a1) ;
    ret.add(a2) ;
    ret.add(a3) ;
    ret.add(a4) ;
    ret.add(a5) ;
    ret.add(a6) ;
    ret.add(a7) ;
    ret.add(a8) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2, T a3, T a4, T a5, T a6, T a7, T a8, T a9)
{
    oneof_reader< T >   ret ;
    ret.add(a1) ;
    ret.add(a2) ;
    ret.add(a3) ;
    ret.add(a4) ;
    ret.add(a5) ;
    ret.add(a6) ;
    ret.add(a7) ;
    ret.add(a8) ;
    ret.add(a9) ;
    return ret ;
}

template< class T >
oneof_reader<T> oneof(T a1, T a2, T a3, T a4, T a5, T a6, T a7, T a8, T a9,
                                                                      T a10)
{
    oneof_reader< T >   ret ;
    ret.add(a1) ;
    ret.add(a2) ;
    ret.add(a3) ;
    ret.add(a4) ;
    ret.add(a5) ;
    ret.add(a6) ;
    ret.add(a7) ;
    ret.add(a8) ;
    ret.add(a9) ;
    ret.add(a10) ;
    return ret ;
}

class option_base
{
public:
    virtual             ~option_base() noexcept {}

    virtual bool        has_value() const = 0 ;
    virtual bool        set() = 0 ;
    virtual bool        set( const std::string &value ) = 0 ;
    virtual bool        is_set() const = 0 ;
    virtual bool        is_valid() const = 0 ;
    virtual bool        is_mandatory() const = 0 ;

    virtual std::string name() const = 0 ;
    virtual char        short_name() const = 0 ;
    virtual std::string description() const = 0 ;
    virtual std::string short_description() const = 0 ;
  };

class program_option_without_value
        :   public option_base
 {
  public:
                        program_option_without_value( const std::string &name,
                                                      char short_name,
                                                      const std::string & desc ) ;

    bool                has_value() const override ;
    bool                set() override ;
    bool                set( std::string const & ) override;
    bool                is_set() const override ;
    bool                is_valid() const override;
    bool                is_mandatory() const override ;
    std::string         name() const override ;
    char                short_name() const override ;
    std::string         description() const override ;
    std::string         short_description() const override ;

  private:
    std::string         m_name;
    char                m_short_name;
    std::string         m_description;
    bool                m_is_set ;
} ;

template< class T >
class program_option_with_value
    :   public option_base
{
public:
    //      Declare this explicitly to avoid Visual C++ C4626 (and
    //      C5027)
    // -----------------------------------------------------------------------
    void                operator=( program_option_with_value const & ) = 
                                                                       delete ;
    program_option_with_value( std::string const & name,
                    char short_name,
                    bool mandatory,
                    T const & def,
                    std::string const & desc,
        option_reader< T > const & reader = default_reader< T >() ) ;

    T const &           get() const ;
    bool                has_value() const override ;
    bool                set() override ;
    bool                set( std::string const & value ) override ;
    bool                is_set() const override ;
    bool                is_valid() const override;
    bool                is_mandatory() const override ;

    std::string         name() const override ;
    char                short_name() const override ;
    std::string         description() const override ;
    std::string         short_description() const override ;

private:
    std::string         full_description( std::string const & descr ) ;

    virtual             T read( std::string const & s ) ;

    std::string         m_name ;
    char                m_short_name ;
    bool                m_is_mandatory ;
    std::string         m_description ;
    bool                m_is_set ;
    T                   m_default_value ;
    T                   m_actual_value;
    option_reader< T > const &
                        m_reader ;
} ;

extern program_option_without_value
                    help_option ;

}

#include "brt/program_option.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
