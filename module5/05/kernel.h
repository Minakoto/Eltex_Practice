#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/net_namespace.h>
#include <linux/string.h>

#define NETLINK_USER 31
#define MSG_LEN 1034

static int __init kern_init(void);
static void __exit kern_exit(void);
static void rcv_msg(struct sk_buff* sbuff);

struct sock *net_sock = NULL;

struct netlink_kernel_cfg conf = {
    .groups  = 1,
    .input = rcv_msg,
 };
