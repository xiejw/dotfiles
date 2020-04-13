Brew
====

Install in Custom Folder
------------------------

    cd ~/Workspace
    mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
    export PATH=~/Workspace/homebrew/bin:$PATH

For this case, Qt related envs must be adjusted. For `gnuplot`, it can be set as

    export QT_QPA_PLATFORM_PLUGIN_PATH=/Users/xiejw/Workspace/homebrew/opt/qt/plugins/

Common Packages to Install
--------------------------

    brew install cmake
    brew install tmux
    brew install graphviz
    brew install bash-completion

Command CLI
-----------

    brew update
    brew upgrade
    brew cask upgrade
    brew doctor
    brew cleanup -s [-n]
    brew list
    brew cask list

    brew info package_name

## Clean Up


### Print Package Size

```
for pkg in `brew list -f1 | egrep -v '\.|\.\.'`
  do echo $pkg `brew info $pkg | egrep '[0-9]* files, ' | sed 's/^.*[0-9]* files, \(.*\)).*$/\1/' | awk '{print "\033[1;32m"$1;}/[0-9]$/{s+=$1};/[mM][bB]$/{s+=$1*(1024*1024);next};/[kK][bB]$/{s+=$1*1024;next} END { suffix="  KBMBGBTB"; for(i=1; s>1024 && i < length(suffix); i+=2) s/=1024; printf "\033[0m\t(all versions: \033[33m%0.1f %s\033[0m)",s,substr(suffix, i, 2), $3; }'`
done
```

### Cache Folder

Run `brew --cache` to get the folder path. Note that `brew cleanup` does not
clean it. So manually cleanup is needed.
