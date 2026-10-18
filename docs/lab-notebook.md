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

gerber po jednym pliku na warstwę, drl - jakim wiertłem gdzie i jak wiercić

zamawianie na stronie - outer copper weight 1 oz, 35 um miedzi tak jak w projkecie , 1 oz miedzi przy ścieżce 0,6mm 
spokojnie wystarcza na prąd przekaźnika i czytnika 

## 2026-10-18

lutowanie od najniższych: rezystory, D3, C2 C4, Q1, podstawki nano, goldpiny, ledy, elektrolity, buzzer
pady GND na wylewce, cyna nie przechodzi na drugą stronę, wylewka odciąga ciepło, 


test zwarć TP3-TP2, TP1-TP2, TP3-TP1 przed i po lutowaniu - nic nie piszczy (z elektrolitem krótki pisk - kondensator się ładuje)
vf zielonej led 1,91 V (5V z nano przez 300 om) R2 = 300 om, ok 10 mA. 
multimetr w trybie diody pokazuje OL powyżej ok 2 V
bez modułów TP3 4,46 V, TP1 3,28 V
LCD, RFID, klawiatura działają za pierwszym razem, klawiatura pin w pin (C4 na kwadratowy pad)

problem: przekaźnik nie klika, dioda na module świeci, ekran przygasa przy otwarciu
ekran przygasa = spada napięcie na całej szynie 5V, nie wina samego przekaźnika
przekaźnik SRD-05VDC potrzebuje min 75% napięcia = 3,75 V
TP3: 3,94 V spoczynek, 3,44 V z przekaźnikiem, za mało
inny kabel - to samo, kabel odpada
ładowarka zamiast laptopa, to samo,laptop odpada
pin 5V na nano tyle samo co TP3 moja płytka odpada
na spodzie nano dioda S4 między USB a 5V

nano poza płytką, przekaźnik wprost do nano, przed diodą 5,06 V, za diodą 3,8, dioda zabiera 1,26 V (schottky powinien ok 0,3 V)
wniosek: zła dioda w klonie nano, wymiana na MBR0520LT1G (SOD-123, ten sam typ co w oryginalnym nano)
zasada - mierzyć punkt po punkcie wzdłuż drogi prądu, zmieniać jedną rzecz naraz