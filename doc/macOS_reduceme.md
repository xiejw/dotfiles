## Clean Up TimeMachine Snapshots

```
$ tmutil listlocalsnapshots /
com.apple.TimeMachine.2020-04-26-165845
com.apple.TimeMachine.2020-04-30-103739
com.apple.TimeMachine.2020-04-30-170548
com.apple.TimeMachine.2020-05-01-084333

$ sudo tmutil deletelocalsnapshots 2020-04-26-165845
```
