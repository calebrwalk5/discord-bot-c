#include <getopt.h>
#include <stdio.h>
#include <libdiscord.h>

const char *MESSAGE = "i am written in C lmao, because i am a dumb hispter";

void print_help(char *executable_name) {
    printf("no help for you xd\n");
}

int main(int argc, char *argv[]) {

    char *bot_token = ;
    char *message = MESSAGE;
    LD_SNOWFLAKE channel = 0;
    unsigned long log_level = 63;

    if(argc == 1) {
        goto HELP;
    }

    while(1) {
        int option_index = 0, c;
        static struct option long_options[] = {
                {"help",      no_argument,       0, 'h'},
                {"log-level", required_argument, 0, 'l'},
                {"channel", required_argument, 0, 'c'},
                {0, 0,                           0, 0}
        };
        c = getopt_long(argc, argv, "ht:l:m:c:", long_options, &option_index);
        if(c == -1) {
            break;
        }
        switch(c) {
            case 'h':
            HELP:
                print_help(argv[0]);
                return 0;
                break;
            case 'l':
                log_level = strtoul(optarg, NULL, 10);
                break;
            case 'c':
                channel = strtoull(optarg, NULL, 10);
                break;
            default:
                return 1;
        }
    }

    if(message == NULL) {
        ld_notice("no message");
        return 0;
    }

    if(channel == 0) {
        ld_notice("you need to pick a channel");
        return 0;
    }

    if(bot_token == NULL) {
        ld_notice("you need a bot token");
        return 0;
    }

    int retv;
    struct ld_context_info info;
    retv = ld_init_context_info(&info);
    if(retv != 0) {
        return 2;
    }

    info.bot_token = bot_token;

    struct ld_context context;
    retv = ld_init_context(&info, &context);
    if(retv != 0) {
        return 3;
    }

    retv = ld_send_basic_message(&context, channel, message);
    if(retv != 0) {
        return 4;
    }
    return 0;
}
