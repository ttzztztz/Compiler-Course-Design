#include "compiler.h"

tuple<Function *, FunctionType *, Function *, FunctionType *> inject_print_function(LLVMContext &ctx, IRBuilder<> &builder, Module &_module)
{
    vector<Type *> printfArgsTypes({Type::getInt8PtrTy(ctx)});

    Function *printf_func = _module.getFunction("printf");
    FunctionType *printf_func_type = FunctionType::get(
        Type::getInt32Ty(_module.getContext()),
        {Type::getInt8PtrTy(_module.getContext())},
        true);
    if (printf_func == nullptr)
    {
        printf_func = Function::Create(printf_func_type, GlobalValue::ExternalLinkage, "printf", _module);
        printf_func->setCallingConv(llvm::CallingConv::C);
    }

    FunctionType *print_int_func_type = FunctionType::get(
        Type::getInt32Ty(ctx),
        {Type::getInt32Ty(_module.getContext())},
        false);
    Function *print_int_func = Function::Create(print_int_func_type, GlobalValue::ExternalLinkage, "print_int", _module);
    BasicBlock *block = BasicBlock::Create(ctx, "", print_int_func);
    IRBuilder<> block_builder(block);

    vector<Value *> parameters = {
        block_builder.CreateGlobalStringPtr("%d\n"),
        print_int_func->getArg(0)};
    auto ret = block_builder.CreateCall(printf_func, parameters, "");
    block_builder.CreateRet(ret);

    return {printf_func, printf_func_type, print_int_func, print_int_func_type};
}
