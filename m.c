#include <signal.h>
struct ss
{
	int b;
};

typedef struct s_struct
{
	int a;
	const char * str;
	struct ss	sss;
} t_struct;

 char *dbg(char ab)

{
	static a = 0;
	a = ab;
	return (&a);}

int func()
{
	int *a = 2;
	*a = 2;
	if (1)
		return 1;
	return 0;
}

void se(int sig)
{
	printf("yolo");
}

int main()
{
	t_struct	ms;

	signal(SIGSEGV, se);
	ms.a = 5;
	ms.str = "bonjour";
	ms.sss.b = 3;
func();
}
