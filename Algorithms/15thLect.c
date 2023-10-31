/*
31.10.23:
Huffman Coding
It's a lossless data compression algorithm
But how does it work?

It takes advantage of repeated common strings within the data

consider a set of data with many repeated sequences
00000000111000000000000001100000001000000000

we can compress the data by assigning something to a group of zeros
but it kind of doesn't really work

so we can define a set of characters, lets say 8 characters a - h
and assign each character a set of bits
like a is 1101
b is 001010
c is 00000
d is 0110111

they can be different lengths
then we can rewrite the file in terms of the characters instead of bits

we want to choose characters that show up a lot in the file
so things that will have a large frequency

you can turn a file into a tree (?)

oh okay so you use the tree to encode each character (?)

so you get a weird looking tree

lets say

        fgadbiche
        /       \
      fgadb    iche
      /   \    /   \
    fgad   b  ich   e
    /  \     /   \
  fga   d   ic    h
  / \      /  \
 f  ga    i    c
   /  \
  g    a

and a code 0011000100111
it has to be DICE (001) (1000) (1001) (11)
(going left means 0, going right means 1)
you just go until you hit a letter
thats how you know when one letter stops and the next begins

the prefix of the characters are always unique, you cant have a be 0100 and b be 01001110

you need a binary tree AND a heap (?)
we are keeping track of the character frequency and the character itself

so step 1 is we have data
and we turn it into distinct characters (somehow)
and then we build a min heap with the characters, based on frequency

then in the loop we find the two lowest frequency characters
then we concat them into a tree

so if i and c were the lowest frequency with 15 and 20 we get

    ic
   /  \
  i    c

then we put the new ic node back in the heap (heapify)
and keep combining the two lowest

sometimes it'll be two new ones sometimes it'll be an old tree and a new node

then eventually we get the whole binary tree
         iche
        /    \
      ich     e
     /   \
    ic    h
   /  \
  i    c

depending on the frequencies, it could look different

so then to use it to encode:
we just need to keep going until it's a character
so if the data is
0010101110101010100

then we get
001 - c
01 - h
01 - h
1 - e
1 - e
01 - h
01 - h
01 - h
01 - h
00 - ummm we can't do that, but I'll do c

then we get
chheehhhhc
compressed, but actually it's not because each letter takes 2 bits of data and the gains aren't good enough
but then again I didn't build the Huffman thing based on this data specifically

oh i think i have the understanding wrong
the data is made up of these characters, and we are determining how to define each character in bits
the data isn't made up of bits directly

okay that makes a little more sense

so in step 1 when we "counted the characters" that was literally what we were doing
like if the message was "hello world" then the character count would be 7, cuz there are 7 distinct characters

the freq table would be
h - 1
e - 1
l - 3
o - 2
w - 1
r - 1
d - 1

and the huffing paint tree would look like:

      dhelowr
     /       \
    dhel    owr  
   /   \    /  \
  dhe   l  o   wr
  / \         /  \
 d  he       w    r
   /  \
  h    e

or something like that
then hello world would become:
0010 0011 01 01 10 110 10 111 01 000
i forgot the space but whatever

so altogether it becomes
001000110101101101011101000
which is pretty good since ASCII makes it
01101000011001010110110001101100011011110111011101101111011100100110110001100100
so huffing paint made it quite a bit smaller
and even if we just used 3 bit strings cuz there are only 7 letters it'd be
111011000000001110001000001100
that long
so huffing paint was even shorter than that too, by 3 bits

you can also prove that huffing paint works, but im not going to because lemma 15.2 just says so

so huffman summary:
data is made of characters
you can compress data by making a tree with the different characters, and assigning smaller amounts of bits to characters that
are more prevalant in the data
to make the tree you make a frequency table and then combine shit until you get a full tree
then you assign each character in the tree a unique prefix by its position in the tree
and then boom. Compressed

guys i just had a genius idea
so you do huffman with characters, and then also words
so you layer another huffman on top using words

so you just use single "append" bits after characters to do words
actually that wont work

the thing is you also have to store the tree itself in the data
or some kind of table for corresponding characters
which takes up some overhead space

so you gotta remember that

Runtime: depends on the min-priority queue
but with the best one it's
O(n lg n)
cool
*/

#include <stdio.h>

int main(int argc, char *argv[]) {

}