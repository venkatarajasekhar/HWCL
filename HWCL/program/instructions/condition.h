#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class condition : public instruction
    {
    public:
      condition(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

