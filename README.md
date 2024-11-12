<h1 style="text-align: center;">UniLogger</h1>

## Introduction

UniLogger is an open source Logger which can be used currently in Linux platform for logging in C  or C++ Applications, This logger can be used in any C or C++ application with very ease of usage. A single Logger for Logging and Saving. Faster Logging

<details open>
<summary>Features</summary>

- **Ease of Usage**

    This Library can be integrated with any application with very minute effort

- **Ease of Cross Compiling**

    This library can be cross compiled to any Unix Similar platform with ease

- **Ease of Changing the Log Levels**
  
    LogLevels in this library can be easily altered using the Environment Variable, without editing the code to change the LogLevels

- **Ease of Changing the Log Stream**
  
    Log Streams can also be easilty altered using the Environment Variable, without editing the code to change the Log Stream (stdout , stderr)

- **Saving the Log to File**

    This Library allows to save the logs to file without any extra effort, Just by using the environment variable to save the logs to file

- **C or C++**
    
    This Library can be used in C or C++ Application with ease

- **Non-interleaved Messages**
  
    This Library can be used in Multiple parallel threads, messages will be shown without interleaving on the same line

</details>

## Build Steps

Please refer to [Build Steps](docs/BuildSteps.md) for Building UniLogger Library

## Usage of Library

Please refer to [Usage](docs/UserGuide.md) for Using UniLogger in any Application

## TODOs

- [x] Make Library compatable for Linux Environment
- [x] Build Shared and Static Libraries
- [x] Build Examples for Usage of Logger
- [ ] Make Library compatable for Windows
- [ ] Usage of Queue to store the data while dumping into file, instead of using freopen