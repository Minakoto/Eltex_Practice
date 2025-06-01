#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/types.h>
#include <unistd.h>

#define NETLINK_USER 31
#define MAX_LOAD 1024

void init_src_addr();
void init_dst_addr();
void init_header();
void construct_msg(const char*);