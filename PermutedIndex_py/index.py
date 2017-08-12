import sys


def rotate(list, idx):
    ''' shift elements
        idxTH element become the first element
        it is equvalent to std::rotate in c++
        '''
    return list[idx:] + list[:idx]


class PermutedIndex:

    def __init__(self):
        self.maxLen = 0
        self.original = []  # (line, line_num)
        self.__splitted = []  # (words(more than one), lineNum)
        self.__rotated = []
        self.__notFormatted = []
        self.result = []
        return

    def fileIn(self):
        ''' press one more enter to exit getting inputs '''
        if(len(sys.argv) == 1):
            return
        with open(sys.argv[1], 'r', encoding="utf-8") as f:
            s = f.readline()
            self.maxLen = max(self.maxLen, len(s))
            self.original.append(s)
        return

    def __split(self):
        self.__splitted = [(line.split(), lineNum)
                           for lineNum, line in enumerate(self.original)]
        return

    def __rotate(self):
        self.__rotated = [(rotate(words, idx), idx, lineNum) for words, lineNum in self.__splitted
                          for idx in range(len(words))]
        self.__splitted.clear()
        return

    def __sort(self):
        self.__rotated.sort()
        return

    def __unrotate(self):
        self.__notFormatted = [(rotate(words, -wordNum), wordNum, lineNum)
                               for words, wordNum, lineNum in self.__rotated]
        self.__rotated.clear()
        return

    def __trim(self):
        separator = ' ' * 4
        self.maxLen += 4
        for words, wordNum, line in (self.__notFormatted):
            sz = 0
            retString = ""
            for idx, word in enumerate(words):
                if idx == wordNum:
                    sz = self.maxLen - (sz - 1)
                    retString = ' ' * sz + retString + separator
                sz = sz + len(word) + 1
                retString += word + ' '

            retString += ' ' * ((1 + self.maxLen) * 2 - len(retString))
            self.result.append((retString, wordNum, line))

        self.__notFormatted.clear()
        return

    def __compute(self):
        if self.result == []:
            self.__split()
            self.__rotate()
            self.__sort()
            self.__unrotate()
            self.__trim()

    def display(self):
        '''print order: sentence, word index, line number
            monospace font essential'''
        print("display order: sentence, word, line (0 index)")
        if self.result == []:
            self.__compute()
        print(*self.result, sep='\n')

        return

    def __del__(self):
        self.original.clear()
        self.__rotated.clear()
        return


def main():
    p = PermutedIndex()
    p.fileIn()
    p.display()
    return


if __name__ == "__main__":
    exit(int(main() or 0))
