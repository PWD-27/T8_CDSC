#ifndef CUENTA_H
#define CUENTA_H
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Cuenta {
protected:
    static int ultimoNumeroCuenta;
    int numeroCuenta;
    double saldo;
    int idCliente;

public:
    Cuenta();
    Cuenta(double saldoInicial, int idCliente);

    virtual ~Cuenta() = default;

    int getNumeroCuenta() const;
    double getSaldo() const;
    int getIdCliente() const;

    void consignar(double cantidad);
    virtual bool retirar(double cantidad) = 0; // método puro

    virtual json toJson() const = 0;
    static void setUltimoNumeroCuenta(int numero);
};

#endif
