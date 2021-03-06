
// This code was produced by Maphoon 2008.
// Code of struct token:


#include "token.h"


bool token::iswellformed( ) const
{
   switch( type )
   {
   case tkn__recover:
   case tkn__defaultred:
   case tkn_EOF:
   case tkn_SEMICOLON:
   case tkn_BECOMES:
   case tkn_COMMA:
   case tkn_PLUS:
   case tkn_TIMES:
   case tkn_MINUS:
   case tkn_DIVIDES:
   case tkn_OP_EQ:
   case tkn_OP_NEQ:
   case tkn_OP_GE:
   case tkn_OP_LE:
   case tkn_OP_GT:
   case tkn_OP_LT:
   case tkn_OP_AND:
   case tkn_OP_OR:
   case tkn_FACTORIAL:
   case tkn_LPAR:
   case tkn_RPAR:
   case tkn_LBRACKET:
   case tkn_RBRACKET:
   case tkn_FUN_KW:
   case tkn_WHILE_KW:
   case tkn_RETURN_KW:
   case tkn_IF_KW:
   case tkn_ELSE_KW:
   case tkn_EXTERN_KW:
   case tkn_INT_TYPE:
   case tkn_FLOAT_TYPE:
   case tkn_Start:
      if( id. size( ) >= 1 ) return false;
      if( reason. size( ) >= 1 ) return false;
      if( tree. size( ) >= 1 ) return false;
      if( value. size( ) >= 1 ) return false;
      return true;
   case tkn_SCANERROR:
   case tkn_IDENTIFIER:
   case tkn_TYPE:
      if( id. size( ) < 1 ) return false;
      if( id. size( ) >= 2 ) return false;
      if( reason. size( ) >= 1 ) return false;
      if( tree. size( ) >= 1 ) return false;
      if( value. size( ) >= 1 ) return false;
      return true;
   case tkn_NUMBER:
      if( id. size( ) >= 1 ) return false;
      if( reason. size( ) >= 1 ) return false;
      if( tree. size( ) >= 1 ) return false;
      if( value. size( ) < 1 ) return false;
      if( value. size( ) >= 2 ) return false;
      return true;
   case tkn_EB:
   case tkn_EC:
   case tkn_EE:
   case tkn_EF:
   case tkn_EG:
   case tkn_EH:
   case tkn_STATEMENTS:
   case tkn_STATEMENT:
   case tkn_FUNARGS:
   case tkn_FUNARG:
      if( id. size( ) >= 1 ) return false;
      if( reason. size( ) >= 1 ) return false;
      if( tree. size( ) < 1 ) return false;
      if( tree. size( ) >= 2 ) return false;
      if( value. size( ) >= 1 ) return false;
      return true;
   case tkn_LISTARGS:
   case tkn_Session:
   case tkn_Command:
      if( id. size( ) >= 1 ) return false;
      if( reason. size( ) >= 1 ) return false;
      if( value. size( ) >= 1 ) return false;
      return true;
   }
   return false; // Because of unknown type.
}


// If you see an insane error message originating from
// this point, then the most probable reason is that
// one of the attribute types has no print function defined.

std::ostream& operator << ( std::ostream& stream, const token& t )
{
   switch( t. type )
   {
   case tkn__recover:
      stream << "_recover( "; break;
   case tkn__defaultred:
      stream << "_defaultred( "; break;
   case tkn_EOF:
      stream << "EOF( "; break;
   case tkn_SCANERROR:
      stream << "SCANERROR( "; break;
   case tkn_SEMICOLON:
      stream << "SEMICOLON( "; break;
   case tkn_BECOMES:
      stream << "BECOMES( "; break;
   case tkn_COMMA:
      stream << "COMMA( "; break;
   case tkn_IDENTIFIER:
      stream << "IDENTIFIER( "; break;
   case tkn_NUMBER:
      stream << "NUMBER( "; break;
   case tkn_PLUS:
      stream << "PLUS( "; break;
   case tkn_TIMES:
      stream << "TIMES( "; break;
   case tkn_MINUS:
      stream << "MINUS( "; break;
   case tkn_DIVIDES:
      stream << "DIVIDES( "; break;
   case tkn_OP_EQ:
      stream << "OP_EQ( "; break;
   case tkn_OP_NEQ:
      stream << "OP_NEQ( "; break;
   case tkn_OP_GE:
      stream << "OP_GE( "; break;
   case tkn_OP_LE:
      stream << "OP_LE( "; break;
   case tkn_OP_GT:
      stream << "OP_GT( "; break;
   case tkn_OP_LT:
      stream << "OP_LT( "; break;
   case tkn_OP_AND:
      stream << "OP_AND( "; break;
   case tkn_OP_OR:
      stream << "OP_OR( "; break;
   case tkn_FACTORIAL:
      stream << "FACTORIAL( "; break;
   case tkn_LPAR:
      stream << "LPAR( "; break;
   case tkn_RPAR:
      stream << "RPAR( "; break;
   case tkn_LBRACKET:
      stream << "LBRACKET( "; break;
   case tkn_RBRACKET:
      stream << "RBRACKET( "; break;
   case tkn_FUN_KW:
      stream << "FUN_KW( "; break;
   case tkn_WHILE_KW:
      stream << "WHILE_KW( "; break;
   case tkn_RETURN_KW:
      stream << "RETURN_KW( "; break;
   case tkn_IF_KW:
      stream << "IF_KW( "; break;
   case tkn_ELSE_KW:
      stream << "ELSE_KW( "; break;
   case tkn_EXTERN_KW:
      stream << "EXTERN_KW( "; break;
   case tkn_INT_TYPE:
      stream << "INT_TYPE( "; break;
   case tkn_FLOAT_TYPE:
      stream << "FLOAT_TYPE( "; break;
   case tkn_EB:
      stream << "EB( "; break;
   case tkn_EC:
      stream << "EC( "; break;
   case tkn_EE:
      stream << "EE( "; break;
   case tkn_EF:
      stream << "EF( "; break;
   case tkn_EG:
      stream << "EG( "; break;
   case tkn_EH:
      stream << "EH( "; break;
   case tkn_LISTARGS:
      stream << "LISTARGS( "; break;
   case tkn_TYPE:
      stream << "TYPE( "; break;
   case tkn_STATEMENTS:
      stream << "STATEMENTS( "; break;
   case tkn_STATEMENT:
      stream << "STATEMENT( "; break;
   case tkn_FUNARGS:
      stream << "FUNARGS( "; break;
   case tkn_FUNARG:
      stream << "FUNARG( "; break;
   case tkn_Session:
      stream << "Session( "; break;
   case tkn_Command:
      stream << "Command( "; break;
   case tkn_Start:
      stream << "Start( "; break;
   default:
      stream << "UNKNOWNTOKEN( ";
   }

   unsigned int arg = 0;
   unsigned int arginlist;

   arginlist = 0;
   for( std::list< std::string > :: const_iterator
           p = t. id. begin( );
           p != t. id. end( );
           ++ p )
   {
      if( arg != 0 && arginlist == 0 ) stream << "; ";
      if( arg != 0 && arginlist != 0 ) stream << ", ";
      stream << *p;
      ++ arg;
      ++ arginlist;
   }

   arginlist = 0;
   for( std::list< std::string > :: const_iterator
           p = t. reason. begin( );
           p != t. reason. end( );
           ++ p )
   {
      if( arg != 0 && arginlist == 0 ) stream << "; ";
      if( arg != 0 && arginlist != 0 ) stream << ", ";
      stream << *p;
      ++ arg;
      ++ arginlist;
   }

   arginlist = 0;
   for( std::list< struct tree > :: const_iterator
           p = t. tree. begin( );
           p != t. tree. end( );
           ++ p )
   {
      if( arg != 0 && arginlist == 0 ) stream << "; ";
      if( arg != 0 && arginlist != 0 ) stream << ", ";
      stream << *p;
      ++ arg;
      ++ arginlist;
   }

   arginlist = 0;
   for( std::list< double > :: const_iterator
           p = t. value. begin( );
           p != t. value. end( );
           ++ p )
   {
      if( arg != 0 && arginlist == 0 ) stream << "; ";
      if( arg != 0 && arginlist != 0 ) stream << ", ";
      stream << *p;
      ++ arg;
      ++ arginlist;
   }

   stream << " )";
   return stream;
}


