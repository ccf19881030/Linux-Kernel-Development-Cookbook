/*
 * ch5/slab3_maxsize/slab3_maxsize.c
 ***************************************************************
 * This program is part of the source code released for the book
 *  "Linux Kernel Development Cookbook"
 *  (c) Author: Kaiwan N Billimoria
 *  Publisher:  Packt
 *  GitHub repository:
 *  https://github.com/PacktPublishing/Linux-Kernel-Development-Cookbook
 *
 * From: Ch 5 : Linux Kernel Memory Allocation for Module Authors Part 1
 ****************************************************************
 * Brief Description:
 *
 * For details, please refer the book, Ch 5.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#define OURMODNAME   "slab3_maxsize"

MODULE_AUTHOR("Kaiwan N Billimoria");
MODULE_DESCRIPTION("LKDC book:ch/: hello, world");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int stepsz = 200000;
module_param(stepsz, int, 0644);
MODULE_PARM_DESC(stepsz,
 "Amount to increase allocation by on each loop iteration (default=200000");

static int test_maxallocsz(void)
{
	size_t size2alloc = 0;
	void *p;

	while (1) {
		p = kmalloc(size2alloc, GFP_KERNEL);
		if (!p) {
			pr_alert("kmalloc fail, size2alloc=%ld\n", size2alloc);
			return -ENOMEM;
		}
		pr_info("kmalloc(%7ld) = 0x%pK\n", size2alloc, p);
		kfree(p);
		size2alloc += stepsz;
	}
	return 0;
}

static int __init slab3_maxsize_init(void)
{
	pr_debug("%s: inserted\n", OURMODNAME);
	return test_maxallocsz();
}
static void __exit slab3_maxsize_exit(void)
{
	pr_debug("%s: removed\n", OURMODNAME);
}

module_init(slab3_maxsize_init);
module_exit(slab3_maxsize_exit);
