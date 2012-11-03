#!/bin/bash

grep '(base 16)' oui.txt | gsed -e 's/     (base 16)\t\t/ /g' | gsed -e 's/"/\\"/g' > mac.db
