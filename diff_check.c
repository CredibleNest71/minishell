#include <stdio.h>

void compareStrings(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            printf("Difference found at index %d: '%c' vs '%c'\n", i, str1[i], str2[i]);
            return; // Exit function early if difference is found
        }
        i++;
    }
    
    if (str1[i] == '\0' && str2[i] == '\0') {
        printf("The strings are identical.\n");
    } else {
        // Check for remaining characters in either string
        while (str1[i] != '\0') {
            printf("Extra character in first string at index %d: '%c'\n", i, str1[i]);
            i++;
        }
        while (str2[i] != '\0') {
            printf("Extra character in second string at index %d: '%c'\n", i, str2[i]);
            i++;
        }
    }
}

int main() {
    const char *str1 = "cat lol.c | cat > lol.c";
    const char *str2 = "cat lol.c | cat > lol.c";

    compareStrings(str1, str2);
    
    return 0;
}

