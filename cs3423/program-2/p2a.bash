#!/bin/bash

cat lastlog1.out lastlog2.out | sed '/2017$/d;/^Username/d' | sort | sed -f p2aDollar.sed | sed -f p2a.sed | sed 's/\$$//' >p2a.out

#grep -Fwh "**Never logged in**" *.out | sort | sed -f p2aDollar.sed | sed -f p2a.sed >result.txt