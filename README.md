This program is mostly for fun and practice with bitwise functions

User guide
------------------------------------------------------------------------------------------------------------------------------------------------------------------

This program currently can encrypt a file with a key.

First you choose an option to encrypt or decrypt(E/e or D/d are usable respectively)

Then it asks for the name of the file you want to encrypt. It works on files with any extension and will keep the extension(up to 100 characters, changable in the code)

Finally, it asks for the key, which can be andy ascii characters which will change the information(up to 50 characters, also changable in the code)

It will create a file with the same name + "_encoded" or "_decoded" depending on the chosen option then the extension

Some caution
------------------------------------------------------------------------------------------------------------------------------------------------------------------


Some notes one how it encrypts

It repeats the same instructions on every set of 2 letters, so if the same two letter combo(which also means they have to be grouped so "abcab" woul not count because the groups are "ab" and "ca", the group "ab" only appears once) will always change to the same thing, so if it is a plain text message there is a possibility of reverse engineering the more repeated combos, although it would still be difficult

Also, certain characters repeat the same instruction(such as flip all bits) twice, which effectively do nothing in the key, which are the following: NULL, DC1(ascii character 17), ", 3, D, U, f, and w

Under the hood
------------------------------------------------------------------------------------------------------------------------------------------------------------------


Exactly how it works:

I took inspiration from another encoding program, which puts the bits into an array of 16 bits, 4x4 grid, which would be 2 characters in a text file. For example, the 2 character combo "3j" in binary is 0011001101101010.

The grid would look like this:

0  0  1  1

0  0  1  1

0  1  1  0

1  0  1  0

Now every character in the key has 2 instructions since the instructions are on an 4 bit basis and characters are 8 bits

It slices each character in half and rans the first 4 bits' instruction, then the second 4 bits' instruction.

Then the program runs instructions based on the key, which are as follows:

      0:flip every bit          0000
      
      1:flip row 1              0001

      2:flip row 2              0010
      
      3:flip row 3              0011
      
      4:flip row 4              0100
      
      5:flip column 1           0101
      
      6:flip column 2           0110
      
      7:flip column 3           0111
      
      8:flip column 4           1000
      
      9:swap column 1 and 2     1001
      
      10(a):swap column 2 and 3 1010
      
      11(b):swap column 3 and 4 1011
      
      12(c):swap column 1 and 4 1100
      
      13(d):swap row 1 and 3    1101
      
      14(e):swap row 2 and 4    1110
      
      15(f):swap row 2 and 3    1111
      

So on the combo 3j, which the key "2!5A`", we would run the instructions 3, 2, 2, 1, 3, 5, 4, 1, 6, and 0. Seperately, for example, '2' is instrucitons 3 then 2

If the same character follows itself, it will usually result in nothing unless it mixes flipping rows/columns and swapping rows/colums, or

Also, each character has a compliment. for example, the character '2' runs instructions 3 then 2. the character that runs instructions 2 then 3 is '#'. If these characters follow each other, they will always result in no change.


My note
------------------------------------------------------------------------------------------------------------------------------------------------------------------
I know this isn't the most secure method of encryption of available, I just did this for fun. Currently in the code there is some jank surrounding the "flip row x" instructions and the "swap column x and y" as the code would not work how I wanted it to. I had to use different solutions for flip row 1/2, 3, and 4 and for swap columns 1/3 would swap and 2/4 would swap so it is swapped in the code

Feel free to report any bugs. I can not promise the exe will work on your pc, you might need to compile the program yourself. I used this line "gcc encrypt.c decrypt.c program.c helper.c keyInstructions.c -o program -g". You don't have to use the -g flag, I just used it for debugging. You just have to download all the .c and .h files.

Enjoy! feel free to report bugs
