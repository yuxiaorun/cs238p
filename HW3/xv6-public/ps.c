#include "types.h"
#include "stat.h"
#include "user.h"
#include "uproc.h"
int main(){
	int pnum = 12;
	struct uproc *ps=malloc(pnum*sizeof(struct uproc));
	int num = getprocinfo(pnum, ps);
	printf(1, "%d processes find:\n", num);
	int i=0;
	while(i<num){
		printf(1, "#%d  ",i);
		printf(1, "process id:%d  ",ps[i].pid);
		printf(1, "name: %s  ", ps[i].name);
		printf(1, "parent id: %d  ", ps[i].parent_pid);
		printf(1, "killed: %d\n", ps[i].killed);
		i++;
} 
	exit();
}
