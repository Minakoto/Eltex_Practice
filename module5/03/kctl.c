#include <linux/module.h>
#include <linux/configfs.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/console_struct.h>
#include <linux/vt_kern.h>
#include <linux/timer.h>
#include <linux/sysfs.h> 
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/printk.h> 

#define BLINK_DELAY   HZ/8
#define RESTORE_LEDS  0xFF


MODULE_DESCRIPTION("Blinking keyboard lights using ioctl and sysfs");
MODULE_LICENSE("GPL");
struct timer_list blink_timer;
struct tty_driver *blink_driver;
static int mask = 3;
static int led_status = 0;
static struct kobject * keyctl;

static ssize_t get_m(struct kobject * kobj, struct kobj_attribute* attr,const char* buf, size_t count) {
    sscanf(buf, "%du", &mask);
    return count;
}
static ssize_t put_m(struct kobject * kobj, struct kobj_attribute* attr, char* buf) {
    return sprintf(buf, "%d\n", mask);
}

static struct kobj_attribute key_attr =__ATTR(mask, 0775, put_m, get_m);

static int change_led(void) {
    return led_status == mask ? RESTORE_LEDS : mask;
}

static void set_timer(struct timer_list* ptr) {
    led_status = change_led();
    (blink_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, led_status);
    blink_timer.expires = jiffies + BLINK_DELAY;
    add_timer(&blink_timer);
}

static int init_blinker(void) {

    blink_driver = vc_cons[fg_console].d->port.tty->driver;
    
    keyctl = kobject_create_and_add("keyboardctl", kernel_kobj);
    int err = sysfs_create_file(keyctl, &key_attr.attr);

    timer_setup(&blink_timer, set_timer, 0);
    blink_timer.expires = jiffies + BLINK_DELAY;
    add_timer(&blink_timer);
    return err;
}

static void clean_blinker(void) {
    del_timer(&blink_timer);
    (blink_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
                        RESTORE_LEDS);
    kobject_put(keyctl);
}

module_init(init_blinker);
module_exit(clean_blinker);
