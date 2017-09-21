#!/bin/bash

cat lastlog1.out lastlog2.out | sed '/2017$/d;/^Username/d' | sort | sed 's/\(.\{1,15\}\).*/\1/;s/[[:blank:]]//g' | uniq -c | sed -f p2b.sed >p2b.out