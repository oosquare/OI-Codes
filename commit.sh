#!/bin/bash
# commit.sh
read -p "Commit message : " msg
git add .
git commit -m "$msg ( at `date` )"
git push