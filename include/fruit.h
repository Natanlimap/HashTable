/*!
 *  Exemplo de como usar uma tabela hash já fronta (cliente).
 *  Realizado em sala de aula, no dia 12/nov.
 */

#include <unordered_map> // a tabela hash
#include <functional> // std::hash
#include <string>
#include <iostream>

using std::unordered_map;

/// Classe fruta.
class Fruit {

    public:
        Fruit( std::string n="", int w=0, int c=0 ) : name{n}, weight{w}, calories{ c} {}

        int get_weight(void) const { return weight; };
        int get_calories(void) const { return calories; }
        std::string get_name(void) const { return name; }

    private:
        std::string name; // Vamos usar o nome como chave.
        int weight;
        int calories;
};

std::ostream& operator<<( std::ostream &os, const Fruit & f )
{
    os << "[tipo: " << f.get_name() << ", weight: " << f.get_weight() << ", cal: " << f.get_calories() << "]";
    return os;
}

// Functor para gerar hash de fruta.
struct FruitHash {
    size_t operator()( std::string key ) const
    {
		// O hash é a soma acumulada de cada letra convertida para seu código assii.
        size_t hash_value{0};
        for ( char c : key )
            hash_value += (int) c;

        return hash_value;

        /*
		// Funcao hash alternativa.
        std::hash<std::string> my_hash;
        return my_hash( key );
        */
    }
};

/// Functor para comparar se duas chaves são iguais.
struct FruitEqual {
    bool operator()( const std::string &key1, const std::string &key2 ) const
    {
        return key1 == key2; // comparacao por nome.
    }
};



// / Cliente.
// int main(void) {

// 	// Tabela hash de frutas. Templates: < Chave, Dado, a hash function, como comparar chaves >
//     unordered_map< std::string, Fruit, FruitHash, FruitEqual > table;

// 	// Inserindo uma fruta.
//     table["laranja"] = Fruit( "laranja", 50, 55 );

//     std::cout << ">>> Hash da laranja: " << FruitHash()("laranja") << std::endl;

//     std::cout << ">>> Recuperando os dados da laranja: " << table["laranja"]  << std::endl;

	
// 	// Inserindo outra fruta, com método insert().
//     table.insert( std::make_pair("morango", Fruit( "morango", 100, 33 ) ) );

//     std::cout << ">>> Recuperando os dados do morango: " << table["morango"]  << std::endl;

//     std::cout << ">>> # elementos na tabela: " << table.size() << std::endl;

//     return 0;
// }
