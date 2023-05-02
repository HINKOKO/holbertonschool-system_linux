#!/usr/bin/python3

""" Python script that search and replace an ASCII
string in the heap of a running process

Usage: read_write_heap.py [PID] search_string replace_string
Where:
- PID - is the pid of the targeted process (found with ps)
- search_string - the ASCII String we will replace
- replace_string - the new fresh string we gonna put in
"""

import sys


def print_err():
    print('Usage: {} [PID] search_string write_string'.format(sys.argv[0]))
    sys.exit(1)


# check usage
if len(sys.argv) != 4:
    print_err()

# get pid from args
pid = int(sys.argv[1])
if pid <= 0:
    print_err()
search_string = str(sys.argv[2])
if search_string == "":
    print_err()
write_string = str(sys.argv[3])
if write_string == "":
    print_err()

# let's get the maps and mem files of the concerned process
maps_file = "/proc/{}/maps".format(pid)
mem_file = "/proc/{}/mem".format(pid)

# try open and stuff
try:
    _maps = open(maps_file, 'r')
except IOError as e:
    print("[ERROR] Cant open file {}:".format(maps_file))
    print("           I/O error({}): {}".format(e.errno, e.strerror))
    sys.exit(1)

for line in _maps:
    sline = line.split(' ')
    # check if heap is there
    if sline[-1][:-1] != "[heap]":
        continue
    # parse the line
    addr = sline[0]
    perm = sline[1]
    offset = sline[2]
    dev = sline[3]
    inode = sline[4]
    pathname = sline[-1][:-1]

    # check permissions
    if perm[0] != 'r' or perm[1] != 'w':
        _maps.close()
        exit(0)

    # get start/end of the heap in virtual memory
    addr = addr.split("-")
    if len(addr) != 2:
        # Never trust anyone, even your OS haha
        _maps.close()
        exit(1)
    addr_start = int(addr[0], 16)
    addr_end = int(addr[1], 16)

    # open and read mem file
    try:
        _mem = open(mem_file, 'rb+')
    except IOError as e:
        print("[ERROR] Cant open file {}:".format(maps_file))
        print("           I/O error({}): {}".format(e.errno, e.strerror))
        _maps.close()
        exit(1)

    # scan heap
    _mem.seek(addr_start)
    heap = _mem.read(addr_end - addr_start)

    # find the string
    try:
        i = heap.index(bytes(search_string, "ASCII"))
    except Exception:
        print("Can't find '{}'".format(search_string))
        _maps.close()
        _mem.close()
        exit(0)

    # write new truth about banana
    _mem.seek(addr_start + i)
    _mem.write(bytes(write_string + "\0", "ASCII"))

    # close files and your house
    _maps.close()
    _mem.close()

    break
