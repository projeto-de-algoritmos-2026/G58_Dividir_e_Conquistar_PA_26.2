
## Triangulação de Delaunay (dividir e conquistar)

| n | arestas | tempo (ms) | t / (n log2 n) (ns) |
|---:|---:|---:|---:|
| 1000 | 2977 | 0.86 | 86.3 |
| 2000 | 5975 | 1.68 | 76.6 |
| 4000 | 11976 | 3.42 | 71.4 |
| 8000 | 23973 | 9.55 | 92.1 |
| 16000 | 47971 | 15.31 | 68.5 |
| 32000 | 95974 | 31.89 | 66.6 |
| 64000 | 191970 | 69.43 | 67.9 |
| 128000 | 383966 | 155.78 | 71.7 |

## Kruskal: sobre a Delaunay x sobre o grafo completo (k = 10)

| n | arestas (Delaunay) | triangulação (ms) | Kruskal na Delaunay (ms) | total (ms) | arestas (completo) | Kruskal no completo (ms) |
|---:|---:|---:|---:|---:|---:|---:|
| 500 | 1479 | 0.29 | 0.07 | 0.36 | 124750 | 7.16 |
| 1000 | 2980 | 0.65 | 0.16 | 0.81 | 499500 | 32.01 |
| 2000 | 5978 | 1.53 | 0.34 | 1.87 | 1999000 | 141.72 |
| 5000 | 14977 | 3.81 | 1.00 | 4.81 | 12497500 | 1004.30 |

## Par mais próximo: menor aresta da Delaunay x força bruta

| n | Delaunay (ms) | força bruta (ms) | mesma distância? |
|---:|---:|---:|:---:|
| 1000 | 0.75 | 0.62 | sim |
| 2000 | 1.50 | 2.37 | sim |
| 4000 | 3.25 | 9.50 | sim |
| 8000 | 6.85 | 37.96 | sim |
| 16000 | 14.57 | 150.57 | sim |
| 32000 | 30.53 | 602.90 | sim |

## Dicionário inteiro do CMU

| etapa | tempo (ms) |
|---|---:|
| ler o dicionário (135166 entradas) | 83.0 |
| build(15): índice, triangulação e Kruskal | 63.0 |