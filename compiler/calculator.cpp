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
   std::cout << getVal();
}

class IntExprAST : public ExprAST {
   int Val;

   public:
   IntExprAST(int Val) : Val(Val) {}

   int getVal() { return this->Val; }

   void pretty_print();
};

void IntExprAST::pretty_print() {
   std::cout << getVal();
}

class VariableExprAST : public ExprAST {
   std::string Name;

   public:
   VariableExprAST(const std::string &Name) : Name(Name) {}

   std::string getName() { return this->Name; }

   void pretty_print();
};

void VariableExprAST::pretty_print() {
   std::cout << getName();
}

class BinaryExprAST : public ExprAST {
   std::string Op;
   std::unique_ptr<ExprAST> LHS, RHS;

   public:
   BinaryExprAST(const std::string &Op,
         std::unique_ptr<ExprAST> lhs,
         std::unique_ptr<ExprAST> rhs)
      : Op(Op), LHS(std::move(lhs)), RHS(std::move(rhs)) {}

   const std::string getOp() { return Op; }
   ExprAST * getLHS() { return LHS.get(); }
   ExprAST * getRHS() { return RHS.get(); }

   void pretty_print();
};

void BinaryExprAST::pretty_print() {
   std::cout << "(";
   getLHS()->pretty_print();
   std::cout << " " << getOp() << " ";
   getRHS()->pretty_print();
   std::cout << ")";
}

class AssignmentExprAST : public ExprAST {
   std::string Name;
   std::unique_ptr<ExprAST> Expr;

   public:
   AssignmentExprAST(const std::string &Name,
         std::unique_ptr<ExprAST> Expr)
      : Name(Name), Expr(std::move(Expr)) {}

   void pretty_print();
};

void AssignmentExprAST::pretty_print() {
   std::cout << Name << " := ";
   Expr->pretty_print();
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
   std::cout << getCallee() << "(";
   for (auto &a : getArgs()) {
      a->pretty_print();
      std::cout << ", ";
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
   ExternExprAST(const std::string &Name,
         const std::string &ReturnType)
      : Name(Name), ReturnType(ReturnType) {}

   void pretty_print();
};

void ExternExprAST::pretty_print() {
   std::cout << "extern " << ReturnType << " " << Name << "(";
   for (auto &a : Args) {
      a->pretty_print();
      std::cout << ", ";
   }
   std::cout << ")\n";
}

class FunctionDefinitionExprAST : public ExprAST {
   std::string Name;
   std::string ReturnType;
   std::vector<std::unique_ptr<ExprAST>> Args;
   std::vector<std::unique_ptr<ExprAST>> Body;

   public:
   FunctionDefinitionExprAST(const std::string &Name,
         const std::string &ReturnType,
         std::vector<std::unique_ptr<ExprAST>> Args,
         std::vector<std::unique_ptr<ExprAST>> Body)
      : Name(Name), ReturnType(ReturnType), Args(std::move(Args)), Body(std::move(Body)) {}

   void pretty_print();
};

void FunctionDefinitionExprAST::pretty_print() {
   std::cout << "fun " << ReturnType << " " << Name << "(";
   for (auto &a : Args) {
      a->pretty_print();
      std::cout << ", ";
   }
   std::cout << ") {\n";
   for (auto &a : Body) {
      a->pretty_print();
      std::cout << ";\n";
   }
   std::cout << "}\n";
}

class WhileExprAST : public ExprAST {
   std::unique_ptr<ExprAST> Condition;
   std::vector<std::unique_ptr<ExprAST>> Body;

   public:
   WhileExprAST(std::unique_ptr<ExprAST> Condition,
         std::vector<std::unique_ptr<ExprAST>> Body)
      : Condition(std::move(Condition)), Body(std::move(Body)) {}

   void pretty_print();
};

void WhileExprAST::pretty_print() {
   std::cout << "while (";
   Condition->pretty_print();
   std::cout << ") {\n";
   for (auto &a : Body) {
      a->pretty_print();
      std::cout << ";\n";
   }
   std::cout << "}";
}

class IfExprAST : public ExprAST {
   std::unique_ptr<ExprAST> Condition;
   std::vector<std::unique_ptr<ExprAST>> IfTrue;
   std::vector<std::unique_ptr<ExprAST>> IfFalse;

   public:
   IfExprAST(std::unique_ptr<ExprAST> Condition,
         std::vector<std::unique_ptr<ExprAST>> IfTrue,
         std::vector<std::unique_ptr<ExprAST>> IfFalse)
      : Condition(std::move(Condition)), IfTrue(std::move(IfTrue)), IfFalse(std::move(IfFalse)) {}

   void pretty_print();
};

void IfExprAST::pretty_print() {
   std::cout << "if (";
   Condition->pretty_print();
   std::cout << ") {\n";
   for (auto &a : IfTrue) {
      a->pretty_print();
      std::cout << ";\n";
   }
   std::cout << "} else {";
   for (auto &a : IfFalse) {
      a->pretty_print();
      std::cout << ";\n";
   }
   std::cout << "}";
}

class ReturnExprAST : public ExprAST {
   std::unique_ptr<ExprAST> Result;

   public:
   ReturnExprAST(std::unique_ptr<ExprAST> Result) : Result(std::move(Result)) {}

   void pretty_print();
};

void ReturnExprAST::pretty_print() {
   std::cout << "result ";
   Result->pretty_print();
}

class ArgAST : public ExprAST {
   std::string Type;
   std::string Name;

   public:
   ArgAST(const std::string &Name, const std::string &Type) : Name(Name), Type(Type) {}

   void pretty_print();
};

void ArgAST::pretty_print() {
   std::cout << Type << " " << Name;
}

std::unique_ptr<ExprAST> transform(tree t) {
   const std::string nodeName = dynamic_cast<const stringvalue*>(t.pntr->val)->s;

   if (nodeName.compare("EXTERN") == 0) {
      const std::string returnType = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s;
      const std::string name = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(1).pntr->val)->s;
      std::vector< std::unique_ptr<ExprAST> > args;
      for (auto &a : t.pntr->subtrees.at(2).pntr->subtrees) {
         const std::string argType = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(0).pntr->val)->s;
         const std::string argName = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(1).pntr->val)->s;
         args.push_back(std::unique_ptr<ExprAST>(new ArgAST(argName, argType)));
      }
      return std::unique_ptr<ExprAST>(new ExternExprAST(name, returnType, std::move(args)));
   } else if (nodeName.compare("FUN") == 0) {
      const std::string returnType = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s;
      const std::string name = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(1).pntr->val)->s;
      std::vector< std::unique_ptr<ExprAST> > args;
      for (auto &a : t.pntr->subtrees.at(2).pntr->subtrees) {
         const std::string argType = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(0).pntr->val)->s;
         const std::string argName = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(1).pntr->val)->s;
         args.push_back(std::unique_ptr<ExprAST>(new ArgAST(argName, argType)));
      }
      std::vector< std::unique_ptr<ExprAST> > body;
      for (auto &a : t.pntr->subtrees.at(3).pntr->subtrees) {
         body.push_back(transform(a));
      }
      return std::unique_ptr<ExprAST>(new FunctionDefinitionExprAST(name, returnType, std::move(args), std::move(body)));
   } else if (nodeName.compare("ASSIGN") == 0) {
      const std::string name = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s;
      std::unique_ptr<ExprAST> expr = transform(t.pntr->subtrees.at(1));
      return std::unique_ptr<ExprAST>(new AssignmentExprAST(name, std::move(expr)));
   } else if (nodeName.compare("OPCALL") == 0) {
      const std::string op = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s;
      std::unique_ptr<ExprAST> lhs = transform(t.pntr->subtrees.at(1));
      std::unique_ptr<ExprAST> rhs = transform(t.pntr->subtrees.at(2));
      return std::unique_ptr<ExprAST>(new BinaryExprAST(op, std::move(lhs), std::move(rhs)));
   } else if (nodeName.compare("INT") == 0) {
      int val = dynamic_cast<const doublevalue *>(t.pntr->subtrees.at(0).pntr->val)->d;
      return std::unique_ptr<ExprAST>(new IntExprAST(val));
   } else if (nodeName.compare("VAR") == 0) {
      const std::string name = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s;
      return std::unique_ptr<ExprAST>(new VariableExprAST(name));
   } else if (nodeName.compare("FUNCALL") == 0) {
      const std::string name = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s;
      std::vector< std::unique_ptr<ExprAST> > args;
      for (int i = 1; i < t.pntr->subtrees.size(); i++) {
         args.push_back(transform(t.pntr->subtrees.at(i)));
      }
      return std::unique_ptr<ExprAST>(new CallExprAST(name, std::move(args)));
   } else if (nodeName.compare("WHILE") == 0) {
      std::unique_ptr<ExprAST> condition = transform(t.pntr->subtrees.at(0));
      std::vector< std::unique_ptr<ExprAST> > body;
      for (auto &a : t.pntr->subtrees.at(1).pntr->subtrees) {
         body.push_back(transform(a));
      }
      return std::unique_ptr<ExprAST>(new WhileExprAST(std::move(condition), std::move(body)));
   } else if (nodeName.compare("EXPRESSION") == 0) {
      std::unique_ptr<ExprAST> e = transform(t.pntr->subtrees.at(0));
      return e;
   } else if (nodeName.compare("RETURN") == 0) {
      std::unique_ptr<ExprAST> result = transform(t.pntr->subtrees.at(0));
      return std::unique_ptr<ExprAST>(new ReturnExprAST(std::move(result)));
   } else if (nodeName.compare("IF") == 0) {
      std::unique_ptr<ExprAST> condition = transform(t.pntr->subtrees.at(0));
      std::vector< std::unique_ptr<ExprAST> > ifTrue;
      for (auto &a : t.pntr->subtrees.at(1).pntr->subtrees) {
         ifTrue.push_back(transform(a));
      }
      std::vector< std::unique_ptr<ExprAST> > ifFalse;
      for (auto &a : t.pntr->subtrees.at(2).pntr->subtrees) {
         ifFalse.push_back(transform(a));
      }
      return std::unique_ptr<ExprAST>(new IfExprAST(std::move(condition), std::move(ifTrue), std::move(ifFalse)));
   }
   std::cout << "ExprAST name: " << nodeName << std::endl;
   return std::unique_ptr<ExprAST>(new IntExprAST(3));
}

int main(int argc, char* argv []) {

   tokenizer tt;

   varstore vs;

   parser(tt, vs, tkn_Session, 15);

   ASSERT(tt.lookahead.size());
   
   if (tt.lookahead.front().type != tkn_Session) {
      std::cout << "ended with an error\n";
      return 1;
   }

   std::vector< std::unique_ptr<ExprAST> > defs;
   for (auto a : tt.lookahead.front().tree) {
      std::unique_ptr<ExprAST> res = transform(a);
      if (true) {
         res.get()->pretty_print();
      }
      defs.push_back(std::move(res));
   }

   return 0;
}
