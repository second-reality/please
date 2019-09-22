================
Coding standards
================

General
=======

Languages
+++++++++

Use exclusively those languages.

- For documentation: reStructuredText
- For scripting: Bash
- For code: C++

Editor setup
++++++++++++

Use whatever you like for writing stuff, but use this EXACT setup for anything:

- 80 columns max (ALWAYS respect it, even if your stuff just goes to 82 columns)
- Do not use tab (NEVER use it)
- Use 2 spaces for indentation
- Pay attention to extra whitespaces at end of lines or start of empty lines

If you use vim, you can simply add this to your .vimrc:

::

  " format to 80 chars, using tabs of size 2
  set textwidth=80
  set colorcolumn=+1
  set tabstop=2
  set shiftwidth=2
  set softtabstop=2
  set expandtab
  " respect textwidth
  autocmd Filetype * set formatoptions+=t

80 chars rule is very important, and NEVER NEVER should be broken. You can find
it not very convenient, but it is not possible to change about it.

Reasons to format code to 80 char are following:

- you have to write a better code to put it in this space. Less levels of
  indentation means more thinking most of the time.
- you can have two (or more) vertical buffers on your screen by respecting it.
- you can use a vertical screen with this.
- if you like command line, you should enjoy coding on 80 chars

Golden Rule
+++++++++++

Always follow style of the file you are editing, whatever it is.

reStructuredText
================

Source files
++++++++++++

File extension
--------------

You should only use .rst as file extension for reStructuredText doc.

Bash
====

Shell files
+++++++++++

File extensions
---------------

Executables should have no extension (preferred) or a .sh extension.
Libraries must have a .sh extension and should not be executable.

Formatting
++++++++++

Pipelines
---------

They should be split one per line if they don't all fit on one.

Loops
-----

Put do and then on line after while, for or if.

Case statement
--------------

Put ;; on a new line.

Variable expansion
------------------

Always use "$var" instead of $var.

Quoting
-------

Use "$@" for parameters unless you have reason to use $*.

Features
++++++++

Command call
------------

Use $(command) instead of backticks.

Naming conventions
++++++++++++++++++

Function/variable names
-----------------------

Lowercase, with underscore to separate words

Environment variable names
--------------------------

All caps, separated with underscores.

Source filenames
----------------

Lowercase, with underscores to separate words if desired.

Local variables
---------------

Use local keyword for variables in functions.

C++
===

Standard
++++++++

We code using C++14, without any non standard extension. We use modern style for
our C++. If you do not know about it, just ask. A few books are nice on the
topic (Effective C++ from Meyers specially).

We compile using GCC with warnings enabled.

GCC is used for production.

Code should compile warning free and without deactivating any warning of
compiler. Change the code to make it compile, period. Compiler is your best
friend, listen to it.

This coding style is a mix of Google C++ coding style, LLVM coding style
(awesome one), and Geosoft.  You may notice some differences with those
styles. If you have remarks, feel free to talk about it.  Every rule has a goal.

We use LLVM style for our source organization. Generally, if you are asking
yourself how to write something, just check what they do:
https://github.com/llvm-mirror/llvm

Language
++++++++

Exceptions
----------

We do not use exceptions or RTTI. Thus, do not use throw construct,
and do not use dynamic_cast too. You can use try/catch for dealing with 3rd
party code (like Boost) we do not control. Use error codes instead.

Exceptions comes with a memory cost (exception tables) and throwing is always
inefficient. In more, it creates unpredictable behavior for any function (what
can be thrown everywhere?). Some people say it is difficult to write leak-free
code with exceptions. In C++11, this argument is almost false.

Static objects
--------------

Do not use global static variables. Implement a singleton instead.

Source formatting
+++++++++++++++++

Commenting
----------

Comments are in plain english only. Do not add comments that mirror the code,
just add some when explaination is really needed.

When you write a class, explain what it is for, and for non trivial method, add
comment explaining it.

In the code, explain tricky parts.

Too much commenting is a problem, as Too few. Finding balance is difficult. If
in doubt, ask someone if he can understand what you do.

Comments
--------

Use C++ only comments (// for normal comments, /// for doxygen doc)

To comment out a large block of code, use #if 0 and #endif. This is far better
than commenting all the part you are not interested in.

Names
-----

Choosing proper names for methods, variables, and classes if often more useful
than good comment. Take time to think about it.

Documentation
-------------

We use doxygen as documentation tool. Respect its syntax (using \instr style and
not @style).

Naming conventions
++++++++++++++++++

Function/variable/class/namespace names
---------------------------------------

Take time to find names. Those are very important in the code.

In general, names should be in camel case (e.g. TextFileReader and isLValue()).

Different kinds of declarations have different rules:

- Type names (including classes, structs, enums, typedefs, etc) should be nouns
  and start with an upper-case letter (e.g. TextFileReader).
- Variable names should be nouns (as they represent state). The name should be
  camel case, and start with a lower case letter (e.g. leader or boats).
- Function names should be verb phrases (as they represent actions), and
  command-like function should be imperative. The name should be camel case, and
  start with a lower case letter (e.g. openFile() or isFoo()).
- Enum declarations (e.g. enum Foo {...}) are types, so they should follow the
  naming conventions for types. A common use for enums is as a discriminator for
  a union, or an indicator of a subclass. When an enum is used for something
  like this, it should have a Kind suffix (e.g. ValueKind).
- Enumerators (e.g. enum { Foo, Bar }) and public member variables should start
  with an upper-case letter, just like types. Unless the enumerators are defined
  in their own small namespace or inside a class, enumerators should have a
  prefix corresponding to the enum declaration name. For example, enum ValueKind
  { ... }; may contain enumerators like VK_Argument, VK_BasicBlock, etc.
  Enumerators that are just convenience constants are exempt from the
  requirement for a prefix.
- Namespaces use lowercase name.

Members
-------

Define members in the class with a final underscore in the name.

::

  class A
  {
  private:
    int x_;
  };

Source filenames
----------------

Source files are suffixed with .cpp, header files with .h

Define guard
------------

All headers should have a define guard to prevent multiple inclusion. Name of
symbol used is <NAMESPACE>_<MODULE>_<HEADER>_<H>. Module name is taken from
source directory name.

Header files
++++++++++++

Forward declarations
--------------------

Use Forward declarations when possible (when you only need pointer or reference
to a class). If in doubt, include header of the class.

Include order
-------------

Respect following order when including order.

1. Main module header (applies to .cpp files that implement an interface defined
   in a .h file)
2. Local/Private Headers
3. blop/...
4. System #includes (stdlib, boost, ...)

For each category, please respect alphabetical order.

Code
----

Code in header is strictly forbidden, except for templates. Even if your
function is a single line (like an accessor/mutator), put code in a cpp file.
For optimization across compilation units, we rely on LTO
(Link Time Optimization).

Functions
+++++++++

Lambdas
-------

If you use C++11 lambda, please indent it like a block of code.

Pass by
-------

Normally, you should almost never pass object by value. Use a const reference
for passing object you should not modify. Use reference when you might modify
it. And use a pointer if the object may not exist (nullptr) in this case.

Const for the win
-----------------

Const all you can: methods (very important), parameters, variables. This is your
best link to the compiler.

Inline not for the win
----------------------

Do not declare functions inline. Let the compiler decide it for you.

Coding
++++++

Use auto type deduction
-----------------------

Use auto in the code when it helps to simplify reading of the code (like
iterator of a container). Do not use it everywhere for anything (say when an int
is an int, or an object an object). Do not use it for return value type
deduction (easy to write, hard to understand).

Use auto& or auto* instead of plain auto to avoid unncessary copies.

For range based loop
--------------------

When possible, use range based loops (c++11) for iterating on a container

RAII for the Win
----------------

Use RAII where you can for handling resources. Do not use it for normal code
path (set bool to true, then reset it it false for instance) but
where a resource leak can happen (files, memory, connections, ...).

The code should not contain any delete (unique_ptr permits almost anything now).

Rule of zero
------------

When possible, do not define destructor, copy ctor and copy assignment operator
(Rule of zero). In c++11, it is possible with the new unique_ptr accepting a
pointer to function to release resource. Thus, you can handle your files,
connections, and all resources without thinking about freeing it.

If you want to prevent copy, inherit (privately) from boost non copyable.

::

  #include <boost/core/noncopyable.hpp>

  class X: private boost::noncopyable
  {
  };

Move members
------------

Only define move operations when creating a class that can be copied
extensively. In general, avoid it as it can be very tricky.

Stay away from rvalues too.

Operator overloading
--------------------

Absolutely forbidden in our code. Simplicity is better.

Depth of block code
-------------------

You should not need more than 3 levels to code in your functions. It you are
more (nested if), refactor your code. Use continue in loops to make it easy
(instead of a nested if).

nullptr
-------

Use nullptr instead of 0 or NULL.

Assert
------

Assert is your first link with the compiler before const. Use it wherever you
can. It is free (no cost at all in release) and very very useful!

To further assist with debugging, make sure to put some kind of error message in
the assertion statement, which is printed if the assertion is tripped. This
helps the poor debugger make sense of why an assertion is being made and
enforced, and hopefully what to do about it. Here is one complete example:

::

  inline value *getOperand(unsigned i)
  {
    assert(i < operands.size() && "getOperand() out of range!");
    return operands[i];
  }

Here are more examples:

::

  assert(ty->isPointerType() && "Can't allocate a non-pointer type!");

  assert((opcode == Shl || opcode == Shr) && "ShiftInst Opcode invalid!");

  assert(idx < getNumSuccessors() && "Successor # out of range!");

  assert(v1.getType() == v2.getType() && "Constant types must be identical!");

  assert(isa<PHINode>(succ->front()) && "Only works on PHId BBs!");

For unreachable code, use for example:

::

  assert(0 && "Invalid radix for integer literal");

Another issue is that values used only by assertions will produce an "unused
value" warning when assertions are disabled. For example, this code will warn:

::

  unsigned Size = v.size();
  assert(size > 42 && "Vector smaller than it should be");

::

  bool newToSet = myset.insert(Value);
  assert(newToSet && "The value shouldn't be in the set yet");

These are two interesting different cases. In the first case, the call to
v.size() is only useful for the assert, and we don’t want it executed when
assertions are disabled. Code like this should move the call into the assert
itself. In the second case, the side effects of the call must happen whether the
assert is enabled or not. In this case, the value should be cast to void to
disable the warning. To be specific, it is preferred to write the code like
this:

::

  assert(v.size() > 42 && "Vector smaller than it should be");
  bool newToSet = myset.insert(Value); (void)newToSet;
  assert(newToSet && "The value shouldn't be in the set yet");

Watch out for side effects in assert code (like modifying a container). In
general, only const methods should be called in assert.

Code in header
--------------

Avoid it. Do not declare methods inline too.

Do not use using namespace in header
------------------------------------

Never use using namespace XXX in a header. It pollutes all files including it.

Do not use using namespace std or 3rd party
-------------------------------------------

Always prefix std:: for standard classes or external libraries (like boost).
If you have long namespaces (sometimes in boost), define an alias.

You can use using namespace for namespace of our project.

Local variables
---------------

Define variable at the most local place possible.

If needed (especially for RAII objects), use a new scope level for defining your
variable:

::

  int f() {
    ...
    {
      MyRaiiObj l;
    }
    ...
  }

Namespace
---------

All the code you write should be in namespace *blop*.

Anonymous namespace
-------------------

Use them only for class internal to a cpp. For functions private to a cpp file,
use static instead.

Switch
------

Don't use default label in switch for enumeration. This allows compiler to give
error when a new member is added to it.

Enum classes
------------

Use enum class instead of basic enums.

Cast
----

Do not use C style cast but C++ only: static_cast, reinterpret_cast and
const_cast. Do not use dynamic_cast (no RTTI here).

Infinite loop
-------------

For infinite loop, use while(true).

Style
+++++

Spaces Before Parentheses
-------------------------

We prefer to put a space before an open parenthesis only in control flow
statements, but not in normal function call expressions and function-like
macros. For example, this is good:

::

  if (x) ...
  for (i = 0; i != 100; ++i) ...
  while (true) ...
  somefunc(42);
  assert(3 != 4 && "laws of math are failing me");
  a = foo(42, 92) + bar(x);

Prefer Preincrement
-------------------

Preincrement (++x) may be no slower than postincrement (x++) and could very well
be a lot faster than it. Use preincrementation whenever possible.

Namespace indentation
---------------------

Do not give one level for namespace itself.

Braces
------

Always put braces on a new line.
This is valid for namespace/class/functions/method/if/switch/for/while.

Put braces even for one line if.

About references and pointers
-----------------------------

C++ pointers and references should have their reference symbol next to the type
rather than to the name.

::

  float* x; // NOT: float *x;
  int& y;   // NOT: int &y;

The pointer-ness or reference-ness of a variable is a property of the type
rather than the name. C-programmers often use the alternative approach, while in
C++ it has become more common to follow this recommendation.

Goto
----

There is no place in C++ for Goto. In C there are some very useful cases, but
not in C++.
