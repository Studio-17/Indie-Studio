# Indie Studio

## $\color{green}{Grade: A}$

> Setup
```
bash .github/scripts/setup.sh
```

> Build & Execute
```
cd build
cmake ..
cmake --build .
cd ..

./build/bomberman
```

> Generate Doxygen
```
cmake -DDOXYGEN=ON ..
```

> Run Unit Tests
```
cmake -DUNIT_TEST=ON ..
...

./build/unit_tests

```

#

Made by :

Clement FERNANDES <clement.fernandes@epitech.eu>

Gurvan LE LETTY <gurvan.le-letty@epitech.eu>

Martin VANAUD <martin.vanaud@epitech.eu>

Maxime CARABINA <maxime.carabina@epitech.eu>

Valentin DURIEUX <valentin.durieux@epitech.eu>

Victor PALLE <victor.palle@epitech.eu>
