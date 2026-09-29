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

ceramiczny 100 nF: mała pojemność, prawie bez indukcyjności 
reaguje w nanosekundach, ale szybko się opróżnia
Od KRÓTKICH szpilek prądu — każde przełączenie układu cyfrowego
zegar Arduino 16 MHz
Przy 70 mA i spadku 0,25 V wystarcza na 0,36 µs

elektrolityczny 100 µF: 1000× większa pojemność, ale zwinięta folia
działa jak cewka reaguje wolniej.
Od DŁUŻSZYCH spadków, milisekundy załączenie przekaźnika, buzzera
Przy 70 mA i spadku 0,25 V wystarcza na 0,36 ms

Dlatego dajemy oba: ceramik łapie szybkie, elektrolit długie.
Ceramik jak najbliżej pinu zasilania — każdy mm ścieżki to dodatkowa indukcyjność.

podłączenie buzzera do bazy tranzysotra, strzałka na tranzystorze - emiter, dida do wciągania prądu który cofa się z cewki buzzera, 

jeśłi zasilanie to ścieżka 0.6 mm, zwykły sygnał to cienka ścieżka - opisanie klas 
tworzenie klasy - clearance - odstęp od innych wierszy, 

"pierścieniem" (annular ring) - przelotka 0.6 mm wiertło 0.4 mm - zostaje po 0.1 mm, rozwiązanie - zmniejszenie wiertła 

przy wylewce na spodzie siatka na 0.5mm - strefa 0.5 wewnątrz krawędzi 
clearance 0.3 zamiast 0.2 - wylewka dlaje od ścieżek, mniejsze ryzyko mostka cyny, 
pad connnections - thermal relief, 

przy gerberach zaznaczyć - subtract soldermask from silkscreen - farba nie wejdzie na pady
Use Protel filename - końcówki które firmy rozpoznają automatycznie, po zaznaczeniu - plot
-PTH.drl plik - pady, otwory metalizowane, -NPTH.drl - 4 otwory montażowe, niemetalizowane
BOM -> edytor schematu -> Tools -> Generate Bill of Materials → CSV do tego pliku - > export 

NPTH = 4x M3 mounting
holes - osobne pliki wierceń metalizowanych i niemetalizowanych (NPTH to
4 otwory M3)

