#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void printMenu();
void atbashCipher(char *text);
void caesarCipher(char *text, int shift);
void affineCipher(char *text, int a, int b);
void vigenereCipher(char *text, char *key);
void gronsfeldCipher(char *text, char *key);
void beaufortCipher(char *text, char *key);
void autoKeyCipher(char *text, char *key);
void runningKeyCipher(char *text, char *key);
void hillCipher(char *text, int key[2][2]);
void railFenceCipher(char *text, int rails);
void routeCipher(char *text, int rows, int cols);
void columnarCipher(char *text, char *key);
void doubleTransCipher(char *text, char *key1, char *key2);
void myszkowskiCipher(char *text, char *key);

int main() {
    int choice, shift, a, b, rails, rows, cols;
    char text[1000], key[100], key2[100];
    int hillKey[2][2];
    
    while (1) {
        printMenu();
        printf("Enter your choice (1-15, 0 to exit): ");
        scanf("%d", &choice);
        getchar();
        
        if (choice == 0) break;
        
        printf("Enter plaintext: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0;
        
        switch (choice) {
            case 1: // Atbash
                atbashCipher(text);
                break;
            case 2: // Caesar
                printf("Enter shift: ");
                scanf("%d", &shift);
                caesarCipher(text, shift);
                break;
            case 3: // Affine
                printf("Enter a (coprime with 26): ");
                scanf("%d", &a);
                printf("Enter b: ");
                scanf("%d", &b);
                affineCipher(text, a, b);
                break;
            case 4: // Vigenere
                printf("Enter key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                vigenereCipher(text, key);
                break;
            case 5: // Gronsfeld
                printf("Enter numeric key (e.g., 1234): ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                gronsfeldCipher(text, key);
                break;
            case 6: // Beaufort
                printf("Enter key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                beaufortCipher(text, key);
                break;
            case 7: // Auto Key
                printf("Enter initial key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                autoKeyCipher(text, key);
                break;
            case 8: // Running Key
                printf("Enter long key (e.g., book text): ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                runningKeyCipher(text, key);
                break;
            case 9: // Hill (2x2 matrix)
                printf("Enter 4 numbers for 2x2 matrix (e.g., 1 2 3 4): ");
                scanf("%d %d %d %d", &hillKey[0][0], &hillKey[0][1], 
                      &hillKey[1][0], &hillKey[1][1]);
                hillCipher(text, hillKey);
                break;
            case 10: // Rail Fence
                printf("Enter number of rails: ");
                scanf("%d", &rails);
                railFenceCipher(text, rails);
                break;
            case 11: // Route
                printf("Enter rows: ");
                scanf("%d", &rows);
                printf("Enter columns: ");
                scanf("%d", &cols);
                routeCipher(text, rows, cols);
                break;
            case 12: // Columnar
                printf("Enter key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                columnarCipher(text, key);
                break;
            case 13: // Double Transpositional
                printf("Enter first key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                printf("Enter second key: ");
                fgets(key2, sizeof(key2), stdin);
                key2[strcspn(key2, "\n")] = 0;
                doubleTransCipher(text, key, key2);
                break;
            case 14: // Myszkowski
                printf("Enter key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = 0;
                myszkowskiCipher(text, key);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }
        printf("Ciphertext: %s\n\n", text);
    }
    return 0;
}

void printMenu() {
    printf("\n=== Cipher Menu ===\n");
    printf("1. Atbash Cipher\n2. Caesar Cipher\n3. Affine Cipher\n");
    printf("4. Vigenere Cipher\n5. Gronsfeld Cipher\n6. Beaufort Cipher\n");
    printf("7. Auto Key Cipher\n8. Running Key Cipher\n9. Hill Cipher\n");
    printf("10. Rail Fence Cipher\n11. Route Cipher\n12. Columnar Cipher\n");
    printf("13. Double Transpositional Cipher\n14. Myszkowski Cipher\n");
    printf("0. Exit\n");
}

void atbashCipher(char *text) {
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i]))
            text[i] = isupper(text[i]) ? 'Z' - (text[i] - 'A') : 'z' - (text[i] - 'a');
}

void caesarCipher(char *text, int shift) {
    shift = shift % 26;
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i]))
            text[i] = isupper(text[i]) ? 
                ((text[i] - 'A' + shift) % 26 + 26) % 26 + 'A' : 
                ((text[i] - 'a' + shift) % 26 + 26) % 26 + 'a';
}

void affineCipher(char *text, int a, int b) {
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i]))
            text[i] = isupper(text[i]) ? 
                (((a * (text[i] - 'A') + b) % 26 + 26) % 26) + 'A' : 
                (((a * (text[i] - 'a') + b) % 26 + 26) % 26) + 'a';
}

void vigenereCipher(char *text, char *key) {
    int j = 0, keyLen = strlen(key);
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i])) {
            char k = toupper(key[j % keyLen]) - 'A';
            text[i] = isupper(text[i]) ? 
                ((text[i] - 'A' + k) % 26) + 'A' : 
                ((text[i] - 'a' + k) % 26) + 'a';
            j++;
        }
}

void gronsfeldCipher(char *text, char *key) {
    int j = 0, keyLen = strlen(key);
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i])) {
            int k = key[j % keyLen] - '0';
            text[i] = isupper(text[i]) ? 
                ((text[i] - 'A' + k) % 26) + 'A' : 
                ((text[i] - 'a' + k) % 26) + 'a';
            j++;
        }
}

void beaufortCipher(char *text, char *key) {
    int j = 0, keyLen = strlen(key);
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i])) {
            char k = toupper(key[j % keyLen]) - 'A';
            text[i] = isupper(text[i]) ? 
                ((k - (text[i] - 'A') + 26) % 26) + 'A' : 
                ((k - (text[i] - 'a') + 26) % 26) + 'a';
            j++;
        }
}

void autoKeyCipher(char *text, char *key) {
    char fullKey[1000];
    strcpy(fullKey, key);
    strcat(fullKey, text);
    int j = 0, keyLen = strlen(fullKey);
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i])) {
            char k = toupper(fullKey[j]) - 'A';
            text[i] = isupper(text[i]) ? 
                ((text[i] - 'A' + k) % 26) + 'A' : 
                ((text[i] - 'a' + k) % 26) + 'a';
            j++;
        }
}

void runningKeyCipher(char *text, char *key) {
    int j = 0, keyLen = strlen(key);
    for (int i = 0; text[i]; i++)
        if (isalpha(text[i])) {
            char k = toupper(key[j % keyLen]) - 'A';
            text[i] = isupper(text[i]) ? 
                ((text[i] - 'A' + k) % 26) + 'A' : 
                ((text[i] - 'a' + k) % 26) + 'a';
            j++;
        }
}

void hillCipher(char *text, int key[2][2]) {
    int len = strlen(text);
    char temp[1000];
    strcpy(temp, text);
    for (int i = 0; i < len - 1; i += 2) {
        if (!isalpha(temp[i]) || !isalpha(temp[i+1])) continue;
        int x = toupper(temp[i]) - 'A';
        int y = toupper(temp[i+1]) - 'A';
        int a = (key[0][0] * x + key[0][1] * y) % 26;
        int b = (key[1][0] * x + key[1][1] * y) % 26;
        text[i] = a + 'A';
        text[i+1] = b + 'A';
    }
}

void railFenceCipher(char *text, int rails) {
    int len = strlen(text);
    char rail[rails][len];
    memset(rail, 0, sizeof(rail));
    int row = 0, dir = 1;
    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];
        row += dir;
        if (row == rails - 1 || row == 0) dir = -dir;
    }
    int k = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j]) text[k++] = rail[i][j];
    text[k] = '\0';
}

void routeCipher(char *text, int rows, int cols) {
    int len = strlen(text);
    char grid[rows][cols];
    memset(grid, ' ', sizeof(grid));
    int k = 0;
    for (int i = 0; i < rows && k < len; i++)
        for (int j = 0; j < cols && k < len; j++)
            grid[i][j] = text[k++];
    k = 0;
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            if (grid[i][j] != ' ') text[k++] = grid[i][j];
    text[k] = '\0';
}

void columnarCipher(char *text, char *key) {
    int len = strlen(text), keyLen = strlen(key);
    int rows = (len + keyLen - 1) / keyLen;
    char grid[rows][keyLen];
    memset(grid, ' ', sizeof(grid));
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < keyLen && k < len; j++)
            grid[i][j] = text[k++];
    k = 0;
    for (int col = 0; col < keyLen; col++)
        for (int row = 0; row < rows; row++)
            if (grid[row][col] != ' ') text[k++] = grid[row][col];
    text[k] = '\0';
}

void doubleTransCipher(char *text, char *key1, char *key2) {
    columnarCipher(text, key1);
    columnarCipher(text, key2);
}

void myszkowskiCipher(char *text, char *key) {
    int len = strlen(text), keyLen = strlen(key);
    int rows = (len + keyLen - 1) / keyLen;
    char grid[rows][keyLen];
    memset(grid, ' ', sizeof(grid));
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < keyLen && k < len; j++)
            grid[i][j] = text[k++];
    k = 0;
    for (char c = 'A'; c <= 'Z'; c++)
        for (int j = 0; j < keyLen; j++)
            if (toupper(key[j]) == c)
                for (int i = 0; i < rows; i++)
                    if (grid[i][j] != ' ') text[k++] = grid[i][j];
    text[k] = '\0';
}