Qt-Ogre-Widget
==============

Embed OGRE into a QtWidget in a cross compatible way. This widget has been tested on *Ubuntu 12.04 LTS* and *Mac OS X 10.9*.

## Requirements
* Qt 5.1
* OGRE 1.9

## Why does this repository exist?
When I was starting to use OGRE, I needed a cross compatible way of handling a window to host OGRE inside of. Instead of using preprocessor if-else statements with Objective-C I decided to use Qt instead. There are a ton of information about integrating Qt into OGRE but I found it extremely hard to find a guide that worked, probably because many of them are outdated. The code might not be optimized and there might be tons of better ways to do it, but this is the result of what worked for me. I created this repository in the hopes that it could help others in the future.

Note! The code will not compile in its current state. There are some places inside the code where I have written comments, such as "Create a scene". These are parts where I have removed my own code, as these lines does not make sense without extra code (that has nothing to do about the Qt integration).

## Disclaimer

## Credit
I take no credit to the code inside this repository. Thanks to:

* [QtOgre guide](http://www.ogre3d.org/tikiwiki/QtOgre)
* [Radman games](http://www.radmangames.com/programming/successfully-integrating-qt-and-ogre3d)
* [Ogre forum thread - Qt and Ogre 1.8 RC on Mac](http://www.ogre3d.org/forums/viewtopic.php?f=2&t=68324)
* [Ogre forum thread - Qt + Ogre on X](http://www.ogre3d.org/forums/viewtopic.php?f=2&t=62805)

I am not claiming that the code in the links above does not work, I might have been doing something wrong.
