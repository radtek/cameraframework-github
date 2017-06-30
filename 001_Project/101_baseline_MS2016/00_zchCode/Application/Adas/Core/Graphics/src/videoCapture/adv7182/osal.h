#ifndef __OSAL_H__
#define __OSAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/mman.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <atomic.h>
#include <inttypes.h>
#include <sys/mman.h>
#include <sys/rsrcdbmgr.h>
#include <sys/rsrcdbmsg.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <sys/slog.h>
#include <fcntl.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <ctype.h>
#include <dlfcn.h>
#include <stddef.h>

#define LIKELY_EXPECT
#ifdef LIKELY_EXPECT
# define likely(x)	    __builtin_expect(!!(x), 1)
# define unlikely(x)	__builtin_expect(!!(x), 0)
#else
# define likely(x)      (x)  
# define unlikely(x)    (x)
#endif

#ifdef LOG_TAG

#define __E(fmt, args...)  ({fprintf(stderr, "Error  : %20s -> %3d: %s(): " fmt, LOG_TAG,  __LINE__, __FUNCTION__, ## args);})
#define __W(fmt, args...)  ({fprintf(stderr, "Warning: %20s -> %3d: %s(): " fmt, LOG_TAG,  __LINE__, __FUNCTION__, ## args);})
#define __I(fmt, args...)  ({fprintf(stderr, "Info   : %20s -> %3d: %s(): " fmt, LOG_TAG,  __LINE__, __FUNCTION__, ## args);})

#ifdef NDEBUG
#define __D(fmt, args...)
#else
#define __D(fmt, args...)  ({fprintf(stderr, "Debug  : %20s -> %3d: %s(): " fmt, LOG_TAG,  __LINE__, __FUNCTION__, ## args);})

#if 0
#define LOG_FILE_NAME "/tmp/log_file_name"
static FILE *LOG_FILE;			//stdout
static inline int __D(const char* info, ...)
{
	if(LOG_FILE == NULL) {
		LOG_FILE = fopen(LOG_FILE_NAME, w+);
	}
	
	va_list         vargs;
    va_start(vargs, info);
    //LogInfoV(info, vargs);
	vfprintf(LOG_FILE, info, vargs);
    fprintf(LOG_FILE, "\n");
    fflush(LOG_FILE);
    va_end(vargs);
	return 0;
}
#endif

#endif	/* NDEBUG */

#else

#define __D(fmt, args...)
#define __E(fmt, args...)
#define __W(fmt, args...)
#define __I(fmt, args...)

#endif	/* LOG_TAG */

#define BILLION             1000000000L

#define EXPORT_SYMBOL(symbol)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* align addr on a size boundary - adjust address up/down if needed */
#define SIZE_MASK(size)         (~((size)-1))
#define _ALIGN_UP(addr,size)	(((addr)+((size)-1))&SIZE_MASK(size))
#define _ALIGN_DOWN(addr,size)	((addr)&(SIZE_MASK(size)))
#define _ALIGN(addr,size)       _ALIGN_UP(addr,size)

#define USING_RT_CLOCK
#if defined USING_CLOCK
#define test_speed_fps_start()					\
	static clock_t t_start, t_stop;				\
	t_start = clock()

#define test_speed_fps_stop_by_count(c) ({								\
			static double t_duration = 0;								\
			static int    t_cnt      = 1;								\
			t_stop = clock();											\
			t_duration += (double)(t_stop - t_start) / CLOCKS_PER_SEC;	\
			if(++t_cnt == (c)) __I("framerate = %.2f(fps)\n", t_cnt / t_duration); \
		})
#define test_speed_fps_per_count(c) ({									\
			static double t_duration = 0;								\
			static int    t_cnt      = 1;								\
			t_stop = clock();											\
			t_duration += (double)(t_stop - t_start) / CLOCKS_PER_SEC;	\
			if((++t_cnt % (c)) == 0) {__I("framerate = %.2f(fps)\n", t_cnt / t_duration); t_cnt = 1; t_duration = 0;} \
		})

#elif defined USING_RT_CLOCK
#define test_speed_fps_start()					\
	static struct timespec rt_start, rt_stop;	\
	clock_gettime(CLOCK_MONOTONIC, &rt_start)

#define test_speed_fps_stop_by_count(c) ({								\
			static double          rt_duration = 0;						\
			static int             rt_cnt     = 1;						\
			clock_gettime(CLOCK_MONOTONIC, &rt_stop);					\
			rt_duration += (rt_stop.tv_sec - rt_start.tv_sec) + (double)(rt_stop.tv_nsec - rt_start.tv_nsec) / BILLION; \
			if(++rt_cnt == (c)) __I("framerate = %.2f(fps)\n", rt_cnt / rt_duration); \
		})
#define test_speed_fps_per_count(c) ({									\
			static double          rt_duration = 0;						\
			static int             rt_cnt     = 1;						\
			clock_gettime(CLOCK_MONOTONIC, &rt_stop);					\
			rt_duration += (rt_stop.tv_sec - rt_start.tv_sec) + (double)(rt_stop.tv_nsec - rt_start.tv_nsec) / BILLION; \
			if((++rt_cnt % (c)) == 0) {__I("%.2f fps\n", rt_cnt / rt_duration); rt_cnt = 1; rt_duration = 0;} \
		})
#define test_speed_fps_per_count_by(v, c) ({							\
			static double          rt_duration = 0;						\
			static int             lt_cnt;						\
			if(lt_cnt == 0) lt_cnt = v;									\
			clock_gettime(CLOCK_MONOTONIC, &rt_stop);					\
			rt_duration += (rt_stop.tv_sec - rt_start.tv_sec) + (double)(rt_stop.tv_nsec - rt_start.tv_nsec) / BILLION; \
			if((((v) - lt_cnt) % (c)) == 0) {__I("%s: %.2f fps\n", #v, ((v) - lt_cnt) / rt_duration); lt_cnt = (v); rt_duration = 0;} \
		})
#else
#define test_speed_fps_start()
#define test_speed_fps_stop_by_count(c)
#define test_speed_fps_per_count(c)
#endif



										 //typedef int8_t s8;
typedef char    s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

//typedef uint8_t u8;
typedef unsigned char u8;
typedef uint16_t u16;
typedef uint64_t u64;
typedef volatile uint32_t u32;

typedef volatile uint32_t v32;

typedef struct {
	u8    b00:1;
	u8    b01:1;
	u8    b02:1;
	u8    b03:1;
	u8    b04:1;
	u8    b05:1;
	u8    b06:1;
	u8    b07:1;
} bit8_t;

typedef struct {
	u8    b00:1;
	u8    b01:1;
	u8    b02:1;
	u8    b03:1;
	u8    b04:1;
	u8    b05:1;
	u8    b06:1;
	u8    b07:1;
	u8    b08:1;
	u8    b09:1;
	u8    b10:1;
	u8    b11:1;
	u8    b12:1;
	u8    b13:1;
	u8    b14:1;
	u8    b15:1;
} bit16_t;

typedef struct {
	u8    b00:1;
	u8    b01:1;
	u8    b02:1;
	u8    b03:1;
	u8    b04:1;
	u8    b05:1;
	u8    b06:1;
	u8    b07:1;
	u8    b08:1;
	u8    b09:1;
	u8    b10:1;
	u8    b11:1;
	u8    b12:1;
	u8    b13:1;
	u8    b14:1;
	u8    b15:1;
	u8    b16:1;
	u8    b17:1;
	u8    b18:1;
	u8    b19:1;
	u8    b20:1;
	u8    b21:1;
	u8    b22:1;
	u8    b23:1;
	u8    b24:1;
	u8    b25:1;
	u8    b26:1;
	u8    b27:1;
	u8    b28:1;
	u8    b29:1;
	u8    b30:1;
	u8    b31:1;
} bit32_t;

typedef struct sigevent sigevent_t;
typedef u32             phys_addr_t;
typedef struct pm_message {
	s32  event;
} pm_message_t;
typedef struct resource {
#define RESSIZE(ressource) (((ressource)->end - (ressource)->start)+1)
	phys_addr_t   start;
	phys_addr_t   end;

#define IORESOURCE_IO		0x00000100
#define IORESOURCE_MEM		0x00000200
#define IORESOURCE_IRQ		0x00000400
#define IORESOURCE_DMA		0x00000800
#define IORESOURCE_BUSY		0x80000000	/* Driver has marked this resource busy */
	s32           flags;
	s8           *name;
}resource_t;

#define request_mem_region(start,n,name) ({ __D("request_mem_region: [%u - %u] for %s \n", (start), (start)+(n), (name)); (resource_t*)&(start);})


typedef struct device {
	s8             *bus_id;
	void           *driver_data;
}device_t;

typedef struct platform_device {
	device_t        dev;
	s8             *name;
	s32             id;
	u32		        num_resources;
	resource_t     *resource;
}platform_device_t;

static inline void *platform_get_drvdata(const platform_device_t *pdev)
{
	return pdev->dev.driver_data;
}

static inline void platform_set_drvdata(platform_device_t *pdev, void *data)
{
	pdev->dev.driver_data = data;
}


typedef struct module {
	s8  *name;
	s8   srcversion[25];
}module_t;
#define THIS_MODULE ((module_t *)0)
#define __devinit

typedef struct device_driver {
	s8             *name;
	module_t       *owner;
}device_driver_t;

typedef struct platform_driver {
	device_driver_t driver;

	s32 (*probe)     (platform_device_t *);
	s32 (*remove)    (platform_device_t *);
	void (*shutdown)(platform_device_t *);
	s32 (*suspend)(platform_device_t *, pm_message_t state);
	s32 (*suspend_late)(platform_device_t *, pm_message_t state);
	s32 (*resume_early)(platform_device_t *);
	s32 (*resume)(platform_device_t *);

}platform_driver_t;


static resource_t ioresource_dma_list[128];

/**
 * release_resource - release a previously reserved resource
 * @old: resource pointer
 */
static inline int release_resource(resource_t *old_r)
{
	unsigned int i;
	rsrc_request_t req;
	switch(old_r->flags) {
	case IORESOURCE_DMA:
		for(i = 0; i < ARRAY_SIZE(ioresource_dma_list); i++) {
			resource_t *r = &ioresource_dma_list[i];
			if(r->start && r->end) {
				req.length =  r->end - r->start + 1;
				req.start = r->start;
				req.flags  = RSRCDBMGR_DMA_CHANNEL;
				rsrcdbmgr_detach(&req, 1);
				memset(r, 0, sizeof(*r));
			}
		}
		break;
	default:
		break;
	}
	
	return 0;
}
/**
 * platform_get_resource - get a resource for a device
 * @dev: platform device
 * @type: resource type
 * @num: resource index
 */
static inline resource_t *platform_get_resource(platform_device_t *dev,
												u32 type,
												u32 num)
{
	u32 i;
	rsrc_request_t req;
	for(i = 0; i < dev->num_resources; i++) {
		resource_t *r = &dev->resource[i];
	
		if(type == (u32)(r->flags)) {
			
			switch(r->flags) {
			case IORESOURCE_DMA:
				if(r->start && r->end) {
					if(ioresource_dma_list[r->start].start == 0) {
						/* this dma_channel(r->start), we haven't
						 * requested it, it is user customized,
						 * so, don't manage it!
						 */
						return r;
					}
					/* this dma_channel have used
					 * we can not reuse dma_channel now
					 * so, to request a new dma_channel is good idea
					 */
				}
				
//				rsrc_request_t req = {
//					.length = 1,
//					.flags  = RSRCDBMGR_DMA_CHANNEL,
//				};
				req.length = 1;
				req.flags = RSRCDBMGR_DMA_CHANNEL;
				
				if(rsrcdbmgr_attach(&req, 1) == -1) {
					return NULL;
				}
				r->start = req.start;
				r->end   = req.start + req.length - 1;
				ioresource_dma_list[r->start] = *r;
				
				break;
				
			default:
				break;
			}
				
			return r;
		}
	}
	return NULL;
}

/**
 * platform_get_irq - get an IRQ for a device
 * @dev: platform device
 * @num: IRQ number index
 */
static inline int platform_get_irq(platform_device_t *dev, unsigned int num)
{
	resource_t *r = platform_get_resource(dev, IORESOURCE_IRQ, num);
	return r ? r->start : -ENXIO;
}

#define __writeb(v,a)	(*(u8  *)(a) = (v))
#define __writew(v,a)	(*(u16 *)(a) = (v))
#define __writel(v,a)	(*(u32 *)(a) = (v))

#define __readb(a)		(*(u8  *)(a))
#define __readw(a)		(*(u16 *)(a))
#define __readl(a)		(*(u32 *)(a))

typedef struct gl_buffer {
	void *  vaddr; /* start */
	u8*     paddr; /* paddr_start */
	size_t  length;
	s32     w;
	s32     h;
	s32     stride;
	s32     offset;
	s32     id;
	s32     used;
	void   *gf_surf;
}gl_buffer_t;

typedef struct buffer {
	void *  vaddr; /* start */
	u8*     paddr; /* paddr_start */
	size_t  length;
	s32     w;
	s32     h;
	s32     stride;
	s32     offset;
	s32     id;
	s32     used;
	void   *gf_surf;
	s32     n_pointers;
	s32     format;
	s32     csize[2];
	int     ssize[2];
	int     spos[2];
	gl_buffer_t gl_buffer;
}buffer_t;

static inline void rate_control(int fps)
{
	struct timespec         t_end;
	static struct timespec  t_start;
	struct timespec         t_sleep;
	long                    t_dif;
	long                    t_span = BILLION / fps;	//33333333 ,30fps */
	long                    t_tmp;
	
	clock_gettime(CLOCK_MONOTONIC, &t_end);
	
	t_dif = t_end.tv_nsec - t_start.tv_nsec;
	if(t_dif < t_span && t_dif >= 0) {
		t_tmp = t_span - t_dif;
		t_sleep.tv_sec  = 0;
		t_sleep.tv_nsec = t_tmp;
		
		nanosleep(&t_sleep, NULL);

		t_end.tv_nsec = (t_end.tv_nsec + t_tmp) % BILLION;
		
		__D("sleep %10d(ns) \n", (int)t_sleep.tv_nsec);
	} 

	t_start = t_end;
}

/**
 * kzalloc - allocate memory. The memory is set to zero.
 *
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kmalloc).
 */
typedef enum {
	__GFP_ZERO,
	GFP_KERNEL,
	NR_GFP
} gfp_t;

static inline void * kzalloc(size_t size, gfp_t flags)
{
	s32   align  = 16;
	u8    value  = sizeof(value);
	u8   *p      = (typeof(p))malloc(size + align + value);
	if(p == NULL) return NULL;
	
	u8   *a      = (typeof(a))_ALIGN((unsigned long)p+value, align);
	(a-1)[0] = a - p;				/* set value of offset */
	
	memset(a, 0, size);
	__D("size = %d, alloc_addr = %p,  align%d_addr = %p \n", size, p, align, a);
	return a;
}


/**
 * kfree - free previously allocated memory.
 *
 * @objp: pointer returned by kmalloc.
 */
static inline void kfree(void * objp)
{
	u8   *a      = (typeof(a))objp;
	u8   *p      = a - (a-1)[0];
	
	__D("alloc_addr = %p,  align_addr = %p \n", p, a);
	free(p);
}

/**
 * Prototype: void * mmap_device_memory( void * addr, size_t len, int prot, int flags, uint64_t  physical );
 *
 * Description:
 * Map a device's physical memory into a process's address space
 * #include <sys/mman.h>
 */
typedef struct iomap_addrs {
	u32 vaddr;
	u32 paddr;
	u32 size;
} iomap_addrs_t;

static iomap_addrs_t iomap_addrs[8] = {{0}};
static inline u32 ioremap(u32 phys_addr, u32 size)
{
	u32 i;
		
	ThreadCtl( _NTO_TCTL_IO, 0 ); // enable HW memory permitted
	s32 prot      = PROT_READ | PROT_WRITE | PROT_NOCACHE;
	u32 virt_addr = (u32)mmap_device_memory(0, size, prot, 0, phys_addr);

		
	for(i = 0; i < ARRAY_SIZE(iomap_addrs); i++) {
		if(iomap_addrs[i].vaddr == 0) {
			iomap_addrs[i].vaddr = virt_addr;
			iomap_addrs[i].paddr = phys_addr;
			iomap_addrs[i].size  = size;
			break;
		}
	}

	return virt_addr;
}
/**
 * iounmap - Free a IO remapping
 * @addr: virtual address from ioremap_*
 *
 * Caller must ensure there is only one unmapping for the same pointer.
 */
static inline void iounmap(u32 virt_addr)
{
	u32 i;
	u32 size = 0;
	
	for(i = 0; i < ARRAY_SIZE(iomap_addrs); i++) {
		if(iomap_addrs[i].vaddr == virt_addr) {
			size = iomap_addrs[i].size;
			iomap_addrs[i].vaddr = 0;
			break;
		}
	}
	
	munmap_device_memory((void *)virt_addr, size);
}


/**
 *	request_irq - allocate an interrupt line
 *	@irq: Interrupt line to allocate
 *	@handler: Function to be called when the IRQ occurs
 *	@irqflags: Interrupt type flags
 *	@devname: An ascii name for the claiming device
 *	@dev_id: A cookie passed back to the handler function
 *
 *	This call allocates interrupt resources and enables the
 *	interrupt line and IRQ handling. From the point this
 *	call is made your handler function may be invoked. Since
 *	your handler function must clear any interrupt the board
 *	raises, you must take care both to initialise your hardware
 *	and to set up the interrupt handler in the right order.
 *
 *	Dev_id must be globally unique. Normally the address of the
 *	device data structure is used as the cookie. Since the handler
 *	receives this value it makes sense to use it.
 *
 *	If your interrupt is shared you must pass a non NULL dev_id
 *	as this is required when freeing the interrupt.
 *
 *	Flags:
 *
 *	IRQF_SHARED		Interrupt is shared
 *	IRQF_DISABLED	Disable local interrupts while processing
 *	IRQF_SAMPLE_RANDOM	The interrupt can be used for entropy
 *	IRQF_TRIGGER_*		Specify active edge(s) or level
 *
 */
typedef sigevent_t * (* irq_handler_t)(void *, int);
#define request_irq(irq, handler, irqflags, devname, dev_id) ({			\
			__D("request_irq: %u \n", (irq));						\
			InterruptAttach((irq),(handler),(void*)(dev_id),0,(irqflags));})


/**
 *	free_irq - free an interrupt
 *	@irq:    Interrupt line to free
 *	@dev_id: Device identity to free
 *
 *	Remove an interrupt handler. The handler is removed and if the
 *	interrupt line is no longer in use by any driver it is disabled.
 *	On a shared IRQ the caller must ensure the interrupt is disabled
 *	on the card it drives before calling this function. The function
 *	does not return until any executing interrupts for this IRQ
 *	have completed.
 *
 *	This function must not be called from interrupt context.
 */
static inline void free_irq(unsigned int irq, void *dev_id)
{
	return;
}

/**
 *	disable_irq - disable an irq and wait for completion
 *	@irq: Interrupt to disable
 *
 *	Disable the selected interrupt line.  Enables and Disables are
 *	nested.
 *	This function waits for any pending IRQ handlers for this interrupt
 *	to complete before returning. If you use this function while
 *	holding a resource the IRQ handler may need you will deadlock.
 *
 *	This function may be called - with care - from IRQ context.
 */
static inline void disable_irq(unsigned int irq)
{
	return;
}


/**
 *	enable_irq - enable handling of an irq
 *	@irq: Interrupt to enable
 *
 *	Undoes the effect of one call to disable_irq().  If this
 *	matches the last disable, processing of interrupts on this
 *	IRQ line is re-enabled.
 *
 *	This function may be called from IRQ context.
 */
static inline void enable_irq(unsigned int irq)
{
	
	return;
}

/**
 * kthread_create - create a kthread.
 * @threadfn: the function to run until signal_pending(current).
 * @data:     data ptr for @threadfn.
 * @namefmt:  printf-style name for the thread.
 *
 * Description: This helper function creates and names a kernel
 * thread.  The thread will be stopped: use wake_up_process() to start
 * it.  See also kthread_run(), kthread_create_on_cpu().
 *
 * When woken, the thread will run @threadfn() with @data as its
 * argument. @threadfn() can either call do_exit() directly if it is a
 * standalone thread for which noone will call kthread_stop(), or
 * return when 'kthread_should_stop()' is true (which means
 * kthread_stop() has been called).  The return value should be zero
 * or a negative error number; it will be passed to kthread_stop().
 *
 * Returns a task_struct or ERR_PTR(-ENOMEM).
 */
typedef struct task_struct {
	pthread_t           thread;
	pthread_attr_t      attr;
	void               *thread_return;
	s32                 stop;
	s8                  name[64];
}task_struct_t;

static inline struct task_struct *kthread_create(void* (*th)(void *data), void *data, const char name[], ...)
{
	task_struct_t      *t   = (task_struct_t*)kzalloc(sizeof(*t), GFP_KERNEL);
	struct sched_param  param;
	int                 policy;
	pthread_attr_init(&t->attr);
	pthread_getschedparam(pthread_self(), &policy, &param);
	pthread_attr_setinheritsched(&t->attr, PTHREAD_EXPLICIT_SCHED);
#if 1
	const char  *str = NULL;
	if((str = strstr(name, "SCHED_"))) {
		if((str = strstr(name, "RR"))) {
			policy = SCHED_RR;
		} else if((str = strstr(name, "FIFO"))) {
			policy = SCHED_FIFO;
		} else if((str = strstr(name, "SPORADIC"))) {
			policy = SCHED_SPORADIC;
		} else {
			//policy = SCHED_NOCHANGE;
		}
	} 
	
	pthread_attr_setschedpolicy(&t->attr, policy);
	if((str = strstr(name, "="))) {
		int priority = 0;
		sscanf(str, "=%d", &priority);
		param.sched_priority = priority;
	}
	__I("policy:%d {%d, %d, %d, %d}, priority:%3d {%d - %d} \n", 
		policy, SCHED_RR, SCHED_FIFO, SCHED_SPORADIC, SCHED_NOCHANGE,
		param.sched_priority,
		sched_get_priority_min(policy),
		sched_get_priority_max(policy));
#endif

	pthread_attr_setschedparam(&t->attr, &param);
	pthread_create(&t->thread, &t->attr, th, data);
	return t;
}


/**
 * kthread_stop - stop a thread created by kthread_create().
 * @k: thread created by kthread_create().
 *
 * Sets kthread_should_stop() for @k to return true, wakes it, and
 * waits for it to exit.  Your threadfn() must not call do_exit()
 * itself if you use this function!  This can also be called after
 * kthread_create() instead of calling wake_up_process(): the thread
 * will exit without calling threadfn().
 *
 * Returns the result of threadfn(), or %-EINTR if wake_up_process()
 * was never called.
 */
static inline int kthread_stop(struct task_struct *k)
{
	/* send stop signal */
	k->stop = 1;
	
	pthread_join(k->thread, &k->thread_return);

	kfree(k);
	return 0;
}

typedef struct shmem_list {
	void *vaddr;
	u32   size;
	char  name[32];
} shmem_list_t;

static shmem_list_t shmem_list[8] = {{0}};
static inline void* shmem_open(char *name, int size)
{
    int fd = shm_open(name, O_RDWR | O_CREAT, S_IRWXU);
    if(fd == -1) {
        __E("error opening the shared memory object '%s': %s\n",
			name, strerror(errno));
        return NULL;
    }
    ftruncate(fd, size);
    void *shmem = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED,
				 fd, 0);
    close(fd);

	//s32 i;
    u32 i;
	for(i = 0; i < ARRAY_SIZE(shmem_list); i++) {
		if(shmem_list[i].vaddr == 0) {
			shmem_list[i].vaddr = shmem;
			shmem_list[i].size  = size;
			strncpy(shmem_list[i].name, name,
					sizeof(shmem_list[i].name));
			break;
		}
	}
	
	return shmem;
}

static inline int shmem_close(void *shmem)
{
	char *name;
	int   size;

	//s32 i;
	u32 i;
	for(i = 0; i < ARRAY_SIZE(shmem_list); i++) {
		if(shmem_list[i].vaddr == shmem) {
			size = shmem_list[i].size;
			name = shmem_list[i].name;
			shmem_list[i].vaddr = 0;
			break;
		}
	}
	
    munmap(shmem, size);
    shm_unlink(name);
	return 0;
}


static inline s32 mem_buffer_copy_execute(buffer_t *s, buffer_t *d)
{
	s32 i;
	
	for(i = 0; i < s->h; i++) {
		u8 *s_l = ((u8*)s->vaddr) + s->stride * i;
		u8 *d_l = ((u8*)d->vaddr) + d->stride * i;
		memcpy(d_l, s_l, s->w*2);
	}
	
	return 0;
}

static inline s32 buffer_copy_execute(buffer_t *s, buffer_t *d)
{
	return mem_buffer_copy_execute(s, d);
}


typedef struct timer_list {
	u32    sec;
	u32    expire;				/* expire = jiffies + sec * HZ */
	void (*function)(int, siginfo_t*, void*);
	void*  data;
} timer_list_t;

static inline void timer_set(long sec, void (*fn)(int, siginfo_t*, void*))
{
	//long              sec = 1;	/* 1 sec */
	struct sigaction  act;
	timer_t           timerid;
	struct itimerspec value;

	act.sa_flags     = SA_SIGINFO;
	act.sa_sigaction = fn;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, NULL);

	timer_create(CLOCK_REALTIME, NULL, &timerid);
	value.it_interval.tv_sec  = sec;
	value.it_interval.tv_nsec = 0;
	value.it_value = value.it_interval;
	timer_settime(timerid, 0, &value, NULL);
}


static inline void setup_timer(struct timer_list *timer,
				 void (*function)(int, siginfo_t*, void*),
				 void* data)
{
	memset(timer, 0, sizeof(*timer));
	timer->function = function;
	timer->data     = data;
}

/**
 * add_timer - start a timer
 * @timer: the timer to be added
 *
 * The kernel will do a ->function(->data) callback from the
 * timer interrupt at the ->expires point in the future. The
 * current time is 'jiffies'.
 *
 * The timer's ->expires, ->function (and if the handler uses it, ->data)
 * fields must be set prior calling this function.
 *
 * Timers with an ->expires field in the past will be executed in the next
 * timer tick.
 */
static inline void add_timer(struct timer_list *timer)
{
	if(timer->sec && timer->function) {
		timer_set(timer->sec, timer->function);
	}
}




#ifdef __cplusplus
}
#endif


#endif	/* __OSAL_H__ */
