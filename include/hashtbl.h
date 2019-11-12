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
                m_data_table = new std::forward_list< entry_type >[TableSz_];
                m_size = 0;
                m_count = 0;
            }

            HashTbl( const HashTbl& );
            HashTbl( const std::initializer_list< entry_type > & );
            HashTbl& operator=( const HashTbl& );
            HashTbl& operator=( const std::initializer_list< entry_type > & );

            virtual ~HashTbl(){
            
            }

            bool insert( const KeyType & key, const DataType & data){
                //falta verificar se ja existe
                int pos = hashToInt(key); 
                m_data_table[pos].push_front({key, data});
                m_count++;
               
            } 
            bool retrieve( const KeyType & key, DataType & data) const{
                int pos = hashToInt(key);
                auto it = m_data_table[pos].begin();
                while(it != m_data_table[pos].end()){
                    if(data == it->data){
                        return true;
                    }
                    it++;
                }
                return false;
            }

            bool erase( const KeyType & );

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
            }

            bool empty() const{
                if(m_count == 0){
                    return true;
                }else{
                    return false;
                }
            }
            inline size_type size() const { return m_count; }

            DataType& at( const KeyType& );

            // DataType& operator[]( const KeyType& key){
            //     return m_data_table[]
            // }

            size_type count( const KeyType& ) const;


            void print(){

            }

            friend std::ostream & operator<<( std::ostream & os_, const HashTbl & ht_ )
            {
                for(size_t i = 0;i < ht_.m_Tablesz - 1;i++){
                    auto it = ht_.m_data_table[i].begin();
                         while(it != ht_.m_data_table[i].end()){
                            os_ << "CHAVE --> [ " << i << " ] "<<it->m_key <<" DADOs --> "<< it->m_data << std::endl;
                            it++;
                    }

                    }
                
                return os_;
            }

            int hashToInt(const KeyType & key){
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
            void rehash();        //!< Change Hash table size if load factor >1.0
            //=== Private memnbers
        private:
            unsigned int m_size;  //!< Tamanho da tabela.
            unsigned int m_count; //!< Numero de elementos na tabel. 
            std::forward_list< entry_type> *m_data_table; //!< Tabela de listas para entradas de tabela.
            size_t m_Tablesz;
    };

} // MyHashTable
#include "hashtbl.inl"
#endif











