#!/bin/bash

cat lastlog1.out lastlog2.out | sed -f p2a.sed | sort | uniq -c | sed -f p2b.sed #>p2b.out