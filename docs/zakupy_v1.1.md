# Zakupy — Smart Access v1.1

Sprawdzone 2026-09-29 z datasheetami i footprintami płytki.
Stan magazynu sprawdź w koszyku — strona TME czasem pokazuje „0”, mimo że towar jest.

## Do kupienia — TME (jedno zamówienie)

| Na płytce | Co | Symbol TME | Ile | Dlaczego ten |
|---|---|---|---|---|
| C1 | 100 µF 25 V, Ø6,3 mm, rozstaw 2,5 mm | [ECA1EM101](https://www.tme.eu/pl/details/eca1em101/kondensatory-elektrolityczne-tht/panasonic/) | 2 | wymiary = footprint; 25 V zamiast 16 V jest OK (to maksimum, zapas nie szkodzi) |
| C3 | 10 µF 16 V, Ø5 mm, rozstaw 2,0 mm | [ECA1CM100](https://www.tme.eu/pl/details/eca1cm100/kondensatory-elektrolityczne-tht/panasonic/) | 2 | wymiary = footprint |
| Q1 | BC547B | [BC547B-DIO](https://www.tme.eu/pl/details/bc547b-dio/tranzystory-npn-tht/diotec-semiconductor/bc547b/) | 3 | nóżki 1=C 2=B 3=E, tak samo jak na schemacie |
| D3 | 1N4148 | [1N4148-DIO](https://www.tme.eu/pl/details/1n4148-dio/diody-uniwersalne-tht/diotec-semiconductor/1n4148/) | 3 | pomiń, jeśli masz w zestawie |
| R5, R6, R8 | rezystor 2 kΩ 1% | [MF0207FTE-2K](https://www.tme.eu/pl/details/mf0207fte-2k/rezystory-metalizowane-tht-06w/yageo/mf0207fte52-2k/) | 5 | od 1 szt.; tańsze węglowe 2k są wyprzedane |
| R1 | rezystor 300 Ω 1% | [MF0207FTE-300R](https://www.tme.eu/pl/details/mf0207fte-300r/rezystory-metalizowane-tht-06w/yageo/mf0207fte52-300r/) | 2 | od 1 szt. |

Zapasowy kondensator do C3, gdyby ECA1CM100 był niedostępny: dowolny 10 µF, 16–35 V,
**Ø5 mm**, rozstaw 2,0 mm albo 2,5 mm (ECA1CM100I; nóżki lekko ścisnąć do 2 mm).

## Do kupienia — Botland

| Co | Link | Ile |
|---|---|---|
| Zestaw nylonowych śrub i dystansów M3 (otwory montażowe H1–H4) | [Botland](https://botland.com.pl/srubki-i-nakretki/13577-zestaw-nylonowych-srubek-i-podkladek-dystansowych-m3-180-elementow-5904422320973.html) | 1 |
| Kable dupont żeńsko-żeńskie (tylko jeśli nie masz) | wyszukaj „przewody połączeniowe żeńsko-żeńskie” | 1 paczka |

## Płytki PCB

JLCPCB albo PCBWay, 5 szt. Pliki: `Zamek_RFID_Hardware/fab/v1.1/`.
Zamawiasz **po** sprawdzeniu footprintów z częściami w ręku.

## Już masz

| Na płytce | Co | Status |
|---|---|---|
| J1–J4 | goldpin męski 1x40 | OK |
| podstawka Nano | goldpin żeński 1x40 → 2×15 | OK |
| C2, C4 | 100 nF | sprawdź rozstaw nóżek: płytka ma 5 mm |
| R3, R4, R7, R9 | 1 kΩ z zestawu | OK |
| R2 | 200 Ω z zestawu | OK |
| D1, D2 | LED czerwona i zielona z zestawu | OK |
| BZ1 | buzzer HCM1206X | OK: Ø12×9,5 mm, rozstaw 7,6 mm = footprint; 6 V znamionowo, działa od 4 V |
| — | ARK KF301 | nie pasują do płytki, zapas |
| — | 2,2 kΩ z zestawu | **nie używać zamiast 2k** |
