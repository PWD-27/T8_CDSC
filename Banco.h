#ifndef BANCO_H
#define BANCO_H
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "Cliente.h"
#include "Cuenta.h"
#include "CuentaAhorro.h"
#include "CuentaCorriente.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Banco {
private:
    string nombre;
    vector<Cliente> clientes;
    vector<Cuenta*> cuentas;
    double tasaInteresAhorro = 0.0;

public:
    Banco(const string& nombre);
    ~Banco();

    void setTasaInteres(double tasa);
    void agregarCliente(const string& nombre, const string& direccion);
    void agregarCuentaAhorro(int idCliente, double saldoInicial);
    void agregarCuentaCorriente(int idCliente, double saldoInicial, double limiteSobregiro);

    void listarClientes() const;
    void listarCuentas() const;

    void aplicarInteres();
    bool consignar(int numeroCuenta, double monto);
    bool retirar(int numeroCuenta, double monto);

    void mostrarEstadisticas() const;

    void guardarDatos(const string& rutaArchivo) const;
    void cargarDatos(const string& rutaArchivo);
};

#endif