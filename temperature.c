#include <stdio.h>
#include <ctype.h>

/*
 * Program: Temperature Conversion and Weather Advisory
 *
 * This program prompts the user for a temperature value, the original
 * temperature scale (C, F, or K), and the desired target scale. It
 * converts the temperature appropriately, displays the converted value
 * rounded to two decimal places, and then categorizes the resulting
 * temperature using Celsius thresholds. A simple weather advisory is
 * printed based on the category. Invalid scale inputs are detected and
 * reported.
 */

/* Convert a temperature from the given origin scale to Celsius. */
static int to_celsius(double value, char orig_scale, double *out_celsius) {
    switch (orig_scale) {
        case 'C':
            *out_celsius = value;
            return 0;
        case 'F':
            *out_celsius = (value - 32.0) * 5.0 / 9.0;
            return 0;
        case 'K':
            *out_celsius = value - 273.15;
            return 0;
        default:
            return -1; /* invalid origin scale */
    }
}

/* Convert a temperature from Celsius to the given target scale. */
static int from_celsius(double celsius, char target_scale, double *out_value) {
    switch (target_scale) {
        case 'C':
            *out_value = celsius;
            return 0;
        case 'F':
            *out_value = celsius * 9.0 / 5.0 + 32.0;
            return 0;
        case 'K':
            *out_value = celsius + 273.15;
            return 0;
        default:
            return -1; /* invalid target scale */
    }
}

/* Determine the temperature category and a corresponding advisory.  */
static void categorize(double celsius, const char **out_category, const char **out_advisory) {
    if (celsius < 0.0) {
        *out_category = "Freezing";
        *out_advisory = "Wear a heavy coat and stay warm.";
    } else if (celsius < 10.0) {
        *out_category = "Cold";
        *out_advisory = "Wear a jacket or sweater.";
    } else if (celsius < 25.0) {
        *out_category = "Comfortable";
        *out_advisory = "Enjoy the pleasant weather.";
    } else if (celsius < 35.0) {
        *out_category = "Hot";
        *out_advisory = "Stay hydrated and wear light clothing.";
    } else {
        *out_category = "Extreme Heat";
        *out_advisory = "Stay indoors and drink plenty of water.";
    }
}

int main(void) {
    double value;
    char orig_scale, target_scale;

    printf("Enter the temperature value: ");
    if (scanf("%lf", &value) != 1) {
        fprintf(stderr, "Invalid temperature value.\n");
        return 1;
    }

    printf("Enter the original scale (C, F, or K): ");
    /* consume any leading whitespace */
    do {
        if (scanf(" %c", &orig_scale) != 1) {
            fprintf(stderr, "Error reading original scale.\n");
            return 1;
        }
        orig_scale = (char)toupper((unsigned char)orig_scale);
    } while (orig_scale == '\n' || orig_scale == ' ');

    printf("Enter the scale to convert to (C, F, or K): ");
    do {
        if (scanf(" %c", &target_scale) != 1) {
            fprintf(stderr, "Error reading target scale.\n");
            return 1;
        }
        target_scale = (char)toupper((unsigned char)target_scale);
    } while (target_scale == '\n' || target_scale == ' ');

    double celsius;
    if (to_celsius(value, orig_scale, &celsius) != 0) {
        printf("Invalid original scale entered. Please use C, F, or K.\n");
        return 1;
    }

    double converted;
    if (from_celsius(celsius, target_scale, &converted) != 0) {
        printf("Invalid target scale entered. Please use C, F, or K.\n");
        return 1;
    }

    /* Determine the converted temperature in Celsius for categorization. */
    double converted_celsius;
    if (target_scale == 'C') {
        converted_celsius = converted;
    } else if (target_scale == 'F') {
        converted_celsius = (converted - 32.0) * 5.0 / 9.0;
    } else { /* target_scale == 'K' */
        converted_celsius = converted - 273.15;
    }

    /* Obtain a category and advisory for the converted temperature. */
    const char *category;
    const char *advisory;
    categorize(converted_celsius, &category, &advisory);

    /* Print the results */
    printf("Converted temperature: %.2f %c\n", converted, target_scale);
    printf("Temperature category: %s\n", category);
    printf("Weather advisory: %s\n", advisory);

    return 0;
}