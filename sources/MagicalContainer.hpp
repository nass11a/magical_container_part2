#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

namespace ariel{
    
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

class MagicalContainer
    {
    private:
        std::vector<int> elements;
        std::vector<int> prime_vec;
        std::vector<int> sidecross_vec;
        std::vector<int> ascending_vec;

    public:
      //  using AscendingIterator=ariel::AscendingIterator;
      // using PrimeIterator=ariel::PrimeIterator;
      // using SideCrossIterator=ariel::SideCrossIterator;

        MagicalContainer(){

        };
        
        ~MagicalContainer() = default;
        void addElement(int element){
            elements.push_back(element);

            ascending_vec.push_back(element);
            //ascending_vec.erase(remove_if(ascending_vec.begin(), ascending_vec.end(), [](int num) { return !isPrime(num); }), ascending_vec.end());
            std::sort(ascending_vec.begin(),ascending_vec.end());
            
            if(isPrime(element)){
            prime_vec.push_back(element);
            }
            
            //prime_vec.erase(remove_if( prime_vec.begin(),  prime_vec.end(), [](int num) { return !isPrime(num); }),  prime_vec.end());

            //  sidecross_vec.push_back(element);
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
        void removeElement(int element) {
            auto it = std::find(elements.begin(), elements.end(), element);
            if (it != elements.end()) {
            elements.erase(std::next(elements.begin(), std::distance(elements.begin(), it)));
            }
          
            else{
                throw std::runtime_error("container dons't contain this element");
            }

        }

        int size() const{
            return elements.size();
        }
    std::vector<int> getElements() {
    return elements;
    }

    std::vector<int> getElements_prime() {
    return prime_vec;
    }


    std::vector<int> getElements_Ascending() {
    return ascending_vec;
    }

    std::vector<int> getElements_sidecross() {
    return sidecross_vec;
    }

class AscendingIterator{

    private:
        //std::vector<int> elements;
        MagicalContainer & contianer_;
        std::vector<int>::size_type index;

    public:

 AscendingIterator( MagicalContainer &container):contianer_(container){
       //contianer_ = container;
        
        index = 0;

    //std::sort(elements.begin(), elements.end());
    }

    AscendingIterator(const AscendingIterator& ascIter):contianer_(ascIter.contianer_){
        //contianer_ = ascIter.contianer_;
        index = ascIter.index;
    }

  AscendingIterator begin() {
    AscendingIterator itr(*this);
    itr.index = 0;
    return itr;
}


AscendingIterator end() {
    AscendingIterator itr(*this);
    itr.index = contianer_.ascending_vec.empty() ? 0 : contianer_.ascending_vec.size();
    return itr;
}

AscendingIterator& operator++() {
   if (index >= contianer_.ascending_vec.size()) {
        throw std::runtime_error("out of range");
    }
        index++;
    return *this;
}

    int operator--(){
        index--;
        return contianer_.ascending_vec[index];
    }
    int operator*(){
        return contianer_.ascending_vec[index];
    }

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

class PrimeIterator{
    private:
        //std::vector<int> elements;
        MagicalContainer & contianer_;
        std::vector<int>::size_type index;

    public:

 PrimeIterator( MagicalContainer &container):contianer_(container){
       //contianer_ = container;
        
        index = 0;

    //std::sort(elements.begin(), elements.end());
    }

    PrimeIterator(const PrimeIterator& ascIter):contianer_(ascIter.contianer_){
        //contianer_ = ascIter.contianer_;
        index = ascIter.index;
    }

    PrimeIterator begin() {
    PrimeIterator itr(*this);
    itr.index = 0;
    return itr;
    }


    PrimeIterator end() {
        PrimeIterator itr(*this);
        itr.index = contianer_.prime_vec.empty() ? 0 : contianer_.prime_vec.size();
    return itr;
    }

    PrimeIterator& operator++() {
        if (index >= contianer_.prime_vec.size()) {
            throw std::runtime_error("out of range");
        }
            index++;
    return *this; 
    }

    int operator--(){
        index--;
        return contianer_.prime_vec[index];
    }
    int operator*(){
        return contianer_.prime_vec[index];
    }

  PrimeIterator operator=(const PrimeIterator &ascIter){
        if(contianer_.prime_vec != ascIter.contianer_.prime_vec){
            throw std::runtime_error("not equal containers");
        }
        contianer_.prime_vec = ascIter.contianer_.prime_vec;
        index = ascIter.index;
        return *this;
    }


        bool operator!=(const  PrimeIterator &ascIter)const {
                
                return this->index!=ascIter.index;
        } 

         bool  operator==(const  PrimeIterator &ascIter)const {
              
                return this->index==ascIter.index;

        }
         bool  operator>=(const  PrimeIterator &ascIter)const {
             
                return this->index >= ascIter.index;


        }
         bool  operator<=(const  PrimeIterator &ascIter)const {
               
                return this->index<=ascIter.index;
        }

        bool   operator<(const  PrimeIterator &ascIter)const {
            return this->index<ascIter.index;
        }
        bool   operator>(const PrimeIterator &ascIter)const {
            return this->index>ascIter.index;
         }

};

class SideCrossIterator{
    private:
        //std::vector<int> elements;
        MagicalContainer & contianer_;
        std::vector<int>::size_type index;

    public:

 SideCrossIterator(MagicalContainer &container):contianer_(container){
       //contianer_ = container;
        
        index = 0;

    //std::sort(elements.begin(), elements.end());
    }

     SideCrossIterator(const  SideCrossIterator& ascIter):contianer_(ascIter.contianer_){
        //contianer_ = ascIter.contianer_;
        index = ascIter.index;
    }
 SideCrossIterator begin() {
     SideCrossIterator itr(*this);
    itr.index = 0; 
    return itr;
}


 SideCrossIterator end() {
     SideCrossIterator itr(*this);
    itr.index = contianer_.sidecross_vec.empty() ? 0 : contianer_.sidecross_vec.size(); 
    return itr;
}

SideCrossIterator& operator++() {
     if (index >= contianer_.sidecross_vec.size()) {
        throw std::runtime_error("out of range");
    }
        index++;
    return *this;
}
    int  operator--(){
        index--;
        return contianer_.sidecross_vec[index];
    }
    int  operator*(){
        return contianer_.sidecross_vec[index];
    }

      SideCrossIterator operator=(const SideCrossIterator &ascIter){
        if(contianer_.sidecross_vec != ascIter.contianer_.sidecross_vec){
            throw std::runtime_error("not equal containers");
        }
        contianer_ = ascIter.contianer_;
        index = ascIter.index;
        return *this;
    }


    bool   operator!=(const SideCrossIterator &ascIter)const {
        return this->index != ascIter.index;
    }

    bool operator==(const  SideCrossIterator &ascIter)const {
        return this->index == ascIter.index;
    }
    bool operator>=(const  SideCrossIterator &ascIter)const {
        return this->index >= ascIter.index;
    }
    bool  operator<=(const  SideCrossIterator &ascIter)const {
        return this->index <= ascIter.index;
    }
    bool  operator<(const  SideCrossIterator &ascIter)const {
        return this->index < ascIter.index;
    }
     bool operator>(const  SideCrossIterator &ascIter)const {
        return this->index > ascIter.index;
    }
};
    };

}


#endif