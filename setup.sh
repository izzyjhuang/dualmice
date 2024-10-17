#!/usr/bin/env bash

# compile and move to executable folder
make dualmice
mkdir -p $HOME/bin && cp dualmice $HOME/bin/

# create launcher agent
mkdir -p $HOME/Library/LaunchAgents && cat local.dualmice.plist | sed 's@$HOME@'"$HOME"'@' | sed 's@$ARG@'"$1"'@'> $HOME/Library/LaunchAgents/local.dualmice.plist

echo ""
echo "    Go to System Preferences -> Security & Privacy -> Privacy:"
echo "    Add $HOME/bin/dualmice"
echo ""
echo "    Log out & Log in. Enjoy!"
echo ""