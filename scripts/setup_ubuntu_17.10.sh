#!/usr/bin/env bash
sudo apt-get install libglew2.0 libglew-dev libglm-dev libassimp3v5 libassimp-dev libfreetype6 libfreetype6-dev
sudo apt-get install doxygen valgrind vera++ cccc
#libspdlog-dev package is broken in 17.10
#/usr/include/spdlog/fmt/bundled/format.h: In member function ‘void fmt::internal::ArgFormatterBase<Impl,
# Char>::visit_char(int)’:
#/usr/include/spdlog/fmt/bundled/format.h:2236:24: error: expected unqualified-id before numeric constant
#https://github.com/blizzard4591/openMittsu/issues/19 here explained