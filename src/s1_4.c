// #include ... /* 包含内核中的多个头文件 */

/* 设备结构体 */
struct light_dev {
	struct cdev cdev; /* 字符设备 cdev 结构体 */
	unsigned char value; /* LED 电平值，用户可读写此值 */
};

struct light_dev *light_devp;
int light_major = LIGHT_MAJOR;

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>")
MODULE_LICENCE("Dual BSD/GPL");

/* 打开和关闭函数 */
int light_open(struct inode *inode, struct file *filp)
{
	struct light_dev *dev;

	/* 获得设备结构体指针 */
	dev = container_of(inode->i_cdev, struct light_dev, cdev);
	/* 让设备结构体作为设备的私有信息 */
	filp->private_data = dev;
	return 0;
}

int light_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/* 读写设备：可以不需要 */
ssize_t light_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct light_dev *dev = filp->private_data; /* 获得设备结构体 */

	if (copy_to_user(buf, &(dev->value), 1)) 
		return -EFAULT;

	return 1;
}

ssize_t light_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct light_dev *dev = filp->private_data;

	if (copy_from_user(&(dev->value), buf, 1))
		return -EFAULT;

	/* ioctl 函数 */

}
