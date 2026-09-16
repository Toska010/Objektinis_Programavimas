#include <chrono>
#include <iostream>
#include <string>

using namespace std;

struct Person {
    public:
    string Vardas;
    string Pavarde;
    chrono::year_month_day Gimimo;

    Person(string vardas, string pavarde, chrono::year_month_day gimimo) {
        Vardas = vardas;
        Pavarde = pavarde;
        Gimimo = gimimo;
    }

    int SkaiciuotiAmziu() {
        auto dabar_lt = chrono::time_point_cast<chrono::days>(chrono::system_clock::now());
        chrono::year_month_day dabar{dabar_lt};
        int amzius = int(dabar.year()) - int(Gimimo.year());
        if (dabar.month() < Gimimo.month() || (dabar. month() == Gimimo.month() &&dabar.day() < Gimimo.day())) {
            amzius--;
        }
        return amzius;
    };
    int IkiGimtadienio() {
        auto dabar_lt = chrono::time_point_cast<chrono::days>(chrono::system_clock::now());
        chrono::year_month_day dabar{ dabar_lt };
        chrono::year_month_day gimtadienis{
            dabar.year(),
            Gimimo.month(),
            Gimimo.day()
        };
        chrono::sys_days siandien{ dabar };
        chrono::sys_days ikiGimtadienio{ gimtadienis };
        if (ikiGimtadienio < siandien) {
            gimtadienis = chrono::year_month_day{
                dabar.year() + chrono::years{1},
                Gimimo.month(),
                Gimimo.day()
            };

            ikiGimtadienio = chrono::sys_days{ gimtadienis };
        }

        return (ikiGimtadienio - siandien).count();
    }
};

int main() {
Person pirmas("Tautvydas", "Bagdzius", chrono::year{2000}/1/17);
    cout << "Vardas: " << pirmas.Vardas << "\nPavarde: " << pirmas.Pavarde << "\nAmzius: " << pirmas.SkaiciuotiAmziu() << endl;
    cout << "Iki gimtadienio liko: " << pirmas.IkiGimtadienio() << endl;
    return 0;
}
