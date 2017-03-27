// Copyright (c) 2015-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_INTERNAL_ERRORS_HH
#define TAOCPP_JSON_INCLUDE_INTERNAL_ERRORS_HH

#include <string>

#include "../external/pegtl/normal.hpp"
#include "../external/pegtl/parse_error.hpp"

#include "grammar.hh"

namespace tao
{
   namespace json
   {
      namespace internal
      {
         template< typename Rule >
         struct errors
            : public json_pegtl::normal< Rule >
         {
            static const std::string error_message;

            template< typename Input, typename... States >
            static void raise( const Input& in, States&&... )
            {
               throw json_pegtl::parse_error( error_message, in );
            }
         };

         // clang-format off
         template<> const std::string errors< rules::text >::error_message __attribute__(( weak )) = "no valid JSON";

         template<> const std::string errors< rules::end_array >::error_message __attribute__(( weak )) = "incomplete array, expected ']'";
         template<> const std::string errors< rules::end_object >::error_message __attribute__(( weak )) = "incomplete object, expected '}'";
         template<> const std::string errors< rules::member >::error_message __attribute__(( weak )) = "expected member";
         template<> const std::string errors< rules::name_separator >::error_message __attribute__(( weak )) = "expected ':'";
         template<> const std::string errors< rules::array_element >::error_message __attribute__(( weak )) = "expected value";
         template<> const std::string errors< rules::value >::error_message __attribute__(( weak )) = "expected value";

         template<> const std::string errors< rules::edigits >::error_message __attribute__(( weak )) = "expected at least one exponent digit";
         template<> const std::string errors< rules::fdigits >::error_message __attribute__(( weak )) = "expected at least one fraction digit";
         template<> const std::string errors< rules::xdigit >::error_message __attribute__(( weak )) = "incomplete universal character name";
         template<> const std::string errors< rules::escaped >::error_message __attribute__(( weak )) = "unknown escape sequence";
         template<> const std::string errors< rules::chars >::error_message __attribute__(( weak )) = "invalid character in string";
         template<> const std::string errors< rules::string::content >::error_message __attribute__(( weak )) = "unterminated string";
         template<> const std::string errors< rules::key::content >::error_message __attribute__(( weak )) = "unterminated key";

         template<> const std::string errors< json_pegtl::eof >::error_message __attribute__(( weak )) = "unexpected character after JSON value";
         // clang-format on

      }  // internal

   }  // json

}  // tao

#endif
