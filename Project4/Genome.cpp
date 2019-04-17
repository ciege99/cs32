#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <cctype>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
    int m_size;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
    m_size = static_cast<int>(sequence.size());
    // This compiles, but may not be correct
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    string s;
    string name = "";   //initialize to empty str
    string sequence;
    while (getline(genomeSource, s))
    {
        if (s[0] == '>')
        {
            if (name.size() > 0)
                genomes.push_back(Genome(name, sequence));
            name = s.substr(1); //reset for new genome
            sequence = "";
            continue;
        }

                for (int i = 0; i < s.size(); i++)
                {
                    if (toupper(s[i]) ==  'A' ||    //make sure character is a base
                        toupper(s[i]) ==  'T' ||
                        toupper(s[i]) ==  'C' ||
                        toupper(s[i]) ==  'G' ||
                        toupper(s[i]) ==  'N')
                        sequence += toupper(s[i]);
                    else
                        return false;   //return false if not a valid base
                }
    }
    genomes.push_back(Genome(name, sequence));
    return true;  //true if this point is reached
}

int GenomeImpl::length() const
{
    return static_cast<int>(m_sequence.size());  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (length > this->length())  //length is too long
        return false;
    if (position >= this->length())   //position is too high
        return false;
    if (position + length > this->length())    //ending position is too high
        return false;
    
    fragment = m_sequence.substr(position, length);
    return true;  //
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}


