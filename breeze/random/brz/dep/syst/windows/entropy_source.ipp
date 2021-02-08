// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breeze_ns {

constexpr entropy_source::result_type
entropy_source::min BREEZE_PREVENT_MACRO_EXPANSION () noexcept
{
    return 0 ;
}

constexpr entropy_source::result_type
entropy_source::max BREEZE_PREVENT_MACRO_EXPANSION () noexcept
{
    return 255 ;
}

}
