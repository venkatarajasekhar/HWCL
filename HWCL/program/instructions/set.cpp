#include "set.h"
#include "../../parser/parser.h"
#include "../../calculator/calculator.h"
#include "../../vm/process.h"

using namespace program::instructions;

set::set(const string &source)
: instruction(source, "set")
{

}

set::~set()
{
  if (proc)
    delete proc;
}

bool set::Signature(const string &source)
{
  return parser::CompareCommand(source, "SET");
}

void set::Bind(vm::context &c)
{
  auto tokens = parser::Split(Source() , ' ', true);
  string expr;

  auto t = parser::Split(tokens[1], '=', true);
  auto name = t[0];
  variable = name;

  decltype(tokens) expr_tokens;
  if (t.size() > 1)
  {
    throw_assert(t.size() == 2); // mean SET A=B=C
    expr_tokens.assign(t.begin() + 1, t.end());
  }
  expr_tokens.insert(expr_tokens.end(), tokens.begin() + 2, tokens.end());

  expr = convert<string>(expr_tokens);
  proc = NEW calculator::calculator(expr);
}

void set::Execute(vm::context &c)
{
  throw_assert(proc);
  calculator::calculator::get_callback GetC = [&](string name) -> dbl
  {
    return c.Local(name);
  };

  double res = proc->Calculate(GetC);
  c.Local(variable) = res;
}