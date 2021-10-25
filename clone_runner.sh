#!/bin/bash

make
mkdir systems
cp -r data/smart_contracts systems/source-code
python python_scripts/create_clone_df.py