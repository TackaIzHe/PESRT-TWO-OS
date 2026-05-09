#ifndef __ASH_H__
#define __ASH_H__

enum{
    CMD_ECHO = 0,
    CMD_LS   = 1,
    CMD_MKDIR,
    CMD_TOUCH,
    CMD_CAT,
    CMD_PROCEDURE,
    CMD_LSPCI,
    CMD_CGPU,
    CMD_CLEAR,
    CMD_SNAKE,
    CMD_EXIT
};

#define CMDSTR_ECHO      "echo"
#define CMDSTR_LS        "ls"
#define CMDSTR_MKDIR     "mkdir"
#define CMDSTR_TOUCH     "touch"
#define CMDSTR_CAT       "cat"
#define CMDSTR_PROCEDURE "procedure"
#define CMDSTR_LSPCI     "lspci"
#define CMDSTR_CGPU      "cgpu"
#define CMDSTR_CLEAR     "clear"
#define CMDSTR_SNAKE     "snake"
#define CMDSTR_EXIT      "exit"

#define USER_LINE "<PESRT-TWO-OS>[%s] / "

int ash_main(void);
uint32_t main_procedure(uint32_t patern);
int snake_main(void);

#endif