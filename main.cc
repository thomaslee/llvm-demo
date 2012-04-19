#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/IRBuilder.h>

static llvm::Function*
printf_prototype(llvm::LLVMContext& ctx, llvm::Module *mod)
{
    std::vector<const llvm::Type*> printf_arg_types;
    printf_arg_types.push_back(llvm::Type::getInt8PtrTy(ctx));

    llvm::FunctionType* printf_type =
        llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), printf_arg_types, true);

    llvm::Function *func = llvm::Function::Create(
                printf_type, llvm::Function::ExternalLinkage,
                llvm::Twine("printf"),
                mod
           );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

static llvm::Function*
main_prototype(llvm::LLVMContext& ctx, llvm::Module *mod)
{
    std::vector<const llvm::Type*> main_arg_types;

    llvm::FunctionType* main_type =
        llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), main_arg_types, false);

    llvm::Function *func = llvm::Function::Create(
                main_type, llvm::Function::ExternalLinkage,
                llvm::Twine("main"),
                mod
           );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

int
main(int argc, char **argv)
{
    llvm::LLVMContext& ctx = llvm::getGlobalContext();
    llvm::Module module("example", ctx);
    llvm::IRBuilder<> builder(ctx);

    llvm::Function *printf_func = printf_prototype(ctx, &module);

    llvm::Function *main_func = main_prototype(ctx, &module);
    llvm::BasicBlock *block =
        llvm::BasicBlock::Create(ctx, "", main_func, 0);
    builder.SetInsertPoint(block);

    llvm::Constant *left = llvm::ConstantInt::get(ctx, llvm::APInt(32, 15));
    llvm::Constant *right = llvm::ConstantInt::get(ctx, llvm::APInt(32, 10));
    llvm::Value *add = builder.CreateAdd(left, right);

    llvm::Constant *format_const =
        llvm::ConstantArray::get(ctx, "%d\n");
    llvm::GlobalVariable *var =
        new llvm::GlobalVariable(
            module, llvm::ArrayType::get(llvm::IntegerType::get(ctx, 8), 4),
            true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");
    llvm::Constant *zero = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(ctx));

    //
    // NOTE: using constant array works here.
    // &std::vector<Value*>[...] does not. Don't know why.
    //
    llvm::Constant *indices[] = {
        zero,
        zero
    };
    llvm::Constant *var_ref =
        llvm::ConstantExpr::getGetElementPtr(var, indices, 2);

    llvm::CallInst *call = builder.CreateCall2(printf_func, var_ref, add);
    call->setTailCall(false);

    llvm::ReturnInst::Create(ctx, zero, block);

    module.dump();

    return 0;
}

