// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <ios>

namespace breath {

template< typename Stream >
stream_equivalent< Stream >::stream_equivalent( Stream & original )
    :   m_original( original ),
        m_equivalent( original.rdbuf() )
{
    m_equivalent.clear( m_original.rdstate() ) ;

    if ( m_original.good() ) {

        //      m_original and m_equivalent have the same rdstate():
        //
        //      if that isn't good() then no actual input or output will
        //      occur, so there's no point in copyfmt()'ing anything;
        //
        //      otherwise, both m_original and m_equivalent are good()
        //      and there can be no std::ios_base::failure exception
        //      when copyfmt()'ing the exception mask---but there can
        //      still be an exception, for instance because copyfmt()
        //      fails to allocate memory in which to copy the iword()/
        //      pword() elements.
        // -------------------------------------------------------------------
        m_equivalent.copyfmt( original ) ;
    }
}

template< typename Stream >
stream_equivalent< Stream >::~stream_equivalent() noexcept
{
    //      We can safely eat std::ios_base::failure, here, because in
    //      case the exception mask on m_original required an exception,
    //      we already got that from m_equivalent (in that case, this
    //      destructor is being called during stack unwinding).
    // -------------------------------------------------------------------
    try {
        m_original.clear( m_original.rdstate() |
                          m_equivalent.rdstate() ) ;
    } catch ( std::ios_base::failure & ) {
    }
}

template< typename Stream >
typename stream_equivalent< Stream >::stream_type &
stream_equivalent< Stream >::get() noexcept
{
    return m_equivalent ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
