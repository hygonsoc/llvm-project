//===-- llvm/CodeGen/MachineCodeEmitter.h - Code emission -------*- C++ -*-===//
//
// This file defines an abstract interface that is used by the machine code
// emission framework to output the code.  This allows machine code emission to
// be seperated from concerns such as resolution of call targets, and where the
// machine code will be written (memory or disk, f.e.).
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CODEGEN_MACHINE_CODE_EMITTER_H
#define LLVM_CODEGEN_MACHINE_CODE_EMITTER_H

class MachineFunction;
class MachineBasicBlock;
class Value;
class GlobalValue;

struct MachineCodeEmitter {
  virtual ~MachineCodeEmitter() {}

  /// startFunction - This callback is invoked when the specified function is
  /// about to be code generated.
  ///
  virtual void startFunction(MachineFunction &F) {}
  
  /// finishFunction - This callback is invoked when the specified function has
  /// finished code generation.
  ///
  virtual void finishFunction(MachineFunction &F) {}

  /// startBasicBlock - This callback is invoked when a new basic block is about
  /// to be emitted.
  ///
  virtual void startBasicBlock(MachineBasicBlock &BB) {}

  /// emitByte - This callback is invoked when a byte needs to be written to the
  /// output stream.
  ///
  virtual void emitByte(unsigned char B) {}

  /// emitPCRelativeDisp - This callback is invoked when we need to write out a
  /// PC relative displacement for the specified Value*.  This is used for call
  /// and jump instructions typically.
  ///
  virtual void emitPCRelativeDisp(Value *V) {}

  /// emitGlobalAddress - This callback is invoked when we need to write out the
  /// address of a global value to machine code.  This is important for indirect
  /// calls as well as accessing global variables.
  ///
  virtual void emitGlobalAddress(GlobalValue *V) {}


  /// createDebugMachineCodeEmitter - Return a dynamically allocated machine
  /// code emitter, which just prints the opcodes and fields out the cout.  This
  /// can be used for debugging users of the MachineCodeEmitter interface.
  ///
  static MachineCodeEmitter *createDebugMachineCodeEmitter();
};

#endif
