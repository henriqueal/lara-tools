#include "richards_benchmark.c"

int main()
{
    struct packet *wkq = 0;
    int retval;

    printf("Bench mark starting\n");

    createtask(I_IDLE, 0, wkq, S_RUN, idlefn, 1, Count);

    wkq = pkt(0, 0, K_WORK);
    wkq = pkt(wkq, 0, K_WORK);

    createtask(I_WORK, 1000, wkq, S_WAITPKT, workfn, I_HANDLERA, 0);

    wkq = pkt(0, I_DEVA, K_DEV);
    wkq = pkt(wkq, I_DEVA, K_DEV);
    wkq = pkt(wkq, I_DEVA, K_DEV);

    createtask(I_HANDLERA, 2000, wkq, S_WAITPKT, handlerfn, 0, 0);

    wkq = pkt(0, I_DEVB, K_DEV);
    wkq = pkt(wkq, I_DEVB, K_DEV);
    wkq = pkt(wkq, I_DEVB, K_DEV);

    createtask(I_HANDLERB, 3000, wkq, S_WAITPKT, handlerfn, 0, 0);

    wkq = 0;
    createtask(I_DEVA, 4000, wkq, S_WAIT, devfn, 0, 0);
    createtask(I_DEVB, 5000, wkq, S_WAIT, devfn, 0, 0);

    tcb = tasklist;

    qpktcount = holdcount = 0;

    printf("Starting\n");

    tracing = FALSE;
    layout = 0;

    schedule();

    printf("finished\n");

    printf("qpkt count = %d  holdcount = %d\n",
           qpktcount, holdcount);

    printf("These results are ");
    if (qpktcount == Qpktcountval && holdcount == Holdcountval) {
      printf("correct");
      retval = 0;
    } else {
      printf("incorrect");
      retval = 1;
    }
    
    printf("\nend of run\n");
    return retval;
}

