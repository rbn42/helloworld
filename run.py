#!/usr/bin/env python
import sys

sys.path.insert(0, './bobscheme')
from bob.cmd import compile_file
from bob.cmd import run_compiled

if __name__ == '__main__':
    import os.path
    output = 'build/1'
    root = os.path.split(output)[0]
    if not os.path.exists(root):
        os.mkdir(root)

    compile_file(filename=sys.argv[1], out_filename=output)
    run_compiled(output)
