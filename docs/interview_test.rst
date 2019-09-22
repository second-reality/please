Interview test
==============

:Today:
:Name:
:Start time:
:End time:

Do not lose time to make long sentences, just answer what we expect shortly
(some keywords simply).

Pseudo code is okay. Includes do not matter. Syntax is checked by a compiler,
not a human. We are not pedantic about that.

Skip questions where you have no idea at all (not bad).

We will discuss of all this with you after. If it is not clear, we'll ask.

You should be able to complete the test in 1 hour and half. If you finish
before, come to see us.

Questions are about 4 topics: C/C++/System and Personal taste.

C
-

What are the different years of standards of the language? Which version is
current?

..
  C90, C99, C11. C11 is current.

|
|
|
|
|
|
|

Write a recursive function that computes sum of int from 1 to n (parameter).

..
  int f(unsigned int n) {
    return n == 0? 0: f(n-1)+n;
  }

|
|
|
|
|
|
|

What is difference between ++i and i++? Which one do you use when both are
available for your case and why?

..
  i++: increment i and return old value
  ++i: increment i and return new value
  ++i should be preferred. It can not be slower than first, but can be faster
  (especially for loops iteration).

|
|
|
|
|
|
|

What is a macro? What is the preprocessor?

..
  Macro is a symbol that expands during preprocessing in text.
  It can be a function.
  Preprocessor is called in C/C++ before compilation and treats a lot of
  directives (#include, ...) and macros expansion.

|
|
|
|
|
|
|

What does mean const keyword? And volatile keyword?

..
  const is a variable qualifier saying that it can not be modified.
  Basic answer: volatile is a variable qualifier saying that it can be modified
                out of context (like a hardware memory mapping).
  Guru answer: It prevents compiler from optimizing read/write for this variable
               (do not keep it in a register).
  Guru++ answer: This qualifier is often misused in concurrent programming to
                 hide memory barrier problems.

|
|
|
|
|
|
|

What is an extern function or variable? And a static one?

..
  extern symbol can be seen outside of compilation unit.
  static symbol is only accessible from current compilation unit.

|
|
|
|
|
|

What each line define?

::

  const int a                             = 0;
  int const b                             = 0;
  int *c                                  = 0;
  const int* d                            = 0;
  const int* const e                      = 0;
  const int const* f                      = 0;
  int (*g)(int, int)                      = 0;
  int const* (*h)(const int*, int* const) = 0;

..
  simple rule: const always applies to element at its left
  a constant int
  b constant int
  c pointer to int
  d pointer to const int
  e constant pointer to constant int
  f pointer to constant int
  g pointer to function that return int and takes double int as param
  h pointer to function that return pointer to const int and takes
    pointer to const int and const pointer to in as param

|
|
|
|
|
|
|
|

What does this code do in C99?

::

  #include <stdio.h>

  int main()
  {
    char *str = "lol";
    for (char *it = str; *it; ++it)
      *it = *it == 'o' ? 'u': 'a';
    puts(str);
  }

..
  Basic answer: prints "aua";
  Guru answer: might segfault on some architecture because strings are
               kept in read-only memory despite being of type char* for
               compatibility sake.

|
|
|
|
|
|
|

What do this code do? Explain why

::

  #include <stdio.h>

  int main()
  {
    int* ptr = malloc(4*sizeof(int));
    ptr[1] = 42;
    int* tmp = (long long)ptr ^ (long long)ptr;
    while(tmp) {
      ++*tmp;
    }
    printf("%d", ptr[1]);
  }

..
  Basic FALSE answer: prints 43, segfault or infinite loop.
                      Means "I didn't understand anything" about this code.
  Basic answer: print 42 but I don't know why.
  Advanced answer: print 42 because tmp is always 0 (xoring a variable with
                   itself just results in 0, thus while loop is not entered)

|
|
|
|
|
|
|

Write two versions of a function that creates a new process (POSIX code) and
executes /bin/ls in C.

..
  void f()
  {
    system("/bin/ls");
  }
  void f()
  {
    pid_t ret = fork();
    if (ret == 0) // child process
      execl("/bin/ls", NULL);
    elsif (ret == -1)
      ; //error
    else // parent process
      waitpid(ret); // wait child process
  }
  Guru++ answer: I use syscall clone directly but it is not POSIX.

|
|
|
|
|
|
|

C++
---

What are the different years of standards of the language? Which version is
current?

..
  C++98, C++03, C++11, C++14, C++17. Current is C++14.

|
|
|
|
|
|
|

What is STL? Boost? (do not explain all stuff, be short)

..
  Standard Template Library: standard classes (containers, ...) for C++
  Boost: Library presenting new concepts that will be possibly be included in
         next standard of C++.
  Guru++ answer: I list all libraries of Boost.

|
|
|
|
|
|
|

Given following code, how do you print each element of vector vec? If possible,
answer for C++03 and, more modern, C++11.

::

  #include <vector>
  #include <iostream>

  int main()
  {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // ... code here









  }

..
  C++03
  for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    std::cout << *it << '\n';
  C++11
  for (auto it = vec.begin(); it != vec.end(); ++it)
    std::cout << *it << '\n';
  C++11 Guru
  for (const auto& e: vec)
    std::cout << e<< '\n';


What are the three ways of passing an object to a function? Give (short) example
of each and say when do you use it?

..
  pass by value: void f(A a)
    a should be modified in function (we need a copy)
  pass by pointer: void f(A* a)
    we want to pass an object than should be modified and nullptr is possible.
  pass by reference: void f(A& a)
    all other cases. Const reference if a should not be modified.
  Guru C++11: pass by rvalue reference: void f(A &&a)
    we want to pass to function a temporary object.

|
|
|
|
|
|
|

What are the 4 types of cast you can perform in c++? When do you use each?

..
  dynamic_cast: only cast in an object of the same class hierarchy.
  reinterpret_cast: c style cast, no rule (raw memory)
  const_cast: remove const qualifier for object
  static_cast: cast used for integer/float conversion + pointers conversion

|
|
|
|
|
|
|

What is a forward declaration in C++? Why do you use it for?

..
  we simply declare a class without getting its implementation: class A;
  a forward declaration can only be used to get a pointer or reference to A.
  Advanced answer: use it to resolve cyclic dependency (A needs B and B needs A)
  Guru answer: speeds up compilation time (vs including header of class).

|
|
|
|
|
|
|

What is RAII? And the Rule of Three?

..
  Resource Acquisition is Initialisation: get a resource in constructor and
  release it in destructor.
  Rule of Three: If you declare destructor, copy constructor or assignment
  operator, you should write all the three (to avoid problem).
  Guru C++11: Rule of five: move constructor and move assignment should be
  declared as well.
  Guru++ C++11: Rule of zero: stop doing thing manually and use unique_ptr to
  hold all your resources. No need of destructor or other stuff.

|
|
|
|
|
|
|

What is output of following program?

::

  #include <iostream>

  class A
  {
    public:
    A(int data): data_(new int(5))
    {
      std::cout << "ctor\n";
    }
    ~A()
    {
      std::cout << "dtor\n";
      delete data_;
    }
    int data()
    {
      return *data_;
    }
    int* data_;
  };

  void f(A a)
  {
    std::cout << "f " << a.data() << "\n";
  }

  int main()
  {
    A a(1);
    f(a);
  }

..
  False answer:
  ctor
  5
  dtor
  False answer (but better):
  ctor
  5
  dtor
  dtor
  Correct answer (and he gets the C++ right!):
  ctor
  5
  dtor
  dtor
  segfault (double delete of data)

|
|
|
|
|
|
|
|

What is a smart pointer? Name the different types.
Correct previous question program by using one (just explain, do not write code)
.

..
  smart pointer is a class to handle resource. RAII concept.
  Different pointers are: unique, shared and weak (shared without ownership).
  in previous code, remove delete and replace int* by std::unique_ptr<int>. In
  more, declare copy ctor and assignment operator for class A. Or just pass a
  reference to A in function.

|
|
|
|
|
|
|

What is inheritance? Give an example

..
  A class can inherit another to reuse its code and members.
  class A
  {
    ..
  };
  class B: public A
  {
    ..
  };

|
|
|
|
|
|
|

What is the diamond problem in inheritance? How can you solve it? You can answer
with a drawing...

..
  Happens with multiple inheritance (what an idea!).
   A
  / \
  B C
  \ /
   D
  D has two times A as a Base.
  Use virtual inheritance in this case.
  Guru Answer: DO NOT DO THIS IN YOUR CODE.

|
|
|
|
|
|
|

What are the 3 class access modifiers for each member/method of a class? What
means each of it?

..
  private, public, protected.
  private: only class can access members/methods
  protected: class and child classes can access it
  public: everybody can access it

|
|
|
|
|
|
|

What is a static method?

..
  a method of the class than can be called without object.

|
|
|
|
|
|
|

What is a const method?

..
  a method that does not modify state of object.

|
|
|
|
|
|
|

What does mutable keyword means?

..
  keywork for class members to indicate if can be modified in a const method.
  Guru Answer: Should not happen.

|
|
|
|
|
|
|

Write an example of interface class in C++? And an example of class implementing
it. Your example should be usable in production (don't forget some member
functions...).

..
  class A
  {
    virtual void f() = 0; // pure virtual function
    virtual void ~A() {}; // dtor MUST be virtual
  };
  class B: public A
  {
    virtual void f() override {...}
  };

|
|
|
|
|
|
|
|

What is polymorphism? What are the three types of it?

..
  polymorphism is ability to execute different code for same function name.
  Can be of 3 types:
  - runtime polymorphism: virtual func
  - ad hoc polymorphism: same function implemented with different parameters
                         types (max for example)
  - compile time polymorphism: templates

|
|
|
|
|
|
|

What is a virtual function? And a pure virtual function?

..
  a function that can be redefined in child class.
  A pure virtual one prevents class from being instantiated.
  Guru C++: A pure virtual one can have a body (to get default behavior for
  instance).

|
|
|
|
|
|
|

How a compiler implements virtual function? What is the cost?

..
  VERY GURU ANSWER.
  using a vtable (table of pointers)
  Cost is that each object having a virtual function gets a pointer to this
  vtable and call of function is not direct (not decided at compile time).
  Compiler can optimize this and just resolve type at compile time for some
  calls.

|
|
|
|
|
|
|

What is a template class? A template function? Give an example of class (just
the syntax).

..
  A class or function parametered by a type.
  template <typename T>
  class A
  {
    T t;
  };

|
|
|
|
|
|
|

What is template meta programming?

..
  Write template code parametered by other templates. Make your compiler
  computes stuff for you.
  Guru answer: You can compute Fibonacci at compile time with this.
  Guru++ answer: Did you know some guys wrote a compile time raytracer with TMP?

|
|
|
|
|
|
|

What means auto in C++03 and C++11?

..
  c++03: put variable where you want (register, memory). Obsolete.
  c++11: infer type of variable.

|
|
|
|
|
|
|

What is an rvalue reference in C++11? What are new members functions related to
it that are available in a class?

..
  VERY GURU ANSWER.
  reference to a temporary object.
  New function members are move ctor and move assign operator. They are not
  compiler generated to difference of copy ctor and assign operator.

|
|
|
|
|
|
|

What is a lambda function in c++11?

..
  A function nested in another, than can capture some variables of the scope
  with different semantics (value, ref, ...).
  Guru Answer: Give an example.

|
|
|
|
|
|
|

System
------

Write "Hello world" in any script language you like.

..
  #!/bin/bash
  echo "Hello world!"

|
|
|
|
|
|
|

What are a process and a thread? What is the difference?

..
  A process is a program running.
  A thread is the same, but several can run in one process. They share the same
  memory space (not the case for processes).

|
|
|
|
|
|
|

Which functions can you use under POSIX for creating a new process and thread in
C? (no example needed)

..
  fork
  spawn
  pthread_create
  GURU: clone, put it is Linux only

|
|
|
|
|
|
|

What is a mutex?

..
  a lock to order threads execution

|
|
|
|
|
|
|

What is a syscall? What is cost associated with it? If you know, describe what
happens on a processor performing one.

..
  a function call in the kernel. Cost thousands of CPU cycles, mainly due to
  cache update (L1, L2, TLB...).
  If you write system intensive code, syscall reduction is a possible
  optimization.
  On x86:
  - interrupt dedicated (param passed by register)
  - runs kernel code to treat it
  - interrupt return

|
|
|
|
|
|
|

What is difference between kernel and user space?

..
  Memory of kernel and of program.
  User can't access kernel memory (protected).

|
|
|
|
|
|
|

What is virtual memory? What is the TLB?

..
  Virtual memory is translation from a virtual adress to physical memory. Can be
  used to get more virtual memory than physical one and allows memory protection
  between processes.
  TLB (Translation lookaside buffer) is a cache (a few entries) that gives
  mapping of a virtual page to a physical one. VERY VERY VERY Useful.

|
|
|
|
|
|
|

What tools do you know for analyzing performance of a program? How do they work
(technically, not options of program)?

..
  valgrind (virtual machine)
  oprofile (use kernel perf_events under Linux)
  gprof (modify binary generated to record functions called)
  ...

|
|
|
|
|
|
|

Personal questions for the fun and profit (no wrong answer here!)
-----------------------------------------------------------------

A more personal question (no wrong answer): Do you like C++? Why?

..
  Abstraction
  Efficiency
  Pay for what you use
  Different programming style (object, imperative, functional)

|
|
|
|
|
|
|

Which C++ books have you read?

..
  Bjarne book (The C++ bible)
  Meyers books (Effective C++)
  ...

|
|
|
|
|
|
|
|

What development environment and tools do you use for coding?

..
  Are you more a command line guy or IDE guy?

|
|
|
|
|
|
|

