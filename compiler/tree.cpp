
#include "tree.h"

namespace
{
   void printindent( unsigned int indent, std::ostream& out )
   {
      for( unsigned int i = 0; i < indent; ++ i )
         out << "   ";
   }

   void printtree( unsigned int indent, std::ostream& out, const tree& t )
   {
      printindent( indent, out );
      t. printnode( out ); 
      out << "\n";

      for( size_t i = 0; i < t. nrsubtrees( ); ++ i )
      {
         printtree( indent + 1, out, t[i] );
      }
   }
}


std::ostream& operator << ( std::ostream& out, const tree& t )
{
   printtree( 0, out, t ); 
   return out;
}

