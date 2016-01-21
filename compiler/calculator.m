
%token EOF SCANERROR
%token SEMICOLON BECOMES COMMA 
%token IDENTIFIER NUMBER 
%token PLUS TIMES MINUS DIVIDES
%token OP_EQ OP_NEQ
%token FACTORIAL
%token LPAR RPAR
%token LBRACKET RBRACKET
%token FUN_KW WHILE_KW RETURN_KW IF_KW ELSE_KW EXTERN_KW
%token INT_TYPE FLOAT_TYPE

// Non-terminal symbols:

%token B EC E F G H LISTARGS 
%token TYPE
%token STATEMENTS STATEMENT
%token FUNARGS FUNARG

%token Session Command 
%token Start 

%intokenheader #include "tree.h"

%startsymbol Session EOF 

%attribute value         double
%attribute tree          struct tree
%attribute id            std::string
%attribute reason        std::string

%constraint TYPE id 1 2
%constraint FUNARGS tree 1 2
%constraint FUNARG tree 1 2
%constraint STATEMENTS tree 1 2
%constraint STATEMENT tree 1 2
%constraint IDENTIFIER id 1 2
%constraint B tree 1 2
%constraint EC tree 1 2
%constraint E tree 1 2
%constraint F tree 1 2
%constraint G tree 1 2
%constraint H tree 1 2
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

% Command : FUN_KW TYPE IDENTIFIER LPAR FUNARGS RPAR LBRACKET STATEMENTS RBRACKET
   token t = tkn_Command;
   tree newt = tree("FUN");
   newt.pntr->subtrees.push_back(tree(TYPE2 -> id.front()));
   newt.pntr->subtrees.push_back(tree(IDENTIFIER3 -> id.front()));
   newt.pntr->subtrees.push_back(FUNARGS5 -> tree.front());
   newt.pntr->subtrees.push_back(STATEMENTS8 -> tree.front());
   t.tree.push_back(newt);
   return t;
%         | EXTERN_KW TYPE IDENTIFIER LPAR FUNARGS RPAR
   token t = tkn_Command;
   tree newt = tree("EXTERN");
   newt.pntr->subtrees.push_back(tree(TYPE2 -> id.front()));
   newt.pntr->subtrees.push_back(tree(IDENTIFIER3 -> id.front()));
   newt.pntr->subtrees.push_back(FUNARGS5 -> tree.front());
   t.tree.push_back(newt);
   return t;
%         | _recover SEMICOLON
   std::cout << "recovered from error\n\n";
%         ;

% FUNARG : TYPE IDENTIFIER
   token t = tkn_FUNARG;
   tree newt = tree("FUNARG");
   newt.pntr->subtrees.push_back(tree(TYPE1 -> id.front()));
   newt.pntr->subtrees.push_back(tree(IDENTIFIER2 -> id.front()));
   t.tree.push_back(newt);
   return t;
%        ;

% FUNARGS : FUNARG
   token t = tkn_FUNARGS;
   tree newt = tree("FUNARGS");
   newt.pntr->subtrees.push_back(FUNARG1 -> tree.front());
   t.tree.push_back(newt);
   return t;
%         | FUNARGS COMMA FUNARG
   FUNARGS1 -> tree.front().pntr->subtrees.push_back(FUNARG3 -> tree.front());
   return FUNARGS1;
%         |
   token t = tkn_FUNARGS;
   tree newt = tree("FUNARGS");
   t.tree.push_back(newt);
   return t;
%         ;

% STATEMENTS :
   token t = tkn_STATEMENTS;
   tree newt = tree("STATEMENTS");
   t.tree.push_back(newt);
   return t;
%            | STATEMENTS STATEMENT SEMICOLON
   STATEMENTS1 -> tree.front().pntr->subtrees.push_back(STATEMENT2 -> tree.front());
   return STATEMENTS1;
%            ;

% STATEMENT : E
   token t = tkn_STATEMENT;
   tree newt = tree("EXPRESSION");
   newt.pntr->subtrees.push_back(E1 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | IDENTIFIER BECOMES E
   token t = tkn_STATEMENT;
   tree newt = tree("ASSIGN");
   newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   newt.pntr->subtrees.push_back(E3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | WHILE_KW B LBRACKET STATEMENTS RBRACKET
   token t = tkn_STATEMENT;
   tree newt = tree("WHILE");
   newt.pntr->subtrees.push_back(B2 -> tree.front());
   newt.pntr->subtrees.push_back(STATEMENTS4 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | RETURN_KW E
   token t = tkn_STATEMENT;
   tree newt = tree("RETURN");
   newt.pntr->subtrees.push_back(E2 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | IF_KW B LBRACKET STATEMENTS RBRACKET ELSE_KW LBRACKET STATEMENTS RBRACKET
   token t = tkn_STATEMENT;
   tree newt = tree("IF");
   newt.pntr->subtrees.push_back(B2 -> tree.front());
   newt.pntr->subtrees.push_back(STATEMENTS4 -> tree.front());
   newt.pntr->subtrees.push_back(STATEMENTS8 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           ;

% TYPE : INT_TYPE
   token t = tkn_TYPE;
   t.id.push_back("INT");
   return t;
%      | FLOAT_TYPE
   token t = tkn_TYPE;
   t.id.push_back("FLOAT");
   return t;
%      ;

% B : EC
   EC1 -> type = tkn_B;
   return EC1;
%   ;

% EC : EC OP_EQ E
   token t = tkn_EC;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("=="));
   newt.pntr->subtrees.push_back(EC1 -> tree.front());
   newt.pntr->subtrees.push_back(E3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EC OP_NEQ E
   token t = tkn_EC;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("!="));
   newt.pntr->subtrees.push_back(EC1 -> tree.front());
   newt.pntr->subtrees.push_back(E3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | E
   E1 -> type = tkn_EC;
   return E1;
%   ;

% E : E PLUS F 
   token t = tkn_E;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("+"));
   newt.pntr->subtrees.push_back(E1 -> tree.front());
   newt.pntr->subtrees.push_back(F3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | E MINUS F 
   token t = tkn_E;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("-"));
   newt.pntr->subtrees.push_back(E1 -> tree.front());
   newt.pntr->subtrees.push_back(F3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | F 
   F1 -> type = tkn_E;
   return F1;
%   ;

% F : F TIMES G 
   token t = tkn_F;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("*"));
   newt.pntr->subtrees.push_back(F1 -> tree.front());
   newt.pntr->subtrees.push_back(G3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | F DIVIDES G
   token t = tkn_F;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("/"));
   newt.pntr->subtrees.push_back(F1 -> tree.front());
   newt.pntr->subtrees.push_back(G3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | G 
   G1 -> type = tkn_F;
   return G1;
%   ;

% G : MINUS G 
   token t = tkn_G;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("-"));
   newt.pntr->subtrees.push_back(G2 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | PLUS G 
   return G2;
%   | H 
   H1 -> type = tkn_G;
   return H1;
%   ;

% H : LPAR E RPAR
   E2 -> type = tkn_H;
   return E2;
%   | IDENTIFIER 
   token t = tkn_H;
   tree newt = tree("VAR");
   newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   t.tree.push_back(newt);
   return t;
%   | NUMBER 
   token h = tkn_H;
   tree newt = tree("INT");
   newt.pntr->subtrees.push_back(tree(NUMBER1 -> value.front()));
   h.tree.push_back(newt);
   return h;
%   | IDENTIFIER LPAR LISTARGS RPAR 
   token t = tkn_H;
   tree newt = tree("FUNCALL");
   newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   for (auto a : LISTARGS3 -> tree) {
      newt.pntr->subtrees.push_back(a);
   }
   t.tree.push_back(newt);
   return t;
%   ;

% LISTARGS : E 
   token t = tkn_LISTARGS;
   t.tree.push_back(E1 -> tree.front());
   return t;
%          | LISTARGS COMMA E
   LISTARGS1 -> tree.push_back(E3 -> tree.front());
   return LISTARGS1;
%          ;
