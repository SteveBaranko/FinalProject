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
		nums[i] = (void*) malloc(6*sizeof(char));
	y = 0;
	int pnum;
	void* ppt;
	void* empty = malloc(2*sizeof(char));

	mask = (unsigned long long) -1;
	fprintf(stdout,"biggest number in hex %x\n",mask);

	system("clear");
	while (1)	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

		// READ in 6 Bytes from the Mouse 
		fread((void*)nums[cnt],1,6,stdin);
		mask = 0x80;
		ppt = (void*)(4 + (char*) nums[cnt]);
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

		system("clear");

		// print the Mouse Location
		mask = 0xFF;
		ppt = (void*)(4+ (char*) nums[cnt]);
		pnum = (unsigned long long) mask & *(unsigned long long*)ppt;
		if (pnum < 128) {
			fprintf(stdout,"Mouse X: %u\n",pnum);
			ppt = (void*)(5+ (char*) nums[cnt]);
			pnum = (unsigned long long) mask & *(unsigned long long*)ppt;
			fprintf(stdout,"Mouse Y: %u\n",pnum);
		} else {
			fprintf(stdout,"OUT OF RANGE\n");
		}

		cnt++;
		if (cnt > 90) break;
	}

	fprintf(stdout,"\033[?1000l");
	//system("reset");
	return 0;
}
