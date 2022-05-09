#!/bin/bash

chmod +x .github/scripts/*.sh
rm -f .git/hooks/pre-push.sample
cp .github/scripts/pre-push .git/hooks/pre-push
ls -l .git/hooks/

echo "[WARNING] ! Do not forgot to modify '.github/workflows/main.yml' with your repository name at line 66"
