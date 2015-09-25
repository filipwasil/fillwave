#!/bin/sh
rm ../doc/apitrace/testGame.trace
/usr/local/bin/apitrace trace --output=../doc/apitrace/testGame.trace $1
