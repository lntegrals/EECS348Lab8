#include <stdio.h>
#include <stdbool.h>

/*
 * Program: Football Score Possibilities
 *
 * This program prompts the user to enter a final score for an NFL game
 * and then enumerates all possible combinations of scoring plays that
 * could result in that score. Valid scoring plays in this simplified model
 * include:
 *   • Touchdown followed by a 2‑point conversion (8 points)
 *   • Touchdown followed by a 1‑point field goal (7 points)
 *   • Touchdown with no extra points (6 points)
 *   • Field goal (3 points)
 *   • Safety (2 points)
 *
 * The user may enter multiple scores; entering a score of 1 terminates
 * the program. Negative scores are considered invalid and will prompt
 * the user to try again. A score of zero is possible, but there are no
 * combinations of plays that yield zero points, so a helpful message
 * will be displayed in that case.
 */

int main(void) {
    while (1) {
        int score;
        printf("Enter the NFL score (Enter 1 to stop): ");
        if (scanf("%d", &score) != 1) {
            /* If we can't read an integer, exit early */
            fprintf(stderr, "Error reading input. Exiting.\n");
            return 1;
        }

        /* A sentinel value of 1 terminates the loop. */
        if (score == 1) {
            break;
        }

        /* Negative scores are invalid – prompt the user again. */
        if (score < 0) {
            printf("Invalid score. Please enter a non‑negative score (or 1 to stop).\n");
            continue;
        }

        printf("Possible combinations of scoring plays if a team’s score is %d:\n", score);

        bool found = false;
        /*
         * Iterate through all possible counts of each scoring play.  We use
         * nested loops where each play type subtracts from the remaining
         * total. The innermost loop computes safeties by remainder.
         */
        for (int td2 = 0; td2 * 8 <= score; ++td2) {
            for (int td1 = 0; td2 * 8 + td1 * 7 <= score; ++td1) {
                for (int td0 = 0; td2 * 8 + td1 * 7 + td0 * 6 <= score; ++td0) {
                    for (int fg = 0; td2 * 8 + td1 * 7 + td0 * 6 + fg * 3 <= score; ++fg) {
                        int remaining = score - (td2 * 8 + td1 * 7 + td0 * 6 + fg * 3);
                        if (remaining < 0) {
                            continue;
                        }
                        /* Safeties are worth 2 points. Only consider if remainder is even. */
                        if (remaining % 2 == 0) {
                            int safeties = remaining / 2;
                            /* Print the combination. */
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                                   td2, td1, td0, fg, safeties);
                            found = true;
                        }
                    }
                }
            }
        }
        if (!found) {
            printf("No combinations can result in that score.\n");
        }
        printf("\n");
    }

    return 0;
}