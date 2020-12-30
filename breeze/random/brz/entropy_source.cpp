// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2008-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/random/entropy_source.hpp"
#include "breeze/porting/dependent_source.hpp"
#include BREEZE_DEPENDENT_SOURCE( system_family, entropy_source.cpp )
#include "breeze/random/subrange_adaptor.hpp"

namespace breeze_ns {

entropy_source::entropy_source()
    :   m_impl( new impl )
{
}

entropy_source::~entropy_source() noexcept
{
    delete m_impl ;
}

entropy_source::result_type
entropy_source::next()
{
    return m_impl->next() ;
}

bool
entropy_source::release() noexcept
{
    return m_impl->release() ;
}

entropy_source::result_type
entropy_source::operator ()()
{
    return next() ;
}

entropy_source::result_type
entropy_source::operator ()( result_type maximum )
{
    subrange_adaptor< entropy_source >
                        adaptor( *this, maximum ) ;
    return adaptor.next() ;
}

entropy_source::result_type
entropy_source::operator ()( result_type minimum, result_type maximum )
{
    BREEZE_ASSERT( minimum <= maximum ) ;
    return operator ()( maximum - minimum ) + minimum ;
}

entropy_source::exception::
exception( std::string const & msg )
    :   std::runtime_error( msg )
{
}

}
