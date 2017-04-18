#include "methcall.c"

int main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 50000000
#else
#define LENGTH 500000000
#endif
    int i, n = ((argc == 2) ? atoi(argv[1]) : LENGTH);
    Toggle *tog;
    NthToggle *ntog;
    char val = true;

    tog = new_Toggle(true);
    for (i=0; i<n; i++) {
	val = tog->activate(tog)->value(tog);
    }
    puts(val ? "true\n" : "false\n");
    DESTROY(tog);
    
    val = true;
    ntog = new_NthToggle(val, 3);
    for (i=0; i<n; i++) {
	val = ntog->activate(ntog)->value(ntog);
    }
    puts(val ? "true\n" : "false\n");
    DESTROY(ntog);
    return 0;
}
