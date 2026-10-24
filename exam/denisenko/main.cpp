#include <stdio.h>
#include <stdlib.h>

#define N 12
#define THRESH_GOOD 35   /* порог 1: отличный канал, дБ */
#define THRESH_OK   20   /* порог 2: приемлемый канал, дБ */

int main(void)
{
    int snr[N] = { -42, -38, -25, -17, -33, -45, -29, -12,
                   -36, -41, -22, 30 };

    int val[N];          /* значения SNR по модулю, как в примере вывода */
    int min, max, idx_min = 0, idx_max = 0;
    int sum = 0;
    int cnt_good = 0, cnt_ok = 0, cnt_bad = 0;

    for (int i = 0; i < N; i++)
        val[i] = abs(snr[i]);

    min = max = val[0];

    for (int i = 0; i < N; i++) {
        if (val[i] < min) { min = val[i]; idx_min = i; }
        if (val[i] > max) { max = val[i]; idx_max = i; }
        sum += val[i];

        if (val[i] >= THRESH_GOOD) cnt_good++;
        if (val[i] >= THRESH_OK)   cnt_ok++;
        else                       cnt_bad++;
    }

    double avg = (double)sum / N;

    const char *min_label = (min >= THRESH_GOOD) ? "Отличный"
                          : (min >= THRESH_OK)   ? "Нормальный" : "Плохой";
    const char *max_label = (max >= THRESH_GOOD) ? "Отличный"
                          : (max >= THRESH_OK)   ? "Нормальный" : "Плохой";

    const char *verdict;
    if (cnt_bad == 0)
        verdict = "хорошая, проблемных клиентов нет";
    else if (cnt_bad > N / 2)
        verdict = "плохая, большинство клиентов с плохим каналом";
    else
        verdict = "рабочая, но есть проблемные клиенты";

    printf("===== Отчёт по соте Wi-Fi (N=%d) =====\n", N);
    printf("Минимальный SNR : %d дБ (клиент %02d) — %s\n", min, idx_min, min_label);
    printf("Максимальный SNR: %d дБ (клиент %02d) — %s\n", max, idx_max, max_label);
    printf("Средний SNR : %.2f дБ\n", avg);
    printf("--------------------------------------\n");
    printf("Клиентов с SNR >= %d дБ : %d\n", THRESH_GOOD, cnt_good);
    printf("Клиентов с SNR >= %d дБ : %d\n", THRESH_OK, cnt_ok);
    printf("Клиентов с SNR < %d дБ : %d%s\n", THRESH_OK, cnt_bad,
           cnt_bad ? " <-- требуют внимания" : "");
    printf("--------------------------------------\n");
    printf("Разброс (max-min) : %d дБ\n", max - min);
    printf("Оценка соты: %s\n", verdict);

    return 0;
}
