/* 
 * simple_netfilter.c.c
 * Copyright (C) 2013 Chaitanya H. <C@24.IO>
 * Date: Tue Feb 19 11:08:27 PST 2013
 * 
 * This file is a simple "Hello World" implementation of Netfilter Hooks.
 * I am using it to study the Netfilters hook implementation. 
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 * 
 * Code from: http://www.paulkiddie.com/2009/10/creating-a-simple-hello-world-netfilter-module/ 
 * Machine: 3.2.0-37-generic
 *
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chaitanya H <C@24.IO>");
MODULE_DESCRIPTION("Hello World Netfilter Hook module");
MODULE_ALIAS("simple_netfilter");


static struct nf_hook_ops nfhookops; // Hook function options

//Function where work will be done and this function will be called by the hook
unsigned int hook_function(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
  printk(KERN_INFO "packet dropped\n");                                             //log to var/log/messages
  
  printk(KERN_ERR "Function - %s file %s line %i\n", __FUNCTION__, __FILE__, __LINE__);

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

