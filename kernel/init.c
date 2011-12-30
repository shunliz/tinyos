#include <print.h>
#include <task.h>
#include <x86.h>
#include <mm.h>

void mm_init(void);
void text_init(void);
void int_init(void);
void block_init(void);
void task_init(void);
void fs_init(void);
void pit_init(void);
void keyboard_init(void);
void load_first_program(char *, int, char **);

void kidle(void)
{
	printk("Kernel is idle now\n\n");
	/* Open interrupt */
	sti();
	while (1) {
#ifdef TIMER_INT_SCHED
		hlt();
#else
		schedule();
#endif
	}
}

void load_init(void)
{
	char *argv[] = { "/init", NULL };
	load_first_program("/init", 1, argv);
}

void init(void)
{
	/*
	 * Init video before initing memory.
	 * Assert that video initialization dont need boot_alloc.
	 */
	text_init();
	mm_init();
	int_init();
	task_init();
	block_init();
	fs_init();
	keyboard_init();
#ifdef TIMER_INT_SCHED
	pit_init();
#endif
	load_init();
	kidle();
}
