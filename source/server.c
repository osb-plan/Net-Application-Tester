
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

#include <semaphore.h>

#include <unistd.h>
#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)

// External Libraries
#include <libxml/xmlversion.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlstring.h>
#include <libxml/tree.h>

// Application Specific Header
#include "data_defs.h"
#include "bsp.h"
#include "xmlHandle.h"
#include "core_func_ptr.h"

#define FL  fflush(stdout);

FILE *fptr_log, *fptr_dictionary;
int comm_fd;
int global_verbose_level;
char buff_print[100];

FIELD parser_field_ll;
uint32_t n_fields_parsed = 0;
uint32_t pseudo_packet_byte_len = 0;

char* pseudo_packet;

PACKET_BUILDER *pck_builder;
uint32_t exit_thread_called = 0;

sem_t sem_packet;

STRUCT_DESCRIPTION dict_description[MAX_STRUCT_DESCRIPTION];
unsigned int idx_dict_description = 0;

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

void *internal_timer(void *data) {
    FIELD* this_field = ((CHARACTERISTICS_THREAD *) data)->field;
    uint32_t idx = ((CHARACTERISTICS_THREAD *) data)->id_field;

    /* Extract offset */
    uint32_t cnt = 0;
    uint32_t offset;
    FIELD * field = dict_description[0].first_field;

    /* Retrieve field offset*/
    for (cnt = 0; field; field = field->next, cnt++) {
        offset += convert_field_type_byte(field->field_info.field_type);
        if (cnt == idx)
            break;
    }

    float ret_value = 0;

    switch (this_field->field_info.variation->var_type) {
        case(SWAP):
            ret_value = _swap_func(this_field, idx);
            break;
        case(BINARY):
            ret_value = _binary_func(this_field, idx);
            break;
        case(FIXED):
            ret_value = _fixed_func(this_field, idx);
            break;
    }

    printf("Starting Thread num %u\n", (unsigned int) gettid());

    while (!exit_thread_called) {

        usleep(1000 * this_field->field_info.field_repeat_time);
        printf("Thread[%d] sleep for %u ms\n"
                , (unsigned int) gettid()
                , this_field->field_info.field_repeat_time);

        char *pseudo_packet_tmp = malloc(pseudo_packet_byte_len);
        printf("Thread[%d] waiting on semaphore\n", (unsigned int) gettid());
        sem_wait(&sem_packet);
        *(pseudo_packet + offset) = ret_value;
        memcpy(pseudo_packet_tmp, pseudo_packet, pseudo_packet_byte_len);
        sem_post(&sem_packet);

        send(comm_fd, pseudo_packet, pseudo_packet_byte_len, 0);

        free(pseudo_packet_tmp);
    }
    printf("Thread field[%d] Exit!", (unsigned int) pthread_self());

    /* call the cb to inform the user time is out */
    //(*function_pointer)();

    pthread_exit(NULL);
}

//void send_packet(unsigned int fd, )

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
                /* TODO fare parsing dell'IP e della porta */
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
    FL;
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

    /* Now Packet Builder is filled */
    memset(pseudo_packet, 0, pseudo_packet_byte_len);

    /* Fare la connessione */
    while (1) {
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
        unsigned int err = 0;
        if (0 != (err = sem_init(&sem_packet, 0, 1))) {
            printf("Unable to init Semaphore! Error = %u", err);
            plog("Unable to init Semaphore! Error = %d", err, 1);
        }
        FL;


        while (1) {
            char *str_ = "pippo\n";
            bzero(buffer, 1024);
            int flag = 0;
            // Receive in blocking mode a packet        
            /*int n = recv(comm_fd, buffer, sizeof (MSGIN_PACKET), 0);
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
                    tot_len_received += n;
                }

            } else */
            {
                /* Start thread to test app */
                uint32_t idx = 0;
                FIELD *actual_field;

                pthread_t * list_of_spaned_threads[n_fields_parsed];
                for (actual_field = dict_description[0].first_field;
                        actual_field;
                        actual_field = actual_field->next) 
                {
                    pthread_t *mthread = malloc(sizeof (pthread_t));

                    CHARACTERISTICS_THREAD * ch_thread = 
                            malloc(sizeof(CHARACTERISTICS_THREAD));
                    ch_thread->id_field = idx;
                    ch_thread->field = actual_field;

                    /* build the thread info */
                    pthread_create(mthread,
                            NULL,
                            internal_timer,
                            (void *) ch_thread);
                    list_of_spaned_threads[idx] = mthread;
                    idx++;
                }

                for (idx = 0; idx < n_fields_parsed; idx++) {
                    if (!pthread_join(*list_of_spaned_threads[idx], NULL));
                    printf("Thread[%u] joined\n", idx);
                    FL;
                }
            }
        }
        usleep(2000000);
    }
    return EXIT_SUCCESS;
}












