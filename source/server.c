
// System Header
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include <stdlib.h>
#include <signal.h>

#include <stdio.h>
#include <ctype.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// External Libraries
#include <libxml/xmlversion.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlstring.h>
#include <libxml/tree.h>

// Application Specific Header
#include "data_defs.h"
#include "bsp.h"
#include "xmlHandle.h"




FILE *fptr_log, *fptr_dictionary;
int comm_fd;
int global_verbose_level;
char buff_print[100];
FIELD parser_field_ll;

void do_sent(PACKET_TYPE msg_type_id) {
    HEADER head;
    MSGIN_PACKET test_packet;

    memset(&head, 0, sizeof (HEADER));
    memset(&test_packet, 0, sizeof (MSGIN_PACKET));

    switch (msg_type_id) {
        case(1):
        {
            plog("Ready to send message", DEBUG2, 1);

        }
            break;

        default:
            printf("Attention default branch in do_sent\n");
            break;


    }
    // Send packet
    //write(comm_fd, (char *) &test_packet, sizeof (MSGIN_PACKET));
    pid_t tid = syscall(SYS_gettid);
    /*snprintf(tosend, 100
            , "%s [%d] %s %d "
            , "THREAD:"
            , tid
            , "message sent code"
            , msg_type_id);
    plog(tosend, DEBUG2, 1);*/
}

void *do_periodic_sent(void *data) {
    /*    TODO ch_th = *(TODO *) data;
        for (;;) {
            do_sent(ch_th.msg_type_id);
            usleep(ch_th.ms_interval * 1000);
        }*/
}

int main(int argc, char *argv[]) {


    // Init libxml
    LIBXML_TEST_VERSION

            char buffer[1024];
    int listen_fd, c;
    char *l_flag = NULL;
    char *d_flag = NULL;
    int v_flag = 0;


    struct sockaddr_in servaddr;

    signal(SIGINT, SIGINThandler);
    int option = 0;


    //Specifying the expected options
    //The two options l and b expect numbers as argument
    while ((option = getopt(argc, argv, "l:v:d:")) != -1) {
        switch (option) {
            case 'l': l_flag = (optarg);
                break;
            case 'v': v_flag = atoi(optarg);
                break;
            case 'd': d_flag = (optarg);
                break;
            default: //print_usage(); 
                exit(EXIT_FAILURE);
        }
    }

    /* Control the input provided */
    if (v_flag > 3) {
        v_flag = 3;
    } else if (v_flag < 0) {
        v_flag = 0;
    }
    global_verbose_level = v_flag;

    if (l_flag != NULL && d_flag != NULL) {
        // Open the log file
        fptr_log = fopen(l_flag, "w+");
        if (fptr_log == NULL) {
            perror("Error: ");
            return (EXIT_FAILURE);
        }

        // Check log file
        struct stat sb;
        if (!stat(l_flag, &sb)) {
            if ((sb.st_mode & S_IFMT) != S_IFREG) {
                return EXIT_FAILURE;
            }
        }


        if (!stat(d_flag, &sb)) {
            if ((sb.st_mode & S_IFMT) != S_IFREG) {
                return EXIT_FAILURE;
            }
        }

    } else {
        printf("ERROR control file logging option and dictionary file!\n");
        return EXIT_FAILURE;
    }

    // TODO Parse xml File

    /* Print Welcome message */
    printf("-----------------------------------------------------------------\n");
    printf("Welcome to Net-Application-Tester VER[%s].\n"
            "Tool for testing custom packet receive on your application.\n", SOFWARE_VERSION);
    printf("-----------------------------------------------------------------\n");
    printf("Option Choosen: \n "
            "\t Log support -> [%s] [file:%s].\n"
            "\t Verbose lvl -> [%s] [%d]. \n"
            "\t Dictionary  -> [%s] [file:%s]. \n"
            , (l_flag != NULL) ? "ON" : "OFF"
            , l_flag
            , (v_flag != 0) ? "ON" : "OFF"
            , v_flag
            , (d_flag != 0) ? "ON" : "OFF"
            , d_flag
            );
    printf("-----------------------------------------------------------------\n");

    plog("Entered the main loop", INFO, 0);

    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(d_flag);

    if (doc == NULL) {
        fprintf(stderr, "Document not parsed successfully. \n");
        return (0);
    }

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return (0);
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) "dictionary")) {
        fprintf(stderr, "document of the wrong type, root node != config");
        cur = cur->xmlChildrenNode;
        xmlFreeDoc(doc);
        return (0);
    }
    //parse_config(doc, cur);
    printf("Ok ready for parsing\n");
    parse_config(doc, cur);


    return 0;

    //pthread_create(&thread, NULL, do_periodic_sent, (void *) &ch_th_pool1[1]);


    while (1) {
        usleep(1000000);
        plog("MAIN LOOP", INFO, 0);
        printf("MAIN LOOP");
        fflush(stdout);
    }
    return EXIT_SUCCESS;


    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof (servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(6178);

    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof (servaddr));
    printf("Bind Done\n");
    listen(listen_fd, 10);
    printf("After List Waiting for connection...\n");
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
    printf("Accepted a Client %d\n", comm_fd);



    uint16_t tot_len_received = 0;

    while (1) {
        char *str_ = "pippo\n";
        bzero(buffer, 1024);
        int flag = 0;
        // Receive in blocking mode a packet        
        int n = recv(comm_fd, buffer, sizeof (MSGIN_PACKET), 0);
        if (n < 0) {
            perror("Problem in receive packet ERROR CODE [0001]");
            return EXIT_FAILURE;
        }
        printf("Received raw msg.\n");

        if (flag == 0) {
            if ((n + tot_len_received) >= sizeof (MSGIN_PACKET)) {
                printf("Msg received \n");
                MSGIN_PACKET *inpack;
                inpack = (MSGIN_PACKET *) buffer;

                // Control if the packet received is ping
                if (inpack->header.type == PING_PACKET_ID) {
                    printf("Msg received PING\n");
                    // exit from this loop and enter in the core application loop
                    flag = 1;
                }
            } else {
                printf("Entered in the core loop\n");

                pthread_t thread;
                CHARACTERISTICS_THREAD ch_th_pool1[1];

                /* Set up a pool of thread for test*/
                ch_th_pool1[0].ms_interval = 250;
                ch_th_pool1[0].msg_type_id = MAIN_A_ID;

                pthread_create(&thread, NULL, do_periodic_sent, (void *) &ch_th_pool1[0]);
                while (1) {
                    printf("Server Alive...\n");
                    usleep(5000000);

                }
            }

        }


        /*        printf("\n Sent Packet header %x %d\n", packet_sent.header, 
                sizeof(packet_sent));
                write(comm_fd, (char *) &packet_sent, sizeof(packet_sent));*/
        usleep(2000000);
    }






}

