#!/bin/bash
ps -au | grep './main' | grep -o '^[a-z]* *[0-9]*' | grep -o [0-9]* | head -1 | xargs kill
