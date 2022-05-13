// CMSC 341 - Spring 2022 - Project 4
#include "dnadb.h"
DnaDb::DnaDb(int size, hash_fn hash){
    m_oldCap = 0;
    m_oldNumDeleted =0;
    m_oldSize = 0;
    m_oldTable = nullptr;
    m_currNumDeleted = 0;
    m_currentSize = 0;

    if (isPrime(size)){
        if (size > MAXPRIME){
            m_currentCap = MAXPRIME;
            size = MAXPRIME;
        }
        else if (size < MINPRIME){
            m_currentCap = MINPRIME;
            size = MINPRIME;
        }
        else{
            m_currentCap = size;
        }

        m_currentTable = new DNA[size];
        for(int i = 0; i< size; i++){
            m_currentTable[i] = EMPTY;
        }
    }
}

DnaDb::~DnaDb(){
    
}

bool DnaDb::insert(DNA dna){
    int index = 0;
    
    //regular insertion
    if (dna.m_location > MAXLOCID || dna.m_location < MINLOCID){
        return false;
    }
    else if (sequenceChecker(dna)){
        m_sequence += dna.m_sequence;
        return false;
    }
    else{
        index = DNASequenceGenerator(m_sequence, m_location);
        while (!m_currentTable[index] == EMPTY){
            m_currentTable[index] = dna;
            m_currentSize++;
            return true;
        }
        return 
    }
    m_hash()


    //insert into m_current table using hash_funct
    //do quadratic probing
    if (dna )
    //make sure DNA location in bound
    //make sure DNA not in iold list or current list
    //probe and find location it's supposed to be
    //check if criteria for new list is met
    //check if old list exists and transfer 25% to new list

    return true;
}

bool DnaDb::remove(DNA dna){
    return true;
}

DNA DnaDb::getDNA(string sequence, int location){
    DNA thig;
    return thig;
}

float DnaDb::lambda() const {
      return 0.233;
}

float DnaDb::deletedRatio() const {
    return 0.233;
}

int DnaDb::DNASequenceGenerator(int hashkey, int pos){
    //index = ((Hash(key) % TableSize) + (i x i)) % TableSize
    int index = 0;

    index = ((m_hash(m_sequence) % m_currentTable) + (pos * pos)) % m_currentTable;

    return index;
}

bool DnaDb::sequenceChecker(DNA dna){
    for (int i = 0; i < m_currentSize: i++){
        if (m_currentTable[i] == dna){
            return true;
        }

    }
    return false;
}

void DnaDb::dump() const {
    cout << "Dump for current table: " << endl;
    if (m_currentTable != nullptr)
        for (int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for old table: " << endl;
    if (m_oldTable != nullptr)
        for (int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool DnaDb::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int DnaDb::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

DNA::DNA(string sequence, int location) {
    if ((location >= MINLOCID && location <= MAXLOCID) ||
        (location == 0 && sequence == "DELETED")){
        // this is a normal or a DELETED object
        m_sequence = sequence;
        m_location = location;
    }
    else{
        // this is the empty object
        m_sequence = "";
        m_location = 0;
    }
}

string DNA::getSequence() const {
    return m_sequence;
}

int DNA::getLocId() const {
    return m_location;
}

// Overloaded assignment operator
const DNA& DNA::operator=(const DNA& rhs){
    if (this != &rhs){
        m_sequence = rhs.m_sequence;
        m_location = rhs.m_location;
    }
    return *this;
}

// Overloaded insertion operator.  Prints DNA's sequence (key),
// and the location ID. This is a friend function in DNA class.
ostream& operator<<(ostream& sout, const DNA &dna ) {
    if (!dna.m_sequence.empty())
        sout << dna.m_sequence << " (Location ID " << dna.m_location << ")";
    else
        sout << "";
  return sout;
}

// Overloaded equality operator. This is a friend function in DNA class.
// To test inequality we may negate the results of this operator.
bool operator==(const DNA& lhs, const DNA& rhs){
    return ((lhs.m_sequence == rhs.m_sequence) && (lhs.m_location == rhs.m_location));
}