#include <stdio.h>

int main(int argc,char* argv[]){
    FILE* script_f;
    char script[65536];
    int mem[30000];
    int loopStart[256];
    int loopEnd[256];
    int loopStart_set = 0;
    int loopEnd_set = 0;
    int point = 0;
    int depth = 0;

    for(int j = 0; j < 256; j++){
        loopStart[j] = -1;
        loopEnd[j] = -1;
    }

    for(int j = 0; j < 30000; j++){
        mem[j] = 0;
    }

    script_f = fopen(argv[1],"r");

    for(;fgets(script,65535,script_f) != NULL;);

    for(int j = 0; j < 50000; j++){
        if(script[j] == '['){
            loopStart[loopStart_set] = j;
            loopStart_set++;
        }else if(script[j] == ']'){
            loopEnd[loopEnd_set] = j;
            loopEnd_set++;
        }
    }

    for(int pos = 0; script[pos] != 0; pos++){
        if(script[pos] < 0) {
            printf("Error:Value of pointer %d < 0\n",point);
            break;
        }else{
            switch(script[pos]){
                case '>':
                    point++;
                    break;
                case '<':
                    point--;
                    break;
                case '+':
                    mem[point]++;
                    break;
                case '-':
                    mem[point]--;
                    break;
                case '[':
                    if(mem[point] == 0){
                        pos = loopEnd[depth];
                    }else{
                        depth++;
                    }
                    break;
                case ']':
                    if(mem[point] == 0){
                        depth--;
                    }else{
                        pos = loopStart[depth-1];
                    }
                    break;
                case ',':
                    mem[point] = getchar();
                    break;
                case '.':
                    putchar(mem[point]);
                    break;
                default:
                    break;
            }
        }
    }
    fclose(script_f);
    return 0;
}