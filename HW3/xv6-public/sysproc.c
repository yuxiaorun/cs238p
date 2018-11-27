#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

if(argint(0, &n) < 0)
return -1;
acquire(&tickslock);
ticks0 = ticks;
while(ticks - ticks0 < n){
if(myproc()->killed){
release(&tickslock);
return -1;
}
sleep(&ticks, &tickslock);
}
release(&tickslock);
return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
uint xticks;

acquire(&tickslock);
xticks = ticks;
release(&tickslock);
return xticks;
}

int
sys_backtrace(void)
{
	uint eax, ebx, ecx, edx, eip, ebp, esp, ret;
	uint last_ebp; 
	eax=myproc()->tf->eax;
	ebx=myproc()->tf->ebx;
	ecx=myproc()->tf->ecx;
	edx=myproc()->tf->edx;
	eip=myproc()->tf->eip;
	esp=myproc()->tf->esp;
	ebp=myproc()->tf->ebp;
	cprintf("eax:0x%x\n", eax);
	cprintf("ebx:0x%x\n", ebx);
	cprintf("ecx:0x%x\n", ecx);
	cprintf("edx:0x%x\n", edx);
	cprintf("eip:0x%x\n", eip);
	cprintf("esp:0x%x\n", esp);
	cprintf("ebp:0x%x\n", ebp);
	int i=0;
	while(1){
		last_ebp=*(uint*)ebp;
		ret=*(uint*)(ebp+4);
		cprintf("#%d:   0x%x\n", i, ret);
		if(ret == 0xffffffff )break;
		ebp=last_ebp;
		i++;
}
	return eax; 

}































