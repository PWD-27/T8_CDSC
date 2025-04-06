#ifndef CUENTA_AHORRO_H
#define CUENTA_AHORRO_H

#include "Cuenta.h"

class CuentaAhorro : public Cuenta {
private:
    double tasaInteres;

public:
    CuentaAhorro() = default;
    CuentaAhorro(double saldoInicial, int idCliente, double tasaInteres);

    void aplicarInteresMensual();
    bool retirar(double cantidad) override;

    json toJson() const override;
    static CuentaAhorro fromJson(const json& j);

    double getTasaInteres() const;
    void setTasaInteres(double tasa);
};

#endif
