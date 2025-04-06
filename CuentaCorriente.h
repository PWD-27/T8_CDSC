#ifndef CUENTA_CORRIENTE_H
#define CUENTA_CORRIENTE_H

#include "Cuenta.h"

class CuentaCorriente : public Cuenta {
private:
    double limiteSobregiro;

public:
    CuentaCorriente() = default;
    CuentaCorriente(double saldoInicial, int idCliente, double limiteSobregiro);

    bool retirar(double cantidad) override;

    json toJson() const override;
    static CuentaCorriente fromJson(const json& j);

    double getLimiteSobregiro() const;
    void setLimiteSobregiro(double limite);
};

#endif
