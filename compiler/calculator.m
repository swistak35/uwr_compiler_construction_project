

%token EOF SCANERROR
%token SEMICOLON BECOMES COMMA 
%token IDENTIFIER NUMBER 
%token PLUS TIMES MINUS DIVIDES
%token FACTORIAL
%token LPAR RPAR

// Non-terminal symbols:

%token E F G H LISTARGS 
%token Session Command 
%token Start 

%intokenheader #include "tree.h"

%startsymbol Session EOF 

%attribute value         double
%attribute tree          struct tree
%attribute id            std::string
%attribute reason        std::string

%constraint IDENTIFIER id 1 2
%constraint E value 0 2
%constraint F value 0 2
%constraint G value 0 2
%constraint H value 0 2
%constraint E tree 0 2
%constraint F tree 0 2
%constraint G tree 0 2
%constraint H tree 0 2
%constraint LISTARGS value 0
%constraint LISTARGS tree 0
%constraint SCANERROR id 1 2
%constraint NUMBER value 1 2
%constraint Command tree 0

%global memory varstore
   // Contains the stored variables.

#include "varstore.h"
#include "tree.h"

#include "assert.h"
#include <math.h>


% Start : Session EOF
   std::cout << "bye bye\n";
%   ;

% Session : Session Command 

   if( Command2 -> tree. size( )) {
      std::cout << Command2 -> tree. front( ) << "\n";
   } else {
      std::cout << " Result is undefined\n";
   }

%         |
%         ;


% Command : E SEMICOLON

   token t = tkn_Command;
   tree newt = tree("compute");
   if (E1 -> tree.size())
      newt.pntr->subtrees.push_back(tree(E1 -> tree.front()));
   t.tree.push_back(newt);
   return t;

%         | IDENTIFIER BECOMES E SEMICOLON

   token t = tkn_Command;
   tree newt = tree("assign");
   if (IDENTIFIER1 -> id.size())
      newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   if (E3 -> tree.size())
      newt.pntr->subtrees.push_back(E3 -> tree.front());
   t.tree.push_back(newt);
   return t;

%         | _recover SEMICOLON

   std::cout << "recovered from error\n\n";

%         ;

% E   : E PLUS F 

   token t = tkn_E;
   tree newt = tree("+");
   if (E1 -> tree.size())
      newt.pntr->subtrees.push_back(E1 -> tree.front());
   if (F3 -> tree.size())
      newt.pntr->subtrees.push_back(F3 -> tree.front());
   t.tree.push_back(newt);
   return t;

%     | E MINUS F 

   token t = tkn_E;
   tree newt = tree("-");
   if (E1 -> tree.size())
      newt.pntr->subtrees.push_back(E1 -> tree.front());
   if (F3 -> tree.size())
      newt.pntr->subtrees.push_back(F3 -> tree.front());
   t.tree.push_back(newt);
   return t;

%     | F 

   // Change F into E, don't touch attribute.

   F1 -> type = tkn_E;
   return F1;

%     ;

% F   : F TIMES G 

   token t = tkn_F;
   tree newt = tree("*");
   if (F1 -> tree.size())
      newt.pntr->subtrees.push_back(F1 -> tree.front());
   if (G3 -> tree.size())
      newt.pntr->subtrees.push_back(G3 -> tree.front());
   t.tree.push_back(newt);
   return t;

%     | F DIVIDES G

   token t = tkn_F;
   tree newt = tree("/");
   if (F1 -> tree.size())
      newt.pntr->subtrees.push_back(F1 -> tree.front());
   if (G3 -> tree.size())
      newt.pntr->subtrees.push_back(G3 -> tree.front());
   t.tree.push_back(newt);
   return t;
 
%     | G 

   G1 -> type = tkn_F;
   return G1;

%     ;


%  G : MINUS G 

   token t = tkn_G;
   tree newt = tree("-");
   if (G2 -> tree.size())
      newt.pntr->subtrees.push_back(G2 -> tree.front());
   t.tree.push_back(newt);
   return t;

%    | PLUS G 

   return G2;

%    | H 

   H1 -> type = tkn_G;
   return H1;

%    ;


% H   : H FACTORIAL

   token t = tkn_H;
   tree newt = tree("!");
   if (H1 -> tree.size())
      newt.pntr->subtrees.push_back(H1 -> tree.front());
   t.tree.push_back(newt);
   return t;
 
%     | LPAR E RPAR 
 
   E2 -> type = tkn_H;
   return E2;

%     | IDENTIFIER 

   token h = tkn_H;
   tree newt = tree("var");
   newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   h.tree.push_back(newt);
   return h;

%     | NUMBER 

   token h = tkn_H;
   tree newt = tree("num");
   newt.pntr->subtrees.push_back(tree(NUMBER1 -> value.front()));
   h.tree.push_back(newt);
   return h;

%     | IDENTIFIER LPAR LISTARGS RPAR 

   token h = tkn_H;
   std::vector<tree> strees = std::vector<tree>();
   for (auto a : LISTARGS3 -> tree) {
      strees.push_back(a);
   }
   tree newt = tree(IDENTIFIER1 -> id.front(), strees);
   h.tree.push_back(newt);
   return h;

%     ;


% LISTARGS : E 
   token t = tkn_LISTARGS;
   t.tree.push_back(E1 -> tree.front());
   return t;

%          | LISTARGS COMMA E

   LISTARGS1 -> tree.push_back(E3 -> tree.front());
   return LISTARGS1;

%          ;

