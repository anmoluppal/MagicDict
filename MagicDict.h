#ifndef MAGIC_DICT_H
#define MAGIC_DICT_H

#include <cmath>
#include <vector>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>

class MagicDict {
    typedef std::vector<uint64_t> Layer;
    typedef std::vector<Layer> LayerStack;
private:
    const unsigned int MAX_CHARACTERS =     26;
    const unsigned int MAX_WORD_LENGTH =    20;
    const unsigned char CHAR_START =        'a';
    const unsigned char CHAR_END =          'z';

    Layer mLayer;
    LayerStack mLayerStack;
    const unsigned int mMaxCharNum;
    const unsigned int mMaxWordLen;

    std::vector<uint64_t> mIsChildMask;
    std::vector<uint64_t> mIsTerminalMask;

    /**
     * Initializes the required private class attributes, with default values.
     */
    void init();

    /**
     * Checks if the input query word contains only valid ascii characters in range: 'a' - 'z'.
     *
     * @param word Input query word, characters in small caps ascii range.
     * @param sz   Size of input word.
     * @return     a boolean value defining if all the characters in the word are in the range specified.
     */
    bool isInputWordValid(const char* word, size_t sz) const;
public:
    MagicDict();

    /**
     * Inserts the given word in the Data Structure.
     *
     * @param word Input query word, characters in small caps ascii range.
     * @param sz   Size of input word.
     */
    void insert(const char* word, size_t sz);

    /**
     * Checks if input set of characters form a valid word.
     *
     * @param word Input query word, characters in small caps ascii range.
     * @param sz   Size of input word.
     * @return     a boolean value if all the characters in the word form a valid known word to data structure.
     */
    bool isWordExists(const char* word, size_t sz) const;

    /**
     * Removes the input word from data structure, if it already exists, else ignores.
     *
     * @param word Input query word, characters in small caps ascii range.
     * @param sz   Size of input word.
     */
    void remove(const char* word, size_t sz);

    /**
     * Preserve the Data Structure to file stream.
     *
     * @param stream An output stream, ready to be written. Client must close the stream after this routine.
     */
    void serialize(std::ofstream &stream) const;

    /**
     * Inflate the Data Structure from persistent state.
     *
     * @param stream An input stream, ready to be read. Client must close the stream after this routine.
     */
    void deserialize(std::ifstream &stream);
};

#endif