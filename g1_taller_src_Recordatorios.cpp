#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    // Completar declaraciones funciones
    Fecha(int mes, int dia);
    int mes();
    int dia();
    void incrementar_dia();
    bool operator<(Fecha f);

    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

  private:
    //Completar miembros internos
    int mes_;
    int dia_;
};

Fecha::Fecha(int mes, int dia) : mes_(mes), dia_(dia) {}

int Fecha::mes() {
    return mes_;
}

int Fecha::dia() {
    return dia_;
}

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    // Completar iguadad (ej 9)
    bool igual_mes = this->mes() == o.mes();

    return igual_dia && igual_mes;
}

void Fecha::incrementar_dia() {
    //Caso 31 de diciembre
    if(mes_ == 12 && dia_ == 31){
        mes_= 1;
        dia_= 1;
    }
    if (dia() == dias_en_mes(mes())){
        mes_++;
        dia_ = 1;
    } else {
        dia_++;
    }
}

bool Fecha::operator<(Fecha f) {
    bool fecha_menor = false;
    if (this->mes() < f.mes())
        fecha_menor = true;
    if (this->mes() == f.mes()){
        if (this->dia() < f.dia()){
            fecha_menor = true;
        }
    }
    return fecha_menor;
}

#endif

// Ejercicio 11, 12

// Clase Horario

class Horario{
    public:
        Horario(uint hora, uint min);
        uint hora();
        uint min();
        bool operator==(Horario h);
        bool operator<(Horario h);

    private:
        int hora_;
        int min_;
};

Horario::Horario(uint hora, uint min) : hora_(hora), min_(min) {}

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}

bool Horario::operator==(Horario h) {
    bool igual_hora = this->hora() == h.hora();
    bool igual_minutos = this->min() == h.min();

    return igual_hora && igual_minutos;
}

bool Horario::operator<(Horario h) {
    bool hora_menor = false;
    if (this->hora() < h.hora())
        hora_menor = true;
    if (this->hora() > h.hora())
        hora_menor = false;
    if (this->hora() == h.hora()){
        if (this->min() < h.min()){
            hora_menor= true;
        }
    }
    return hora_menor;
}

ostream& operator<<(ostream& os, Horario h) {
    os << h.hora() << ":" << h.min();
    return os;
}


// Ejercicio 13

// Clase Recordatorio

class Recordatorio {
    public:
        Recordatorio(Fecha fecha, Horario horario, string mensaje);
        string mensaje();
        Fecha fecha();
        Horario horario();
        bool operator<(Recordatorio r);

    private:
        string mensaje_;
        Fecha fecha_;
        Horario horario_;
};

Recordatorio::Recordatorio(Fecha fecha, Horario horario, string mensaje) : fecha_(fecha), horario_(horario), mensaje_(mensaje){};

string Recordatorio::mensaje() {
    return mensaje_;
}

Fecha Recordatorio::fecha() {
    return fecha_;
}

Horario Recordatorio::horario() {
    return horario_;
}

bool Recordatorio::operator<(Recordatorio r) {
    bool recordatorio_menor = false;
    if (this->fecha() < r.fecha())
        recordatorio_menor = true;
    if (this->fecha() == r.fecha()){
        if (this->horario() < r.horario()){
            recordatorio_menor = true;
        }
    }
    return recordatorio_menor;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.mensaje() << " @ " << r.fecha() << " " << r.horario();
    return os;
}

// Ejercicio 14

// Clase Agenda

class Agenda {
    public:
        Agenda(Fecha fecha_inicial);
        void agregar_recordatorio(Recordatorio rec);
        void incrementar_dia();
        list<Recordatorio> recordatorios_de_hoy();
        Fecha hoy();

    private:
        list<Recordatorio> recordatorios_de_hoy_;
        Fecha hoy_;
};

Agenda::Agenda(Fecha fecha_inicial) : hoy_(fecha_inicial), recordatorios_de_hoy_(){}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    recordatorios_de_hoy_.push_back(rec);
    recordatorios_de_hoy_.sort();
}

void Agenda::incrementar_dia() {
    hoy_.incrementar_dia();
}

list <Recordatorio> Agenda::recordatorios_de_hoy() {
    return recordatorios_de_hoy_;
}

Fecha Agenda::hoy() {
    return hoy_;
}

ostream& operator<<(ostream& os, Agenda a) {
    os << a.hoy() << endl;
    os << "=====" << endl;
    for(auto i : a.recordatorios_de_hoy()) {
        if (i.fecha() == a.hoy())
            os << i << endl;
    }
    return os;
}