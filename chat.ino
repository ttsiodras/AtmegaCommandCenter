#include <Arduino.h>

#define BAUD           4800
#define MAX_CMD_LENGTH 128

#define YELLOW  "\e[1;33m"
#define RED     "\e[1;31m"
#define NOCOLOR "\e[0m"

void setup(void) {
    Serial.begin(BAUD);
}

///////////////
// Menu actions

void ledOn()
{
    analogWrite(5, 255);
}

void ledOff()
{
    analogWrite(5, 0);
}

void showHelp()
{
    Serial.print(
        "\r\n\r\nUsage:\r\n    "
        YELLOW "led on" NOCOLOR "      to light me up\r\n    "
        YELLOW "led off" NOCOLOR "     to go to sleep...\r\n");
}


//////////////////////////////////////////////
// Gather the function pointers of the actions

struct Cmd {
    const char *cmd;
    void (*func)();
} cmds[] = {
    {"led on", ledOn},
    {"led off", ledOff},
    {"help", showHelp},
};
int maxCmdIdx = sizeof(cmds)/sizeof(cmds[0]);


//////////////////////////////////////////////////////////////////
// Read incoming command over serial while also handling backspace

void get(char *cmd)
{

    int cmdIdx = 0;
    while(1) {
        int c = Serial.read();
        if (c!=-1) {
            if (c == 8 && cmdIdx>0) {
                Serial.print("\b \b");
                cmdIdx--;
            } else if (c == '\r') {
                cmd[cmdIdx & (MAX_CMD_LENGTH-1)] = '\0';
                break;
            } else if (isprint(c)) {
                Serial.print((char)c);
                cmd[cmdIdx++ & (MAX_CMD_LENGTH-1)] = (char)c;
            }
        }
    }
}

void loop()
{
    int i;
    static char cmd[MAX_CMD_LENGTH];

    Serial.print("\r\nType 'help' if you need usage instructions\r\n>>> ");
    get(cmd);
    for(i=0; i<maxCmdIdx; i++) {
        if (!strcmp(cmd, cmds[i].cmd)) {
            Serial.print("\r\n\nExecuting command: '" YELLOW);
            Serial.print(cmds[i].cmd);
            Serial.print(NOCOLOR "'\r\n");
            cmds[i].func();
            break;
        }
    }
    if (i == maxCmdIdx) {
        Serial.print("\r\n\nCommand '" RED);
        Serial.print(cmd);
        Serial.println(NOCOLOR "' is not recognized...\n\rAvailable commands are:\r\n");
        for(i=0; i<maxCmdIdx; i++) {
            Serial.print("    " YELLOW);
            Serial.print(cmds[i].cmd);
            Serial.print(NOCOLOR "\r\n");
        }
    }
}
