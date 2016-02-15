#include "assert.h"
#include "reader.h"
#include "tokenizer.h"
#include "varstore.h"
#include "parser.h"
#include <memory>

// for IR compiler
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

// for JIT execution
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"

using namespace llvm;

class ArgAST {
   std::string Name;
   std::string Type;

   public:
   ArgAST(const std::string &Name, const std::string &Type) : Name(Name), Type(Type) {}

   std::string getName() { return Name; }

   void pretty_print();
};

void ArgAST::pretty_print() {
   std::cout << Type << " " << Name;
}

class ExprAST {
   public:
   virtual ~ExprAST() {}
   virtual void pretty_print() = 0;
   virtual Value * codegen() = 0;
};

class DoubleExprAST : public ExprAST {
   double Val;

   public:
   DoubleExprAST(double Val) : Val(Val) {}

   double getVal() { return this->Val; }

   void pretty_print();
   Value * codegen();
};

void DoubleExprAST::pretty_print() {
   std::cout << getVal() << "f";
}

class IntExprAST : public ExprAST {
   int Val;

   public:
   IntExprAST(int Val) : Val(Val) {}

   int getVal() { return this->Val; }

   void pretty_print();
   Value * codegen();
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
   Value * codegen();
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
   Value * codegen();
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
   Value * codegen();
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
   Value * codegen();
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
   Value * codegen();
};

void ExternExprAST::pretty_print() {
   std::cout << "extern " << ReturnType << " " << Name << "(";
   for (auto &a : Args) {
      a->pretty_print();
      std::cout << ", ";
   }
   std::cout << ")\n";
}

class FunctionDefinitionAST {
   std::string Name;
   std::string ReturnType;
   std::vector<std::unique_ptr<ArgAST>> Args;
   std::vector<std::unique_ptr<ExprAST>> Body;

   public:
   FunctionDefinitionAST(const std::string &Name,
         const std::string &ReturnType,
         std::vector<std::unique_ptr<ArgAST>> Args,
         std::vector<std::unique_ptr<ExprAST>> Body)
      : Name(Name), ReturnType(ReturnType), Args(std::move(Args)), Body(std::move(Body)) {}

   void pretty_print();
   Function * codegen();
};

void FunctionDefinitionAST::pretty_print() {
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
   Value * codegen();
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
   Value * codegen();
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
   Value * codegen();
};

void ReturnExprAST::pretty_print() {
   std::cout << "return ";
   Result->pretty_print();
}

std::unique_ptr<ExprAST> transform(tree t) {
   const std::string nodeName = dynamic_cast<const stringvalue*>(t.pntr->val)->s;

   if (nodeName.compare("ASSIGN") == 0) {
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
      for (size_t i = 1; i < t.pntr->subtrees.size(); i++) {
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

std::unique_ptr<FunctionDefinitionAST> transform_func(tree t) {
   const std::string nodeName = dynamic_cast<const stringvalue*>(t.pntr->val)->s;

   if (nodeName.compare("EXTERN") == 0) {
      std::cout << "EXTERN MEH ERROR";
      /* const std::string returnType = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s; */
      /* const std::string name = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(1).pntr->val)->s; */
      /* std::vector< std::unique_ptr<ExprAST> > args; */
      /* for (auto &a : t.pntr->subtrees.at(2).pntr->subtrees) { */
      /*    const std::string argType = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(0).pntr->val)->s; */
      /*    const std::string argName = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(1).pntr->val)->s; */
      /*    args.push_back(std::unique_ptr<ExprAST>(new ArgAST(argName, argType))); */
      /* } */
      /* return std::unique_ptr<ExprAST>(new ExternExprAST(name, returnType, std::move(args))); */
      std::vector< std::unique_ptr<ArgAST> > args;
      std::vector< std::unique_ptr<ExprAST> > body;
      return std::unique_ptr<FunctionDefinitionAST>(new FunctionDefinitionAST("foo", "bar", std::move(args), std::move(body)));
   } else if (nodeName.compare("FUN") == 0) {
      const std::string returnType = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(0).pntr->val)->s;
      const std::string name = dynamic_cast<const stringvalue *>(t.pntr->subtrees.at(1).pntr->val)->s;
      std::vector< std::unique_ptr<ArgAST> > args;
      for (auto &a : t.pntr->subtrees.at(2).pntr->subtrees) {
         const std::string argType = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(0).pntr->val)->s;
         const std::string argName = dynamic_cast<const stringvalue *>(a.pntr->subtrees.at(1).pntr->val)->s;
         args.push_back(std::unique_ptr<ArgAST>(new ArgAST(argName, argType)));
      }
      std::vector< std::unique_ptr<ExprAST> > body;
      for (auto &a : t.pntr->subtrees.at(3).pntr->subtrees) {
         body.push_back(transform(a));
      }
      return std::unique_ptr<FunctionDefinitionAST>(new FunctionDefinitionAST(name, returnType, std::move(args), std::move(body)));
   }
}

// IR COMPILER

Value *ErrorV(const char *str) {
   fprintf(stderr, "Error: %s\n", str);
   return 0;
}

static std::unique_ptr<Module> TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<std::string, Value*> NamedValues;

Value * DoubleExprAST::codegen() {
   return ConstantFP::get(getGlobalContext(), APFloat(Val));
}

Value * IntExprAST::codegen() {
   return ConstantInt::get(getGlobalContext(), APInt(32, Val));
}

Value *VariableExprAST::codegen() {
   // Look this variable up in the function.
   Value *V = NamedValues[Name];
   return V ? V : ErrorV("Unknown variable name");
}

Value *ReturnExprAST::codegen() {
   // Look this variable up in the function.
   return Result->codegen();
}

Value *BinaryExprAST::codegen() {
  Value *L = LHS->codegen();
  Value *R = RHS->codegen();

  if (L == 0 || R == 0) {
    return 0;
  }

  if (Op.compare("+") == 0) {
    return Builder.CreateAdd(L, R, "addtmp");
  } else if (Op.compare("*") == 0) {
    return Builder.CreateMul(L, R, "multmp");
  } else if (Op.compare("-") == 0) {
    return Builder.CreateSub(L, R, "subtmp");
  } else if (Op.compare("==") == 0) {
    return Builder.CreateICmpEQ(L, R, "cmptmp");
  } else if (Op.compare(">=") == 0) {
    return Builder.CreateICmpSGE(L, R, "cmptmp");
  } else if (Op.compare("<=") == 0) {
    return Builder.CreateICmpSLE(L, R, "cmptmp");
  } else if (Op.compare(">") == 0) {
    return Builder.CreateICmpSGT(L, R, "cmptmp");
  } else if (Op.compare("<") == 0) {
    return Builder.CreateICmpSLT(L, R, "cmptmp");
  } else if (Op.compare("!=") == 0) {
    return Builder.CreateICmpNE(L, R, "cmptmp");
  } else {
    return ErrorV("invalid binary operator");
  }
}

Value * CallExprAST::codegen() {
   // Look up the name in the global module table.
   Function *CalleeF = TheModule->getFunction(Callee);
   if (CalleeF == 0)
      return ErrorV("Unknown function referenced");

   // If argument mismatch error.
   if (CalleeF->arg_size() != Args.size())
      return ErrorV("Incorrect # arguments passed");

   std::vector<Value*> ArgsV;
   for (unsigned i = 0, e = Args.size(); i != e; ++i) {
      ArgsV.push_back(Args[i]->codegen());
      if (ArgsV.back() == 0) return 0;
   }

   return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

Value * IfExprAST::codegen() {
  Value *CondV = Condition->codegen();

  if (CondV == 0) {
    // generating of condition code failed
    return 0;
  }

  // Convert condition to a bool by comparing equal to 0.0.
  CondV = Builder.CreateICmpNE(CondV,
      ConstantInt::get(getGlobalContext(), APInt(1, 0)),
      "ifcond");

  Function *TheFunction = Builder.GetInsertBlock()->getParent();

  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  BasicBlock *ThenBB = BasicBlock::Create(getGlobalContext(), "then", TheFunction);
  BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
  BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

  Builder.CreateCondBr(CondV, ThenBB, ElseBB);

  // Emit then value.
  Builder.SetInsertPoint(ThenBB);

  Value *ThenV = IfTrue.front()->codegen();
  if (ThenV == 0) return 0;

  Builder.CreateBr(MergeBB);
  // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
  ThenBB = Builder.GetInsertBlock();

  // Emit else block.
  TheFunction->getBasicBlockList().push_back(ElseBB);
  Builder.SetInsertPoint(ElseBB);

  Value *ElseV = IfFalse.front()->codegen();
  if (ElseV == 0) {
    return 0;
  }

  Builder.CreateBr(MergeBB);
  // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
  ElseBB = Builder.GetInsertBlock();

  // Emit merge block.
  TheFunction->getBasicBlockList().push_back(MergeBB);
  Builder.SetInsertPoint(MergeBB);
  PHINode *PN = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()), 2, "iftmp");

  PN->addIncoming(ThenV, ThenBB);
  PN->addIncoming(ElseV, ElseBB);
  return PN;
}


Function *FunctionDefinitionAST::codegen() {
  // First, check for an existing function from a previous 'extern' declaration.
  Function *TheFunction = TheModule->getFunction(Name);

  if (!TheFunction) {
  /*   TheFunction = Proto->codegen(); */
     // Make the function type:  double(double,double) etc.
     std::vector<Type *> Ints(Args.size(),
           Type::getInt32Ty(getGlobalContext()));
     FunctionType *FT =
        FunctionType::get(Type::getInt32Ty(getGlobalContext()), Ints, false);

     Function *F =
        Function::Create(FT, Function::ExternalLinkage, Name, TheModule.get());

     // Set names for all arguments.
     unsigned Idx = 0;
     for (auto &Arg : F->args()) {
        Arg.setName(Args[Idx++]->getName());
     }

     TheFunction = F;
  }

  if (!TheFunction)
    return nullptr;

  // Create a new basic block to start insertion into.
  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
  Builder.SetInsertPoint(BB);

  // Record the function arguments in the NamedValues map.
  NamedValues.clear();
  for (auto &Arg : TheFunction->args())
    NamedValues[Arg.getName()] = &Arg;

  if (Value *RetVal = Body.front()->codegen()) {
    // Finish off the function.
    Builder.CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    verifyFunction(*TheFunction);

    return TheFunction;
  }

  // Error reading body, remove function.
  TheFunction->eraseFromParent();
  return nullptr;
}

Value * WhileExprAST::codegen() { return 0; }
Value * AssignmentExprAST::codegen() { return 0; }
Value * ExternExprAST::codegen() { return 0; }


int main(int argc, char* argv []) {

   tokenizer tt;

   varstore vs;

   parser(tt, vs, tkn_Session, 15);

   ASSERT(tt.lookahead.size());
   
   if (tt.lookahead.front().type != tkn_Session) {
      std::cout << "ended with an error\n";
      return 1;
   }

   std::vector< std::unique_ptr<FunctionDefinitionAST> > defs;
   for (auto a : tt.lookahead.front().tree) {
      std::unique_ptr<FunctionDefinitionAST> res = transform_func(a);
      /* res.get()->pretty_print(); */
      defs.push_back(std::move(res));
   }

   TheModule = llvm::make_unique<Module>("my cool jit", getGlobalContext());

   for (auto &func : defs) {
      Function *llvm_func = func->codegen();
      /* llvm_func->dump(); */
   }

   TheModule->dump();

   return 0;
}
