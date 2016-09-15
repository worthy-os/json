// Copyright (c) 2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_SAX_TO_PRETTY_STREAM_HH
#define TAOCPP_JSON_INCLUDE_SAX_TO_PRETTY_STREAM_HH

#include <ostream>
#include <cstddef>
#include <string>
#include <cstdint>

#include "../external/double.hh"

#include "../internal/escape.hh"

namespace tao
{
   namespace json
   {
      namespace sax
      {
         // SAX consumer to build a JSON pretty string representation
         class to_pretty_stream
         {
         private:
            std::ostream & os;
            const std::size_t indent;

            std::string current = "\n";
            bool first_value = true;
            bool after_key = true;

            void next()
            {
               if ( after_key ) {
                  after_key = false;
               }
               else {
                  os << current;
               }
            }

         public:
            to_pretty_stream( std::ostream & os, const std::size_t indent )
              : os( os ),
                indent( indent )
            { }

            void null()
            {
               next();
               os.write( "null", 4 );
            }

            void boolean( const bool v )
            {
               next();
               if ( v ) {
                  os.write( "true", 4 );
               }
               else {
                  os.write( "false", 5 );
               }
            }

            void number( const std::int64_t v )
            {
               next();
               os << v;
            }

            void number( const std::uint64_t v )
            {
               next();
               os << v;
            }

            void number( const double v )
            {
               next();
               json_double_conversion::Dtostr( os, v );
            }

            void string( const std::string & v )
            {
               next();
               internal::escape( os, v );
            }

            // array
            void begin_array()
            {
               next();
               os.put( '[' );
               current.resize( current.size() + indent, ' ' );
               first_value = true;
            }

            void element()
            {
               os.put( ',' );
               first_value = false;
            }

            void end_array()
            {
               current.resize( current.size() - indent );
               if ( ! first_value ) {
                  os.seekp( -1, std::ios_base::cur );
                  os << current;
               }
               os.put( ']' );
               first_value = false;
            }

            // object
            void begin_object()
            {
               next();
               os.put( '{' );
               current.resize( current.size() + indent, ' ' );
               first_value = true;
            }

            void key( const std::string & v )
            {
               next();
               internal::escape( os, v );
               os.write( ": ", 2 );
               after_key = true;
            }

            void member()
            {
               os.put( ',' );
               first_value = false;
            }

            void end_object()
            {
               current.resize( current.size() - indent );
               if ( ! first_value ) {
                  os.seekp( -1, std::ios_base::cur );
                  os << current;
               }
               os.put( '}' );
               first_value = false;
            }
         };

      } // sax

   } // json

} // tao

#endif
