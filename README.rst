Please
======

Getting started
---------------

All you need is bash, git and docker.

Following commands should bring you with a complete built sandbox on any Linux
machine, either here at work, or at home.

::

  # start by installing necessary dependencies on your machine
  sudo apt-get install bash git
  # docker must be installed as well (see docker website)
  # https://docs.docker.com/install/linux/docker-ce/debian/
  git clone https://github.com/second-reality/please
  cd please
  # build (docker env will be built automatically)
  ./please build

In more, you should take some time to tune your .gitconfig, or edit your
favorite editor configuration.

Introducing please
------------------

please is a script we wrote to help with any task we should be able to do as
developer. This goes from building, to access our code review or jenkins server,
running tests...

It will automatically build and maintain a docker image to execute its commands.
It calls itself recursively inside this environment.

Discover all features using './please help', and if you have new ideas, do not
hesitate to discuss for adding it. All productive ideas are welcome.

Documentation
-------------

We want to document as much as we can things we use. For this, the docs folder
should be your reference. Forget about wikis and google docs, all you need is a
text editor.

All documentation is written using only reStructured Text.

Take time to learn it:
http://docutils.sourceforge.net/docs/user/rst/quickref.html

You can write slides too (one section per page) and convert to S5 (HTML
slides) using ./please exec rst2s5.

You can either read rst format directly, or use './please rst2man file' to print
it using man. How simple is that?

Folders
-------

Our repo is organized like that:

- 3rdparty/: 3rd party dependencies we are using (binaries only, libraries are
  built from scratch and added in build env)
- docs/: documentation
- include/: public headers for each library
- lib/: where all our code goes (we split all in libraries)
- src/: main functions for binaries we produce (directly calling a library)
- test/: integration tests
- unittests/: unit tests for each library
- tools/: stuff we use to get a productive environment

In more, build/ folder is generated when you update-build-env and all stuff
built is found there.

If you are looking for an example of creating a new library/binary, check the
HelloWorld module (in src, include, lib, test and unittests folders).

Stuff to read
-------------

Before going coding, you should take some time to read our documentation about:

- Setup tools (how to setup the tools we use)
- Git workflow
- Coding standards

Finally, take some time to setup your editor or IDE (to fit coding standards)
because it is one of the program you use the most.
