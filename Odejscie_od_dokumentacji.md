# Co jest inaczej niż w dokumentacji
Ten plik ma na celu zebranie informacji o tym jak **kod** różni się od tego co jest w **dokumentacji implementacyjnej**.  
Dzięki temu będzie łatwiej napisać **raport końcowy** i połapać się w projekcie.

## GraphicsGenerator
### savePng
Metoda `savePng` nie przyjmuje ustawień `Config* c`. Nie są one potrzebne do generowania obrazu. Zamiast tego przyjmuję nazwę (może być ścieżka do pliku jaki ma być wygenerowany).  
Zamiast tekstu `char* data` jako pierwszy argument przyjmuje strukturę planszy. Łatwiej jest pracować na strukturze niż na tekście.

### saveGif
Zmiana nazwy metody na `saveHistoryAsGif` ponieważ w bibliotece do gifów istniej funkcja `saveGif`.
Zmiana argumentów z tego samego powodu co przy [savePng](###savePng).

## Rules
Modół potrzebuję połączenia z modułem Board, bo używa struktury CellState.
