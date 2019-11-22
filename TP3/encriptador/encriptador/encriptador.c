/*
 *  encriptador.c: crea un dispositivo de caracter y guarda en el mismo una cadena de caracteres previamente encriptada. 
 *  
 */
#include "encriptador.h"
MODULE_LICENSE("GPL");

static int Major;		/* Major number asignado al controlador de dispositivo */
static int Device_Open = 0;	 //Usado para prevenir accesos multiples al dispositivo
static char msg[BUF_LEN];	
static char *msg_Ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

/*
 * Se llama a esta funcion cuando el modulo es cargado
 */
int init_module(void)
{
        Major = register_chrdev(0, DEVICE_NAME, &fops);//n° mayor pasado es 0, entonces se asigna dinamicamente un n° mayor
		//no se pasa n° menor porque no es de interes para el kernel
	if (Major < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);//ERROR
	  return Major;
	}

	printk(KERN_INFO "Me asignaron un numero mayor igual a %d. Para comunicarse\n", Major);
	printk(KERN_INFO "con el driver, por favor crear un dev file con el comando\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Prueba varios numeros menores. Intenta hacer cat y echo al device file.\n");
	printk(KERN_INFO "Elimine el archivo y el modulo del dispositivo cuando haya terminado.\n");

	return SUCCESS;
}

/*
 * Esta funcion es llamada cuando el modulo es descargado
 */
void cleanup_module(void)
{
	printk(KERN_INFO "FUNCION CLEANUP.\n");
	unregister_chrdev(Major, DEVICE_NAME);//desregistra el dispositivo
	printk(KERN_INFO "Dispositivo desregistrado satisfactoriamente.\n");
}
/* 
 * Llamada cuando un proceso trata de abrir el archivo de dispositivo (device file) como por ej: "cat /dev/chardev"
 */
static int device_open(struct inode *inode, struct file *file)
{
	if (Device_Open)
		return -EBUSY;

	Device_Open++;
	try_module_get(THIS_MODULE);//incrementa el contador de usos(cuantas veces se usa el modulo)
	printk(KERN_INFO "FUNCION OPEN.\n");
	return SUCCESS;
}

/* 
 * Llamada cuando un procesos cierra el device file
 */
static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;		
	/* 
	 * Decrement the usage count, or else once you opened the file, you'll
	 * never get get rid of the module. 
	 */
	module_put(THIS_MODULE);//decrementa el contador de usos
	printk(KERN_INFO "FUNCION RELEASE.\n");

	return 0;
}

/* 
 * Llamada cuando un proceso, el cual ya abrió el dev file, intenta leer de el.
 */
static ssize_t device_read(struct file *filp,	/* ver include/linux/fs.h  */
			   char *buffer,	/* buffer para llenar con datos */
			   size_t length,	/* longitud del buffer     */
			   loff_t * offset)
{
	int bytes_read = 0;//numero de bytes actualmente escritos en el buffer

	if (*msg_Ptr == 0)//si estamos en el final del mensaje, retorna 0 indicando EOF
		return 0;

	while (length && *msg_Ptr) {//pone los datos en el buffer

		/* 
		 * The buffer is in the user data segment, not the kernel 
		 * segment so "*" assignment won't work.  We have to use 
		 * put_user which copies data from the kernel data segment to
		 * the user data segment. Copies a single simple value from 
         * kernel space to user space. It supports simple types like 
         * char and int, but not larger data types like structures or arrays.
		 */
		put_user(*(msg_Ptr++), buffer++);//

		length--;
		bytes_read++;
	}
    printk(KERN_INFO "FUNCION READ\n");
	return bytes_read; //retorna el numero de bytes colocados en el buffer
}

/*  
 * Llamada cuando un proceso escribe al archivo de dispositivo (dev file): echo "hi" > /dev/chardev  
 */
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
        int bytes_write = 0;
        for(bytes_write = 0; bytes_write < len && bytes_write < BUF_LEN; bytes_write++)
                get_user(msg[bytes_write], buff + bytes_write);//Copia de a un dato por vez desde el espacio de usuario al espacio del kernel
        
        /*
		 *	Toma los caracteres ingresados por el usuario y les suma UN "ENTERO FIJO" para encriptarlos.
		 */
		for(bytes_write = 0; bytes_write < len && bytes_write < BUF_LEN; bytes_write++)
				msg[bytes_write] = msg[bytes_write]+ENTERO_FIJO;

        msg_Ptr = msg;
		printk(KERN_INFO "FUNCION WRITE.\n");
        return bytes_write;//retorna el numero de caracteres escritos
	

}