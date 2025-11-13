#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"
#define MAX_LOTTO_NUM 7
#define MAX_LOTTO_NUMSET 5

void init_file();
int get_counter();
void set_counter(int counter);
void do_lotto_main(int counter);
void print_lottofile(int num_set, int counter, char lotto_file[]);
void print_lotto_row(FILE* tmpfp, int n);
int num_in_numset(int num, int numset[], int Len);

void init_file() {
    int write_array[1] = {0};
    FILE* fp = fopen(COUNTER_FILE,"r");
    if (fp == NULL) {
        FILE* tmpfp = fopen(COUNTER_FILE,"wb+");
        fwrite(write_array, sizeof(int), 1, tmpfp);
        fclose(tmpfp);
    } else {
        fclose(fp);
    }
}

int get_counter() {
    int read_array[1];
    FILE* tmpfp = fopen(COUNTER_FILE,"rb");
    fread(read_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
    return read_array[0];
}

void set_counter(int counter) {
    int write_array[1] = {counter};
    FILE* tmpfp = fopen(COUNTER_FILE, "wb");
    fwrite(write_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
}

int num_in_numset(int num, int numset[], int Len) {
    for (int i = 0; i < Len; i++) {
        if (num == numset[i]) return 1;
    }
    return 0;
}

void print_lotto_row(FILE* tmpfp, int n) {
    int numset[MAX_LOTTO_NUM] = {0};
    fprintf(tmpfp, "[%d]: ", n);
    
    // 產生前 6 個樂透號碼 (1–69)
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ) {
        int num = (rand() % 69) + 1;
        if (!num_in_numset(num, numset, i)) {
            numset[i++] = num;
        }
    }
    // 排序前 6 個號碼
    for (int i = 0; i < MAX_LOTTO_NUM - 2; i++) {
        for (int j = i + 1; j < MAX_LOTTO_NUM - 1; j++) {
            if (numset[i] > numset[j]) {
                int temp = numset[i];
                numset[i] = numset[j];
                numset[j] = temp;
            }
        }
    }

    // 印出前 6 個號碼
    for (int i = 0; i < MAX_LOTTO_NUM - 1; ++i) {
        fprintf(tmpfp, "%02d ", numset[i]);
    }

    // 最後一個是特別號 (1–10)
    int special = (rand() % 10) + 1;
    fprintf(tmpfp, "%02d\n", special);
}

void print_lottofile(int num_set, int counter, char lotto_file[]) {
    time_t curtime;
    time(&curtime);
    srand(time(0));
    
    FILE* tmpfp = fopen(lotto_file, "w+");
    fprintf(tmpfp, "========= lotto649 =========\n");
    fprintf(tmpfp, "========+ No.%05d +========\n", counter);
    fprintf(tmpfp, "=%s", ctime(&curtime));
    
    for (int i = 0; i < MAX_LOTTO_NUMSET; i++) {
        if (i < num_set) {
            print_lotto_row(tmpfp, i + 1);
        } else {
            fprintf(tmpfp, "[%d]: __ __ __ __ __ __ __\n", i + 1);
        }
    }
    fprintf(tmpfp, "========= csie@CGU =========\n");
    fclose(tmpfp);
}

void do_lotto_main(int counter) {
    char lotto_file[32];
    int num_set = 0;
    snprintf(lotto_file, 32, "lotto[%05d].txt", counter);
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &num_set);
    print_lottofile(num_set, counter, lotto_file);
    printf("已為您購買的 %d 組樂透組合輸出至 %s\n", num_set, lotto_file);
}

int main() {
    int counter;
    init_file();
    counter = get_counter();
    printf("counter = %d\n", counter);
    do_lotto_main(++counter);
    set_counter(counter);
    return 0;
}
