// read the last n lines of a large file, to simulate the "tail" utility
#include<iostream>
#include<time.h>
#include<assert.h>
// sleep function
#include<thread>
#include<chrono>
using namespace std;
#define SIZE 100
void tail(FILE *in, int n) {
    int count = 0;  // count '\n' chars
    unsigned long long pos; // stores up to 2^64 - 1 chars
    char str[2 * SIZE];

    if (fseek(in, 0, SEEK_END)) {   // if failed, return a non-zero value
        perror("fseek failed.\n");
    }
    else {
        // pos will contain num of chars in input file
        pos = ftell(in);    // get current position, pos = file size!
        while (pos) {
            // move 'pos' away from the end of file
            if (!fseek(in, --pos, SEEK_SET)) {
                // find the last 2nd line's newline '\n'
                if (fgetc(in) == '\n') {
                    // stop reading when n newlines is found
                    if (count++ == n) {
                        break;
                    }
                }
            }
            else {
                perror("fseek() failed.\n");
            }
        }

        // print last n lines
        printf("Printing last %d lines -\n", n);
        while (fgets(str, sizeof(str), in)) {
            printf("%s", str);
        }
    }
    printf("\n\n");
}

// utility function so sleep for n seconds
void sleep(unsigned int n) {
    // does not work!
    /*
    clock_t end_time = n * 1000 + clock();
    while (end_time > clock());
    */
    std::this_thread::sleep_for(std::chrono::seconds(n));
}

int main() {
    FILE *fp;
    /*
    char buffer[SIZE];
    // open file in binary mode wb+, for reading and writing simultaneously
    fp = fopen("input.txt", "wb+");
    assert(fp);
    srand(time(NULL));
    // dynamically add lines to input file and call tail() each time
    for (int index = 1; index <= 10; index++) {
        // generate random logs to print in input file
        for (int i = 0; i < SIZE - 1; i++) {
            buffer[i] = rand() % 26 + 'A';
        }
        buffer[SIZE - 1] = '\0';

        // print timestamp in logs
        time_t ltime = time(NULL);
        char *date = asctime(localtime(&ltime));

        // replace the '\n' char in the date string with '\0'
        date[strlen(date) - 1] = '\0';
        // note in text mode '\n' appends two chars, so we open file in binary mode
        fprintf(fp, "\nLine #%d [%s] - %s", index, date, buffer);

        // flush the input stream before calling tail()
        fflush(fp);

        // read the last index lines from the file
        tail(fp, index);
        
        // sleep for 3 seconds, note difference in the timestamps in logs
        sleep(3);
    }
    */
    // test get last 5 lines of input file (10 lines in all)
    fp = fopen("input.txt", "rb+");
    assert(fp);
    tail(fp, 5);

    // close file
    fclose(fp);
    return 0;
}
