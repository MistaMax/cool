#!/bin/bash

sed -f p2aDollar.sed lastlog1.out >res1.txt
sed -f p2a.sed lastlog2.out >res2.txt
grep -f res1.txt res2.txt >p2a.out