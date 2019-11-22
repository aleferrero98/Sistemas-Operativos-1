#ifndef _ENCRIPTADOR_H_
#define _ENCRIPTADOR_H_

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* funcion put_user y get_user */

int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "encriptador"	/* Dev name. Asi aparece en /proc/devices   */
#define BUF_LEN 80		/* maxima longitud del mensaje desde el usuario */
#define ENTERO_FIJO 5 //n° para encriptar-desencriptar
//#define NUMERO_MAYOR 510

#endif //_ENCRIPTADOR_H_