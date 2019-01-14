### American Name
What’s in a name? In a racialized society it could mean access to financial loans, job interviews, favorable response in academia and greater earnings. One’s name can often be used as a proxy for race, and race is a problem that will continue to exist as long as white rage exists.

Americans and Immigrants to the United States are at times faced with forsaking their identities to fit into a society where whiteness is the dominant power structure. The need to accomodate whiteness may involve changing one’s speech/accent, dress, food and name. Those with foreign sounding names, often ‘non-white’, are expected to provide nicknames or shortened versions of their names as an attempt to integrate into society.

This app uses an [Double Metaphone](https://en.wikipedia.org/wiki/Metaphone#Double_Metaphone) 
algorithm an English phonetic algorithm 
and [Levenshtein Distance](https://en.wikipedia.org/wiki/Levenshtein_distance) string comparison
algorithm to transform a name into its nearest sounding English counterpart (as much as is possible).
I'm using the U.S. Census'  publicly available [dataset](https://www.ssa.gov/oact/babynames/limits.html)
of the top popular ~2000 names from 2008.

## Install
* compile: `gcc main.c double_metaphone.c levenshtein.c -o an`


### Open Source Libraries
C version
* [double metaphone](
https://github.com/oubiwann/metaphone/tree/38b385b1239a3edec125dfd2a46767a3ba2d5b2c/resources)
* [Levenshtein](https://github.com/wooorm/levenshtein.c)

Javsacript Version
* [double metaphone](https://github.com/words/levenshtein-edit-distance)
* [levenshtein distance](https://github.com/words/levenshtein-edit-distance)

