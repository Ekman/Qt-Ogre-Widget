Qt-Ogre-Widget
==============

Embed OGRE into a QtWidget in a cross compatible way. This widget has been tested on *Ubuntu 12.04 LTS* and *Mac OS X 10.9*.

## System requirements
* Qt 5.1
* OGRE 1.9

# Why?
When I was starting to use OGRE, I needed a cross compatible way of handling a window to host OGRE inside of.
Instead of using preprocessor if-else statements with Objective-C I decided to use Qt instead. There are a ton
of information about integrating Qt into OGRE but I found it extremely hard to find a guide that worked, probably
because many of them are outdated. This is the result of what worked for me.

There are some places inside the code where I have written comments, such as "Create a scene". These are parts
where I have removed my own code, as these lines does not make sense without extra code (that has nothing to do about the Qt integration).


