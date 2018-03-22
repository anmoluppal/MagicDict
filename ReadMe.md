# MagicDict
Smallest and Fastest Data Structure to query english words.

**Note:** This is implementation of [Bloom Filter](https://en.wikipedia.org/wiki/Bloom_filter) for Trie Data Structure.
It can be used to test whether query word is valid or not.
False positive matches are possible, but false negatives are not –
in other words, a query returns either "possibly in set" or "definitely
not in set".

## Benchmarks:

|Data Strcuture|Insert (370k words)|Query (100k words)| Delete (100k words)|
|--------------|-------------------|------------------|--------------------|
|     Set      |461 ms             |220 ms            |39 ms               |
|    Trie      |530 ms             |50 ms             |26 ms               |
|   HashMap    |180 ms             |110 ms            |14 ms               |
|**MagicDict** |**13 ms**          |**3 ms**          |**1 ms**            |

**Note:** Current benchmarks have been calculated on
[370k valid english words](https://github.com/dwyl/english-words/blob/master/words_alpha.txt)


## Build
You can `make` this project using:
```bash
mkdir build
cd build
cmake ..
```
to generate a lib file or directly use `MagicDict` class in your source
tree.