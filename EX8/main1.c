#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    printf("請輸入要買幾組樂透: ");
    scanf("%d", &n);
    srand(1); 

    FILE *fp;
    fp = fopen("lotto.txt", "w");
    fprintf(fp, "========= lotto649 =========\n");
    for (int i = 0; i < 5; i++) {
        fprintf(fp, "[%d]:", i + 1);
        if (i < n) {
            int lotto[7]; 
            for (int j = 0; j < 7; ) {
                int num = rand() % 69 + 1;
                int dup = 0;
                for (int k = 0; k < j; k++) {
                    if (lotto[k] == num) {
                        dup = 1;
                        break;
                    }
                }
                if (dup == 0) {
                    lotto[j] = num;
                    fprintf(fp, " %02d", num);
                    j++;
                }
            }
        } else {
            fprintf(fp, " __ __ __ __ __ __ __");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    int win[3];
    printf("請輸入中獎號碼三個: ");
    scanf("%d %d %d", &win[0], &win[1], &win[2]);
    printf("輸入中獎號碼為: %02d %02d %02d\n", win[0], win[1], win[2]);
    printf("以下為中獎彩券:\n");

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char date_str[64];
    strftime(date_str, sizeof(date_str), "%B %d %Y", tm_info);

    fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        printf("找不到 lotto.txt 檔案！\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '[') { 
            int nums[7];
            int idx;
            if (sscanf(line, "[%d]: %d %d %d %d %d %d %d",
                       &idx, &nums[0], &nums[1], &nums[2],
                       &nums[3], &nums[4], &nums[5], &nums[6]) == 8) {
                int match = 0;
                for (int i = 0; i < 7; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (nums[i] == win[j]) match = 1;
                    }
                }
                if (match) {
                    printf("售出時間: %s: %s", date_str, line);
                }
            }
        }
    }
    fclose(fp);
    return 0;
}
