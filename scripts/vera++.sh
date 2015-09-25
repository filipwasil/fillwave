#!/bin/sh
cd ../doc/vera++
echo "vera++ is analyzing headers"
find ../../inc -name '*.h' | xargs vera++
echo "vera++ is analyzing sources"
find ../../src -name '*.cpp' | xargs vera++
cd ../scripts
