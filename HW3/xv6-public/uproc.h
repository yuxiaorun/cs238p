struct uproc{
	uint pid;
	uint parent_pid;
	uint size;
	char name[16];
	void *chan; 
	int killed;	
};
