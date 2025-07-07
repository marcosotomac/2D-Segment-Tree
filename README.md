# 📊 Árbol Segmentado 2D en C++

Esta es una implementación en C++ del **Segment Tree 2D**, una estructura de datos avanzada que permite realizar consultas y actualizaciones eficientes sobre submatrices en arreglos bidimensionales.

## 🔧 Características

- ✅ Construcción eficiente del árbol segmentado 2D
- ✅ Consulta de suma en rangos rectangulares: `O(log n × log m)`
- ✅ Actualización de un solo elemento
- ✅ Código modular y bien comentado
- ✅ Fácil de adaptar a operaciones como mínimo, máximo o AND/OR bit a bit

## 📁 Estructura

- `SegmentTree2D`: clase que encapsula la construcción y operaciones
- Métodos disponibles:
  - `SegmentTree2D(const vector<vector<int>>& input)` → Constructor con matriz base
  - `int query(int x1, int y1, int x2, int y2)` → Suma en submatriz definida por dos esquinas
  - `void update(int x, int y, int val)` → Actualiza el valor de la celda (x, y)

## ▶️ Ejemplo de uso

```cpp
#include <iostream>
#include <vector>
#include "SegmentTree2D.h" // si separas el archivo

int main() {
    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    SegmentTree2D st(mat);

    std::cout << "Suma (0,0)-(1,1): " << st.query(0, 0, 1, 1) << std::endl; // 12
    st.update(1, 1, 10);
    std::cout << "Suma (0,0)-(1,1) tras update: " << st.query(0, 0, 1, 1) << std::endl; // 17

    return 0;
}
