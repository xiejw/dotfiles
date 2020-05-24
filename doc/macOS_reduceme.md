### Homebrew

```sh
brew update
brew upgrade
brew cask upgrade
brew cleanup -s

# Check size
du -h "$(brew --cache)"
du -h -d 1 /usr/local/Cellar

# Occationally
rm -f "$(brew --cache)"/*.tar.gz
rm -rf "$(brew --cache)"/downloads
```

### Clean Up TimeMachine Snapshots

```sh
$ tmutil listlocalsnapshots /
com.apple.TimeMachine.2020-04-26-165845
com.apple.TimeMachine.2020-04-30-103739
com.apple.TimeMachine.2020-04-30-170548
com.apple.TimeMachine.2020-05-01-084333

$ sudo tmutil deletelocalsnapshots 2020-04-26-165845
```
