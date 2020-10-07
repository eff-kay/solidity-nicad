import sys
import os
import subprocess as sp

from create_clone_df import clone_types

def take_diff(from_path, to_path):
    for type in clone_types:
        print('taking diff of {}'.format(type))
        cmd = 'diff {}/{} {}/{}'.format(from_path, type+'.xml', to_path, type+'.xml')

        sp.run(cmd.split(' '))   
    

if __name__ == "__main__":
    take_diff('duplicates/final', 'old_duplicates/old_final')
    