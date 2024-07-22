#!/bin/bash
mv $1 swapfile
mv $2 $1
mv swapfile $2

