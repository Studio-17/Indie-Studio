#!/bin/bash

chmod +x .github/scripts/*.sh
ln -sf .github/scripts/pre-push .git/hooks/pre-push

echo "[WARNING] ! Do not forgot to modify '.github/workflows/main.yml' with your repository name at line 66"
