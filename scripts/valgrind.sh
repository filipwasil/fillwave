#!/bin/sh
valgrind --suppressions=../doc/valgrind/suppressions.supp --log-file=../doc/valgrind/report.xml $1
