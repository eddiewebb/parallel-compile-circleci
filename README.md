# parallel-compile-circleci
Can large C type compilation jobs be spread over many containers

This is a trivial example, and merely demonstrates the use of globbing and splitting to pass a subset of source code across multiple containers.

The compile machine code is then aggergated in a follow-up job that links them all into a single program.

See https://circleci.com/gh/eddiewebb/parallel-compile-circleci for example workflow result in CircleCI.

[![CircleCI](https://circleci.com/gh/eddiewebb/parallel-compile-circleci.svg?style=svg)](https://circleci.com/gh/eddiewebb/parallel-compile-circleci)