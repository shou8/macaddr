#!/bin/bash

grep '(base 16)' oui.txt | sed -e 's/     (base 16)\t\t/ /g' | sed -e 's/"/\\"/g' > mac.db
