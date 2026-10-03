"""Maps the functions of a module: data they reference, modules that call them and functions of the module they call

Prints one line per function of the module: address, size, name, then
  D: the data of the module that the function references (last 3 hex digits of the addresses)
  X: the other modules that call the function
  C: the functions of the module that the function calls (last 3 hex digits)
It helps to split a module into translation units: a TU's functions share its data and call each other.

Usage: python tools/map_functions.py ov026
       python tools/map_functions.py ov026 0x021dc040 0x021de6a0
"""
import collections
import glob
import os
import re
import sys

module = sys.argv[1]
low = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0
high = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0xffffffff
number = int(module[2:]) if module.startswith('ov') else None
base = 'config/eur/arm9/overlays/%s/' % module if number is not None else 'config/eur/arm9/'
delinks = open(base + 'delinks.txt').read()
data_start = int(re.search(r'\.rodata\s+start:(\S+)', delinks)[1], 16)
data_end = int(re.search(r'\.bss\s+start:\S+ end:(\S+)', delinks)[1], 16)

functions = []
for line in open(base + 'symbols.txt'):
    m = re.match(r'(\S+) kind:function\(arm,size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)', line)
    if m:
        functions.append((int(m[3], 16), int(m[2], 16), m[1]))
functions.sort()


def function_of(address):
    for start, size, name in functions:
        if start <= address < start + size:
            return (start, name)
    return None


refs = collections.defaultdict(set)
callers = collections.defaultdict(set)
calls = collections.defaultdict(set)
for path in glob.glob('config/eur/arm9/overlays/*/relocs.txt') + ['config/eur/arm9/relocs.txt']:
    source = os.path.basename(os.path.dirname(path))
    if source == 'arm9':
        source = 'main'
    for line in open(path):
        m = re.match(r'from:0x([0-9a-f]+) kind:(\S+) to:0x([0-9a-f]+)(?: add:(\S+))? module:(\S+)', line)
        if not m:
            continue
        origin = int(m[1], 16)
        target = int(m[3], 16)
        if number is None:
            mine = m[5] == 'main'
        else:
            mine = 'overlay(%d)' % number in m[5] or re.search(r'overlays\((\d+,)*%d[,)]' % number, m[5])
        if source == module or (number is None and source == 'main'):
            function = function_of(origin)
            if function and data_start <= target < data_end:
                refs[function].add(target)
            if function and mine:
                called = function_of(target)
                if called and called != function:
                    calls[function].add(called[0])
        elif mine:
            called = function_of(target)
            if called:
                callers[called].add(source)

for start, size, name in functions:
    if not low <= start < high:
        continue
    key = (start, name)
    print(hex(start)[4:], hex(size), name[:34],
          'D:' + ' '.join(hex(x)[5:] for x in sorted(refs[key])),
          '| X:' + ','.join(sorted(callers[key])),
          '| C:' + ' '.join(hex(x)[5:] for x in sorted(calls[key])))
