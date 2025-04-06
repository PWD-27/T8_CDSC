#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Cliente {
private:
    static int ultimoID;
    int id;
    string nombre;
    string direccion;

public:
    Cliente() = default;
    Cliente(const string& nombre, const string& direccion);

    int getId() const;
    string getNombre() const;
    string getDireccion() const;

    void setNombre(const string& nombre);
    void setDireccion(const string& direccion);

    json toJson() const;
    static Cliente fromJson(const json& j);
    static void setUltimoID(int id);
};

#endif

