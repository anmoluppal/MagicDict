#include "MagicDict.h"


MagicDict::MagicDict() : mMaxCharNum(MAX_CHARACTERS), mMaxWordLen(MAX_WORD_LENGTH) {
    init();
}

void MagicDict::insert(const char *word, const size_t sz) {
    if (sz > mMaxWordLen) {
        return;
    }
    if (!isInputWordValid(word, sz)) return;

    size_t sz_1 = sz - 1;

    for (size_t i = 0; i < sz_1; i++) {
        mLayerStack[i][word[i] - 'a'] |= mIsChildMask[word[i + 1] - 'a'];
    }

    mLayerStack[sz_1][word[sz_1] - 'a'] |= mIsTerminalMask[word[sz_1] - 'a'];
}

bool MagicDict::isWordExists(const char *word, const size_t sz) const {
    if (sz > mMaxWordLen) {
        return false;
    }
    if (!isInputWordValid(word, sz)) return false;

    size_t sz_1 = sz - 1;

    for (size_t i = 0; i < sz_1; i++) {
        if ((mLayerStack[i][word[i] - 'a'] & mIsChildMask[word[i + 1] - 'a']) == 0) {
            return false;
        }
    }

    return (mLayerStack[sz_1][word[sz_1] - 'a'] & mIsTerminalMask[word[sz_1] - 'a']) != 0;
}

void MagicDict::remove(const char *word, const size_t sz) {
    if (sz > mMaxWordLen) {
        return;
    }
    if (!isInputWordValid(word, sz)) return;

    size_t sz_1 = sz - 1;

    for (size_t i = 0; i < sz_1; i++) {
        if ((mLayerStack[i][word[i] - 'a'] & mIsChildMask[word[i + 1] - 'a']) == 0) {
            return;
        }
    }

    if ((mLayerStack[sz_1][word[sz_1] - 'a'] & mIsTerminalMask[word[sz_1] - 'a']) == 0) {
        return;
    }

    mLayerStack[sz_1][word[sz_1] - 'a'] ^= mIsTerminalMask[word[sz_1] - 'a'];
}

void MagicDict::serialize(std::ofstream &stream) const {
    if (!stream.good()) return;
    if (!stream.is_open()) return;


    stream.write((char *) &mMaxWordLen, sizeof(mMaxWordLen));
    stream.write((char *) &mMaxCharNum, sizeof(mMaxCharNum));

    for (int i = 0; i < mMaxWordLen; i++) {
        for (int j = 0; j < mMaxCharNum; j++) {
            stream.write((char *) &mLayerStack[i][j], sizeof(uint64_t));
        }
    }
}

void MagicDict::deserialize(std::ifstream &stream) {
    if (!stream.good()) return;
    if (!stream.is_open()) return;

    stream.read((char *) &mMaxWordLen, sizeof(mMaxWordLen));
    stream.read((char *) &mMaxCharNum, sizeof(mMaxCharNum));

    init();

    for (int i = 0; i < mMaxWordLen; i++) {
        for (int j = 0; j < mMaxCharNum; j++) {
            stream.read((char *) &mLayerStack[i][j], sizeof(uint64_t));
        }
    }
}

void MagicDict::init() {
    mLayer = Layer(mMaxCharNum, 0);
    mLayerStack = LayerStack(mMaxWordLen, mLayer);

    mIsChildMask = std::vector<uint64_t>(mMaxCharNum, 0);
    mIsTerminalMask = std::vector<uint64_t>(mMaxCharNum, 0);

    for (int nc = 0; nc < mMaxCharNum; nc++) {
        mIsChildMask[nc] = static_cast<uint64_t>(std::pow(2, nc));
    }
    for (int nt = mMaxCharNum; nt < 2 * mMaxCharNum; nt++) {
        mIsTerminalMask[nt - mMaxCharNum] = static_cast<uint64_t>(std::pow(2, nt));
    }
}

bool MagicDict::isInputWordValid(const char *word, const size_t sz) const {
    for (size_t i=0; i<sz; i++) {
        if (word[i] < CHAR_START || word[i] > CHAR_END) {
            return false;
        }
    }
    return true;
}
