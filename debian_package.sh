#!/bin/bash

# Create Debian package
tar -cvzf cli-1.0.0.tar.gz cli-1.0.0
cd cli-1.0.0 && debmake && debuild