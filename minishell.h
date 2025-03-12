
#define EXEC 1
#define REDIRECT 2
#define PIPE 3
#define LIST 4
#define BACK 5

#define MAXARGS 10   //MAX nbr of arguments we can handle

struct cmd
{
    int type;
};

struct execcmd
{
    int type;
    char *argv[MAXARGS];    //Ptr to start of string
    char *earg[MAXARGS];    //Ptr to end of string to put '\0'
    
};
#endif