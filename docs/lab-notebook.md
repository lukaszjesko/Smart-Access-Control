# Lab notebook

Format: data, co robiłem, co zaobserwowałem, co z tego wynika.
Wpisuję też porażki — one są najcenniejsze.

## 2026-09-22
- Przegląd v1.0 wykazał brak kondensatorów odsprzęgających.
- Zapad napięcia przy załączaniu przekaźnika, który obszedłem
  programowo (stan HIGH), był w rzeczywistości problemem sprzętowym.
- Wniosek: problem zasilania rozwiązuje się zasilaniem, nie kodem.

## 2026-09-24

anoda dłuższa wchodzi prąd, katoda krótsza ścieta do gnd ok na stykówce ale źle na schemacie 
siatka była ustawiona 2.54 a nie 1,27 przez co nie mozna było ustwić punktów q, bo wielokrotności arduino nano to 1.27 

dodane kondensatory elektrolityczne, mają dużą pojemność ale w środku mają zwiniętą folię która ma indukcyjność, więc przy szybkich zmianach nie nadąża, jest od dłużych spadków napięcia 

ceramiczny 100nF mała pojemność, prawie bez indukcyjności działa na MHz, jest od dłuższych spadków napięcia 

podłączenie buzzera do bazy tranzysotra, strzałka na tranzystorze - emiter, dida do wciągania prądu który cofa się z cewki buzzera, 