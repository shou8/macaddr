#!/bin/bash

grep '(hex)' oui.txt | sed -e 's/(hex)/ /g; s/"/\\"/g' | sed -e "s/^[	 ]*\([0-9a-fA-F]\{2\}\)-\([0-9a-fA-F]\{2\}\)-\([0-9a-fA-F]\{2\}\)[	 ]*\([^	 ].*\)$/\1\2\3 \4/" > mac.db
nkf -w --overwrite mac.db
