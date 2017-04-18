#include "objinst.c"

int main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 7000000
#else
#define LENGTH 70000000
#endif
    int i, n = ((argc == 2) ? atoi(argv[1]) : LENGTH);
    Toggle *tog;
    NthToggle *ntog;

    tog = new_Toggle(true);
    for (i=0; i<5; i++) {
	puts((tog->activate(tog)->value(tog)) ? "true" : "false");
    }
    DESTROY(tog);
    for (i=0; i<n; i++) {
	tog = new_Toggle(true);
	DESTROY(tog);
    }
    
    puts("");

    ntog = new_NthToggle(true, 3);
    for (i=0; i<8; i++) {
    	const char *Msg;
	if (ntog->base.activate((Toggle*)ntog)->value((Toggle*)ntog))
	  Msg = "true";
	else
	  Msg = "false";
	puts(Msg);
    }
    DESTROY(ntog);
    for (i=0; i<n; i++) {
	ntog = new_NthToggle(true, 3);
	DESTROY(ntog);
    }
    return 0;
}
