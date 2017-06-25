#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

static const char *ALLOWED_COMMANDS[] =
{
    "-listallnetworkservices",
    "-getwebproxy",
    "-setwebproxy",
    "-setwebproxystate",
    "-getsecurewebproxy",
    "-setsecurewebproxy",
    "-setsecurewebproxystate",
    "-getautoproxyurl",
    "-setautoproxyurl",
    "-setautoproxystate",
    "-getproxybypassdomains",
    "-setproxybypassdomains",
    "-help",
    "-printcommands",
    "END_OF_LIST" // always keep this at the end
};

int main (int argc, char **argv)
{
    // Check parameters
    if (argc > 1)
    {
        char *subCmd = argv[1];
        int cmdAllowed = 0;
        for (int i = 0; i < INT_MAX; i++)
        {
            const char *allowedCmd = ALLOWED_COMMANDS[i];
            if (strcmp(allowedCmd, "END_OF_LIST") == 0)
            {
                break;
            }
            else
            {
                if (strcmp(subCmd, allowedCmd) == 0)
                {
                    cmdAllowed = 1;
                    break;
                }
            }
        }
        if (!cmdAllowed)
        {
            fprintf(stderr, "Command %s not allowed", subCmd);
            return EXIT_FAILURE;
        }
    }

    // Build our command
    char *baseCmd = "/usr/sbin/networksetup";
    int length = strlen(baseCmd);
    for (int i = 1; i < argc; ++i)
    {
        length += strlen(argv[i]) + 3; // +3 for quotes and space;
    }
    char *cmd;
    if ((cmd = (char *)malloc(length + 1)) == NULL)
    {
        fprintf(stderr, "unable to malloc space for building cmd.\n");
        return EXIT_FAILURE;
    }
    int c = 0;
    for (int i = 0; i < argc; ++i)
    {
        cmd[c++] = ' ';
        cmd[c++] = '"';
        char *src = i == 0 ? baseCmd : argv[i];
        while (*src)
        {
            cmd[c++] = *src++;
        }
        cmd[c++] = '"';
    }
    // *cmd ++ = '\0';
    cmd[c++] = '\0';

    // Set ourselves as root
    setuid(0);

    // Run our command
    FILE *output;
    output = popen(cmd, "w");
    if (!output)
    {
        fprintf (stderr, "incorrect parameters or too many files.\n");
        return EXIT_FAILURE;
    }
    int exitCode = pclose(output);
    return WEXITSTATUS(exitCode);
}
