# C-SudokuSolver
No memory leaks

## Installation :

Clone repository, then
#### Linux
``` sh
git clone https://github.com/anthonyraymond/SudokuSolver.git
cd SudokuSolver/
make
```
#### Windows
Use Cmake to compile windows version.


## Usage :
Suppose you want to solve the following grid :

| 8 | 0 | 0 |#| 0 | 0 | 0 |#| 0 | 0 | 0 |<br />
| 0 | 0 | 3 |#| 6 | 0 | 0 |#| 0 | 0 | 0 |<br />
| 0 | 7 | 0 |#| 0 | 9 | 0 |#| 2 | 0 | 0 |<br />
\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#<br />
| 0 | 5 | 0 |#| 0 | 0 | 7 |#| 0 | 0 | 0 |<br />
| 0 | 0 | 0 |#| 0 | 4 | 5 |#| 7 | 0 | 0 |<br />
| 0 | 0 | 0 |#| 1 | 0 | 0 |#| 0 | 3 | 0 |<br />
\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#<br />
| 0 | 0 | 1 |#| 0 | 0 | 0 |#| 0 | 6 | 8 |<br />
| 0 | 0 | 8 |#| 5 | 0 | 0 |#| 0 | 1 | 0 |<br />
| 0 | 9 | 0 |#| 0 | 0 | 0 |#| 4 | 0 | 0 |<br />

./sudokuSolver 800000000-003600000-070090200-050007000-000045700-000100030-001000068-008500010-090000400

### Output :
The output is the solved grid formatted the same way as the input.
