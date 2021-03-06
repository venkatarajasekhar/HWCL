#pragma once

#include "../export_header.h"
#include <memory>

namespace vm
{
  class process_handler;
}

namespace particular
{
  enum PROC_STATUSES
  {
    UNDEFINED, // Invalid value
    STORING,  // Program save state performing
    RESTORING,  // Program load state performing
    PARSING, // Program transliteration
    COMPILING, // Linking with memory, compile instructions
    RUNNING, // Run state
    WAITING, // Wait for resource instruction
    PAUSED, // Execution paused
    STOPED, // Execution stopped (aborted)
    FINISHED, // Process finished

    INVALID_HANDLER, // System detected handler as invalid

    _FICTIVE_VALUE // Dont mess with comma and CVS
  };

  struct process_impl
#if CPP11_SUPPORTED
  {
    std::shared_ptr<::vm::process_handler> p;

    process_impl(std::shared_ptr<::vm::process_handler> pp)
      : p(pp)
    {

    }
  }
#endif
  ;

  class _HWCL_METHOD_ process
  {
    process_impl *i;
  public:
    ~process();
    process();
    process(const process &);
    process(::vm::process_handler);
    PROC_STATUSES Status();
  };
}