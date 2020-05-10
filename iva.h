/*
    Extra:

    El analista también le pide que desarrolle una clase donde tendrá como función el cálculo del iva mas el 25% 
    de ganancia sobre el precio costo y el resultado será el precio venta, la debe aplicar cada vez que agreguen 
    el precio costo, el precio venta automáticamente se calculara.
*/

class IVA {
    private:
        double iva;
        double ganancia; 
        double precio_venta;

    public:
        double obtener_precio_venta(double);
};

double IVA::obtener_precio_venta(double costo) {

    iva = 0.12 * costo;
    ganancia = 0.25 * costo;

    precio_venta = iva + ganancia + costo; 

    return precio_venta;
}