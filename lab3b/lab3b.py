#!/usr/bin/env python3
#NAME:  Matthew Chan
#EMAIL: matthew_2185@yahoo.com
#ID:    805291212

import sys
import csv

#Superblock & Variables
sb=None
group_descriptor=None
faulty = False

#arrays
bfree_list=[]
ifree_list=[]
inode_list=[]
dirent_list=[]
indirect_list=[]
used_inodes=[]

#set
#Inode number, offset, level of indirection
block_dict={}

#Constants
MAX_BLOCKS =0
FIRST_UNRESERVED_BLOCK =0

class SUPERBLOCK:
    def __init__(self, line):
        self.s_blocks_count = int(line[1])
        self.s_inodes_count = int(line[2])
        self.s_block_size = int(line[3])
        self.s_inode_size = int(line[4])
        self.s_blocks_per_group = int(line[5])
        self.s_inodes_per_group = int(line[6])
        self.s_first_ino = int(line[7])

class GROUP:
    def __init__(self, line):
        self.group_number = int(line[1])
        self.total_blocks = int(line[2])
        self.total_inodes = int(line[3])
        self.free_blocks_count = int(line[4])
        self.free_inodes_count = int(line[5])
        self.block_bitmap = int(line[6])
        self.inode_bitmap = int(line[7])
        self.first_block = int(line[8])

class INODE:
    def __init__(self, line):
        self.inode_number = int(line[1])
        self.file_type = line[2]
        self.i_mode = int(line[3])
        self.i_uid = int(line[4])
        self.i_gid = int(line[5])
        self.i_links_count = int(line[6])
        self.ctime = line[7]
        self.mtime = line[8]
        self.atime = line[9]
        self.file_size = int(line[10])
        self.blocks = int(line[11])
        self.dirent_blocks = [int(block) for block in line[12:24]]
        self.indirect_blocks = [int(block) for block in line[24:27]]

class DIRENT:
    def __init__(self, line):
        self.parent_inode = int(line[1])
        self.offset = int(line[2])
        self.inode = int(line[3])
        self.rec_len = int(line[4])
        self.name_len = int(line[5])
        self.name = line[6]

class INDIRECT:
    def __init__(self, line):
        self.inode = int(line[1])
        self.level = int(line[2])
        self.offset = int(line[3])
        self.indirect_block = int(line[4])
        self.ref_block = int(line[5])

def Block_Audit():
    #THIS SHIT RIGHT HERE
    global block_dict
    #THIS SHIT RIGHT HERE
    for inode in inode_list:
        if inode.file_type == 's' and inode.file_size <= 60:
            continue;
        offset = 0
        level = 0
        for datablock in inode.dirent_blocks:
            if datablock != 0:
                if datablock < 0 or datablock > MAX_BLOCKS - 1:
                    print("INVALID BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                    faulty = True
                if datablock < FIRST_UNRESERVED_BLOCK and datablock > 0:
                    print("RESERVED BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                    faulty = True
                if datablock in bfree_list:
                    print("ALLOCATED BLOCK %d ON FREELIST" %(datablock))
                    faulty = True
                if datablock in block_dict:
                    block_dict[datablock].append([inode.inode_number, offset, level])
                    faulty = True
                else:
                    block_dict[datablock] = [[inode.inode_number, offset, level]]
            offset += 1

        #single indirect
        offset = 12
        level = 1
        datablock = inode.indirect_blocks[0]
        if datablock != 0:
            if datablock < 0 or inode.indirect_blocks[0] > MAX_BLOCKS - 1:
                print("INVALID INDIRECT BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                faulty = True
            if datablock < FIRST_UNRESERVED_BLOCK and datablock > 0:
                print("RESERVED INDIRECT BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                faulty = True
            if datablock in bfree_list:
                print("ALLOCATED INDIRECT BLOCK %d ON FREELIST" %(datablock))
                faulty = True
            if datablock in block_dict:
                block_dict[datablock].append([inode.inode_number, offset, level])
                faulty = True
            else:
                block_dict[datablock] = [[inode.inode_number, offset, level]]

        #double indirect
        offset = 268
        level = 2
        datablock = inode.indirect_blocks[1]
        if datablock != 0:
            if datablock < 0 or inode.indirect_blocks[1] > MAX_BLOCKS - 1:
                print("INVALID DOUBLE INDIRECT BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                faulty = True
            if datablock < FIRST_UNRESERVED_BLOCK and datablock > 0:
                print("RESERVED DOUBLE INDIRECT BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                faulty = True
            if datablock in bfree_list:
                print("ALLOCATED DOUBLE INDIRECT BLOCK %d ON FREELIST" %(datablock))
                faulty = True
            if datablock in block_dict:
                block_dict[datablock].append([inode.inode_number, offset, level])
                faulty = True
            else:
                block_dict[datablock] = [[inode.inode_number, offset, level]]

        #triple indirect
        offset = 65804
        level = 3
        datablock = inode.indirect_blocks[2]
        if datablock != 0:
            if datablock < 0 or inode.indirect_blocks[2] > MAX_BLOCKS - 1:
                print("INVALID TRIPLE INDIRECT BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                faulty = True
            if datablock < FIRST_UNRESERVED_BLOCK and datablock > 0:
                print("RESERVED TRIPLE INDIRECT BLOCK %d IN INODE %d AT OFFSET %d" %(datablock, inode.inode_number, offset))
                faulty = True
            if datablock in bfree_list:
                print("ALLOCATED TRIPLE INDIRECT BLOCK %d ON FREELIST" %(datablock))
                faulty = True
            if datablock in block_dict:
                block_dict[datablock].append([inode.inode_number, offset, level])
                faulty = True
            else:
                block_dict[datablock] = [[inode.inode_number, offset, level]]

    #indirect blocks now
    for i in range(len(indirect_list)):
        level = indirect_list[i].level
        offset = indirect_list[i].offset
        if indirect_list[i].ref_block != 0:
            indirect_str = ""
            if level == 1:
                indirect_str = "INDIRECT "
            elif level == 2:
                indirect_str = "DOUBLE INDIRECT "
            elif level == 3:
                indirect_str = "TRIPLE INDIRECT "
            if indirect_list[i].ref_block < 0 or indirect_list[i].ref_block > MAX_BLOCKS - 1:
                print("INVALID " + indirect_str + "BLOCK " + str(indirect_list[i].ref_block) + " in INODE " + str(indirect_list[i].inode) + " AT OFFSET " + str(offset))
                faulty = True
            if indirect_list[i].ref_block < FIRST_UNRESERVED_BLOCK and indirect_list[i].ref_block > 0:
                print("RESERVED " + indirect_str + "BLOCK " + str(indirect_list[i].ref_block) + " in INODE " + str(indirect_list[i].inode) + " AT OFFSET " + str(offset))
                faulty = True
            if indirect_list[i].ref_block in bfree_list:
                print("ALLOCTED " + indirect_str + "BLOCK %d ON FREELIST" %(indirect_list[i].ref_block))
                faulty = True
            if indirect_list[i].ref_block in block_dict:
                block_dict[indirect_list[i].ref_block].append(indirect_list[i].ref_block, offset, level)
                faulty = True
            else:
                block_dict[indirect_list[i].ref_block] = [[indirect_list[i].ref_block, offset, level]]

    for block in range(FIRST_UNRESERVED_BLOCK, MAX_BLOCKS):
        if block not in block_dict and block not in bfree_list:
            print("UNREFERENCED BLOCK %d" %(block))
            faulty = True
    for block in range(FIRST_UNRESERVED_BLOCK, MAX_BLOCKS):
        if block in block_dict:
            if len(block_dict[block]) > 1:
                faulty = True
                for entry in block_dict[block]:
                    level = int(entry[2])
                    indirect_str = ""
                    if level == 1:
                        indirect_str = "INDIRECT "
                    elif level == 2:
                        indirect_str = "DOUBLE INDIRECT "
                    elif level == 3:
                        indirect_str = "TRIPLE INDIRECT "
                    print("DUPLICATE " + indirect_str + "BLOCK " + str(block) + " IN INODE " + str(entry[0]) + " AT OFFSET " + str(entry[1]))

def Inode_Audit():
    global used_inodes
    for inode in inode_list:
        used_inodes.append(inode.inode_number)
        if inode.file_type != '0' and inode.inode_number in ifree_list:
            print("ALLOCATED INODE %d ON FREELIST" %(inode.inode_number))
            faulty = True
    for number in range(sb.s_first_ino, sb.s_inodes_count):
        if number not in used_inodes and number not in ifree_list:
            print("UNALLOCATED INODE %d NOT ON FREELIST" %(number))
            faulty = True        

def Directory_Audit():
    linkcount = {}
    parent_inode = {2: 2}
    for i in  range(1, sb.s_inodes_count):
        linkcount[i] = 0
    for directory in dirent_list:
        if directory.inode > sb.s_inodes_count or directory.inode < 1:
            print("DIRECTORY INODE %d NAME %s INVALID INODE %d" %(directory.parent_inode, directory.name, directory.inode))
            faulty = True
        elif directory.inode not in used_inodes:
            print("DIRECTORY INODE %d NAME %s UNALLOCATED INODE %d" %(directory.parent_inode, directory.name, directory.inode))
            faulty = True
        if directory.name == "'.'" and directory.inode != directory.parent_inode:
            print("DIRECTORY INODE %d NAME '.' LINK TO INODE %d SHOULD BE %d" %(directory.parent_inode, directory.inode, directory.parent_inode))
            faulty = True
        if directory.name != "'.'" and directory.name != "'..'":
            parent_inode[directory.inode] = directory.parent_inode
        if directory.inode in linkcount:
            linkcount[directory.inode] += 1
        if directory.name == "'..'":
            if(directory.inode != parent_inode[directory.parent_inode]):
                print("DIRECTORY INODE %d NAME '..' LINK TO INODE %d SHOULD BE %d" %(directory.parent_inode, directory.inode, parent_inode[directory.parent_inode]))
                faulty = True
    for inode in inode_list:
        if inode.inode_number in linkcount:
            if inode.i_links_count != linkcount[inode.inode_number]:
                print("INODE %d HAS %d LINKS BUT LINKCOUNT IS %d" %(inode.inode_number, linkcount[inode.inode_number], inode.i_links_count))
                faulty = True

def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Use like ./lab3b file\n")
        sys.exit(1)

    global sb

    try:
        with open(sys.argv[1]) as csvfile:
            parser = csv.reader(csvfile)
            for line in parser:
                if line[0] == "SUPERBLOCK":
                    sb = SUPERBLOCK(line)
                if line[0] == "GROUP":
                    group_descriptor = GROUP(line)
                if line[0] == "BFREE":
                    bfree_list.append(int(line[1]))
                if line[0] == "IFREE":
                    ifree_list.append(int(line[1]))
                if line[0] == "INODE":
                    inode_list.append(INODE(line))
                if line[0] == "DIRENT":
                    dirent_list.append(DIRENT(line))
                if line[0] == "INDIRECT":
                    indirect_list.append(INDIRECT(line))
    except IOError:
        sys.stderr.write("Error parsing through csv file\n")
        sys.exit(1)

    global MAX_BLOCKS
    MAX_BLOCKS = sb.s_blocks_count
    global FIRST_UNRESERVED_BLOCK
    FIRST_UNRESERVED_BLOCK = int(group_descriptor.first_block + sb.s_inode_size * group_descriptor.total_inodes / sb.s_block_size)

    Block_Audit()
    Inode_Audit()
    Directory_Audit()

    if faulty is True:
        sys.exit(2)
    else:
        sys.exit(0)

if __name__ == '__main__':
    main() 
