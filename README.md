This repository contains a cross platform suite of client API for the MarkLogic Server REST API.

## Introduction

The MLCPlusPlus project maintains the MarkLogic C++ mlclient API. This API provides a C++ native connection
to MarkLogic Server version 6 and above.

A C wrapper API around the core C++ API is also provided. This enables legacy C applications to be configured to
talk to MarkLogic Server. All C++ usage is abstracted behind this wrapper API.

Cross platform C# and Python wrappers are also now available! These reflect those language's own programming idioms,
but use the core C++ API for speed of execution. This is transparent to the developer.

## Latest release

The latest release is 8.0.2 - See [The release notes](https://github.com/marklogic/mlcplusplus/blob/develop/documentation/release-notes/release-notes-8.0.2.md) for details.

Note the Major and Minor version numbers of this project track MarkLogic Server, the revision number tracks this API's changes, rather than the revision number of MarkLogic Server.

## Documentation

Various documentation is available:-
 - Client documentation home page for all languages - http://marklogic.github.io/mlcplusplus/api/index.html
 - GitHub future Release features - https://github.com/marklogic/mlcplusplus/milestones
 - GitHub Issues tracker - https://github.com/marklogic/mlcplusplus/issues

## Getting involved

Please see [CONTRIBUTING.md](https://github.com/marklogic/mlcplusplus/blob/develop/CONTRIBUTING.md) if you are interested in helping out.
