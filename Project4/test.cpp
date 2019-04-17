//
//  test.cpp
//  Project4
//
//  Created by Collin Prince on 3/7/19.
//  Copyright © 2019 Collin Prince. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Trie.h"
#include "provided.h"

using namespace std;

/*
            c
        N      a
      t   g      t
 
 
 
 
 */


int main() {
//    Trie<int> test;
//    test.insert("ACTGC", 1);
//    test.insert("ACTGA", 2);
//
//    test.insert("CN", 9);
//    test.insert("CN", 17);
//    test.insert("CNT", 1);
//    test.insert("CNT", 2);
//    test.insert("CNG", 10);
//    test.insert("CNG", 20);
//    test.insert("CAT", 7);
//    test.insert("CAT", 8);
//    test.insert("CAT", 9);
//    test.printTest();
//    std::vector<int> values = test.find("CNT", false);
//    for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++)
//    {
//        std::cout << (*it) << std::endl;
//    }
    
    vector<Genome> genomes;
    string filename = "/Users/collin/Desktop/Halorientalis_regularis.txt";
    ifstream input(filename);
    if ( ! input )           // Did the creation fail?
    {
        cerr << "Error: Cannot create results.txt!" << endl;
    }
    
    Genome::load(input, genomes);   //from genome
    if (genomes.empty())
        cout << "well shit" << endl;
    
    cout << genomes.size() << endl;
    cout << genomes[0].name() << endl;
    cout << genomes[0].length() << endl;
    
    string fragment;
    cout << genomes[54].name() << endl;
    genomes[54].extract(0, 100, fragment);
    cout << fragment << endl;
    
    GenomeMatcher test(5);
    
    test.addGenome(genomes[0]);
    
    cout << "ok";
    
    
    /*
     Genome    1:    CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC
     Genome    2:    TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG
     Genome    3:    TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA
     
     
     */
//    string name1 = "Genome 1";
//    string name2 = "Genome 2";
//    string name3 = "Genome 3";
//    string seq1 = "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC";
//    string seq2 = "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG";
//    string seq3 = "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA";
//    Genome genome1(name1, seq1);
//    Genome genome2(name2, seq2);
//    Genome genome3(name3, seq3);
//
//    GenomeMatcher test(4);
//    test.addGenome(genome1);
//    test.addGenome(genome2);
//    test.addGenome(genome3);
//
//    vector<DNAMatch> matches;
//    bool result;
//    result = test.findGenomesWithThisDNA("GAAG", 4, true, matches);
//
//    if (result)
//        cout << "true" << endl;
//    cout << "I hope" << endl;
//
//    result    =    test.findGenomesWithThisDNA("GAATAC",    4,    true,    matches);
//    assert(result == true);
//
//    result    =    test.findGenomesWithThisDNA("GAATAC",    6,    true,    matches);
//    assert(result == false);
//
//    result    =    test.findGenomesWithThisDNA("GAATAC",    6,    false,    matches);
//    assert(result);
//
//    vector<DNAMatch> newMatches;
//    result    =    test.findGenomesWithThisDNA("GTATAT",    6,    false,    newMatches);
//    assert(result);
//
//    result    =    test.findGenomesWithThisDNA("GAATACG",    6,    false,    matches);
//    assert(result);
//
//    result    =    test.findGenomesWithThisDNA("GAAGGGTT",    5,    false,    matches);
//    assert(result);
//
//    result    =    test.findGenomesWithThisDNA("GAAGGGTT",    6,    false,    matches);
//    assert(result);
//
//    result    =    test.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC",    12,    false,    matches);
//    assert(result);
//
//    result    =    test.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG",    12,    false,    matches);
//    assert(result);
//
//    result    =    test.findGenomesWithThisDNA("GAAG",    3,    true,    matches);
//    assert(!result);
//
//    result    =    test.findGenomesWithThisDNA("GAAG",    5,    true,    matches);
//    assert(!result);
//
//    vector<GenomeMatch> wowplz;
//    Genome genome4("Genome 4", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
//    test.findRelatedGenomes(genome4, 4, false, 20, wowplz);
//
//    if (! wowplz.empty())
//        cout << "thank you" << endl;
    
}
