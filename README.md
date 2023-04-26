Egy Qt-ban elkészített sudoku játék kódja látható (a zip fájlban a játék is megtalálható).

A program úgy kezdődik, hogy kiválasztjuk, hogy új játékot akarunk, vagy betöltjük a már mentettet. Az új játék választása esetén a következő lépés a nehézségi szint eldöntése (könnyű, közepes, nehéz).
Ezután jön a sudoku legenerálása. Először 17 db véletlen számot (1 és 9 között) generál a program 17 db véletlen helyre a táblán. Utána megnézi a program, hogy a sudoku szabályai szerint tud-e beírni számokat (ha tud, akkor beírja), majd jón a backtrack.

Backtrack: a sudoku tábla jobb felső sarkától kezdve a program beírja a számokat növekvő sorrendbe azokba a cellákba, amikben még nincsenek számok. Ha egy cellába nem lehet egy számot se beírni, akkor az előző cellában lévő számot növeljük.

A backtrack után a kész sudoku tábla a Solution.txt fájlba kerül, majd a kiválasztott nehézségi szintnek megfelelő mennyiségű szám törlésre kerül úgy, hogy egyértelmű legyen a megoldás. Végül kezdetét veszi a játék.

A mentett játék betöltése érdekében, a játék kezdeti állapota mentésre kerül a firstnumbers.txt fájlba.
