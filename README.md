# parallel-compile-circleci
Can large C type compilation jobs be spread over many containers

This is a trivial example, and merely demonstrates the use of globbing and splitting to pass a subset of source code across multiple containers.

The compile machine code is then aggergated in a follow-up job that links them all into a single program.

See https://circleci.com/gh/eddiewebb/parallel-compile-circleci for example workflow result in CircleCI.

[![CircleCI](https://circleci.com/gh/eddiewebb/parallel-compile-circleci.svg?style=svg)](https://circleci.com/gh/eddiewebb/parallel-compile-circleci)


## Split by Timing

This branch uses additional logic to generate a JUNit style xml report of all compiled files and their compile time.  

```
<testsuites>
<testsuite file="src/finally.c"><testcase name="compile src/finally.c" time="0.13" /></testsuite>
<testsuite file="src/goodbye.c"><testcase name="compile src/goodbye.c" time="0.03" /></testsuite>
<testsuite file="src/more.c"><testcase name="compile src/more.c" time="0.03" /></testsuite>
</testsuites>
```
This file is then used by subsequent executions of `circleci tests split --split-by=timings` to balance the compilation more evenly across containers.

Full example can be found in config.yml, but the core to creating the file is

```
      #split all c files based on the index ID we're running on, pass subset to gcc compile (this uses previous run's data)
      - run: circleci tests glob "**/*.c" | circleci tests split --split-by=timings > file_list
      - run: |
          while read LINE;do
            echo "Compiling" $LINE
            TIME=`gcc -ftime-report -c $LINE 2>&1 | grep TOTAL | tr -s " " | cut -d" " -f6`
            echo "<testsuite file=\"$LINE\"><testcase name=\"compile $LINE\" time=\"$TIME\" /></testsuite>" >>timing_body.xml
          done<file_list
      # save timings as junit format report that the tests service will use on future splitting
      - run: mkdir gcc-timings && cat .circleci/timing_head.xml timing_body.xml .circleci/timing_foot.xml > gcc-timings/timing.xml
      # IMPORTANT: you must save the file as test results for CircleCI to read it on future runs.
      - store_test_results:
          path: gcc-timings
```