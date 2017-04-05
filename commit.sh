#!/bin/bash
git add *
git ls-files --deleted -z | xargs -0 git rm --ignore-unmatch
git commit
git push
