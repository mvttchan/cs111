//NAME:  Matthew Chan
//EMAIL: matthew_2185@yahoo.com
//ID:    805291212

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ext2_fs.h"

#define SUPERBLOCK_OFFSET 1024
struct ext2_super_block superblock;
unsigned int block_size;
int fd = -1;

struct ext2_group_desc group_descriptor;

void print_directory(unsigned int num, unsigned int block_offset);
void print_indirect(unsigned int num, int level, unsigned int current_block, int offset);

void print_time(time_t temp) {
  char buf[64];
  struct tm* tm;
  time_t time = temp;
  tm = gmtime(&time);
  strftime(buf, 64, "%m/%d/%y %H:%M:%S", tm);
  printf("%s,", buf);
}

void print_superblock() {
  printf("SUPERBLOCK,%d,%d,%d,%d,%d,%d,%d\n",
	 superblock.s_blocks_count,
	 superblock.s_inodes_count,
	 block_size,
	 superblock.s_inode_size,
	 superblock.s_blocks_per_group,
	 superblock.s_inodes_per_group,
	 superblock.s_first_ino);
}

void print_group_descriptor() {
  printf("GROUP,%d,%d,%d,%d,%d,%d,%d,%d\n",
	 0,
	 superblock.s_blocks_count,
	 superblock.s_inodes_count,
	 group_descriptor.bg_free_blocks_count,
	 group_descriptor.bg_free_inodes_count,
	 group_descriptor.bg_block_bitmap,
	 group_descriptor.bg_inode_bitmap,
	 group_descriptor.bg_inode_table);
}

void print_free_blocks(const int offset) {
  char* bitmap = malloc(sizeof(char) * block_size);
  if(pread(fd, bitmap, block_size, offset) < 0) {
    fprintf(stderr, "Could not read free blocks\n");
    exit(2);
  }
  unsigned int i, j;
  for(i = 0; i < block_size; ++i) {
    char byte = bitmap[i];
    for(j = 0; j < 8; ++j) {
      int used = 1 & byte;
      if(!used) printf("BFREE,%d\n", ((i * 8) + (j + 1)));
      byte >>= 1;
    }
  }
  free(bitmap);
}

void print_free_inodes(const int offset) {
  char* bitmap = malloc(sizeof(char) * block_size);
  if(pread(fd, bitmap, block_size, offset) < 0) {
    fprintf(stderr, "Could not read free inodes\n");
    exit(2);
  }
  unsigned int i, j;
  for(i = 0; i < block_size; ++i) {
    char byte = bitmap[i];
    for(j = 0; j < 8; ++j) {
      int used = 1 & byte;
      if(!used) printf("IFREE,%d\n", ((i * 8) + (j + 1)));
      byte >>= 1;
    }
  }
  free(bitmap);
}

void print_inode_summary(const int offset) {
  struct ext2_inode inode;
  unsigned int i;
  for(i = 0; i < superblock.s_inodes_count; ++i) {
    if(pread(fd, &inode, sizeof(inode), offset + (i * sizeof(inode))) < 0) {
      fprintf(stderr, "Could not read inode summary\n");
      exit(2);
    }
    if(inode.i_mode == 0 || inode.i_links_count == 0) continue;
    char file_type = '?';
    if(S_ISDIR(inode.i_mode)) file_type = 'd';
    else if(S_ISREG(inode.i_mode)) file_type = 'f';
    else if(S_ISLNK(inode.i_mode)) file_type = 's';
    printf("INODE,%d,%c,%o,%d,%d,%d,",
	   i + 1,
	   file_type,
	   inode.i_mode & 0xFFF,
	   inode.i_uid,
	   inode.i_gid,
	   inode.i_links_count);
  
    print_time(inode.i_ctime);
    print_time(inode.i_mtime);
    print_time(inode.i_atime);
    printf("%d,%d", inode.i_size, inode.i_blocks);
    if(file_type == 's' && inode.i_size < 60) {
      //supposed to leave the next fifteen entries blank
      printf("\n");
      continue;
    }
    int index_address;
    for(index_address = 0; index_address < EXT2_N_BLOCKS; ++index_address) {
      printf(",%d", inode.i_block[index_address]);
    }
    printf("\n");

    if(file_type == 's') continue;

    if(file_type == 'd') {
      int j;
      for(j = 0; j < EXT2_NDIR_BLOCKS; ++j) {
	if(inode.i_block[j] != 0) {
	  print_directory(i + 1, inode.i_block[j]);
	}
      }
    }
    if(inode.i_block[EXT2_IND_BLOCK] != 0) {
      //single indirect reference
      print_indirect(i + 1, 1, inode.i_block[EXT2_IND_BLOCK], 12);
    }
    if(inode.i_block[EXT2_DIND_BLOCK] != 0) {
      //DOUBLE INDIRECT
      print_indirect(i + 1, 2, inode.i_block[EXT2_DIND_BLOCK], 268);
    }
    if(inode.i_block[EXT2_TIND_BLOCK] != 0) {
      //TRIPLE INDIRECT
      print_indirect(i + 1, 3, inode.i_block[EXT2_TIND_BLOCK], 65804);
    }
  }
}

void print_directory(unsigned int num, unsigned int block_offset) {
  struct ext2_dir_entry directory;
  unsigned int directory_entry;
  unsigned int offset = SUPERBLOCK_OFFSET + (block_offset - 1) * block_size;
  for(directory_entry = 0; directory_entry < block_size; directory_entry += directory.rec_len) {
    if(pread(fd, &directory, sizeof(directory), offset + directory_entry) < 0) {
      fprintf(stderr, "Cannot read directory\n");
      exit(2);
    }
    if(directory.inode != 0) {
      printf("DIRENT,%d,%d,%d,%d,%d,\'%s\'\n",
	     num,
	     directory_entry,
	     directory.inode,
	     directory.rec_len,
	     directory.name_len,
	     directory.name);
    }
  }
}

void print_indirect(unsigned int num, int level, unsigned int current_block, int offset) {
  int buf[block_size];
  if(pread(fd, buf, block_size, block_size * current_block) < 0) {
    fprintf(stderr, "Cannot read indirect\n");
    exit(2);
  }
  unsigned int i;
  for(i = 0; i < block_size / 4; ++i) {
    if(buf[i] != 0) {
      printf("INDIRECT,%d,%d,%d,%d,%d\n",
	     num,
	     level,
	     offset,
	     current_block,
	     buf[i]);

    }
    if(level != 1) print_indirect(num, level - 1, buf[i], offset);
    if(level == 1) offset++;
    if(level == 2) offset += 256;
    if(level == 3) offset += 65536;
  }
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    fprintf(stderr, "Try ./lab3a \"file_image\"\n");
    exit(1);
  }
  fd = open(argv[1], O_RDONLY);
  if(fd < 0) {
    fprintf(stderr, "Could not open the image\n");
    exit(1);
  }
  if(pread(fd, &superblock, sizeof(superblock), 1024) < 0) {
    fprintf(stderr, "Could not read the superblock\n");
    exit(2);
  }
  block_size = 1024 << superblock.s_log_block_size;
  print_superblock();

  int group_desc_offset;
  group_desc_offset = 2;
  if(block_size > 1024) group_desc_offset = 1;
  const int GROUP_OFFSET = (block_size * group_desc_offset);
  if(pread(fd, &group_descriptor, sizeof(group_descriptor), GROUP_OFFSET) < 0) {
    fprintf(stderr, "Could not read group descriptor\n");
    exit(2);
  }
  print_group_descriptor();

  print_free_blocks(GROUP_OFFSET + block_size);
  print_free_inodes(GROUP_OFFSET + (2 * block_size));

  print_inode_summary(GROUP_OFFSET + (3 * block_size));

  exit(0);
}
