/* uvcompress.cpp
   CSC 485B/CSC 578B/SENG 480B

   Assignment 1 (with starter code provided by B. Bird.)

   Austin Lee - 05/19/2020
*/

#define BYTESIZE 8
#define maxBits 16
#define MAGIC1 0x1f
#define MAGIC2 0x9d
#define MODE 0x90

#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

using namespace std;

/*
    Convert function - Takes an index and creates a deque
        of char with the binary of the index stored of size
        equal to the number of bits to use.
    @param index - int
    @param numBits - int
*/
deque<char> Convert(int index, int numBits)
{
    deque<char> output;
    bitset<16> temp(index);
    string s = temp.to_string();
    for(auto &&c: s)
        output.push_back(c);
    for(int i = 0; i < 16 - numBits; i++)
        output.pop_front();
    return output;
}

/*
    ReverseBits function - Takes streams of bits and reverses them.
        Inspiration provided by Stewbond on the cplusplus 
        forum (see readme for reference.) Modified to use
        deques of char instead of longs.
    @param input - deque<char>
*/
deque<char> ReverseBits(deque<char> input)
{
    deque<char> output;
    input.begin();
    for(auto it = input.rbegin(); it != input.rend(); ++it)
        output.push_back(*it);

    return output;
}

/*
    PrintDeque function - Takes a deque and prints it to
        cout for testing purposes.
    @param printee - deque<char>
*/
void PrintDeque(deque<char> printee)
{
    for(auto it = printee.begin(); it != printee.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main()
{
    char c;
    string working;
    string augmented;
    int nextIndex = 0;  // Next free index in symbol table.
    int numBits = 9;    // Number of bits each character is made of.

    deque<char> stream; // Buffer that holds a chunk of bits to write.
    unordered_map<string, int> sTable;

    /* Populates the symbol table with single characters. */
    for(int i = 0; i < 256; i++)
    {
        c = i;
        string key (1, c);  // These two lines were a hint given to me by Cooper.
        sTable[key] = i;    // Would have spent way more time on my downward research spiral otherwise.
    }

    nextIndex = 257;    // Set the next available index to skip reset character.

    /* Set the Magic and Mode Bytes for compression. */
    cout.put(MAGIC1);
    cout.put(MAGIC2);
    cout.put(MODE);

    /* Reads in a char at a time and performs the LZW algorithm. */
    while(cin.get(c))
    {
        augmented = working + c;
        deque<char> temp;   // Temporary buffer to hold each individual symbol for reversing.

        if(!(sTable.find(augmented) == sTable.end()))
            working = augmented;

        else if(nextIndex >= pow(2, maxBits))
        {
            // Converts the working index to specified number of bits and reverses it.
            temp = ReverseBits(Convert(sTable.at(working), numBits));
            // Inserts the bits into a stream of bits for later grouping.
            stream.insert(stream.end(), make_move_iterator(temp.begin()), 
                make_move_iterator(temp.begin()+ temp.size()));
            working = c;
        }
        else
        {
            sTable[augmented] = nextIndex; 
            temp = ReverseBits(Convert(sTable.at(working), numBits));
            nextIndex++;
            stream.insert(stream.end(), make_move_iterator(temp.begin()), 
                make_move_iterator(temp.begin()+ temp.size()));
            working = c;

            if(nextIndex > pow(2, numBits))
                numBits++;
        }

        /* If the buffer is divisible by 8, group into bytes, and output. */
        if(stream.size() % 8 == 0)
        {
            //PrintDeque(stream); // Testing
            string gCube;   // string used to group bits into 8 bit bytes.
            int i = 0;      // Counter to count out 8 bits.
            
            /* While the buffer has bits, group, and output. */
            while(stream.size())
            {  
                gCube = stream.front() + gCube; //Reverse bits as they're grouped.
                stream.pop_front();
                i++;

                /* Once byte is made, convert to char and output to standard output. */
                if(i % 8 == 0)
                {
                    bitset<8> byte(gCube);
                    char outByte = (char) byte.to_ulong();
                    cout.put(outByte);
                    gCube.erase();
                    i = 0;
                }
            }
        }
    }

    /* If a symbol is left in the working string, add it to buffer. */
    if (working.length() > 0)
    {
        deque<char> temp = ReverseBits(Convert(sTable.at(working), numBits));
        stream.insert(stream.end(), make_move_iterator(temp.begin()), 
            make_move_iterator(temp.begin()+ temp.size()));
    }

    /* If there is remaining buffer, pad and then finish LZW. */
    if(stream.size())
    {
        /* While buffer isn't divisble by 8, pad with 0s. */
        while(stream.size() % 8 != 0)
            stream.push_back('0');
        //PrintDeque(stream); // Testing
        string gCube;
        int i = 0;
        while (stream.size())
        {
            gCube = stream.front() + gCube;
            stream.pop_front();
            i++;

            if (i % 8 == 0)
            {
                bitset<8> byte(gCube);
                char outByte = (char) byte.to_ulong();
                cout.put(outByte);
                gCube.erase();
                i = 0;
            }
        }
    }

    return 0;
}