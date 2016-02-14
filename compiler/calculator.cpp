#include "assert.h"
#include "reader.h"
#include "tokenizer.h"
#include "varstore.h"
#include "parser.h"
#include <memory>

class ExprAST {
   public:
   virtual ~ExprAST() {}
   virtual void pretty_print() = 0;
};

class DoubleExprAST : public ExprAST {
   double Val;

   public:
   DoubleExprAST(double Val) : Val(Val) {}

   double getVal() { return this->Val; }

   void pretty_print();
};

void DoubleExprAST::pretty_print() {
   std::cout << "(DOUBLE " << getVal() << ")";
}

class IntExprAST : public ExprAST {
   int Val;

   public:
   IntExprAST(int Val) : Val(Val) {}

   int getVal() { return this->Val; }

   void pretty_print();
};

void IntExprAST::pretty_print() {
   std::cout << "(INT " << getVal() << ")";
}

class VariableExprAST : public ExprAST {
   std::string Name;

   public:
   VariableExprAST(const std::string &Name) : Name(Name) {}

   std::string getName() { return this->Name; }

   void pretty_print();
};

void VariableExprAST::pretty_print() {
   std::cout << "(VAR " << getName() << ")";
}

class BinaryExprAST : public ExprAST {
   char Op;
   std::unique_ptr<ExprAST> LHS, RHS;

   public:
   BinaryExprAST(char op,
         std::unique_ptr<ExprAST> lhs,
         std::unique_ptr<ExprAST> rhs)
      : Op(op), LHS(std::move(lhs)), RHS(std::move(rhs)) {}

   char getOp() { return Op; }
   ExprAST * getLHS() { return LHS.get(); }
   ExprAST * getRHS() { return RHS.get(); }

   void pretty_print();
};

void BinaryExprAST::pretty_print() {
   std::cout << "(BINOP " << getOp();
   getLHS()->pretty_print();
   getRHS()->pretty_print();
   std::cout << ")";
}

class CallExprAST : public ExprAST {
   std::string Callee;
   std::vector<std::unique_ptr<ExprAST>> Args;

   public:
   CallExprAST(const std::string &Callee,
         std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}

   std::string getCallee() { return Callee; }
   std::vector<std::unique_ptr<ExprAST>> const& getArgs() {
      return Args;
   }

   void pretty_print();
};

void CallExprAST::pretty_print() {
   std::cout << "(CALL " << getCallee();
   for (auto &a : getArgs()) {
      a->pretty_print();
   }
   std::cout << ")";
}

class ExternExprAST : public ExprAST {
   std::string Name;
   std::string ReturnType;
   std::vector<std::unique_ptr<ExprAST>> Args;

   public:
   ExternExprAST(const std::string &Name,
         const std::string &ReturnType,
         std::vector<std::unique_ptr<ExprAST>> Args)
      : Name(Name), ReturnType(ReturnType), Args(std::move(Args)) {}

   void pretty_print();
};

void ExternExprAST::pretty_print() {
   std::cout << "(EXTERN " << ReturnType << " " << Name;
   for (auto &a : Args) {
      a->pretty_print();
   }
   std::cout << ")";
}

std::unique_ptr<ExprAST> transform(tree t) {
   /* std::cout << t.pntr->val << std::endl; */
   const stringvalue * sv = dynamic_cast<const stringvalue*>(t.pntr->val);
   std::string s = sv->s;
   if (s.compare("EXTERN") == 0) {
      std::cout << "Extern";
      /* std::vector< std::unique_ptr<ExprAST> > args; */
      /* return std::unique_ptr<ExprAST>(new ExternExprAST("foo", "bar", args)); */
      return std::unique_ptr<ExprAST>(new IntExprAST(3));
   }
   std::cout << "ExprAST name: " << s << std::endl;
   return std::unique_ptr<ExprAST>(new IntExprAST(3));
}

int main(int argc, char* argv []) {

   tokenizer tt;

#if 0
   tt. scan( );

   // Test the tokenizer:

   while( tt. lookahead. size( ) && 
          tt. lookahead. front( ). type != tkn_EOF )
   {
      std::cout << tt. lookahead. front( ) << "\n";
      tt. lookahead. pop_front( ); 
      tt. scan( ); 
   }

   // Actually if the size of lookahead gets 0, something went wrong.

   ASSERT( tt. lookahead. size( ));
   std::cout << tt. lookahead. front( ) << "\n";
      // This is an EOF token. 
   return 0;
 
#endif

   varstore vs;

   parser(tt, vs, tkn_Session, 15);

   ASSERT(tt.lookahead.size());
   
   if (tt.lookahead.front().type != tkn_Session) {
      std::cout << "ended with an error\n";
      return 1;
   }

   /* std::cout << tt.lookahead.front().tree.front(); */
   for (auto a : tt.lookahead.front().tree) {
      /* auto a = tt.looakead.front().tree.front(); */
      std::cout << a << std::endl;
      std::unique_ptr<ExprAST> res = transform(a);
      ExprAST * expr_ptr = res.get();
      expr_ptr->pretty_print();
   }

   return 0;
}
