
%token EOF SCANERROR
%token SEMICOLON BECOMES COMMA 
%token IDENTIFIER NUMBER 
%token PLUS TIMES MINUS DIVIDES
%token OP_EQ OP_NEQ
%token OP_AND OP_OR
%token FACTORIAL
%token LPAR RPAR
%token LBRACKET RBRACKET
%token FUN_KW WHILE_KW RETURN_KW IF_KW ELSE_KW EXTERN_KW
%token INT_TYPE FLOAT_TYPE

// Non-terminal symbols:

%token EB EC EE EF EG EH LISTARGS 
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
%constraint EB tree 1 2
%constraint EC tree 1 2
%constraint EE tree 1 2
%constraint EF tree 1 2
%constraint EG tree 1 2
%constraint EH tree 1 2
%constraint LISTARGS tree 0
%constraint SCANERROR id 1 2
%constraint NUMBER value 1 2
%constraint Command tree 0
%constraint Session tree 0

%global memory varstore
   // Contains the stored variables.

#include "varstore.h"
#include "tree.h"

#include "assert.h"
#include <math.h>


% Start : Session EOF
   std::cout << "bye bye\n";
   return Session1;
%   ;

% Session : Session Command 
   Session1 -> tree.push_back( Command2 -> tree.front() );
   return Session1;
%         |
   token t = tkn_Session;
   return t;
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

% STATEMENT : EB
   token t = tkn_STATEMENT;
   tree newt = tree("EXPRESSION");
   newt.pntr->subtrees.push_back(EB1 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | IDENTIFIER BECOMES EB
   token t = tkn_STATEMENT;
   tree newt = tree("ASSIGN");
   newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   newt.pntr->subtrees.push_back(EB3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | WHILE_KW EB LBRACKET STATEMENTS RBRACKET
   token t = tkn_STATEMENT;
   tree newt = tree("WHILE");
   newt.pntr->subtrees.push_back(EB2 -> tree.front());
   newt.pntr->subtrees.push_back(STATEMENTS4 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | RETURN_KW EB
   token t = tkn_STATEMENT;
   tree newt = tree("RETURN");
   newt.pntr->subtrees.push_back(EB2 -> tree.front());
   t.tree.push_back(newt);
   return t;
%           | IF_KW EB LBRACKET STATEMENTS RBRACKET ELSE_KW LBRACKET STATEMENTS RBRACKET
   token t = tkn_STATEMENT;
   tree newt = tree("IF");
   newt.pntr->subtrees.push_back(EB2 -> tree.front());
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

% EB : EB OP_AND EC
   token t = tkn_EB;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("&&"));
   newt.pntr->subtrees.push_back(EB1 -> tree.front());
   newt.pntr->subtrees.push_back(EC3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EB OP_OR EC
   token t = tkn_EB;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("||"));
   newt.pntr->subtrees.push_back(EB1 -> tree.front());
   newt.pntr->subtrees.push_back(EC3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EC
   EC1 -> type = tkn_EB;
   return EC1;
%   ;

% EC : EC OP_EQ EE
   token t = tkn_EC;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("=="));
   newt.pntr->subtrees.push_back(EC1 -> tree.front());
   newt.pntr->subtrees.push_back(EE3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EC OP_NEQ EE
   token t = tkn_EC;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("!="));
   newt.pntr->subtrees.push_back(EC1 -> tree.front());
   newt.pntr->subtrees.push_back(EE3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EE
   EE1 -> type = tkn_EC;
   return EE1;
%   ;

% EE : EE PLUS EF 
   token t = tkn_EE;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("+"));
   newt.pntr->subtrees.push_back(EE1 -> tree.front());
   newt.pntr->subtrees.push_back(EF3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EE MINUS EF 
   token t = tkn_EE;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("-"));
   newt.pntr->subtrees.push_back(EE1 -> tree.front());
   newt.pntr->subtrees.push_back(EF3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EF 
   EF1 -> type = tkn_EE;
   return EF1;
%   ;

% EF : EF TIMES EG 
   token t = tkn_EF;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("*"));
   newt.pntr->subtrees.push_back(EF1 -> tree.front());
   newt.pntr->subtrees.push_back(EG3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EF DIVIDES EG
   token t = tkn_EF;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("/"));
   newt.pntr->subtrees.push_back(EF1 -> tree.front());
   newt.pntr->subtrees.push_back(EG3 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | EG 
   EG1 -> type = tkn_EF;
   return EG1;
%   ;

% EG : MINUS EG 
   token t = tkn_EG;
   tree newt = tree("OPCALL");
   newt.pntr->subtrees.push_back(tree("-"));
   newt.pntr->subtrees.push_back(EG2 -> tree.front());
   t.tree.push_back(newt);
   return t;
%   | PLUS EG 
   return EG2;
%   | EH 
   EH1 -> type = tkn_EG;
   return EH1;
%   ;

% EH : LPAR EB RPAR
   EB2 -> type = tkn_EH;
   return EB2;
%   | IDENTIFIER 
   token t = tkn_EH;
   tree newt = tree("VAR");
   newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   t.tree.push_back(newt);
   return t;
%   | NUMBER 
   token h = tkn_EH;
   tree newt = tree("INT");
   newt.pntr->subtrees.push_back(tree(NUMBER1 -> value.front()));
   h.tree.push_back(newt);
   return h;
%   | IDENTIFIER LPAR LISTARGS RPAR 
   token t = tkn_EH;
   tree newt = tree("FUNCALL");
   newt.pntr->subtrees.push_back(tree(IDENTIFIER1 -> id.front()));
   for (auto a : LISTARGS3 -> tree) {
      newt.pntr->subtrees.push_back(a);
   }
   t.tree.push_back(newt);
   return t;
%   ;

% LISTARGS : EB
   token t = tkn_LISTARGS;
   t.tree.push_back(EB1 -> tree.front());
   return t;
%          | LISTARGS COMMA EB
   LISTARGS1 -> tree.push_back(EB3 -> tree.front());
   return LISTARGS1;
%          ;
