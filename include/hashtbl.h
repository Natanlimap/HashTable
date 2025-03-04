#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>
#include <forward_list> // forward_list
#include <math.h>
#include <vector>
using namespace std;

namespace ac {

    template<class KeyType, class DataType,typename KeyHash = std :: hash < KeyType >,typename KeyEqual = std :: equal_to < KeyType > >
    class HashEntry
    {
        public:

            KeyType m_key;  // Armazena a chave associada a informcao
            DataType m_data;// A informacao.

            HashEntry( KeyType kt_, DataType dt_ ) : m_key(kt_), m_data(dt_)
            {/*Empty*/}
    };

    template<class KeyType, class DataType,typename KeyHash = std :: hash < KeyType >,typename KeyEqual = std :: equal_to < KeyType > >
    class HashTbl
    {
        public:
            // Aliases
            using entry_type = HashEntry<KeyType,DataType>;
            using list_type = std::forward_list< entry_type >;
            using size_type = std::size_t;

            explicit HashTbl( int TableSz_ = 11 ){
                m_Tablesz = returnPrime(TableSz_);
                m_data_table = new std::forward_list< entry_type >[m_Tablesz];
                m_count = 0;
            }

            HashTbl( const HashTbl& other){
                m_Tablesz = other.m_Tablesz;
                m_data_table = new std::forward_list< entry_type >[m_Tablesz];
                for(size_t i = 0;i < other.m_Tablesz - 1;i++){
                    auto it = other.m_data_table[i].begin();
                         while(it != other.m_data_table[i].end()){
                            m_data_table[i].push_front({it->m_key, it->m_data});
                            it++;
                    }
                }

                m_count = other.m_count;
            }  
            HashTbl( const std::initializer_list< entry_type > & inl){
                auto first = inl.begin();
                auto last = inl.end();
                size_t distance = std::distance(first, last);
                m_Tablesz = returnPrime(distance);
                m_data_table = new std::forward_list< entry_type >[m_Tablesz];
                m_count = 0;

                while(first != last){
                    insert(first->m_key, first->m_data);
                    first++;
                }
            }

            HashTbl& operator=( const HashTbl& other){
                clear();
                delete[]m_data_table;
                m_Tablesz = other.m_Tablesz;
                m_data_table = new std::forward_list< entry_type>[other.m_Tablesz];
                for(size_t i = 0; i < m_Tablesz;i++){
                    auto it = other.m_data_table[i].begin();
                    while(it != other.m_data_table[i].end()){
                            insert(it->m_key, it->m_data);
                        it++;
                    } 
                }
                return *this;
            }
            HashTbl& operator=( const std::initializer_list< entry_type > & inl){
               clear();
                delete[]m_data_table;
                m_Tablesz = std::distance(inl.begin(), inl.end());
                m_data_table = new std::forward_list< entry_type>[m_Tablesz];
                auto it = inl.begin();
                for(size_t i = 0; i < m_Tablesz;i++){
                        insert(it->m_key, it->m_data);
                        it++;
                } 

                return *this;
            }

            virtual ~HashTbl(){
                
            }

            bool insert( const KeyType & key, const DataType & data){
                m_count++;
                if(m_count > m_Tablesz){
                    rehash();
                    m_count++;
                }
                KeyEqual test;
                int pos = hashToInt(key); 
                 auto it = m_data_table[pos].begin();
                    while(it != m_data_table[pos].end()){
                        if(test(key, it->m_key) == true){
                            it->m_data = data;
                            return false;
                        }
                        it++;   
                    } 

                m_data_table[pos].push_front(entry_type(key, data));
                return true;
               
            } 
            bool retrieve( const KeyType & key, DataType & data){
                int pos = hashToInt(key);
                auto it = m_data_table[pos].begin();
                KeyEqual test;
                while(it != m_data_table[pos].end()){
                     if (test(key, it->m_key) == true){
                        data = it->m_data; 
                        return true;
                     }
                     it++;
                }
                        data = DataType();
                        return false;                
            }

            bool erase( const KeyType & key){
                int pos = hashToInt(key);
                KeyEqual test;
                auto it = m_data_table[pos].begin();
                while(it != m_data_table[pos].end()){
                    if(test(it->m_key, key) == true){
                        it->m_key = KeyType();
                        it->m_data= DataType();
                        m_count--;
                        return true;
                    }
                    it++;
                }
                return false;
            }

            void clear(){
                for(size_t i = 0;i < m_Tablesz - 1;i++){
                    auto it = m_data_table[i].begin();
                    auto it2 = m_data_table[i].end();
                    size_t distance = std::distance(it, it2);
                         while(distance > 0){
                            m_data_table[i].pop_front();
                            distance--;
                        }
                }
                m_count = 0;
            }

            bool empty() const{
                if(m_count == 0){
                    return true;
                }else{
                    return false;
                }
            }

            size_t distance_key(KeyType key){
                int pos = hashToInt(key);
                auto it = m_data_table[pos].begin();
                auto it2 = m_data_table[pos].end();
                return std::distance(it, it2);
            }

            inline size_type size() const { return m_count;}
            inline size_type tbl_size() const { return m_Tablesz;}

            DataType& at( const KeyType& key){
                KeyEqual test;
                int pos = hashToInt(key);
                auto it = m_data_table[pos].begin();
                while(it != m_data_table[pos].end()){
                        if(test(key, it->m_key) == true){
                            return it->m_data;
                        }
                        it++;
                }
                throw std::out_of_range("chave invalida");      

            }
            void print();

            DataType& operator[](const KeyType& key){
                KeyEqual test;
                int pos = hashToInt(key);
                auto it = m_data_table[pos].begin();
                while(it != m_data_table[pos].end()){
                        if(test(key, it->m_key) == true){
                            return it->m_data;
                        }
                        it++;
                }
                insert(key, DataType());
                return m_data_table[pos].begin()->m_data;
            }

            size_type count( const KeyType& key)const{
                size_t count = 0;
                int i = hashToInt(key);
                auto it = m_data_table[i].begin();
                    while(it != m_data_table[i].end()){
                        count++;
                        it++;
                    }
                return count;
                }


            friend std::ostream & operator<<( std::ostream & os_, const HashTbl & ht_ )
            {
                std::cout<<std::endl;   
                for(size_t i = 0;i < ht_.m_Tablesz ;i++){
                    std::cout << "[" << i << "]" << std::endl;
                    auto it = ht_.m_data_table[i].begin();
                    if(ht_.m_data_table[i].empty() == true){
                        std::cout << "EMPTY" <<std::endl;
                    }

                     else{
                        while(it != ht_.m_data_table[i].end()){
                            os_ << it->m_data << std::endl;
                            it++;
                        }
                    }
                }
                    
                return os_;
            }


            int hashToInt(const KeyType & key) const{
               return KeyHash()(key) % m_Tablesz; 
            }


            int returnPrime(int TableSz_){
              int count;
              while(1){
                count = 0;
                for(int i = 1; i <= TableSz_; i++){
                    if(TableSz_ % i == 0){
                        count++;
                    }
                }
                if(count == 2){
                    return TableSz_;
                }
                TableSz_++;
              }
                
            
            }

            //=== Private methods
        private:
            void rehash(){
                int new_m_Tablesz = returnPrime(2*m_Tablesz);
                HashTbl< KeyType, DataType, KeyHash, KeyEqual > aux{new_m_Tablesz};
                 for(size_t i = 0;i < m_Tablesz;i++){
                    auto it = m_data_table[i].begin();
                         while(it != m_data_table[i].end()){
                            aux.insert(it->m_key, it->m_data);
                            it++;
                    }
                }
                this->clear();
                delete[]m_data_table;
                m_data_table = aux.m_data_table;
                m_Tablesz = new_m_Tablesz;
                m_count = aux.m_count;
            }
    
               

            //=== Private members
        private:
            size_t m_Tablesz; //Tamanho da tabela
            unsigned int m_count; //!< Numero de elementos na tabel. 
            std::forward_list< entry_type> *m_data_table; //!< Tabela de listas para entradas de tabela.
    };

} // MyHashTable
#endif











