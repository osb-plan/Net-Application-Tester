#ifndef BSP_H
#define BSP_H

#ifdef __cplusplus
extern "C" {
#endif

/* timestamp suppot */
char* timestamp();

/* Function to log on file */
void plog(char *str, int verbose_level, int whocall);

void SIGINThandler(int);

#define MAX_STRUCT_DESCRIPTION

typedef enum{
    INFO = 0,
    DEBUG1,
    DEBUG2,
    TRACE
} PLOG_LEVEL;

#ifdef __cplusplus
}
#endif

#endif /* BSP_H */

