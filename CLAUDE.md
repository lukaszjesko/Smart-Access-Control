# Smart Access Control — kontekst projektu

Kontrola dostępu: karta RFID → PIN na klawiaturze → otwarcie zamka przez przekaźnik.
Arduino Nano + PlatformIO, projekt płytki w KiCadzie w tym samym repo.

```
src/main.cpp              firmware (jedyny plik zrodlowy)
include/config.h          PIN i UID — PRYWATNY, w .gitignore
include/config.example.h  wzorzec do repo
Zamek_RFID_Hardware/      projekt KiCad + wyeksportowane gerbery
docs/lab-notebook.md      dziennik laboratoryjny — pisze go WYŁĄCZNIE autor
```

**`docs/lab-notebook.md` to prywatne notatki autora. Nie dopisuj tam niczego i
nie poprawiaj go.** Możesz go czytać, żeby wiedzieć, co autor zrobił i zrozumiał.

## Stan projektu (aktualizuj na koniec każdej sesji)

Ostatnia aktualizacja: **2026-09-24**. Wybrany wariant: **B — pełna v1.1**
(wszystkie znane problemy sprzętowe naprawione przed zamówieniem płytek).

**Schemat v1.1 — ZAMKNIĘTY. ERC: 0 błędów, 0 ostrzeżeń.** Zrobione:
- D1/D2 obrócone (pin → R → anoda, katoda → GND); R1 = 300 Ω (czerwona,
  Vf≈2 V), R2 = 200 Ω (zielona, założone Vf≈3 V — sprawdzić z kupioną diodą,
  przy Vf≈2 V dać 300 Ω). Prąd 10 mA.
- Flagi No Connect na D0, D1, 2×RESET, AREF, A6, A7, VIN; `PWR_FLAG` na GND.
- Sieć `PRZEKAŹNIK` → `RELAY`.
- Kondensatory: C1 100 µF/16 V + C2 100 nF na +5V (przy przekaźniku J4),
  C3 10 µF/16 V + C4 100 nF na +3.3V (przy czytniku J1).
- Dzielniki 1k/2k (→3,33 V) na liniach Nano→RC522: SS (R3/R5), MOSI (R4/R6),
  SCK (R7/R8). Sieci po stronie czytnika: `RFID_*_3V3`. MISO bez zmian
  (3,3 V > próg VIH 3,0 V ATmegi).
- Buzzer przez BC547 (Q1): A0 → R9 1k → baza, emiter GND, kolektor → BZ1(−),
  BZ1(+) → +5V, D3 1N4148 równolegle do buzzera (katoda do +5V).
  Logika w firmware bez zmian: HIGH = gra.
- Punkty testowe TP1 +3.3V, TP2 GND, TP3 +5V.
- Otwory montażowe H1–H4 (`MountingHole_3.2mm_M3`, bez pada).
- Drobiazg: R6 ma wartość `2K` zamiast `2k`.

**PCB v1.1 — W TOKU.** Plik PCB jest jeszcze w stanie po naprawie diod
(D1/D2 przestawione na X=154.46, obrót 180°, wylewka przelana); zmian ze
schematu v1.1 nie przeniesiono. Plan:
- **P2 ← NASTĘPNY KROK:** `F8` (Update PCB from Schematic).
- P3: usunąć stare ścieżki, które po F8 zwierają różne sieci — SPI Nano→J1
  (SS, MOSI, SCK idą teraz przez dzielniki) oraz buzzer (BZ1 pin 1 jest teraz
  +5V, pin 2 kolektorem Q1, a nie GND).
- P4: rozmieszczenie: C1/C2 przy J4, C3/C4 przy J1, dzielniki między Nano a J1,
  Q1/D3/R9 przy buzzerze, TP przy krawędzi, H1–H4 w narożnikach. Płytka
  (53,6 × 61,5 mm) może wymagać powiększenia; jeśli zabraknie miejsca, opcja:
  nowe rezystory w footprincie P7.62 mm zamiast P10.16 mm.
- P5: klasa sieci „Power” 0,6 mm dla +5V, +3.3V, GND.
- P6: routing.
- P7: sitodruk — opisy J1–J4 (J1 ma odwróconą kolejność względem RC522),
  wersja „v1.1” i data; usunąć prostokąt narysowany na B.Cu
  (114.7–159.0 × 73.4–126.5 mm, bez sieci); poprawić nachodzenie napisu D1
  na D2; wiszący odcinek GND przy (147.10, 101.00).
- P8: wylewka (`B`), DRC = 0, widok 3D, nowe gerbery (stare w
  `GERBERY_RFID/` są z 2026-09-02, sprzed poprawek — NIE wysyłać ich), BOM.

**Po PCB:** README jest nieaktualne — twierdzi „ERC clean” i „All fixed in
v1.1” zanim to była prawda, wskazuje nieistniejące `hardware/` i
`docs/img/board.jpg`; `.kibot.yaml` szuka plików w `hardware/`. Do poprawy
po zamknięciu PCB. Dodatkowo `Zamek_RFID_Hardware/Zamek_RFID_Hardware/.history`
(lokalna historia KiCada, osobne repo git) jest śledzone jako gitlink mimo
wpisu w `.gitignore` — do usunięcia z indeksu (`git rm --cached`).

## Jak pracujemy (ustalone z autorem)

- Autor sam klika w KiCadzie. Claude daje dokładne instrukcje GUI (klawisz,
  menu, gdzie kliknąć, co ma się pojawić), a po „zrobione” sprawdza plik:
  `kicad-cli sch erc`, `kicad-cli pcb drc` (na kopii w scratchpadzie,
  z `--refill-zones` bez `--save-board`), eksport netlisty i porównanie połączeń.
- Najpierw krótki plan całego etapu, potem punkt po punkcie. Tempo ma być
  szybkie: przy każdej zmianie 1–2 zdania „po co”, bez pytań sprawdzających
  blokujących dalszą pracę. Autor chce umieć wytłumaczyć każdą zmianę
  rekruterowi — przy nowym temacie daj jedno zdanie „dla rekrutera”.
- Pułapki, na które autor już trafił: siatka schematu musi być 1,27 mm (piny
  Nano są między punktami siatki 2,54 mm); jednostki mają być w mm; do
  zaznaczania jednego typu obiektu służy Selection Filter; symbole `+3V3`
  i `+3.3V` to RÓŻNE sieci — w projekcie używamy `+3.3V`; nazwa etykiety =
  sieć, więc obie etykiety tej samej sieci muszą mieć identyczny tekst.

## O autorze i celu

Student 3. semestru mikroelektroniki i komunikacji cyfrowej na Politechnice
Poznańskiej. Buduje portfolio sprzętowe pod staż embedded/PCB. Kierunek
długoterminowy: elektronika mocy.

**To jest projekt, który autor pisze sam, żeby się nauczyć.** Commit, którego
autor nie umie wytłumaczyć na rozmowie kwalifikacyjnej, jest bezwartościowy.

## Najważniejsza zasada

Nie przepisuj działającego kodu na „lepszy". Nie zmieniaj architektury, nazw ani
stylu, jeśli nie zostałeś o to wprost poproszony. Jeśli widzisz coś do poprawy —
powiedz, na czym polega problem i co się stanie, jeśli go zostawić, ale
**czekaj na decyzję zamiast od razu zmieniać**.

Małe, pojedyncze zmiany zamiast dużych refaktorów. Po zmianie wyjaśnij, co
zrobiłeś i dlaczego, w jednym akapicie.

## Jak uczyć autora

- Rozbijaj instrukcje na małe, ponumerowane kroki prostym językiem.
- Tłumacz DLACZEGO, nie tylko co. Podawaj stronę datasheetu albo normę, jeśli
  wartość z nich wynika.
- Po nowym temacie możesz zadać 1–2 pytania sprawdzające, ale nie blokuj nimi
  dalszej pracy — autor uznał to za zbyt wolne (sesja 2026-09-24).
- Kiedy autor się myli, powiedz wprost. Nie łagodź.
- Nie wymyślaj numerów katalogowych, pinów ani wyników pomiarów. Jak nie wiesz —
  powiedz i sprawdź.
- Przy zakupach podawaj konkretnie: co, gdzie, ile.
- Przy diagnozowaniu usterki najpierw zadawaj pytania naprowadzające. Podpowiadaj
  dopiero, gdy autor utknie.

## Platforma

- Arduino Nano v3 (ATmega328P) — 2 kB RAM, 32 kB flash.
- PlatformIO, środowisko `nanoatmega328new`. `Serial.begin(115200)`.
- Biblioteki: `chris--a/Keypad`, `marcoschwartz/LiquidCrystal_I2C`, `miguelbalboa/MFRC522`.
- `arduino-libraries/Servo` jest w `lib_deps`, ale nic go nie używa.

Obecne zużycie: **13580 B flash (41%), 853 B RAM (42%)**. Jeśli po zmianie RAM
przekroczy ~70%, zgłoś to — na 2 kB trzeba zostawić zapas na stos.

## Jak weryfikować zmiany

Po każdej zmianie w `src/` albo `include/`:

```
pio run
```

`pio run -t upload` i `pio device monitor` uruchamia autor, nie Ty — to wymaga
podpiętej płytki. Jeśli zmiana wymaga sprawdzenia na sprzęcie, napisz to wprost
zamiast zakładać, że działa.

## Pinout — sprawdzony wobec schematu

Netlista z `Zamek_RFID_Hardware.kicad_sch` zgadza się z kodem co do pinu.
Jeśli chcesz zmienić przypisanie pinu — **zgłoś to zamiast zmieniać**, bo trzeba
wtedy poprawić schemat i PCB.

| Nano    | Funkcja                                    |
|---------|--------------------------------------------|
| D2–D5   | klawiatura, kolumny C4, C3, C2, C1         |
| D6–D9   | klawiatura, rzędy R1–R4                    |
| D10     | SS czytnika RC522                          |
| D11–D13 | SPI: MOSI, MISO, SCK                       |
| A0      | buzzer aktywny przez tranzystor Q1, HIGH = gra |
| A1      | LED zielona                                |
| A2      | LED czerwona                               |
| A3      | przekaźnik — **LOW załącza**, HIGH zwalnia |
| A4/A5   | I²C do LCD (adres 0x27)                    |

**Wszystkie użyteczne piny są zajęte.** Zanim zaproponujesz cokolwiek, co
potrzebuje nowego pinu (czujnik drzwi, przycisk wyjścia), powiedz o tym wprost.
Wolne zostają tylko D0/D1 (UART — utrata debugowania) oraz A6/A7, które na Nano
są **wyłącznie wejściami analogowymi** i nie mogą być wyjściami ani pinami
klawiatury.

## Fakty sprzętowe

- RST czytnika RC522 jest na płytce podciągnięty na stałe do 3.3V. Dlatego w
  kodzie `RST_PIN -1` (biblioteka czyta to jako 255 = `MFRC522::UNUSED_PIN`)
  i reset programowy.
- IRQ czytnika jest niepodłączony — odczyt tylko przez odpytywanie w `loop()`.
- RC522 zasilany z pinu 3V3 Nano. To słabe źródło, a czytnik ciągnie w impulsie
  ~100 mA. Przy losowych nieodczytach to pierwszy podejrzany, nie kod.
  W v1.1 wspiera go para C3 10 µF + C4 100 nF przy J1.
- Linie SS, MOSI, SCK idą do czytnika przez dzielniki 1k/2k (v1.1).
- Złącze J1 ma kolejność odwróconą względem modułu RC522 — pin 1 płytki trafia
  na pin 8 modułu. Działa, ale wymaga opisu na sitodruku.

## Konwencje

- Nazwy i komentarze w tym projekcie po polsku, bez znaków diakrytycznych
  (tak jest w istniejącym kodzie — nie zmieniamy w trakcie).
  **Projekt 3 pisany będzie po angielsku od początku.**
- README, dokumentacja i opisy commitów po angielsku.
- Teksty na LCD: bez diakrytyków, maksymalnie **16 znaków** na linię.
- Architektura to maszyna stanów (`enum StanSystemu`) w `switch` wewnątrz
  `loop()`. Nową funkcjonalność dodawaj jako stan.
- Nazwy sieci w KiCadzie wyłącznie ASCII — polskie znaki psują narzędzia CAM.

## Bezpieczeństwo

- `include/config.h` zawiera PIN i UID. Jest w `.gitignore`. **Nie commituj go,
  nie wklejaj jego zawartości do innych plików, do README ani do opisów commitów.**
- Przy zmianie struktury `config.h` aktualizuj `include/config.example.h`.
- Uwaga historyczna: PIN był wcześniej wpisany wprost w `main.cpp` i trafił do
  publicznej historii repozytorium. **Trzeba go zmienić na inny.**
- Nigdy nie commituj sekretu. Jeśli jakiś trafi do commita — zgłoś to od razu
  i głośno.

## Zasady sprzętowe (obowiązują w każdym projekcie)

- Każdy układ scalony dostaje 100 nF przy pinie zasilania. Pojemność bufforowa
  na wejściu płytki.
- Sieci zasilania mają własną klasę: min. 0,5–0,8 mm, nigdy domyślna sygnałowa.
- Każda płytka ma otwory montażowe.
- Każdy element bierny ma realną wartość, a gdzie trzeba — napięcie i tolerancję.
- Sprawdzaj poziomy logiczne na każdym styku układów o różnym zasilaniu.
  Nic nie jest tolerancyjne, dopóki datasheet tego nie mówi.
- ERC i DRC muszą być czyste przed wygenerowaniem Gerberów.

## KiCad

- **Nie edytuj plików KiCad.** Pliki `.kicad_sch` i `.kicad_pcb` możesz czytać
  i porównywać netlistę z pinoutem w kodzie, ale poprawki nanosi autor w GUI.
- `GERBERY_RFID/` jest generowane z PCB — nie edytuj ręcznie.

## Checklista przed zamówieniem płytek

Przejdź ją i powiedz, które punkty nie przechodzą:

1. ERC czyste, DRC czyste, wylewki przelane na nowo
2. Każdy footprint porównany z rysunkiem z datasheetu prawdziwego elementu
3. Pin 1 oznaczony na sitodruku przy każdym złączu
4. Otwory montażowe obecne i pasujące do obudowy
5. Wersja płytki i data na sitodruku
6. Punkty testowe na każdej szynie zasilania i na masie
7. Odsprzęganie przy każdym pinie zasilania
8. Szerokości ścieżek zasilania dobrane do rzeczywistego prądu
9. BOM kompletny, realne numery katalogowe, wszystko dostępne
10. Widok 3D sprawdzony pod kątem kolizji mechanicznych

## Znane rzeczy, świadomie zostawione na później

To nie są zadania do wykonania z własnej inicjatywy. Są tu, żebyś ich nie
zgłaszał w kółko jako nowych odkryć.

- `delay()` w stanach `ZAAKCEPTOWANY` i `ODRZUCONY` blokuje system na 2–3 s.
- Brak timeoutu na wpisywanie PIN-u po odczycie karty.
- Brak limitu nieudanych prób PIN-u.
- `pokazLinie()` jest zdefiniowana, ale jeszcze nieużywana.
- Klawisze `*`, `#` i `A`–`D` trafiają do bufora PIN-u.
- Autoryzacja po samym UID — UID karty MIFARE Classic łatwo sklonować.

## Znane problemy sprzętowe

Naprawione na schemacie v1.1 (szczegóły w sekcji „Stan projektu”): odwrócone
diody LED, brak kondensatorów, brak wartości R/LED, brak otworów montażowych,
poziomy logiczne SPI, buzzer bez tranzystora, polski znak w nazwie sieci.

Nadal otwarte:
1. Wszystkie ścieżki 0,25 mm, łącznie z +5V i GND — brak klas sieci (krok P5).
2. Kolejność pinów na złączu klawiatury J2 (C4 C3 C2 C1 R1 R2 R3 R4) nie
   odpowiada typowej taśmie klawiatury membranowej (R1 R2 R3 R4 C1 C2 C3 C4).
   Do sprawdzenia z konkretnym egzemplarzem. Jeśli się nie zgadza, poprawka jest
   w tablicy `keys[][]` albo w `rowPins`/`colPins`, nie na płytce.
