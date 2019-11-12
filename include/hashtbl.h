#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>
#include <forward_list> // forward_list
#include <math.h>

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

            explicit HashTbl( int TableSz_ = DEFAULT_SIZE ){
                TableSz_ = returnPrime(TableSz_);
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
                int pos;
                pos = KeyHash()(key) % m_size; 
                std::cout<<pos;
            } 
            bool retrieve( const KeyType &, DataType & ) const;
            bool erase( const KeyType & );
            void clear();
            bool empty() const{
                if(m_count == 0){
                    return true;
                }else{
                    return false;
                }
            }
            inline size_type size() const { return m_count; }
            DataType& at( const KeyType& );
            DataType& operator[]( const KeyType& );
            size_type count( const KeyType& ) const;
            void print();
            friend std::ostream & operator<<( std::ostream & os_, const HashTbl & ht_ )
            {
                // TODO
                return os_;
            }
            int returnPrime(int TableSz_){
              return 11;
            
            }

            //=== Private methods
        private:
            void rehash();        //!< Change Hash table size if load factor >1.0
            //=== Private memnbers
        private:
            unsigned int m_size;  //!< Tamanho da tabela.
            unsigned int m_count; //!< Numero de elementos na tabel. 
            std::forward_list< entry_type > *m_data_table; //!< Tabela de listas para entradas de tabela.
            static const short DEFAULT_SIZE = 11;
    };

} // MyHashTable
#include "hashtbl.inl"
#endif











