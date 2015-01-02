romclasses-c
=============

**** HACK *** HACK *** HACK *** HACK ****


This is a small wrapper around the IBM WEME (WebSphere Everyplace Micro Environment) libraries to dump IBM J9 Java VM's rom.classes files. You'll have to obtain the development kit containing the libraries yourself. The WEME_DIR user property should point to WEME.

Check out my romclasses-py repo for a different approach to parsing rom.classes.

NOTE: If your rom.classes file is large, this will take a long time to run and the ouput will be **huge**. 


```
>romclasses-c.exe rom.classes
ROM Size: 22B0
Class Name: java/io/File
Superclass Name: java/lang/Object
Access Flags (21): public 
CRC-32: 0
Instance Shape: E
Instance Size: 8
Interfaces (2):
  java/io/Serializable
  java/lang/Comparable

[... lots of output ...]

  Name: <init>
  Signature: (Ljava/lang/String;)V
  Access Flags (1): public 
  Max Stack: 3
  Argument Count: 2
  Temp Count: 0

    0 JBaload0 
    1 JBinvokespecial 119 java/lang/Object.<init>()V
    4 JBaload0 
    5 JBdup 
    6 JBaload1 
    7 JBinvokespecial 122 java/io/File.fixSlashes(Ljava/lang/String;)Ljava/lang/String;
   10 JBputfield 160 java/io/File.path Ljava/lang/String;
   13 JBreturn0 
   14 JBnop 
   15 JBnop 


[... lots of output ...]
```

