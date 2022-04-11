#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>

struct termios orig_termios;

void tty_raw_mode(void)
{
	struct termios tty_attr;

	tcgetattr(0,&tty_attr);

	/* Set raw mode. */
	tty_attr.c_lflag &= (~(ICANON|ECHO));
	tty_attr.c_cc[VTIME] = 0;
	tty_attr.c_cc[VMIN] = 1;

	tcsetattr(0,TCSANOW,&tty_attr);
}

void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() 
{
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO|ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void sig_handler(int signum)
{
	fprintf(stdout,"\033[?1000l");
	//fprintf(stdout,"\033[?1001l");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{

	signal(SIGINT,sig_handler);

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	enableRawMode();
	fprintf(stdout,"\033[?1000h");
	//fprintf(stdout,"\033[?1001h");

	int y;
	int cnt = 0;
	int i;
	unsigned long long mask;
	void** nums = (void**) malloc(100*sizeof(void*));
	for (i = 0; i < 100; i++)
		nums[i] = (void*) malloc(48);
	y = 0;
	int pnum;
	void* ppt;
	void* empty = malloc(2*sizeof(char));

	mask = (unsigned long long) -1;
	fprintf(stdout,"biggest number in hex %x\n",mask);

	while (1)	{
		system("clear");
		//fprintf(stdout,"\033[0;34m");
		//fprintf(stdout,"%s\n",c);
		//fprintf(stdout,"%x\n",*c);
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		//fprintf(stdout,"lines %d\n", w.ws_row);
		//fprintf(stdout,"columns %d\n", w.ws_col);
		/*
		for (y = 3; y < w.ws_row; y++) {
			write(STDOUT_FILENO, "~\r\n", 3);
		}
		*/
		for (y = 0; y < cnt; y++) {
			ppt = nums[y];
			mask = 0xFF;
			for (i = 0; i < 6; i++) {
				pnum = (unsigned long long) mask & *(unsigned long long*)ppt;
			//	pnum = pnum >> (8*i);
				fprintf(stdout,"%u ",pnum);
				fprintf(stdout,"(mask & - %lx) ",pnum);
			//	mask = (unsigned long long) mask << (unsigned long long) 8;
				//mask = (unsigned long long) 0xFF << (unsigned long long) (i+1)*8;
				ppt = (void*)( 1 + (char*) ppt);
			}
			/*
			ppt = empty;
			for (i = 0; i < 2; i++) {
				pnum = (unsigned long long) mask & *(unsigned long long*)ppt;
			//	pnum = pnum >> (8*i);
				fprintf(stdout,"%u ",pnum);
				fprintf(stdout,"(mask & - %lx) ",pnum);
			//	mask = (unsigned long long) mask << (unsigned long long) 8;
				//mask = (unsigned long long) 0xFF << (unsigned long long) (i+1)*8;
				ppt = (void*)( 1 + (char*) ppt);
			}
			*/
			ppt = nums[y];
			fprintf(stdout,"\n%lx",*(unsigned long long*)ppt);
			fprintf(stdout,"\n-----------------\n");
		}
		//c = fgetc(stdin);
		//fscanf(stdin,"%s",str[cnt]);
		fread((void*)nums[cnt],1,6,stdin);
		mask = 0x80;
		ppt = (void*)(4 + (char*) nums[y]);
		if (mask & *(unsigned long*) ppt) {
			/*
			fread(ppt,1,2,stdin);
			*/
			fread(empty,1,1,stdin);
			//*(char*) ppt = *(char*)(void*)(5 + (char*) nums[y]);
			ppt = (void*)(1 + (char*) empty);
			*(char*) ppt = *(char*)(void*)(5 + (char*) nums[y]);
			ppt = (void*)(5 + (char*) nums[y]);
			fread(ppt,1,1,stdin);
		}
		//fgets(c,100,stdin);
		cnt++;
		if (cnt > 90) break;
	}

	fprintf(stdout,"\033[?1000l");
	//system("reset");
	return 0;
}
