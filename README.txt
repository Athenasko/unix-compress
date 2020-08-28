----------------------------------
README Unix-Compressor

Coded by: Austin Lee
Starter code provided by: B. Bird

Date: 05/19/2020
----------------------------------

-----------------------------------------------------------------------------------
-                                     NOTES                                       -
-----------------------------------------------------------------------------------
    This implementation of an LZW and old Unix Compressor is made to work with the 
    Unix decompressor. 

    This was done as part of an assignment for SENG 480B at the University of
    Victoria under the tutelage of Professor B. Bird.

-----------------------------------------------------------------------------------
-                                 IMPLEMENTATION                                  -
-----------------------------------------------------------------------------------
    This implementation uses an alphabet of more than 255 characters, as such each
    character is encoded in 9 bits. As such, this implementation makes its own
    compressed stream of 9 bits, by filling a buffer until it is divisible by 8,
    separating that buffer into 8 bit chunks, converting the 8 bits into a
    character, and putting that character out into the output stream.

    NOTE: This is NOT the best way to do segment a stream of bits when encoding 
    characters into more than 8 bits, but it was what I was able to come up with 
    as an introduction to C++ and never having coded compression or dealt with
    bits.

-----------------------------------------------------------------------------------
-                                   REFERENCES                                    -
-----------------------------------------------------------------------------------

    1. Pseudocode provided by B. Bird.
    2. Cooper Mountford - Student in the class. Discorded a lot to (verbally only)
        discuss aspects of the assignment such as type casting int to char to string and for
        reversing bits. Shared resources as well when we were struggling.
    3. www.stackoverflow.com/questions/19461478/convert-binary-bitset-to-hexadecimal-c - 
        Used to create a binary to hexidecimal converter. Didn't end up using it.
    4. www.cplusplus.com/forum/general/109866/ - Used the ReverseBits
        function as inspiration, provided by user Stewbond, changed to use deques.
    5. www.stackoverflow.com/questions/7349689/how-to-print-using-cout-a-number-in-binary-form -
        User r233967 explained how to use the bitset in cout. Used for testing purposes.
    6. www.quora.com/How-can-I-break-a-string-into-individual-chars-in-C++ -
        Used to convert a string into a deque of chars.
    7. www.stackoverflow.com/questions/49928501/better-way-to-move-obkects-from-one-stddeque-to-another -
        Used user Justin's answer to figure out concatenating deques.
