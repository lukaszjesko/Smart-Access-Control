# Smart Access Control — kontekst projektu

Kontrola dostępu: karta RFID → PIN na klawiaturze → otwarcie zamka przez przekaźnik.
Arduino Nano + PlatformIO, projekt płytki w KiCadzie w tym samym repo.

```
src/main.cpp              firmware (jedyny plik zrodlowy)
include/config.h          PIN i UID — PRYWATNY, w .gitignore
include/config.example.h  wzorzec do repo
Zamek_RFID_Hardware/      projekt KiCad + wyeksportowane gerbery
docs/lab-notebook.md      dziennik laboratoryjny — uzupełniany po każdej sesji
```

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
- Po nowym temacie zadaj 2–3 pytania sprawdzające i nie idź dalej, dopóki autor
  nie odpowie poprawnie.
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
| A0      | buzzer aktywny, HIGH = gra                 |
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
- W projekcie nie ma żadnego kondensatora odsprzęgającego.
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
- Buzzer sterowany wprost z pinu A0, bez tranzystora.

## Znane problemy sprzętowe — do poprawienia w KiCadzie przez autora

1. **KRYTYCZNE: obie diody LED są na schemacie wpięte odwrotnie.** Katoda idzie
   przez rezystor do pinu Arduino, anoda do masy — tak połączona dioda nie
   zaświeci się nigdy, niezależnie od kodu. Potwierdzone w pliku PCB:
   `D1 pad 1 (K) → Net-(D1-K) → R1 → A2`, `D1 pad 2 (A) → GND`.
   Poprawnie: pin Arduino → rezystor → anoda, katoda → masa.
   Obejście przy montażu: wlutować diody obrócone o 180°.
2. Kolejność pinów na złączu klawiatury J2 (C4 C3 C2 C1 R1 R2 R3 R4) nie
   odpowiada typowej taśmie klawiatury membranowej (R1 R2 R3 R4 C1 C2 C3 C4).
   Do sprawdzenia z konkretnym egzemplarzem. Jeśli się nie zgadza, poprawka jest
   w tablicy `keys[][]` albo w `rowPins`/`colPins`, nie na płytce.
3. Brak kondensatorów odsprzęgających — przynajmniej 100 nF + 10 µF przy RC522.
4. Rezystory R1, R2 i diody D1, D2 nie mają wartości w polu Value — BOM jest
   nie do wyprodukowania.
5. Brak otworów montażowych.
6. Wszystkie ścieżki 0,25 mm, łącznie z +5V i GND — brak klas sieci.
7. Poziomy logiczne: SPI z Nano na 5V, a MFRC522 dopuszcza max VDD+0,5V.
8. Nazwa sieci `/PRZEKAŹNIK` zawiera polski znak.
