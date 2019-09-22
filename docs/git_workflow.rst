Git Workflow
============

We use git, not only because it is the coolest, but because it is the most
efficient tool to handle your sources.

If you don't know about git, take some time to read about it, or ask us.

Branches
--------

We use local branches heavily, especially for short time work (< 1 day).

Don't forget local branches are not backed up and if you delete your workspace,
you can lose it.

For long time work, we use feature branches (with meaningful name).

*master* is our stable branch. Only bulletproof code goes there. NEVER commit
directly on master. NEVER. Anyone external to the team who wants to access our
code should be able to access master with production quality.

*dev* is our unstable branch (and where you should work).

Other repositories
------------------

We put all our code in the same repo. This is much more easy to deal with than
multiplying them.

To track other repo, we use git subtree. git submodule is strictly forbidden.
The first (and newer) has a a lot of advantages (no need for recursive clone, no
problem when updating code, ...).

All code we build and use, but we don't modify (like boost) is not checked in,
but kept as source tarball on our jenkins server.

Dev cycle
---------

1) Create a local branch for your new cool feature
2) code/commit(s)
3) test
4) debug
5) go to 2) until feature is ready
6) clean your commits using git rebase -i (and keep a minimum number of commits
   using squash). Take time to write a correct git commit message.
7) once your code is ready to be published, ask a code review using ./please
   post-code-review.
8) once your code is accepted, you can merge it (or rebase it) on dev branch.

For long time feature, you should try to keep things clean (by rebasing). Once
the feature is ready, you can merge it back to dev and delete the branch.

Git history should be clean. Use rebase for it and think about your commit
messages (before pushing).

Commit message
--------------

We don't want to enforce rule, but try to respect following format when
committing (when this commit will be public):

::

  I explain my feature on one line (less than 72 chars)

  After a blank line, I can explain more deeply what I did. No need to quote
  filenames, you have git is about that.

And a concrete example:

::

  Added option to select config file

  Option is named --config-file, (or -c in short), followed by path of the file.
  This can be used in all our binaries.

Code review
-----------

We use ReviewBoard for code review. You can access it using ./please
access-reviewboard-site.

You are expected to perform a code review for all important changes you are
doing. If you are new in the team, all your changes must be code reviewed.
Period.

Continuous Integration
----------------------

We use Jenkins as CI server. You can access it using ./please
access-jenkins-site.

If you broke build or tests, your priority is to FIX it, above everything else.
If you can't fix your mistake, just revert your commit to leave other people
workspace in a decent state.

This is all about responsability and you should take yours. Wild commits before
leaving for holidays should not be done.
