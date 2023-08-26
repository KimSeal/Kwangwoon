#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional or bidirectional
   data transfer protocols (from A to B. Bidirectional transfer of data
   is for extra credit and is not required).  Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
     (although some can be lost).
**********************************************************************/

#define BIDIRECTIONAL 1    /* change to 1 if you're doing extra credit */
                           /* and write a routine called B_output */

/* a "msg" is the data unit passed from layer 5 (teachers code) to layer  */
/* 4 (students' code).  It contains the data (characters) to be delivered */
/* to layer 5 via the students transport level protocol entities.         */
struct msg {
  char data[20];
  };

/* a packet is the data unit passed from layer 4 (students code) to layer */
/* 3 (teachers code).  Note the pre-defined packet structure, which all   */
/* students must follow. */
struct pkt {
   int seqnum;
   int acknum;
   int checksum;
   char payload[20];
    };

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
#define BUFFSIZE 64
#define WINSIZE 8

struct Element1 { //element to save A data
    int base;           //variable to express base
    int next_seqnum;    //variable to express next seq num
    int exp_seqnum;     //variable to express expect seq num
    int buffend;        //buff elements size
    int ACKstate;       //ack state
    int ACKnum;         //variable to send ack at function out
}A;
struct pkt A_BUFF[BUFFSIZE];//save packets about A out

struct Element2 { //element to save B data
    int base;           //variable to express base
    int next_seqnum;    //variable to express next seq num
    int exp_seqnum;     //variable to express expect seq num
    int buffend;        //buff elements size
    int ACKstate;       //ack state
    int ACKnum;         //variable to send ack at function out
}B;
struct pkt B_BUFF[BUFFSIZE];//save packets about B out

unsigned short checksum(struct pkt packet) {//check sum(16bit)
    int checksum = packet.seqnum + packet.acknum +packet.checksum;
    //add all elements
    for (int i = 0; i < 10; i++) {
        checksum += ((int)packet.payload[2 * i]) * 256 + packet.payload[2 * i + 1];
    }
    //change 2 words to 16 bit and add them
     return ~((unsigned short)(checksum + checksum / 65536));
     //use 1's complement and wrap around carry
}
/* called from layer 5, passed the data to be sent to other side */
A_output(message)
  struct msg message;
{
    if (A.next_seqnum < A.base + WINSIZE && A.buffend < BUFFSIZE) {
        //if we can take output more(buff check and distance between base and next seqnum)
        struct pkt packet; //
        packet.seqnum = A.next_seqnum;
        packet.acknum = 999;
        packet.checksum = 0;
        //packet acknum is 999 when state=0
        if (A.ACKstate == 1) {
            packet.acknum = A.ACKnum;
            //when state = 1, check ack to ACKnum
        }
        for (int i = 0; i < 20;i++) {
            packet.payload[i] = message.data[i];
        }
        packet.checksum = checksum(packet);
        //make checksum
        A_BUFF[A.buffend] = packet;
        //put packet to buf
        for (int i = 0; i < 20; i++) {
            A_BUFF[A.buffend].payload[i] = packet.payload[i];
        }
        //put packet's payload in buff
        A.buffend += 1;
        //number of buffer element ++
        printf("A_output: send packet(seq=%d) :", packet.seqnum);
        for (int i = 0; i < 20; i++) {
            printf("%c", packet.payload[i]);
        }
        printf("\n");
        //printf format about A_output
        if (A.ACKstate == 1) {//if we need to send ACK
            printf("A_output: send ACK(ack=%d)\n", packet.acknum);
            //print format about ack
        }
        tolayer3(0, packet);
        //send packet through layer3 to B
        if (A.base == A.next_seqnum) {
            printf("A_output : start timer\n");
            starttimer(0, 10.0);
        }
        //if base equals next seqnum, start timer
        A.next_seqnum += 1;
        A.ACKstate = 0;
        //next seqnum add and change to ack state;
    }
    else {
        printf("A_output : Buffer is full. Drop the message\n");
        //if buffer is full
    }
}

B_output(message)  /* need be completed only for extra credit */
  struct msg message;
{
    if (B.next_seqnum < B.base + WINSIZE && B.buffend < BUFFSIZE) {
        //if we can take output more(buff check and distance between base and next seqnum)
        struct pkt packet;
        packet.seqnum = B.next_seqnum;
        packet.acknum = 999;
        packet.checksum = 0;
        //packet acknum is 999 when state=0
        if (B.ACKstate==1) {
            packet.acknum = B.ACKnum;
            //when state = 1, check ack to ACKnum
        }
        for (int i = 0; i < 20; i++) {
            packet.payload[i] = message.data[i];
        }
        packet.checksum = checksum(packet);
        //make checksum
        B_BUFF[B.buffend] = packet;
        //put packet to buf
        for (int i = 0; i < 20; i++) {
            B_BUFF[B.buffend].payload[i] = packet.payload[i];
        }
        //put packet's payload in buff
        B.buffend += 1;
        //number of buffer element ++
        printf("B_output: send packet(seq=%d) :", packet.seqnum);
        //print format about seq
        for (int i = 0; i < 20; i++) {
            printf("%c", packet.payload[i]);
        }
        printf("\n");
        if (B.ACKstate == 1) {
            printf("B_output: send ACK(ack=%d)\n", packet.acknum);
        }
        //if state == 1, send ACK in packet too
        tolayer3(1, packet);
        //send packet to A
        if (B.base == B.next_seqnum) {
            printf("B_output : start timer\n");
            starttimer(1, 10.0);
        }
        //if base equals next seqnum, start timer
        B.next_seqnum += 1;
        B.ACKstate = 0;
        //next seqnum add and change to ack state;
    }
    else {
        printf("B_output : Buffer is full. Drop the message");
    }
}

/* called from layer 3, when a packet arrives for layer 4 */
A_input(packet)
  struct pkt packet;
{
    unsigned short check = checksum(packet);
    A.ACKstate = 1;
    //when take packet, change state 
    if (check!=0) {
        printf("A_input : Packet corrupted. Drop. \n");
    }
    //if packet is corrupted
    else {
        if (A.next_seqnum - A.base >= BUFFSIZE) {
            printf("A_input: Buffer is full. Drop the message.\n");
            
            return;
        }
        //if buffer is full, drop message
        else if (A.exp_seqnum != packet.seqnum) {
            printf("A_input : not the expected seq. send NAK (ack= %d)\n", A.ACKnum);
        }
        //when we take no expect num, print format
        else if (A.exp_seqnum == packet.seqnum) {
            //if expect seqnum equals packet's seqnum
            printf("A_input : recv.packet (seq = %d) : ", packet.seqnum);
            for (int i = 0; i < 20; i++) {
                printf("%c", packet.payload[i]);
            }
            printf("\n");
            //print format
            tolayer5(0, packet.payload);
            //save payload
            A.ACKnum = A.exp_seqnum;
            A.exp_seqnum++;
            //expect num change
        }
        if (packet.acknum != 999) {
            //if packet have ack
            if (A.base > packet.acknum) {//when base is larger than ack
                printf("A_input : got NAK(ack = %d) Drop.\n", A.base);
                //drop message
            }
            else {
                printf("A_input : got ACK(ack = %d)\n", packet.acknum);
                A.base = packet.acknum + 1;
                //base move to ack's next
                stoptimer(0);
                //stop timer
                if (A.base == A.next_seqnum) {
                     printf("A_input : stoptimer.\n");
                }
                else {
                    printf("A_input: starttimer. \n");
                    starttimer(0, 10.0);
                    //restart timer
                }
            }
        }
    }
}

/* called when A's timer goes off */
A_timerinterrupt()
{
    starttimer(0, 10.0);//start timer to resend
    for (int i = A.base; i < A.next_seqnum; i++) {
        printf("A_timerinterrupt : resend packet (seq = %d) :", A_BUFF[i].seqnum);
        for (int j = 0; j < 20; j++) {
            printf("%c", A_BUFF[i].payload[j]);//printf data
        }
        printf("\n");
        tolayer3(1, A_BUFF[i]);//resend packet using buffer
    }
}  

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
A_init()
{
    A.base = 1;         //start base, expect seq number is 1
    A.exp_seqnum = 1;
    A.next_seqnum = 1; //next seq number, and buffer is 1
    A.buffend = 1;
    A.ACKstate = 0;     //ack state is 0 to set ack=999
    A.ACKnum = 0;       //ack num is 0
}


/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
B_input(packet)
  struct pkt packet;
{
    unsigned short check = checksum(packet);
    B.ACKstate = 1;
    //when take packet, change state 
    if (check!=0) {
        printf("B_input : Packet corrupted. Drop. \n");
    }
    //if packet is corrupted
    else {
        if (B.next_seqnum - B.base >= BUFFSIZE) {
            printf("B_input: Buffer is full. Drop the message.\n");
            return;
        }
        //if buffer is full, drop message
        else if (B.exp_seqnum != packet.seqnum) {
            printf("B_input : not the expected seq. send NAK (ack= %d)\n", B.ACKnum);
        }
        //when we take no expect num, print format
        else if (B.exp_seqnum == packet.seqnum) {
            //if expect seqnum equals packet's seqnum
            
            printf("B_input : recv.packet (seq = %d) : ", packet.seqnum);
            for (int i = 0; i < 20; i++) {
                printf("%c", packet.payload[i]);
            }
            printf("\n");
            //print format
            tolayer5(1, packet.payload);
            //save payload
            B.ACKnum = B.exp_seqnum;
            B.exp_seqnum++;
            //add expect seq num
        }

       if (packet.acknum != 999) {
           //when we take ack
            if (B.base > packet.acknum) {
                 printf("B_input : got NAK(ack = %d) Drop\n", B.base);
                 //drop message
            }
            else {
                printf("B_input : got ACK(ack = %d)\n", packet.acknum);
                B.ACKstate = 1;//change state
                stoptimer(1);
                //stop timer
                B.base = packet.acknum + 1;
                //base move to ack's next
                if (B.base == B.next_seqnum) {
                   printf("B_input : stoptimer.\n");
                }
                else {
                    printf("B_input: starttimer. \n");
                    starttimer(1, 10.0);
                    //restart timer
                }
            }
        }
    }
}

/* called when B's timer goes off */
B_timerinterrupt()
{
    starttimer(1, 10.0);//start timer to resend
    for (int i = B.base; i < B.next_seqnum;i++) {
        printf("B_timerinterrupt : resend packet (seq = %d) :", B_BUFF[i].seqnum);
        for (int j = 0; j < 20; j++) {
            printf("%c", B_BUFF[i].payload[j]);//print data
        }
        printf("\n");
        tolayer3(1, B_BUFF[i]);//resend packet using buffer
    }
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
B_init()
{
    B.base = 1;         //start base, expect seq number is 1
    B.exp_seqnum = 1;
    B.next_seqnum = 1;  //next seq number, and buffer is 1
    B.buffend = 1;
    B.ACKstate = 0;     //ack state is 0 to set ack =999
    B.ACKnum = 0;       //ack num is 0
}


/*****************************************************************
***************** NETWORK EMULATION CODE STARTS BELOW ***********
The code below emulates the layer 3 and below network environment:
  - emulates the tranmission and delivery (possibly with bit-level corruption
    and packet loss) of packets across the layer 3/4 interface
  - handles the starting/stopping of a timer, and generates timer
    interrupts (resulting in calling students timer handler).
  - generates message to be sent (passed from later 5 to 4)

THERE IS NOT REASON THAT ANY STUDENT SHOULD HAVE TO READ OR UNDERSTAND
THE CODE BELOW.  YOU SHOLD NOT TOUCH, OR REFERENCE (in your code) ANY
OF THE DATA STRUCTURES BELOW.  If you're interested in how I designed
the emulator, you're welcome to look at the code - but again, you should have
to, and you defeinitely should not have to modify
******************************************************************/

struct event {
   float evtime;           /* event time */
   int evtype;             /* event type code */
   int eventity;           /* entity where event occurs */
   struct pkt *pktptr;     /* ptr to packet (if any) assoc w/ this event */
   struct event *prev;
   struct event *next;
 };
struct event *evlist = NULL;   /* the event list */

/* possible events: */
#define  TIMER_INTERRUPT 0  
#define  FROM_LAYER5     1
#define  FROM_LAYER3     2

#define  OFF             0
#define  ON              1
#define   A    0
#define   B    1



int TRACE = 1;             /* for my debugging */
int nsim = 0;              /* number of messages from 5 to 4 so far */ 
int nsimmax = 0;           /* number of msgs to generate, then stop */
float time = 0.000;
float lossprob;            /* probability that a packet is dropped  */
float corruptprob;         /* probability that one bit is packet is flipped */
float lambda;              /* arrival rate of messages from layer 5 */   
int   ntolayer3;           /* number sent into layer 3 */
int   nlost;               /* number lost in media */
int ncorrupt;              /* number corrupted by media*/

main()
{
   struct event *eventptr;
   struct msg  msg2give;
   struct pkt  pkt2give;
   
   int i,j;
   char c; 
  
   init();
   A_init();
   B_init();
   
   while (1) {
        eventptr = evlist;            /* get next event to simulate */
        if (eventptr==NULL)
           goto terminate;
        evlist = evlist->next;        /* remove this event from event list */
        if (evlist!=NULL)
           evlist->prev=NULL;
        if (TRACE>=2) {
           printf("\nEVENT time: %f,",eventptr->evtime);
           printf("  type: %d",eventptr->evtype);
           if (eventptr->evtype==0)
	       printf(", timerinterrupt  ");
             else if (eventptr->evtype==1)
               printf(", fromlayer5 ");
             else
	     printf(", fromlayer3 ");
           printf(" entity: %d\n",eventptr->eventity);
           }
        time = eventptr->evtime;        /* update time to next event time */
        if (nsim==nsimmax)
	  break;                        /* all done with simulation */
        if (eventptr->evtype == FROM_LAYER5 ) {
            generate_next_arrival();   /* set up future arrival */
            /* fill in msg to give with string of same letter */    
            j = nsim % 26; 
            for (i=0; i<20; i++)  
               msg2give.data[i] = 97 + j;
            if (TRACE>2) {
               printf("          MAINLOOP: data given to student: ");
                 for (i=0; i<20; i++) 
                  printf("%c", msg2give.data[i]);
               printf("\n");
	     }
            nsim++;
            if (eventptr->eventity == A) 
               A_output(msg2give);  
             else
               B_output(msg2give);  
            }
          else if (eventptr->evtype ==  FROM_LAYER3) {
            pkt2give.seqnum = eventptr->pktptr->seqnum;
            pkt2give.acknum = eventptr->pktptr->acknum;
            pkt2give.checksum = eventptr->pktptr->checksum;
            for (i=0; i<20; i++)  
                pkt2give.payload[i] = eventptr->pktptr->payload[i];
	    if (eventptr->eventity ==A)      /* deliver packet by calling */
   	       A_input(pkt2give);            /* appropriate entity */
            else
   	       B_input(pkt2give);
	    free(eventptr->pktptr);          /* free the memory for packet */
            }
          else if (eventptr->evtype ==  TIMER_INTERRUPT) {
            if (eventptr->eventity == A) 
	       A_timerinterrupt();
             else
	       B_timerinterrupt();
             }
          else  {
	     printf("INTERNAL PANIC: unknown event type \n");
             }
        free(eventptr);
        }

terminate:
   printf(" Simulator terminated at time %f\n after sending %d msgs from layer5\n",time,nsim);
}



init()                         /* initialize the simulator */
{
  int i;
  float sum, avg;
  float jimsrand();
  
  
   printf("-----  Stop and Wait Network Simulator Version 1.1 -------- \n\n");
   printf("Enter the number of messages to simulate: ");
   scanf("%d",&nsimmax);
   printf("Enter  packet loss probability [enter 0.0 for no loss]:");
   scanf("%f",&lossprob);
   printf("Enter packet corruption probability [0.0 for no corruption]:");
   scanf("%f",&corruptprob);
   printf("Enter average time between messages from sender's layer5 [ > 0.0]:");
   scanf("%f",&lambda);
   printf("Enter TRACE:");
   scanf("%d",&TRACE);

   srand(9999);              /* init random number generator */
   sum = 0.0;                /* test random number generator for students */
   for (i=0; i<1000; i++)
      sum=sum+jimsrand();    /* jimsrand() should be uniform in [0,1] */
   avg = sum/1000.0;
   if (avg < 0.25 || avg > 0.75) {
    printf("It is likely that random number generation on your machine\n" ); 
    printf("is different from what this emulator expects.  Please take\n");
    printf("a look at the routine jimsrand() in the emulator code. Sorry. \n");
    exit();
    }

   ntolayer3 = 0;
   nlost = 0;
   ncorrupt = 0;

   time=0.0;                    /* initialize time to 0.0 */
   generate_next_arrival();     /* initialize event list */
}

/****************************************************************************/
/* jimsrand(): return a float in range [0,1].  The routine below is used to */
/* isolate all random number generation in one location.  We assume that the*/
/* system-supplied rand() function return an int in therange [0,mmm]        */
/****************************************************************************/
float jimsrand() 
{
  double mmm = 32767;   /* largest int  - MACHINE DEPENDENT!!!!!!!!   */
  float x;                   /* individual students may need to change mmm */ 
  x = rand()/mmm;            /* x should be uniform in [0,1] */
  return(x);
}  

/********************* EVENT HANDLINE ROUTINES *******/
/*  The next set of routines handle the event list   */
/*****************************************************/
 
generate_next_arrival()
{
   double x,log(),ceil();
   struct event *evptr;
    char *malloc();
   float ttime;
   int tempint;

   if (TRACE>2)
       printf("          GENERATE NEXT ARRIVAL: creating new arrival\n");
 
   x = lambda*jimsrand()*2;  /* x is uniform on [0,2*lambda] */
                             /* having mean of lambda        */
   evptr = (struct event *)malloc(sizeof(struct event));
   evptr->evtime =  time + x;
   evptr->evtype =  FROM_LAYER5;
   if (BIDIRECTIONAL && (jimsrand()>0.5) )
      evptr->eventity = B;
    else
      evptr->eventity = A;
   insertevent(evptr);
} 


insertevent(p)
   struct event *p;
{
   struct event *q,*qold;

   if (TRACE>2) {
      printf("            INSERTEVENT: time is %lf\n",time);
      printf("            INSERTEVENT: future time will be %lf\n",p->evtime); 
      }
   q = evlist;     /* q points to header of list in which p struct inserted */
   if (q==NULL) {   /* list is empty */
        evlist=p;
        p->next=NULL;
        p->prev=NULL;
        }
     else {
        for (qold = q; q !=NULL && p->evtime > q->evtime; q=q->next)
              qold=q; 
        if (q==NULL) {   /* end of list */
             qold->next = p;
             p->prev = qold;
             p->next = NULL;
             }
           else if (q==evlist) { /* front of list */
             p->next=evlist;
             p->prev=NULL;
             p->next->prev=p;
             evlist = p;
             }
           else {     /* middle of list */
             p->next=q;
             p->prev=q->prev;
             q->prev->next=p;
             q->prev=p;
             }
         }
}

printevlist()
{
  struct event *q;
  int i;
  printf("--------------\nEvent List Follows:\n");
  for(q = evlist; q!=NULL; q=q->next) {
    printf("Event time: %f, type: %d entity: %d\n",q->evtime,q->evtype,q->eventity);
    }
  printf("--------------\n");
}



/********************** Student-callable ROUTINES ***********************/

/* called by students routine to cancel a previously-started timer */
stoptimer(AorB)
int AorB;  /* A or B is trying to stop timer */
{
 struct event *q,*qold;

 if (TRACE>2)
    printf("          STOP TIMER: stopping timer at %f\n",time);
/* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
 for (q=evlist; q!=NULL ; q = q->next) 
    if ( (q->evtype==TIMER_INTERRUPT  && q->eventity==AorB) ) { 
       /* remove this event */
       if (q->next==NULL && q->prev==NULL)
             evlist=NULL;         /* remove first and only event on list */
          else if (q->next==NULL) /* end of list - there is one in front */
             q->prev->next = NULL;
          else if (q==evlist) { /* front of list - there must be event after */
             q->next->prev=NULL;
             evlist = q->next;
             }
           else {     /* middle of list */
             q->next->prev = q->prev;
             q->prev->next =  q->next;
             }
       free(q);
       return;
     }
  printf("Warning: unable to cancel your timer. It wasn't running.\n");
}


starttimer(AorB,increment)
int AorB;  /* A or B is trying to stop timer */
float increment;
{

 struct event *q;
 struct event *evptr;
 char *malloc();

 if (TRACE>2)
    printf("          START TIMER: starting timer at %f\n",time);
 /* be nice: check to see if timer is already started, if so, then  warn */
/* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next)  */
   for (q=evlist; q!=NULL ; q = q->next)  
    if ( (q->evtype==TIMER_INTERRUPT  && q->eventity==AorB) ) { 
      printf("Warning: attempt to start a timer that is already started\n");
      return;
      }
 
/* create future event for when timer goes off */
   evptr = (struct event *)malloc(sizeof(struct event));
   evptr->evtime =  time + increment;
   evptr->evtype =  TIMER_INTERRUPT;
   evptr->eventity = AorB;
   insertevent(evptr);
} 


/************************** TOLAYER3 ***************/
tolayer3(AorB,packet)
int AorB;  /* A or B is trying to stop timer */
struct pkt packet;
{
 struct pkt *mypktptr;
 struct event *evptr,*q;
 char *malloc();
 float lastime, x, jimsrand();
 int i;


 ntolayer3++;

 /* simulate losses: */
 if (jimsrand() < lossprob)  {
      nlost++;
      if (TRACE>0)    
	printf("          TOLAYER3: packet being lost\n");
      return;
    }  

/* make a copy of the packet student just gave me since he/she may decide */
/* to do something with the packet after we return back to him/her */ 
 mypktptr = (struct pkt *)malloc(sizeof(struct pkt));
 mypktptr->seqnum = packet.seqnum;
 mypktptr->acknum = packet.acknum;
 mypktptr->checksum = packet.checksum;
 for (i=0; i<20; i++)
    mypktptr->payload[i] = packet.payload[i];
 if (TRACE>2)  {
   printf("          TOLAYER3: seq: %d, ack %d, check: %d ", mypktptr->seqnum,
	  mypktptr->acknum,  mypktptr->checksum);
    for (i=0; i<20; i++)
        printf("%c",mypktptr->payload[i]);
    printf("\n");
   }

/* create future event for arrival of packet at the other side */
  evptr = (struct event *)malloc(sizeof(struct event));
  evptr->evtype =  FROM_LAYER3;   /* packet will pop out from layer3 */
  evptr->eventity = (AorB+1) % 2; /* event occurs at other entity */
  evptr->pktptr = mypktptr;       /* save ptr to my copy of packet */
/* finally, compute the arrival time of packet at the other end.
   medium can not reorder, so make sure packet arrives between 1 and 10
   time units after the latest arrival time of packets
   currently in the medium on their way to the destination */
 lastime = time;
/* for (q=evlist; q!=NULL && q->next!=NULL; q = q->next) */
 for (q=evlist; q!=NULL ; q = q->next) 
    if ( (q->evtype==FROM_LAYER3  && q->eventity==evptr->eventity) ) 
      lastime = q->evtime;
 evptr->evtime =  lastime + 1 + 9*jimsrand();
 


 /* simulate corruption: */
 if (jimsrand() < corruptprob)  {
    ncorrupt++;
    if ( (x = jimsrand()) < .75)
       mypktptr->payload[0]='Z';   /* corrupt payload */
      else if (x < .875)
       mypktptr->seqnum = 999999;
      else
       mypktptr->acknum = 999999;
    if (TRACE>0)    
	printf("          TOLAYER3: packet being corrupted\n");
    }  

  if (TRACE>2)  
     printf("          TOLAYER3: scheduling arrival on other side\n");
  insertevent(evptr);
} 

tolayer5(AorB,datasent)
  int AorB;
  char datasent[20];
{
  int i;  
  if (TRACE>2) {
     printf("          TOLAYER5: data received: ");
     for (i=0; i<20; i++)  
        printf("%c",datasent[i]);
     printf("\n");
   }
  
}