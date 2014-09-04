#!/bin/bash
doxygen config.txt > /dev/null
cd latex
make > /dev/null
mv refman.pdf ../../doxygen_report.pdf

