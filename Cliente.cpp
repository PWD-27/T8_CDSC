#include "Cliente.h"

int Cliente::ultimoID = 0;

Cliente::Cliente(const string& nombre, const string& direccion)
    : nombre(nombre), direccion(direccion) {
    id = ++ultimoID;
}

int Cliente::getId() const {
    return id;
}

string Cliente::getNombre() const {
    return nombre;
}

string Cliente::getDireccion() const {
    return direccion;
}

void Cliente::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Cliente::setDireccion(const string& direccion) {
    this->direccion = direccion;
}

json Cliente::toJson() const {
    return {
            {"id", id},
            {"nombre", nombre},
            {"direccion", direccion}
    };
}

Cliente Cliente::fromJson(const json& j) {
    Cliente c;
    c.id = j.at("id").get<int>();
    c.nombre = j.at("nombre").get<string>();
    c.direccion = j.at("direccion").get<string>();

    if (c.id > ultimoID) {
        ultimoID = c.id;
    }

    return c;
}

void Cliente::setUltimoID(int id) {
    ultimoID = id;
}
