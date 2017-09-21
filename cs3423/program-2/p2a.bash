#!/bin/bash

for ln in $(grep -f "**Never logged in**" lastlog1.out);do
    sed p2a.sed
done