
// Parser generated by Maphoon 2008


#line 1



// Non-terminal symbols:







   // Contains the stored variables.

#include "varstore.h"
#include "tree.h"

#include "assert.h"
#include <math.h>
































#include "token.h"
#include "tokenizer.h"
#include "parser.h"

#include <cstdlib>




// Code generated by Maphoon 2008C
// Written by Hans de Nivelle, June 2008 - May 2010
// See the licence that was included with the code. 



namespace
{
   struct refused
   {
   };

   std::ostream& operator << ( std::ostream& stream, refused ref )
   {
      stream << "REFUSED";
      return stream;
   }
}



namespace
{

// Here come the tables:

   unsigned int starts [] = 
   {
      0, 5, 11, 13, 19, 22, 25, 28, 31, 33, 35, 
      48, 50, 54, 57, 60, 64, 66, 69, 74, 96, 
      103, 106, 118, 120, 126, 129, 136, 143, 146, 151, 
      153, 155, 159, 164, 167, 170, 176, 180, 182, 184, 
      186, 189, 192, 199, 206, 210, 213, 220, 227, 230, 
      233, 235, 238, 245, 0 };

   unsigned int defaults [] = {
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
      11, 12, 13, 14, 3, 16, 17, 18, 19, 20, 
      21, 19, 22, 22, 25, 26, 27, 28, 29, 30, 
      24, 24, 33, 34, 35, 36, 22, 37, 22, 22, 
      41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 
      24, 52, 53, 0 };

   int parsetable [] = 
   {
      tkn__defaultred, -10002, 0, 
      tkn_Session, 10001, 
      tkn__recover, 10002, 
      tkn_FUNKEYWORD, 10003, 
      tkn_Command, 10004, 
      tkn_SEMICOLON, 10005, 
      tkn_INT_TYPE, 10006, 
      tkn_FLOAT_TYPE, 10007, 
      tkn_TYPE, 10008, 
      tkn__defaultred, -10001, 0, 
      tkn__defaultred, -10004, 0, 
      tkn__defaultred, -10013, 0, 
      tkn__defaultred, -10014, 0, 
      tkn_IDENTIFIER, 10009, 
      tkn_LPAR, 10010, 
      tkn__defaultred, -10008, 0, 
      tkn_INT_TYPE, 10006, 
      tkn_FLOAT_TYPE, 10007, 
      tkn_TYPE, 10011, 
      tkn_FUNARGS, 10012, 
      tkn_FUNARG, 10013, 
      tkn_IDENTIFIER, 10014, 
      tkn_COMMA, 10015, 
      tkn_RPAR, 10016, 
      tkn__defaultred, -10006, 0, 
      tkn__defaultred, -10005, 0, 
      tkn_TYPE, 10011, 
      tkn_FUNARG, 10017, 
      tkn_LBRACKET, 10018, 
      tkn__defaultred, -10007, 0, 
      tkn__defaultred, -10009, 0, 
      tkn_STATEMENTS, 10019, 
      tkn_IDENTIFIER, 10020, 
      tkn_NUMBER, 10021, 
      tkn_PLUS, 10022, 
      tkn_MINUS, 10023, 
      tkn_LPAR, 10024, 
      tkn_RBRACKET, 10025, 
      tkn_E, 10026, 
      tkn_F, 10027, 
      tkn_G, 10028, 
      tkn_H, 10029, 
      tkn_STATEMENT, 10030, 
      tkn__defaultred, -10026, 0, 
      tkn_BECOMES, 10031, 
      tkn_LPAR, 10032, 
      tkn__defaultred, -10027, 0, 
      tkn_IDENTIFIER, 10033, 
      tkn_RBRACKET, 0, 
      tkn_E, 0, 
      tkn_F, 0, 
      tkn_G, 10034, 
      tkn_STATEMENT, 0, 
      tkn_G, 10035, 
      tkn_E, 10036, 
      tkn_F, 10027, 
      tkn_G, 10028, 
      tkn__defaultred, -10003, 0, 
      tkn__defaultred, -10011, 0, 
      tkn_PLUS, 10037, 
      tkn_MINUS, 10038, 
      tkn__defaultred, -10017, 0, 
      tkn_TIMES, 10039, 
      tkn_DIVIDES, 10040, 
      tkn__defaultred, -10020, 0, 
      tkn__defaultred, -10023, 0, 
      tkn_FACTORIAL, 10041, 
      tkn_SEMICOLON, 10042, 
      tkn_E, 10043, 
      tkn_E, 10044, 
      tkn_LISTARGS, 10045, 
      tkn__defaultred, -10026, 0, 
      tkn_LPAR, 10032, 
      tkn__defaultred, -10022, 0, 
      tkn__defaultred, -10021, 0, 
      tkn_PLUS, 10037, 
      tkn_MINUS, 10038, 
      tkn_RPAR, 10046, 
      tkn_F, 10047, 
      tkn_G, 10028, 
      tkn_F, 10048, 
      tkn_G, 10049, 
      tkn_G, 10050, 
      tkn__defaultred, -10024, 0, 
      tkn__defaultred, -10010, 0, 
      tkn__defaultred, -10012, 0, 
      tkn_PLUS, 10037, 
      tkn_MINUS, 10038, 
      tkn__defaultred, -10029, 0, 
      tkn_PLUS, 10037, 
      tkn_MINUS, 10038, 
      tkn_COMMA, 10051, 
      tkn_RPAR, 10052, 
      tkn__defaultred, -10025, 0, 
      tkn__defaultred, -10015, 0, 
      tkn_TIMES, 10039, 
      tkn_DIVIDES, 10040, 
      tkn__defaultred, -10016, 0, 
      tkn_TIMES, 10039, 
      tkn_DIVIDES, 10040, 
      tkn__defaultred, -10018, 0, 
      tkn__defaultred, -10019, 0, 
      tkn_E, 10053, 
      tkn__defaultred, -10028, 0, 
      tkn__defaultred, -10030, 0, 
      tkn_PLUS, 10037, 
      tkn_MINUS, 10038, 
   0 };

   int entrypoints [] = 
   {
      tkn_Session, 0, tkn_EOF, -1,
      -1
   };



}


namespace
{


   // There are two reduce functions.
   // 
   // The first returns a token from the parse stack.
   // The other tokens are removed, and it is checked that the
   // token has the right type.
   // 
   // The second returns a new token. All tokens from the parse stack
   // are removed, and the new token is pushed.

   void reduce( std::list< token > & parsestack,
                std::list< token > :: iterator position,
                tokentype expectedtype,
                std::list< token > :: const_iterator result )
   {
      ASSERT( result -> type == expectedtype );
         // Must be type of lhs. 
      ASSERT( result -> iswellformed( ));

      bool seen = false;
      while( position != parsestack. end( ))
      {
         if( position == result )
         {
            ASSERT( !seen );
            seen = true;
            ++ position;
         }
         else
         {
            std::list< token > :: iterator p1 = position;
            ++ position; 
            parsestack. erase( p1 );
         }
      }
      ASSERT( seen );
   }


   void reduce( std::list< token > & parsestack,
                std::list< token > :: iterator position,
                tokentype expectedtype,
                const token& result )
   {
      ASSERT( result. type == expectedtype ); 
      ASSERT( result. iswellformed( )); 

      while( position != parsestack. end( ))
      {
         ASSERT( & (*position) != & result );
            // If this happenes, the user typed 'return *T'
            // for an attribute variable. 
            // He should have typed 'return T' instead. 
  
         std::list< token > :: iterator p1 = position;
         ++ position;
         parsestack. erase( p1 ); 
      }

      parsestack. insert( position, result ); 
   }


   // This is not terribly efficient, but we expect the size of the
   // rules to be moderate.

   std::list< token > :: iterator 
   operator - ( std::list< token > :: iterator p,
                unsigned int diff )
   {
      while( diff > 0 )
      {
         -- diff; 
         -- p;
      }
      return p; 
   }


// Here come the actions:

void reduction_0(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator Session1,
   std::list < token > :: iterator EOF2 ) throw( refused )
{

#line 57 "calculator.m"

std::cout << "bye bye\n";
{ reduce( stack, position, tkn_Start, tkn_Start ); return; }

}


void reduction_1(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator Session1,
   std::list < token > :: iterator Command2 ) throw( refused )
{

#line 61 "calculator.m"

if( Command2 -> tree. size( )) {
std::cout << Command2 -> tree. front( ) << "\n";
} else {
std::cout << " Result is undefined\n";
}
{ reduce( stack, position, tkn_Session, tkn_Session ); return; }

}


void reduction_2(
   std::list < token > & stack,
   std::list < token > :: iterator position ) throw( refused )
{

#line 67 "calculator.m"

{ reduce( stack, position, tkn_Session, tkn_Session ); return; }

}


void reduction_3(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator FUNKEYWORD1,
   std::list < token > :: iterator TYPE2,
   std::list < token > :: iterator IDENTIFIER3,
   std::list < token > :: iterator LPAR4,
   std::list < token > :: iterator FUNARGS5,
   std::list < token > :: iterator RPAR6,
   std::list < token > :: iterator LBRACKET7,
   std::list < token > :: iterator STATEMENTS8,
   std::list < token > :: iterator RBRACKET9 ) throw( refused )
{

#line 71 "calculator.m"

token t = tkn_Command;
tree newt = tree("FUN");
newt.pntr->subtrees.push_back(tree(TYPE2 -> id.front()));
newt.pntr->subtrees.push_back(tree(IDENTIFIER3 -> id.front()));
newt.pntr->subtrees.push_back(FUNARGS5 -> tree.front());
newt.pntr->subtrees.push_back(STATEMENTS8 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_Command, t ); return; }
{ reduce( stack, position, tkn_Command, tkn_Command ); return; }

}


void reduction_4(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator _recover1,
   std::list < token > :: iterator SEMICOLON2 ) throw( refused )
{

#line 80 "calculator.m"

std::cout << "recovered from error\n\n";
{ reduce( stack, position, tkn_Command, tkn_Command ); return; }

}


void reduction_5(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator TYPE1,
   std::list < token > :: iterator IDENTIFIER2 ) throw( refused )
{

#line 84 "calculator.m"

token t = tkn_FUNARG;
tree newt = tree("FUNARG");
newt.pntr->subtrees.push_back(tree(TYPE1 -> id.front()));
newt.pntr->subtrees.push_back(tree(IDENTIFIER2 -> id.front()));
t.tree.push_back(newt);
{ reduce( stack, position, tkn_FUNARG, t ); return; }
{ reduce( stack, position, tkn_FUNARG, tkn_FUNARG ); return; }

}


void reduction_6(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator FUNARG1 ) throw( refused )
{

#line 93 "calculator.m"

token t = tkn_FUNARGS;
tree newt = tree("FUNARGS");
newt.pntr->subtrees.push_back(FUNARG1 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_FUNARGS, t ); return; }
{ reduce( stack, position, tkn_FUNARGS, tkn_FUNARGS ); return; }

}


void reduction_7(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator FUNARGS1,
   std::list < token > :: iterator COMMA2,
   std::list < token > :: iterator FUNARG3 ) throw( refused )
{

#line 99 "calculator.m"

FUNARGS1 -> tree.front().pntr->subtrees.push_back(FUNARG3 -> tree.front());
{ reduce( stack, position, tkn_FUNARGS, FUNARGS1 ); return; }
{ reduce( stack, position, tkn_FUNARGS, tkn_FUNARGS ); return; }

}


void reduction_8(
   std::list < token > & stack,
   std::list < token > :: iterator position ) throw( refused )
{

#line 102 "calculator.m"

token t = tkn_FUNARGS;
tree newt = tree("FUNARGS");
t.tree.push_back(newt);
{ reduce( stack, position, tkn_FUNARGS, t ); return; }
{ reduce( stack, position, tkn_FUNARGS, tkn_FUNARGS ); return; }

}


void reduction_9(
   std::list < token > & stack,
   std::list < token > :: iterator position ) throw( refused )
{

#line 109 "calculator.m"

token t = tkn_STATEMENTS;
tree newt = tree("STATEMENTS");
t.tree.push_back(newt);
{ reduce( stack, position, tkn_STATEMENTS, t ); return; }
{ reduce( stack, position, tkn_STATEMENTS, tkn_STATEMENTS ); return; }

}


void reduction_10(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator STATEMENTS1,
   std::list < token > :: iterator STATEMENT2,
   std::list < token > :: iterator SEMICOLON3 ) throw( refused )
{

#line 114 "calculator.m"

STATEMENTS1 -> tree.front().pntr->subtrees.push_back(STATEMENT2 -> tree.front());
{ reduce( stack, position, tkn_STATEMENTS, STATEMENTS1 ); return; }
{ reduce( stack, position, tkn_STATEMENTS, tkn_STATEMENTS ); return; }

}


void reduction_11(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator E1 ) throw( refused )
{

#line 119 "calculator.m"

token t = tkn_STATEMENT;
t.tree.push_back(E1 -> tree.front());
{ reduce( stack, position, tkn_STATEMENT, t ); return; }
{ reduce( stack, position, tkn_STATEMENT, tkn_STATEMENT ); return; }

}


void reduction_12(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator IDENTIFIER1,
   std::list < token > :: iterator BECOMES2,
   std::list < token > :: iterator E3 ) throw( refused )
{

#line 123 "calculator.m"

token t = tkn_STATEMENT;
tree newt = tree("ASSIGN");
newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
if (E3 -> tree.size())
newt.pntr->subtrees.push_back(E3 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_STATEMENT, t ); return; }
{ reduce( stack, position, tkn_STATEMENT, tkn_STATEMENT ); return; }

}


void reduction_13(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator INT_TYPE1 ) throw( refused )
{

#line 133 "calculator.m"

token t = tkn_TYPE;
t.id.push_back("INT");
{ reduce( stack, position, tkn_TYPE, t ); return; }
{ reduce( stack, position, tkn_TYPE, tkn_TYPE ); return; }

}


void reduction_14(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator FLOAT_TYPE1 ) throw( refused )
{

#line 137 "calculator.m"

token t = tkn_TYPE;
t.id.push_back("FLOAT");
{ reduce( stack, position, tkn_TYPE, t ); return; }
{ reduce( stack, position, tkn_TYPE, tkn_TYPE ); return; }

}


void reduction_15(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator E1,
   std::list < token > :: iterator PLUS2,
   std::list < token > :: iterator F3 ) throw( refused )
{

#line 155 "calculator.m"

token t = tkn_E;
tree newt = tree("+");
if (E1 -> tree.size())
newt.pntr->subtrees.push_back(E1 -> tree.front());
if (F3 -> tree.size())
newt.pntr->subtrees.push_back(F3 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_E, t ); return; }

{ reduce( stack, position, tkn_E, tkn_E ); return; }

}


void reduction_16(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator E1,
   std::list < token > :: iterator MINUS2,
   std::list < token > :: iterator F3 ) throw( refused )
{

#line 165 "calculator.m"


token t = tkn_E;
tree newt = tree("-");
if (E1 -> tree.size())
newt.pntr->subtrees.push_back(E1 -> tree.front());
if (F3 -> tree.size())
newt.pntr->subtrees.push_back(F3 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_E, t ); return; }

{ reduce( stack, position, tkn_E, tkn_E ); return; }

}


void reduction_17(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator F1 ) throw( refused )
{

#line 176 "calculator.m"


// Change F into E, don't touch attribute.

F1 -> type = tkn_E;
{ reduce( stack, position, tkn_E, F1 ); return; }

{ reduce( stack, position, tkn_E, tkn_E ); return; }

}


void reduction_18(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator F1,
   std::list < token > :: iterator TIMES2,
   std::list < token > :: iterator G3 ) throw( refused )
{

#line 185 "calculator.m"


token t = tkn_F;
tree newt = tree("*");
if (F1 -> tree.size())
newt.pntr->subtrees.push_back(F1 -> tree.front());
if (G3 -> tree.size())
newt.pntr->subtrees.push_back(G3 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_F, t ); return; }

{ reduce( stack, position, tkn_F, tkn_F ); return; }

}


void reduction_19(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator F1,
   std::list < token > :: iterator DIVIDES2,
   std::list < token > :: iterator G3 ) throw( refused )
{

#line 196 "calculator.m"


token t = tkn_F;
tree newt = tree("/");
if (F1 -> tree.size())
newt.pntr->subtrees.push_back(F1 -> tree.front());
if (G3 -> tree.size())
newt.pntr->subtrees.push_back(G3 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_F, t ); return; }

{ reduce( stack, position, tkn_F, tkn_F ); return; }

}


void reduction_20(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator G1 ) throw( refused )
{

#line 207 "calculator.m"


G1 -> type = tkn_F;
{ reduce( stack, position, tkn_F, G1 ); return; }

{ reduce( stack, position, tkn_F, tkn_F ); return; }

}


void reduction_21(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator MINUS1,
   std::list < token > :: iterator G2 ) throw( refused )
{

#line 215 "calculator.m"


token t = tkn_G;
tree newt = tree("-");
if (G2 -> tree.size())
newt.pntr->subtrees.push_back(G2 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_G, t ); return; }

{ reduce( stack, position, tkn_G, tkn_G ); return; }

}


void reduction_22(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator PLUS1,
   std::list < token > :: iterator G2 ) throw( refused )
{

#line 224 "calculator.m"


{ reduce( stack, position, tkn_G, G2 ); return; }

{ reduce( stack, position, tkn_G, tkn_G ); return; }

}


void reduction_23(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator H1 ) throw( refused )
{

#line 228 "calculator.m"


H1 -> type = tkn_G;
{ reduce( stack, position, tkn_G, H1 ); return; }

{ reduce( stack, position, tkn_G, tkn_G ); return; }

}


void reduction_24(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator H1,
   std::list < token > :: iterator FACTORIAL2 ) throw( refused )
{

#line 236 "calculator.m"


token t = tkn_H;
tree newt = tree("!");
if (H1 -> tree.size())
newt.pntr->subtrees.push_back(H1 -> tree.front());
t.tree.push_back(newt);
{ reduce( stack, position, tkn_H, t ); return; }

{ reduce( stack, position, tkn_H, tkn_H ); return; }

}


void reduction_25(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator LPAR1,
   std::list < token > :: iterator E2,
   std::list < token > :: iterator RPAR3 ) throw( refused )
{

#line 245 "calculator.m"


E2 -> type = tkn_H;
{ reduce( stack, position, tkn_H, E2 ); return; }

{ reduce( stack, position, tkn_H, tkn_H ); return; }

}


void reduction_26(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator IDENTIFIER1 ) throw( refused )
{

#line 250 "calculator.m"


token h = tkn_H;
tree newt = tree("var");
newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
h.tree.push_back(newt);
{ reduce( stack, position, tkn_H, h ); return; }

{ reduce( stack, position, tkn_H, tkn_H ); return; }

}


void reduction_27(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator NUMBER1 ) throw( refused )
{

#line 258 "calculator.m"


token h = tkn_H;
tree newt = tree("num");
newt.pntr->subtrees.push_back(tree(NUMBER1 -> value.front()));
h.tree.push_back(newt);
{ reduce( stack, position, tkn_H, h ); return; }

{ reduce( stack, position, tkn_H, tkn_H ); return; }

}


void reduction_28(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator IDENTIFIER1,
   std::list < token > :: iterator LPAR2,
   std::list < token > :: iterator LISTARGS3,
   std::list < token > :: iterator RPAR4 ) throw( refused )
{

#line 266 "calculator.m"


token h = tkn_H;
std::vector<tree> strees = std::vector<tree>();
for (auto a : LISTARGS3 -> tree) {
strees.push_back(a);
}
tree newt = tree(IDENTIFIER1 -> id.front(), strees);
h.tree.push_back(newt);
{ reduce( stack, position, tkn_H, h ); return; }

{ reduce( stack, position, tkn_H, tkn_H ); return; }

}


void reduction_29(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator E1 ) throw( refused )
{

#line 280 "calculator.m"

token t = tkn_LISTARGS;
t.tree.push_back(E1 -> tree.front());
{ reduce( stack, position, tkn_LISTARGS, t ); return; }
{ reduce( stack, position, tkn_LISTARGS, tkn_LISTARGS ); return; }

}


void reduction_30(
   std::list < token > & stack,
   std::list < token > :: iterator position,
   std::list < token > :: iterator LISTARGS1,
   std::list < token > :: iterator COMMA2,
   std::list < token > :: iterator E3 ) throw( refused )
{

#line 284 "calculator.m"

LISTARGS1 -> tree.push_back(E3 -> tree.front());
{ reduce( stack, position, tkn_LISTARGS, LISTARGS1 ); return; }
{ reduce( stack, position, tkn_LISTARGS, tkn_LISTARGS ); return; }

}





   
   // The return values are specified as follows: 
   // 
   //                 0 : error.
   //        10000 + X  : push to state X.
   //        -10000 - X : Reduce rule X.
   // 
   // The returned list contains a sequence of reductions, terminated 
   // by an error or a push. 
   //
   // We try to base our decision on lookahead. If more lookahead
   // is required, we extend lookahead by doing: 
   //    lookahead. push_back( input. scan( ));
   

   std::list< int > decideaction( unsigned int ss, tokenizer& input )
   {
      std::list< int > result;

      unsigned int k = starts [ss];
      unsigned int defred = 0;
 
      while( true )
      {
         while( k == starts [ ss + 1 ] )
         {
            // This means that we reached the end.
            // If defaults [ss] != ss, we can continue looking in another
            // state.

            if( defaults [ss] == ss )
            {
               if( defred == 0 )
                  result. push_back(0);
               else
               {
                  result. push_back( defred ); 
                  result. push_back(0);
               }
               return result; 
            }

            ss = defaults [ ss ];
            k = starts [ ss ]; 
         }
          
         if( parsetable [k] == tkn__defaultred )
         {
            ASSERT( parsetable [ k+1 ] < 0 && parsetable [ k+2 ] == 0 );
            ASSERT( defred == 0 );
            defred = parsetable [ k + 1 ];
            k += 3; 
         }
         else
         {
            if( input. lookahead. size( ) == 0 )
            {
               input. scan( );
               ASSERT( input. lookahead. size( ));
               ASSERT( input. lookahead. back( ). iswellformed( ));
            }

            if( input. lookahead. size( ) &&
                input. lookahead. front( ). type == parsetable [k] )
            {
               ++ k; 
               while( parsetable [k] < 0 )
                  result. push_back( parsetable [ k ++ ] );
               result. push_back( parsetable [k] );
               return result;
            }
            
            ++ k;
            while( parsetable [k] < 0 )
               ++ k;
            ++ k; 
         }
      }
   }


   bool stateisempty( unsigned int ss )
   {
      return starts [ss] == starts [ss+1];
   }


   bool isstartlookahead( unsigned int entry, tokenizer& input )
   { 
      ASSERT( input. lookahead. size( ));

      entry += 2;  
      while( entrypoints [ entry ] >= 0 )
      {
         if( entrypoints [ entry ] == input. lookahead. front( ). type )
            return true;
         ++ entry;
      }
      return false;
   }

}
 

// The tokenizer must have the following features:
// It must have a field std::list< token > lookahead; 
// It must have a method void scan( ), which reads a token from somewhere
// and appends it to lookahead. scan( ) must always return a token,
// also when it reaches end of file, or when it is unable to read 
// input for some kind of reason. 
// It must have a method syntaxerror( ), which reports a syntax error
// to the user. 
// 
// The parser is called with the start symbol of the partial grammar
// that has to be parsed. 
// It uses the lookahead list of the tokenizer for returning its value.
// In case of a successful parse, lookahead starts with the start
// symbol. A second symbol need not be present. If there is a second
// symbol, then it is the lookahead symbol of the original start symbol. 
// The parser will read the lookahead only when it is necessary for
// deciding.
// 
// When an error occurred, and the parser reached a lookahead symbol
// while attempting to recover, the lookahead list equals this 
// lookahead symbol. 
// If the parser gave up, because more than
// recoverlength symbols were read, it returns a list of length 1 
// containing a recover symbol. 

// Setting recoverlength = 0 ensures that the parser will not try to
// recover. 


void parser( tokenizer& input,
      varstore & memory, tokentype start, unsigned int recoverlength )
{

   unsigned int errorcount = 0;
      // If errorcount > 0, then errors are not reported. 
      // Instead we assume that the previous recovery was not 
      // successful. 

   unsigned int entry = 0;
   while( entrypoints [ entry ] != -1 && entrypoints [ entry ] != start )
   {
      while( entrypoints [ entry ] != -1 )
         ++ entry;
      ++ entry;
   }

   if( entrypoints [ entry ] != start )
   {
      std::cout<< "could not find startsymbol " << start << "\n";
      ASSERT( false ); 
      exit(0);
   }

   std::list< unsigned int > states; 
   states. push_back( entrypoints [ entry + 1 ] );

   std::list< token > parsestack; 
 
   while( true ) 
   {
      ASSERT( states. size( ) == parsestack. size( ) + 1 );

#ifdef MAPH_DEBUG
      std::cout << "stack of states: "; 
      for( std::list< unsigned int > :: const_iterator
              p = states. begin( );
              p != states. end( );
              ++ p )
      {
         if( p != states. begin( ))
            std::cout << ", "; 
         std::cout << *p;
      }
      std::cout << "\n";

      std::cout << "stack of symbols: "; 
      for( std::list< token > :: const_iterator
              p = parsestack. begin( );
              p != parsestack. end( );
              ++ p )
      {
         if( p != parsestack. begin( ))
            std::cout << ", ";
         std::cout << *p;
      }
      std::cout << "\n";

      if( input. lookahead. size( ))
         std::cout << "lookahead: " << input. lookahead. front( ) << "\n";
#endif
      // We will check if we are in an accepting state. 
      // The parse stack must have size 1, and contain the 
      // start symbol of the grammar.

      if( parsestack. size( ) == 1 && 
          parsestack. front( ). type == entrypoints [ entry ] )
      {
         // This is a good start.
      
         // If we are in an empty state, we simply accept, and that's
         // the end of the story.

         if( stateisempty( states. back( )))
         {
            input. lookahead. splice( input. lookahead. begin( ),
                                      parsestack, parsestack. begin( ));
            
            return;  
         }

         // Otherwise, we check whether lookahead is one of the 
         // lookahead symbols of the start symbol. 
                   
         if( input. lookahead. size( ) == 0 )
         {
            input. scan( );
            ASSERT( input. lookahead. size( ));
            ASSERT( input. lookahead. back( ). iswellformed( ));
         }

         if( isstartlookahead( entry, input )) 
         {
            // This means that we accept. We move the start symbol
            // to the lookahead and quit.

            input. lookahead. splice( input. lookahead. begin( ),
                                     parsestack, parsestack. begin( ));
            return; 
         }
 
         // Otherwise we simply continue, and let things go their way.
         // This does not necessarily imply that there will be an error.
         // It is also possible that the parser will continue.
      }
       
      std::list< int > actions = decideaction( states. back( ), input );

      // If we have reductions, we try to perform them:
      // If we manage to make a reduction, we clear actions,
      // so that we will come out of this loop:

      while( actions. size( ) > 1 ) 
      {
         ASSERT( actions. front( ) < 0 );
         unsigned int rule = - actions. front( ) - 10000;

#ifdef MAPH_DEBUG
         std::cout << "attempting to reduce rule " << rule << "\n";
#endif

         try
         {
            switch( rule ) 
            {
case 0:
   reduction_0( parsestack, parsestack. end( ) - 2, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 1:
   reduction_1( parsestack, parsestack. end( ) - 2, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 2:
   reduction_2( parsestack, parsestack. end( ) - 0 );
   break;
case 3:
   reduction_3( parsestack, parsestack. end( ) - 9, parsestack. end( ) - 9, parsestack. end( ) - 8, parsestack. end( ) - 7, parsestack. end( ) - 6, parsestack. end( ) - 5, parsestack. end( ) - 4, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 4:
   reduction_4( parsestack, parsestack. end( ) - 2, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 5:
   reduction_5( parsestack, parsestack. end( ) - 2, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 6:
   reduction_6( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 7:
   reduction_7( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 8:
   reduction_8( parsestack, parsestack. end( ) - 0 );
   break;
case 9:
   reduction_9( parsestack, parsestack. end( ) - 0 );
   break;
case 10:
   reduction_10( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 11:
   reduction_11( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 12:
   reduction_12( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 13:
   reduction_13( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 14:
   reduction_14( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 15:
   reduction_15( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 16:
   reduction_16( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 17:
   reduction_17( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 18:
   reduction_18( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 19:
   reduction_19( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 20:
   reduction_20( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 21:
   reduction_21( parsestack, parsestack. end( ) - 2, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 22:
   reduction_22( parsestack, parsestack. end( ) - 2, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 23:
   reduction_23( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 24:
   reduction_24( parsestack, parsestack. end( ) - 2, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 25:
   reduction_25( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 26:
   reduction_26( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 27:
   reduction_27( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 28:
   reduction_28( parsestack, parsestack. end( ) - 4, parsestack. end( ) - 4, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;
case 29:
   reduction_29( parsestack, parsestack. end( ) - 1, parsestack. end( ) - 1 );
   break;
case 30:
   reduction_30( parsestack, parsestack. end( ) - 3, parsestack. end( ) - 3, parsestack. end( ) - 2, parsestack. end( ) - 1 );
   break;

            default:
	       std::cout << "unknown rule!\n";
	       exit(0); 
            }

#ifdef MAPH_DEBUG
            std::cout << "reduced rule " << rule << "\n";
#endif

            ASSERT( parsestack. size( )); 

            ASSERT( states. size( ) >= parsestack. size( ));

            while( states. size( ) > parsestack. size( ))
               states. pop_back( );

            // We now need to shift the lhs of the rule.
            // We do not like to copy tokens, because their attributes
            // can be big without borders. Copying can be avoided 
            // using list specific operations. 

            std::list< token > :: iterator p = parsestack. end( ) - 1;
            input. lookahead. splice( input. lookahead. begin( ), 
                                      parsestack, p );
               // Now the back of the parsestack is in front of lookahead.
               // It is possible that lookahead has a length of two now.

            actions = decideaction( states. back( ), input ); 

#if 0
            for( std::list< int > :: const_iterator
                     p = actions. begin( );
                     p != actions. end( );
                     ++ p )
            {
               std::cout << *p << "\n";
            }
#endif 

            // The action may contain reductions, but we are interested
            // in the push. In earlier versions, I assumed that actions 
            // necessarily contains only a single push, but this assumption
            // turned out wrong.  

            while( actions. size( ) > 1 )
            {
               ASSERT( actions. front( ) < 0 );
               actions. pop_front( );
            }

            // Now the action list should consist of a single push:

            ASSERT( actions. size( ) == 1 && actions. front( ) > 0 );

#ifdef MAPH_DEBUG
            std::cout << "goto " << actions. front( ) - 10000 << "\n"; 
#endif
            // We do not carry out the goto. 

            ++ errorcount;
         }
         catch( refused ref )
         {
#ifdef MAPH_DEBUG
            std::cout << "rule " << rule << " refused\n";
#endif
            actions. pop_front( );
               // We are not going to be sad about the refusal. We 
               // simply try the next in line.
         }
      }   
 
      if( actions. size( ) == 1 && actions. front( ) > 0 ) 
      {
         ASSERT( input. lookahead. size( ) == 1 || 
                 input. lookahead. size( ) == 2 );
         actions. front( ) -= 10000;
#ifdef MAPH_DEBUG
         std::cout << "shifting " << input. lookahead. front( ) << "\n"; 
#endif
 
         if( errorcount > 0 ) 
	    -- errorcount; 

         parsestack. splice( parsestack. end( ), 
                             input. lookahead, input. lookahead. begin( ));
            // This puts the symbol on the parsestack without moving it. 

         states. push_back( actions. front( ));

      }
      else
      {
         // If there is something left in actions, it is an error.

         ASSERT( actions. size( ) == 1 && actions. front( ) == 0 );
         ASSERT( input. lookahead. size( ));

#ifdef MAPH_DEBUG
        std::cout << "error!\n"; 
#endif

         // It is the responsability of the tokenizer to process the error:

         input. syntaxerror( );
 
         // Recovery will be the level at which we can recover.
         // As long as we did not recover, it will be -1.
 
         int recovery = -1; 
         unsigned int ignoredtokens = 0;

         while( recovery < 0 && ! isstartlookahead( entry, input ) && 
                ignoredtokens < recoverlength )
         {
            // Our approach is simple and inefficient, we look for
            // states that can push a recovery symbol, and after that
            // would be able to push the current lookahead symbol.

            std::list< unsigned int > :: const_iterator p = states. begin( );

            for( unsigned int k = 0; k < states. size( ); ++ k )
            {
               input. lookahead. push_front( token( tkn__recover ));
               actions = decideaction( *p, input );
               input. lookahead. pop_front( );

               if( actions. size( ) == 1 && actions. front( ) > 0 )
               {
                  // Recover transition is possible. 

                  unsigned int trans = actions. front( ) - 10000; 
                  actions = decideaction( trans, input );
               
                  if( actions. size( ) == 1 && actions. front( ) > 0 )
                     recovery = k;
                        // We remember that recovery was possible.
                        // If more than recovery is possible, we will
                        // remember the highest in recovery. 
               }
            
               ++ p;
            }
       
            if( recovery < 0 )
            {
               input. lookahead. clear( );
               ++ ignoredtokens;
               input. scan( );
               ASSERT( input. lookahead. size( )); 
               ASSERT( input. lookahead. back( ). iswellformed( ));
            }
         }

#ifdef MAPH_DEBUG 
         std::cout << "recovery = " << recovery << "\n";
         if( input. lookahead. size( ))
         {
            std::cout << "lookahead = ";
            std::cout << input. lookahead. front( ) << "\n";
         }
#endif

         if( ignoredtokens >= recoverlength ) 
         {
            // That was it. Game over. We lost.

            input. lookahead. clear( );
            input. lookahead. push_front( tkn__recover );
            return;
         }

         if( isstartlookahead( entry, input ))
         {
            // We reached a lookahead symbol of the grammar. 
            // We admit our defeat. 

            return;
         } 

         while( states. size( ) > recovery + 1 )
         {
            states. pop_back( );
            parsestack. pop_back( ); 
         }

         input. lookahead. push_front( token( tkn__recover ));
         actions = decideaction( states. back( ), input );
         input. lookahead. pop_front( );

         ASSERT( actions. size( ) == 1 && actions. front( ) > 0 );
         actions. front( ) -= 10000;
       
         states. push_back( actions. front( ));
         parsestack. push_back( token( tkn__recover ));

         actions = decideaction( states. back( ), input );
     
         ASSERT( actions. size( ) == 1 && actions. front( ) > 0 );
         actions. front( ) -= 10000;

#ifdef MAPH_DEBUG
         std::cout << "recovering into state " << actions. front( );
         std::cout << " using token " << input. lookahead. front( ) << "\n";
#endif

         states. push_back( actions. front( ));
         parsestack. splice( parsestack. end( ),
                             input. lookahead, input. lookahead. begin( ));

         errorcount = 3;
      }
   }
}


