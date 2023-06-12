#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

namespace ariel{

// helper function that checks if number prime
// used for prime iterator   
bool isPrime(int number) {
    if (number < 2) {
        return false;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}
// container contains four private vectors each with different purpouse:
//      - lements vector: store elements by the order ther are added.
//      - prime_vec vector: store only prime elements during addition.
//      - sidecross_vec  vector: used for sidecross.
//      - ascending_vec vector: sort elemetns in ascending order each time we use add function.
class MagicalContainer
    {
    private:
        std::vector<int> elements;
        std::vector<int> prime_vec;
        std::vector<int> sidecross_vec;
        std::vector<int> ascending_vec;

    public:

        MagicalContainer(){

        };
        
        ~MagicalContainer() = default;

        //add element to elements vector without doing nothing.
        //add element to ascending_vec after that perform ascending sort on ascending_vec.
        //check if element is prime, if so add it to prime_vec
        //Sidecross: create a temp vector that loops througth elemnts vector from diffirent side at a time(sidecross) and make sidecross vector = temp vector.
         void addElement(int element){
            elements.push_back(element);

            ascending_vec.push_back(element);

            std::sort(ascending_vec.begin(),ascending_vec.end());
            
            if(isPrime(element)){
            prime_vec.push_back(element);
            }

            std::vector<int> elements_temp;
        

        std::vector<int>::size_type counter=0;
        std::vector<int>::size_type next=0;
        std::vector<int>::size_type reverse=elements.size()-1;

        while(counter < elements.size() && next < reverse){
            elements_temp.push_back(elements.at(next));
            elements_temp.push_back(elements.at(reverse));
            next++;
            reverse--;
            counter++;      
        }

        if(elements.size() % 2 != 0){
            elements_temp.push_back(elements.at(next));
        }

        
         sidecross_vec=elements_temp;

        
        }
        // removes element from elements vector 
        // first find the index of the element then remove it.
        void removeElement(int element) {
            auto it = std::find(elements.begin(), elements.end(), element);
            if (it != elements.end()) {
            elements.erase(std::next(elements.begin(), std::distance(elements.begin(), it)));
            }
          
            else{
                throw std::runtime_error("container dons't contain this element");
            }

        }

        // return the size of elements vector which represents container size.
        int size() const{
            return elements.size();
        }

    // return elements vector.
    std::vector<int> getElements() {
    return elements;
    }

     // return prime vector.
    std::vector<int> getElements_prime() {
    return prime_vec;
    }

    // return ascending order vector.
    std::vector<int> getElements_Ascending() {
    return ascending_vec;
    }
    // return sidecross vector.
    std::vector<int> getElements_sidecross() {
    return sidecross_vec;
    }

// Ascending iterator contains two private values:
//     - Magical contianer: represents hte container that iterator iterates throught.
//     - index :represents the index that the iterator points to, at the moment.
class AscendingIterator{

    private:
        MagicalContainer & contianer_;
        std::vector<int>::size_type index;

    public:

//constructor:
// assign given container to private container_.
// start index = 0, points to the first of the contianer.
 AscendingIterator( MagicalContainer &container):contianer_(container){
    
        index = 0;
    }

    // copy constructor
    AscendingIterator(const AscendingIterator& ascIter):contianer_(ascIter.contianer_){
      
        index = ascIter.index;
    }
// points to the start of the container.
  AscendingIterator begin() {
    AscendingIterator itr(*this);
    itr.index = 0;
    return itr;
}

//points to the end of the container.
AscendingIterator end() {
    AscendingIterator itr(*this);
    itr.index = contianer_.ascending_vec.empty() ? 0 : contianer_.ascending_vec.size();
    return itr;
}

//update the pointer by one , point to the next element inside container.
//if index is already bigger or equal to container size(reached the end) , throw error.
AscendingIterator& operator++() {
   if (index >= contianer_.ascending_vec.size()) {
        throw std::runtime_error("out of range");
    }
        index++;
    return *this;
}

//decrease pointer by one.
//points to previous element inside the container.
    int operator--(){
        index--;
        return contianer_.ascending_vec[index];
    }
// return the value at place index.
    int operator*(){
        return contianer_.ascending_vec[index];
    }

//assign a new container to the Iterator.
    AscendingIterator operator=(const AscendingIterator &ascIter){
          if(contianer_.ascending_vec != ascIter.contianer_.ascending_vec){
            throw std::runtime_error("not equal containers");
        }
        contianer_ = ascIter.contianer_;
        index = ascIter.index;
        return *this;
    }

    bool  operator!=(const AscendingIterator &ascIter)const {
            return this->index!=ascIter.index;
    }

    bool operator==(const AscendingIterator &ascIter)const {
            return this->index==ascIter.index;
    }
    bool  operator>=(const AscendingIterator &ascIter)const {
            return this->index>=ascIter.index;
    }
    bool  operator<=(const AscendingIterator &ascIter) const {
            return this->index<=ascIter.index;
    }
    bool  operator<(const AscendingIterator &ascIter) const  {
            return this->index<ascIter.index;
    }
    bool   operator> (const AscendingIterator &ascIter) const{
            return this->index>ascIter.index;
    }

};

// Prime iterator contains two private values:
//     - Magical contianer: represents hte container that iterator iterates throught.
//     - index :represents the index that the iterator points to, at the moment.
class PrimeIterator{
    private:
        MagicalContainer & contianer_;
        std::vector<int>::size_type index;

    public:

//constructor:
// assign given container to private container_.
// start index = 0, points to the first of the contianer.
 PrimeIterator( MagicalContainer &container):contianer_(container){      
        index = 0;
    }

//copy constructor
    PrimeIterator(const PrimeIterator& PrimeIter):contianer_(PrimeIter.contianer_){
        index = PrimeIter.index;
    }

//points to the start of the contianer.
    PrimeIterator begin() {
    PrimeIterator itr(*this);
    itr.index = 0;
    return itr;
    }

//points to the end of the container.
    PrimeIterator end() {
        PrimeIterator itr(*this);
        itr.index = contianer_.prime_vec.empty() ? 0 : contianer_.prime_vec.size();
    return itr;
    }

//update the pointer by one , point to the next element inside container.
//if index is already bigger or equal to container size(reached the end) , throw error.
    PrimeIterator& operator++() {
        if (index >= contianer_.prime_vec.size()) {
            throw std::runtime_error("out of range");
        }
            index++;
    return *this; 
    }

//decrease pointer by one.
//points to previous element inside the container.
    int operator--(){
        index--;
        return contianer_.prime_vec[index];
    }
// return the value at place index.
    int operator*(){
        return contianer_.prime_vec[index];
    }
// assign a new container to the iterator.
  PrimeIterator operator=(const PrimeIterator &PrimeIter){
        if(contianer_.prime_vec != PrimeIter.contianer_.prime_vec){
            throw std::runtime_error("not equal containers");
        }
        contianer_.prime_vec = PrimeIter.contianer_.prime_vec;
        index = PrimeIter.index;
        return *this;
    }


        bool operator!=(const  PrimeIterator &PrimeIter)const {
                
                return this->index!=PrimeIter.index;
        } 

         bool  operator==(const  PrimeIterator &PrimeIter)const {
              
                return this->index==PrimeIter.index;

        }
         bool  operator>=(const  PrimeIterator &PrimeIter)const {
             
                return this->index >= PrimeIter.index;


        }
         bool  operator<=(const  PrimeIterator &PrimeIter)const {
               
                return this->index<=PrimeIter.index;
        }

        bool   operator<(const  PrimeIterator &PrimeIter)const {
            return this->index<PrimeIter.index;
        }
        bool   operator>(const PrimeIterator &PrimeIter)const {
            return this->index>PrimeIter.index;
         }

};

// SideCross iterator contains two private values:
//     - Magical contianer: represents hte container that iterator iterates throught.
//     - index :represents the index that the iterator points to, at the moment.
class SideCrossIterator{
    private:
        MagicalContainer & contianer_;
        std::vector<int>::size_type index;

    public:


//constructor:
// assign given container to private container_.
// start index = 0, points to the first of the contianer.
 SideCrossIterator(MagicalContainer &container):contianer_(container){      
        index = 0;
    }

//copy constructor.
     SideCrossIterator(const  SideCrossIterator& SideCrossIter):contianer_(SideCrossIter.contianer_){
        index = SideCrossIter.index;
    }

//points to the start of the contianer.
 SideCrossIterator begin() {
     SideCrossIterator itr(*this);
    itr.index = 0; 
    return itr;
}

//points to the end of the container.
 SideCrossIterator end() {
     SideCrossIterator itr(*this);
    itr.index = contianer_.sidecross_vec.empty() ? 0 : contianer_.sidecross_vec.size(); 
    return itr;
}

//update the pointer by one , point to the next element inside container.
//if index is already bigger or equal to container size(reached the end) , throw error.
SideCrossIterator& operator++() {
     if (index >= contianer_.sidecross_vec.size()) {
        throw std::runtime_error("out of range");
    }
        index++;
    return *this;
}
//decrease pointer by one.
//points to previous element inside the container.
    int  operator--(){
        index--;
        return contianer_.sidecross_vec[index];
    }

// return the value at place index.
    int  operator*(){
        return contianer_.sidecross_vec[index];
    }

// assign a new container to the iterator.
      SideCrossIterator operator=(const SideCrossIterator &SideCrossIter){
        if(contianer_.sidecross_vec != SideCrossIter.contianer_.sidecross_vec){
            throw std::runtime_error("not equal containers");
        }
        contianer_ = SideCrossIter.contianer_;
        index = SideCrossIter.index;
        return *this;
    }


    bool   operator!=(const SideCrossIterator &SideCrossIter)const {
        return this->index !=SideCrossIter.index;
    }

    bool operator==(const  SideCrossIterator &SideCrossIter)const {
        return this->index == SideCrossIter.index;
    }
    bool operator>=(const  SideCrossIterator &SideCrossIter)const {
        return this->index >= SideCrossIter.index;
    }
    bool  operator<=(const  SideCrossIterator &SideCrossIter)const {
        return this->index <= SideCrossIter.index;
    }
    bool  operator<(const  SideCrossIterator &SideCrossIter)const {
        return this->index < SideCrossIter.index;
    }
     bool operator>(const  SideCrossIterator &SideCrossIter)const {
        return this->index > SideCrossIter.index;
    }
};
    };

}


#endif
