===========
Setup tools
===========

You should take some time to configure the tools you use everyday. Here is a
list of proposal for them.

Bash
====

file to modify is ~/.bashrc.

This will add git branch in prompt + color it depending on git status.

::

  #
  #  Completion for please:
  #
  #  please [command] [default_completion]
  #
  function _please() 
  {
    local cur prev opts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    opts=$($(git rev-parse --show-toplevel)/please |&
             grep '^-' |
             sed -e 's/^- //')
    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
    return 0
  }

  export PROMPT_COMMAND=__prompt_command  # Func to gen PS1 after CMDs
  function __prompt_command()
  {
    local EXIT="$?"             # This needs to be first
    history -a; # flush history after each command

    PS1=""
    local RCol='\[\e[0m\]'
    local Red='\[\e[1;91m\]'
    local BgRed='\[\e[1;101m\]'
    local Green='\[\e[1;92m\]'
    local Cyan='\[\e[1;96m\]'

    if [ $EXIT != 0 ]; then
      PS1+="${BgRed}\u${RCol}"      # Add red if exit code non 0
    else
      PS1+="\u"
    fi
    if [ -f /build_env_version ]; then
      PS1+="@\h${Cyan}(env)${RCol}:" # we are inside build env
    else
      PS1+="@\h:"
    fi

    # How many characters of the $PWD should be kept
    local pwd_length=50
    local prefix=
    [[ $(echo -n $PWD | wc -c) -gt $pwd_length ]] && prefix="..."
    PS1+="$prefix$(echo -n $PWD | tail -c $pwd_length)"

    local branch=$(git branch --no-color 2> /dev/null |
      sed -e '/^[^*]/d' -e 's/* \(.*\)/\1/')
    [[ $branch != "" ]] && branch="($branch)"
    local status=$(git status -s 2>/dev/null | wc -l)
    local color="${Red}"
    [[ status -eq 0 ]] && color="${Green}"
    PS1+="${color}$branch${RCol}> "
    
    complete -o default -F _please please
  }

  # readline settings
  # ignore case for auto completion
  bind "set completion-ignore-case on"
  # ignore diff between - and _
  bind "set completion-map-case on"
  # show directly completion results after first TAB
  bind "set show-all-if-unmodified on"
  # limit what is show for completion (hide prefix bigger than 2 char)
  bind "set completion-prefix-display-length 2"
  # do not complete hidden files
  bind "set match-hidden-files off"

Git
===

file to modify is ~/.gitconfig.

You need to change your name in the file (don't copy/paste blindly).

::

  [user]
    name = Your Name
    email = your.name@company.com
  [color]
    diff = auto
    status = auto
    branch = auto
  [core]
    pager = less -r
    preloadindex = true
  [merge]
    conflictstyle = diff3
    ff = false
  [push]
    default = simple

Vim
===

file to modify is ~/.vimrc.

If you are interested in coding with vim (auto completion and other stuff
like that), please ask to someone using it in the team. We have stuff that can
help you.

::

  " format to 80 chars, using tabs (expanded in spaces) of size 2
  set textwidth=80
  set colorcolumn=+1
  set tabstop=2
  set shiftwidth=2
  set softtabstop=2
  set expandtab
  " respect textwidth
  autocmd Filetype * set formatoptions+=t
