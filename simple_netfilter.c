// Simple "Hello World" Netfilter Hook module
// Chaitanya <C@24.IO>
// Code from: http://www.paulkiddie.com/2009/10/creating-a-simple-hello-world-netfilter-module/ 
// Machine: 3.2.0-37-generic
//

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nfhookops; // Hook function options

//Function where work will be done and this function will be called by the hook
unsigned int hook_function(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
  printk(KERN_INFO "packet dropped\n");                                             //log to var/log/messages
  return NF_ACCEPT;                                                                   //drops the packet
}


int init_module (void) {

	printk(KERN_INFO "init_module() called\n");

	nfhookops.hook = hook_function; //This is the hook function getting engaged. 
	nfhookops.hooknum = NF_INET_PRE_ROUTING; //This is which point do you want to engage in, right after the packet enters the kernel stack.
	nfhookops.pf = PF_INET; //IPV4 Packets
	nfhookops.priority = NF_IP_PRI_FIRST; //This is the highest priority over all the other hook functions. 
	nf_register_hook(&nfhookops); //Now actually registering the hook

	return 0;

}

void cleanup_module(void) {

	printk(KERN_INFO "cleanup_module() called\n");

	nf_unregister_hook(&nfhookops); //Removing the hook

}

