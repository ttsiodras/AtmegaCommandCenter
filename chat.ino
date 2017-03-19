#include <Arduino.h>

#include "defines.h"

void setup(void) {
    Serial.begin(BAUD);
}

const char *usage = \
"\r\n\r\nUsage:\r\n\
    led on      to light me up\r\n\
    led off     to go to sleep...\r\n\n>>> ";

void ledOn()  { analogWrite(5, 255); }
void ledOff() { analogWrite(5, 0);   }
void help()   { Serial.print(usage); }

struct Cmd {
    const char *cmd;
    void (*func)();
} cmds[] = {
    {"led on", ledOn},
    {"led off", ledOff},
    {"help", help},
};
int maxCmdIdx = sizeof(cmds)/sizeof(cmds[0]);

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

void getAndExecuteCommand()
{
    int i;
    static char cmd[MAX_CMD_LENGTH];

    Serial.print("\r\nType 'help' if you need usage instructions\r\n>>> ");
    get(cmd);
    for(i=0; i<maxCmdIdx; i++) {
        if (!strcmp(cmd, cmds[i].cmd)) {
            Serial.print("\r\n\nExecuting command: '");
            Serial.print(cmds[i].cmd);
            Serial.print("'\r\n");
            cmds[i].func();
            break;
        }
    }
    if (i == maxCmdIdx) {
        Serial.print("\r\n\nCommand '");
        Serial.print(cmd);
        Serial.println("' is not recognized...\n\rAvailable commands are:\r\n");
        for(i=0; i<maxCmdIdx; i++) {
            Serial.print("    ");
            Serial.print(cmds[i].cmd);
            Serial.print("\r\n");
        }
    }
}

void loop(void) {
    getAndExecuteCommand();
}
