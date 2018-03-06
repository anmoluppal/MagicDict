# MagicDict
Smallest and Fastest Data Structure to query english words.

## Benchmarks:

|Data Strcuture|Insert (370k words)|Query (100k words)| Delete (100k words)|
|--------------|-------------------|------------------|--------------------|
|    MySql     |10,000 ms          |5,396 ms          |2,729 ms            |
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