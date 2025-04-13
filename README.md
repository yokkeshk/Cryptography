# Cryptography
# Classic Cryptographic Ciphers in C

This project implements a collection of classic cryptographic ciphers in C. It provides a menu-driven command-line interface that allows users to encrypt plaintext using various historical encryption algorithms. The goal is to demonstrate and understand the basic principles behind classic ciphers used before the age of modern cryptography.

## Features

The program supports the following ciphers:

1. **Atbash Cipher**
2. **Caesar Cipher**
3. **Affine Cipher**
4. **Vigenère Cipher**
5. **Gronsfeld Cipher**
6. **Beaufort Cipher**
7. **Auto Key Cipher**
8. **Running Key Cipher**
9. **Hill Cipher (2x2 Matrix)**
10. **Rail Fence Cipher**
11. **Route Cipher**
12. **Columnar Transposition Cipher**
13. **Double Transpositional Cipher**
14. **Myszkowski Cipher**

Each cipher is implemented in its own function. The main program allows users to select the desired cipher, input the necessary keys or parameters, and see the encrypted output.

## Usage

1. Compile the program using a C compiler like `gcc`:

   ```bash
   gcc crypto.c -o crypto
