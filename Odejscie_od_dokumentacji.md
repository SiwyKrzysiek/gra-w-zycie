# Co jest inaczej niż w dokumentacji
Ten plik ma na celu zebranie informacji o tym jak **kod** różni się od tego co jest w **dokumentacji implementacyjnej**.  
Dzięki temu będzie łatwiej napisać **raport końcowy** i połapać się w projekcie.

## GraphicsGenerator
### Skalowanie obrazu
Zostały dodane nowe funkcje pomocnicze związane z przeskalowywaniem obrazu. Okazało się, że po stworzeniu obrazu, o rozmiarze w pikselach takich jak plansza, domyślnie jest on wyświetlany w bardzo małej wielkości przez typowe programy. By tego uniknąć dodana została funkcjonalność przeskalowywania obrazów do minimalnej wielkości.  
By skalowanie było uniwersalne pracuje ono na wartościach pikseli, z których ma powstać grafika. Dzięki temu jest niezależne od palet barw, które są różne dla generowania png i gif.  
Skalowanie może tylko zwiększyć wymiary obrazu.  
#### Nowe funkcje
Na potrzeby skalowania zostały napisane funkcje:
* `Pixel *translateBoardToPixels(Board *board, Pixel valueOfAlive, Pixel valueOfDead)` -- funkcja zamieniąca planszę na tablicę pikseli,
* void getUpscaledImageSize(int orginalX, int orginalY, int *newX, int *newY) -- funkcja pomocnicza licząca jakie będą wymiary obrazu po przeskalowaniu
* Pixel *upscaleImage(const Pixel *original, int imageX, int imageY) -- funkcja dokonująca przeskalowania




### savePng
Metoda `savePng` nie przyjmuje ustawień `Config* c`. Nie są one potrzebne do generowania obrazu. Zamiast tego przyjmuję nazwę (może być ścieżka do pliku jaki ma być wygenerowany).  
Zamiast tekstu `char* data` jako pierwszy argument przyjmuje strukturę planszy. Łatwiej jest pracować na strukturze niż na tekście.

### saveGif
Zmiana nazwy metody na `saveHistoryAsGif` ponieważ w bibliotece do gifów istniej funkcja `saveGif`.
Zmiana argumentów z tego samego powodu co przy [savePng](###savePng).

## Rules
Modół potrzebuję połączenia z modułem `Board`, bo używa struktury `CellState`. Dodano funkcję `countALive` zliczającą żywe komórki w otoczeniu.

## Simulator
Funkcja `getArea`, nie potrzebuje rozmiaru planszy, może go pobierać ze stałej `SIZE` w Rules.

## Saver
Nowy moduł organizujący zapisywanie/wyświetlanie wyników. Funkcje:  
`void setup()`  
`void saveCommon(Board** history, Config* config, int i, char* extension)` - wspólna część zapisywanie do png i txt,  
`void saveAsPng(Board** history, Config* config, int i)` - zapisywanie do png,  
`void saveAsTxt(Board** history, Config* config, int i)` - zapisywanie do txt,  
`void saveAsGif(Board** history, Config* config, int historySize)` - zapisywanie do gif,  
`void printToStdout(Board** history, Config* config, int i)` - wyświetlanie w terminalu.  

## BoardHander
**disposeBoard** zwalnia również otrzymany wskaźnik. Dzięki temu nie trzeba potem wywoływać free dla wskaźnika.