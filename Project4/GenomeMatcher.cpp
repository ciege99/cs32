#include "provided.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <list>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Trie.h"
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_searchLength;
    unordered_map<string, Genome> m_genomes;
    Trie<DNAMatch> m_trie;
    
    //helper functions
    int recursiveEquivalentCheck(const string& a, const string& b, bool exactMatch) const;
    
    
    struct genomeMatchSortingFunc {
        bool operator() (const GenomeMatch &a, const GenomeMatch &b) const {
        if (a.percentMatch > b.percentMatch)
            return true;
        else if (a.percentMatch < b.percentMatch)   //return false if less than
            return false;
        else if (a.genomeName < b.genomeName)   //we want to sort in ascending alphabetical if they are equal
            return true;
        else
            return false;
        }
    };
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_searchLength = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomes.insert(pair<string, Genome>(genome.name(), genome));
    //m_genomes[genome.name()] = genome;    //add to map
    if (m_searchLength > genome.length())   //genome is too short
        return;
    
    for (int i = 0; i < genome.length()-m_searchLength+1; i++)  //stop looping when m_searchLength chars left
    {
        string fragment;    //extract fragments and then insert to trie
        genome.extract(i, m_searchLength, fragment);
        DNAMatch match; //create DNA match with relevant info
        match.genomeName = genome.name();
        match.position = i;
        //match.length = genome.length()-i; //length not known yet
        m_trie.insert(fragment, match);
    }
    // This compiles, but may not be correct
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_searchLength;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    //need to call find on the trie, will get back a vector of DNAMatch structs
    if (minimumLength < m_searchLength)
        return false;

    
    vector<DNAMatch> possibles;
    unordered_map<string, vector<DNAMatch>> definites;
    possibles = m_trie.find(fragment.substr(0, m_searchLength), exactMatchOnly);
    
    for (int i = 0; i < possibles.size(); i++)
    {
        DNAMatch cur = possibles[i];
        string subGen; //set subFrag = to beginning of searched for length
        
        for (int j = minimumLength; j <= fragment.size(); j++)
        {
            if (! m_genomes.at(cur.genomeName).extract(cur.position, j, subGen))
                break;  //can't extract a longer sequence
        }
        
        if (subGen.length() < minimumLength)
            continue;   // there wasn't a long enough match
        
        //subGen is now equal to a substring of genome with length >= minLength and <= fragment.size()
        
        int length = recursiveEquivalentCheck(subGen, fragment, exactMatchOnly);
        //length is now set to the match amount of subGen and fragment
        
        if (length < minimumLength)
            continue;   //not a long enough match
        
        possibles[i].length = length;   //set DNAMatch's length to be equal to discoverd length
        definites[possibles[i].genomeName].push_back(possibles[i]);  //put in map
    }

    if (definites.empty())  //no matches
        return false;
    
    vector<DNAMatch> results;
    
    for (unordered_map<string, vector<DNAMatch>>::iterator it = definites.begin(); it != definites.end(); it++)
    {
        DNAMatch greatest;
        greatest.length = 0;    //set equal to lowest amount for that genome
        greatest.genomeName = (*it).second[0].genomeName;
        for (int i = 0; i < (*it).second.size(); i++)
        {
            if ((*it).second[i].length > greatest.length)
            {
                greatest.length = (*it).second[i].length;
                greatest.position = (*it).second[i].position;
            }
            
            if ((*it).second[i].position < greatest.position && (*it).second[i].length >= greatest.length)
            {
                greatest.length = (*it).second[i].length;
                greatest.position = (*it).second[i].position;
            }
        }
        
        results.push_back(greatest);
    }

    matches = results;
    return true;
    
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < m_searchLength)
        return false;
    if (query.length() < fragmentMatchLength)
        return false;
    //numposs is the number of searches we will make
    int numPoss = (static_cast<int>(query.length()) / fragmentMatchLength);
    unordered_map<string, int>matched;    //this will hold the number of matches for each genome
    string fragment;    //this will be used to hold the extracted dna fragment
    vector<DNAMatch> resultMatches; //for the matches from findGenomes
    set<GenomeMatch, genomeMatchSortingFunc> genomeResults;
    
    
    //possibly use this to avoid the inner loop problem
    vector<vector<DNAMatch>> totalResults;
    
    for (unordered_map<string, Genome>::const_iterator it = m_genomes.begin(); it != m_genomes.end(); it++)
        matched[(*it).second.name()] = 0;   //initialize all matched slots to zero
        
    
    for (int i = 0; i < numPoss; i++)   //loop through each fragment and add to matched if match
    {
        query.extract(i*fragmentMatchLength, fragmentMatchLength, fragment);
        if (findGenomesWithThisDNA(fragment, fragmentMatchLength, exactMatchOnly, resultMatches))
        {
            totalResults.push_back(resultMatches);
//            for (int j = 0; j < resultMatches.size(); j++)
//                matched[resultMatches[j].genomeName] += 1;
        }
        
    }
    
    //event though this is nested for loop, it only loops for as many results as it gets from findGenomesWith
    //add to matched if there was a match
    for (int i = 0; i < totalResults.size(); i++)
    {
        for (int j = 0; j < totalResults[i].size(); j++)
            matched[totalResults[i][j].genomeName] += 1;
    }
    
    GenomeMatch temp;
    //this would be less than X because matches must be less than or equal to number of distinct hits
    for (unordered_map<string, int>::iterator it = matched.begin(); it != matched.end(); it++)
    {
        int intPercent = (10000* (*it).second)/ (numPoss);  //set percent to have 2 digits
        double percent = (intPercent/100.00);
        if (percent >= matchPercentThreshold)
        {
            temp.genomeName = (*it).first;  //set temp to be the match
            temp.percentMatch = percent;
            genomeResults.insert(temp);  //push temp onto genomeResults
        }
    }

    
    // need to sort in descending order.
    results.clear();
    for (set<GenomeMatch>::iterator it = genomeResults.begin(); it != genomeResults.end(); it++)
        results.push_back((*it));
    return true;
}


int GenomeMatcherImpl::recursiveEquivalentCheck(const string& a, const string &b, bool exactMatch) const
{
    if ((a.size() <= 0 && b.size() > 0)
        || (a.size() > 0 && b.size() <= 0))
        return 0; //mismatch
    
    if (a.size() == 1 && b.size() == 1 && a[0] == b[0])
        return 1;
    
    if(a.size() == 0)
        return 0;
    
    if (a[0] == b[0])
        return 1 + recursiveEquivalentCheck(a.substr(1), b.substr(1), exactMatch);
    if (a[0] != b[0] && !exactMatch)
        return 1 + recursiveEquivalentCheck(a.substr(1), b.substr(1), true);
    
    return 0;   //none of the conditions were met and should return 0
    
}


//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
