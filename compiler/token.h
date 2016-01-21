
// This code was produced by Maphoon 2008.
// Definition of struct token:


#include "tree.h"



#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED    1


#include <list>
#include <iostream>



enum tokentype
{
   tkn__recover,
   tkn__defaultred,
   tkn_EOF,
   tkn_SCANERROR,
   tkn_SEMICOLON,
   tkn_BECOMES,
   tkn_COMMA,
   tkn_IDENTIFIER,
   tkn_NUMBER,
   tkn_PLUS,
   tkn_TIMES,
   tkn_MINUS,
   tkn_DIVIDES,
   tkn_FACTORIAL,
   tkn_LPAR,
   tkn_RPAR,
   tkn_LBRACKET,
   tkn_RBRACKET,
   tkn_FUNKEYWORD,
   tkn_INT_TYPE,
   tkn_FLOAT_TYPE,
   tkn_STATEMENTS,
   tkn_STATEMENT,
   tkn_E,
   tkn_F,
   tkn_G,
   tkn_H,
   tkn_LISTARGS,
   tkn_TYPE,
   tkn_Session,
   tkn_Command,
   tkn_Start,
   tkn_FUNARGS,
   tkn_FUNARG
};


struct token
{

   tokentype type;

   std::list< std::string > id;
   std::list< std::string > reason;
   std::list< struct tree > tree;
   std::list< double > value;

   token( tokentype t )
      : type(t)
   {
   }

   token( );
      // Should have no definition.

   bool iswellformed( ) const;
      // Check if the attributes satisfy the
      // constraints.
};

std::ostream& operator << ( std::ostream& , const token& );



#endif


