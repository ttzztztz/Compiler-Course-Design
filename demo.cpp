#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;
using std::string;

LLVMContext TheContext;
IRBuilder<> Builder(TheContext);

void expr() {
    Value* left_val = ConstantInt::get(Type::getInt32Ty(TheContext), 12);
    Value* right_val = ConstantInt::get(Type::getInt32Ty(TheContext), 24);

    Value* res = Builder.CreateAdd(left_val, right_val, "add");
    res->print(errs());
}

void fn() {
    std::vector<Type *> parameters(2, Type::getInt32Ty(TheContext));
    FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), parameters, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, "add_fn");

    Value *l = nullptr, *r = nullptr;
    int Idx = 0;
    for (auto &Arg : F->args()) {
        Arg.setName(string{ char('a' + Idx) });

        if (Idx == 0) l = &Arg;
        else r = &Arg;

        Idx++;
    }

    BasicBlock *block = BasicBlock::Create(TheContext, "entry", F);
    Builder.SetInsertPoint(block);

    Value* ret_val = Builder.CreateAdd(l, r, "add");
    Builder.CreateRet(ret_val);

    F->print(errs());
}

int main() {
    // expr();
    fn();

    return 0;
}