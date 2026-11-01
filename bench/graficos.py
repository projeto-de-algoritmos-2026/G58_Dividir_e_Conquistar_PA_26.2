import math
import sys
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter

SAIDA = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(__file__).resolve().parent.parent / "docs" / "graficos"

# --- dados (README, Experimentos e comparação) -------------------------------

TRI_N = [1_000, 2_000, 4_000, 8_000, 16_000, 32_000, 64_000, 128_000]
TRI_MS = [0.86, 1.68, 3.42, 9.55, 15.31, 31.89, 69.43, 155.78]

KR_N = [500, 1_000, 2_000, 5_000]
KR_DELAUNAY_TOTAL_MS = [0.36, 0.81, 1.87, 4.81]  # triangulação + Kruskal
KR_COMPLETO_MS = [7.16, 32.01, 141.72, 1_004.30]

PP_N = [1_000, 2_000, 4_000, 8_000, 16_000, 32_000]
PP_DELAUNAY_MS = [0.75, 1.50, 3.25, 6.85, 14.57, 30.53]
PP_FORCA_BRUTA_MS = [0.62, 2.37, 9.50, 37.96, 150.57, 602.90]

# --- estilo ------------------------------------------------------------------

AZUL = "#2a78d6"      # série 1: Delaunay
LARANJA = "#eb6834"   # série 2: alternativa ingênua
REFERENCIA = "#8a8984"  # curva de referência
TINTA = "#0b0b0b"
TINTA_2 = "#52514e"
GRADE = "#e4e3df"
FUNDO = "#ffffff"

plt.rcParams.update({
    "font.family": "DejaVu Sans",
    "font.size": 11,
    "axes.edgecolor": GRADE,
    "axes.labelcolor": TINTA_2,
    "axes.titlesize": 13,
    "axes.titleweight": "bold",
    "axes.titlecolor": TINTA,
    "axes.titlelocation": "left",
    "axes.titlepad": 12,
    "axes.spines.top": False,
    "axes.spines.right": False,
    "axes.grid": True,
    "grid.color": GRADE,
    "grid.linewidth": 0.8,
    "xtick.color": TINTA_2,
    "ytick.color": TINTA_2,
    "figure.facecolor": FUNDO,
    "axes.facecolor": FUNDO,
    "legend.frameon": False,
    "legend.labelcolor": TINTA,
})


def numero_br(valor, casas=0):
    """1234.5 -> '1.234,5' (separadores do português)."""
    texto = f"{valor:,.{casas}f}"
    return texto.replace(",", "_").replace(".", ",").replace("_", ".")


milhar = FuncFormatter(lambda v, _: numero_br(v))


def ms(v, _=None):
    if v >= 1:
        return numero_br(v)
    return numero_br(v, 1)


def salvar(fig, nome):
    SAIDA.mkdir(parents=True, exist_ok=True)
    fig.savefig(SAIDA / nome, dpi=200, bbox_inches="tight", facecolor=FUNDO)
    plt.close(fig)
    print("gerado:", SAIDA / nome)


# --- 1. triangulação: Θ(n log n) ---------------------------------------------

def triangulacao():
    x = [n * math.log2(n) for n in TRI_N]
    # c que melhor ajusta t = c · n log2 n (mínimos quadrados pela origem)
    c_ms = sum(t * xi for t, xi in zip(TRI_MS, x)) / sum(xi * xi for xi in x)
    razao_ns = [t * 1e6 / xi for t, xi in zip(TRI_MS, x)]

    fig, (esq, dir_) = plt.subplots(1, 2, figsize=(12, 4.6))
    fig.subplots_adjust(wspace=0.28)

    curva_n = [1_000 * 1.02 ** i for i in range(0, 250)]
    curva_n = [n for n in curva_n if n <= 135_000]
    esq.plot(curva_n, [c_ms * n * math.log2(n) for n in curva_n], color=REFERENCIA,
             linewidth=2, linestyle=(0, (5, 4)), zorder=1)
    esq.plot(TRI_N, TRI_MS, linestyle="none", marker="o", markersize=8, color=AZUL,
             markeredgecolor=FUNDO, markeredgewidth=1.5, zorder=3)
    esq.annotate(f"c · n log₂ n,  c ≈ {numero_br(c_ms * 1e6)} ns", xy=(100_000, c_ms * 100_000 * math.log2(100_000)),
                 xytext=(52_000, 128), color=TINTA_2, fontsize=10,
                 arrowprops=dict(arrowstyle="-", color=REFERENCIA, linewidth=1))
    esq.set_title("Tempo medido")
    esq.set_ylabel("tempo (ms)")
    esq.set_xticks([0, 32_000, 64_000, 96_000, 128_000])
    esq.xaxis.set_major_formatter(FuncFormatter(lambda v, _: numero_br(v / 1000)))
    esq.set_xlabel("n (milhares de pontos)")
    esq.set_xlim(0, 135_000)
    esq.set_ylim(0, 170)

    c_ns = c_ms * 1e6
    dir_.axhline(c_ns, color=REFERENCIA, linewidth=2, linestyle=(0, (5, 4)), zorder=1)
    dir_.plot(TRI_N, razao_ns, color=AZUL, linewidth=2, marker="o", markersize=8,
              markeredgecolor=FUNDO, markeredgewidth=1.5, zorder=3)
    dir_.set_xscale("log", base=2)
    dir_.set_xticks(TRI_N)
    dir_.xaxis.set_major_formatter(FuncFormatter(lambda v, _: numero_br(v / 1000)))
    dir_.xaxis.set_minor_formatter(FuncFormatter(lambda v, _: ""))
    dir_.set_ylim(0, 120)
    dir_.set_title("Tempo ÷ n log₂ n")
    dir_.set_xlabel("n (milhares de pontos, escala logarítmica)")
    dir_.set_ylabel("ns por n log₂ n")
    dir_.text(1_000, c_ns - 6, f"c ≈ {numero_br(c_ns)} ns, o mesmo da curva ao lado", va="top",
              color=TINTA_2, fontsize=10)
    dir_.annotate("ruído de medição", xy=(8_000, razao_ns[3]), xytext=(9_500, 108),
                  color=TINTA_2, fontsize=9.5,
                  arrowprops=dict(arrowstyle="-", color=REFERENCIA, linewidth=1))

    fig.suptitle("Triangulação de Delaunay por dividir e conquistar", x=0.125, ha="left",
                 y=1.04, fontsize=15, fontweight="bold", color=TINTA)
    salvar(fig, "triangulacao_nlogn.png")


# --- 2. Kruskal na Delaunay x no grafo completo --------------------------------

def rotulo_fim(eixo, x, y, texto, cor_marca, subir=0):
    eixo.annotate(texto, xy=(x, y), xytext=(8, subir), textcoords="offset points", va="center",
                  color=TINTA, fontsize=10.5)


def comparacao(nome, titulo, n, rapido, lento, rotulo_rapido, rotulo_lento, nota):
    fig, eixo = plt.subplots(figsize=(9, 5.2))
    eixo.plot(n, lento, color=LARANJA, linewidth=2, marker="s", markersize=8,
              markeredgecolor=FUNDO, markeredgewidth=1.5, label=rotulo_lento, zorder=3)
    eixo.plot(n, rapido, color=AZUL, linewidth=2, marker="o", markersize=8,
              markeredgecolor=FUNDO, markeredgewidth=1.5, label=rotulo_rapido, zorder=3)
    eixo.set_xscale("log")
    eixo.set_yscale("log")
    eixo.set_xticks(n)
    eixo.xaxis.set_major_formatter(milhar)
    eixo.xaxis.set_minor_formatter(FuncFormatter(lambda v, _: ""))
    eixo.yaxis.set_major_formatter(FuncFormatter(ms))
    eixo.set_xlabel("n (pontos, escala logarítmica)")
    eixo.set_ylabel("tempo (ms, escala logarítmica)")
    eixo.set_title(titulo)
    eixo.set_xlim(n[0] / 1.25, n[-1] * 2.6)
    rotulo_fim(eixo, n[-1], lento[-1], numero_br(lento[-1], 0 if lento[-1] >= 100 else 2) + " ms", LARANJA)
    rotulo_fim(eixo, n[-1], rapido[-1], numero_br(rapido[-1], 2) + " ms", AZUL)
    eixo.legend(loc="upper left")
    eixo.text(0.99, 0.03, nota, transform=eixo.transAxes, ha="right", va="bottom", color=TINTA_2, fontsize=10.5)
    salvar(fig, nome)


def kruskal():
    razao = KR_COMPLETO_MS[-1] / KR_DELAUNAY_TOTAL_MS[-1]
    comparacao(
        "kruskal_delaunay_x_completo.png",
        "Kruskal (k = 10): Delaunay x grafo completo",
        KR_N, KR_DELAUNAY_TOTAL_MS, KR_COMPLETO_MS,
        "Kruskal na Delaunay + triangulação",
        "Kruskal no grafo completo",
        f"com 5.000 pontos: mais de {numero_br(razao // 100 * 100)}× mais rápido, com os mesmos grupos",
    )


def par_mais_proximo():
    razao = PP_FORCA_BRUTA_MS[-1] / PP_DELAUNAY_MS[-1]
    comparacao(
        "par_mais_proximo.png",
        "Par mais próximo: Delaunay x força bruta",
        PP_N, PP_DELAUNAY_MS, PP_FORCA_BRUTA_MS,
        "triangulação + menor aresta, O(n log n)",
        "força bruta, O(n²)",
        f"com 32.000 pontos: ≈ {numero_br(razao)}× mais rápido, mesma distância",
    )


# --- versões em escala normal: o formato das curvas ----------------------------
# Em escala normal, n² dobra para cima e n log n fica quase reto. Cada linha é a
# curva c · f(n) que melhor ajusta as medições (mínimos quadrados pela origem);
# os pontos são as medições.

def n_log_n(n):
    return n * math.log2(n)


def n_quadrado(n):
    return n * n


def n_quadrado_log_n(n):
    return n * n * math.log2(n)


def ajustar(f, n, tempos):
    """c que minimiza a soma de (t − c · f(n))²."""
    x = [f(v) for v in n]
    return sum(t * xi for t, xi in zip(tempos, x)) / sum(xi * xi for xi in x)


def curva(eixo, f, c, n_max, cor, rotulo, tracejada=False):
    xs = [n_max * i / 400 for i in range(1, 401)]
    eixo.plot(xs, [c * f(v) for v in xs], color=cor, linewidth=2, label=rotulo,
              linestyle=(0, (5, 4)) if tracejada else "-", zorder=2)


def pontos(eixo, n, tempos, cor, marcador):
    eixo.plot(n, tempos, linestyle="none", marker=marcador, markersize=8, color=cor,
              markeredgecolor=FUNDO, markeredgewidth=1.5, zorder=3)


def triangulacao_curvas():
    c_nlogn = ajustar(n_log_n, TRI_N, TRI_MS)
    c_n2 = ajustar(n_quadrado, TRI_N, TRI_MS)

    fig, eixo = plt.subplots(figsize=(9, 5.2))
    curva(eixo, n_quadrado, c_n2, 132_000, LARANJA, "se fosse Θ(n²): melhor curva c · n²", tracejada=True)
    curva(eixo, n_log_n, c_nlogn, 132_000, AZUL, "Θ(n log n): melhor curva c · n log₂ n")
    pontos(eixo, TRI_N, TRI_MS, AZUL, "o")
    eixo.set_xticks([0, 16_000, 32_000, 48_000, 64_000, 80_000, 96_000, 112_000, 128_000])
    eixo.xaxis.set_major_formatter(FuncFormatter(lambda v, _: numero_br(v / 1000)))
    eixo.set_xlim(0, 135_000)
    eixo.set_ylim(0, 175)
    eixo.set_xlabel("n (milhares de pontos)")
    eixo.set_ylabel("tempo (ms)")
    eixo.set_title("Triangulação de Delaunay por dividir e conquistar")
    eixo.legend(loc="upper left")
    eixo.annotate("a parábola passa longe\ndos pontos do meio", xy=(64_000, c_n2 * 64_000 ** 2),
                  xytext=(76_000, 18), color=TINTA_2, fontsize=10,
                  arrowprops=dict(arrowstyle="-", color=REFERENCIA, linewidth=1))
    eixo.text(0.99, 0.03, "pontos: medições · linhas: curvas ajustadas aos pontos", transform=eixo.transAxes,
              ha="right", va="bottom", color=TINTA_2, fontsize=10)
    salvar(fig, "triangulacao_curvas.png")


def comparacao_linear(nome, titulo, n, rapido, lento, f_rapido, f_lento, rotulo_rapido, rotulo_lento, nota):
    fig, eixo = plt.subplots(figsize=(9, 5.2))
    curva(eixo, f_lento, ajustar(f_lento, n, lento), n[-1], LARANJA, rotulo_lento)
    curva(eixo, f_rapido, ajustar(f_rapido, n, rapido), n[-1], AZUL, rotulo_rapido)
    pontos(eixo, n, lento, LARANJA, "s")
    pontos(eixo, n, rapido, AZUL, "o")
    eixo.xaxis.set_major_formatter(milhar)
    eixo.yaxis.set_major_formatter(milhar)
    eixo.set_xlim(0, n[-1] * 1.22)
    eixo.set_ylim(0, lento[-1] * 1.12)
    eixo.set_xlabel("n (pontos)")
    eixo.set_ylabel("tempo (ms)")
    eixo.set_title(titulo)
    rotulo_fim(eixo, n[-1], lento[-1], numero_br(lento[-1], 0) + " ms", LARANJA)
    rotulo_fim(eixo, n[-1], rapido[-1], numero_br(rapido[-1], 2) + " ms", AZUL, subir=10)
    eixo.legend(loc="upper left")
    eixo.text(0.99, 0.12, nota, transform=eixo.transAxes, ha="right", va="bottom", color=TINTA_2, fontsize=10)
    salvar(fig, nome)


def kruskal_linear():
    comparacao_linear(
        "kruskal_curvas.png",
        "Kruskal (k = 10): Delaunay x grafo completo",
        KR_N, KR_DELAUNAY_TOTAL_MS, KR_COMPLETO_MS, n_log_n, n_quadrado_log_n,
        "Delaunay + triangulação: c · n log n",
        "grafo completo: c · n² log n",
        "pontos: medições · linhas: curvas ajustadas aos pontos",
    )


def par_mais_proximo_linear():
    comparacao_linear(
        "par_mais_proximo_curvas.png",
        "Par mais próximo: Delaunay x força bruta",
        PP_N, PP_DELAUNAY_MS, PP_FORCA_BRUTA_MS, n_log_n, n_quadrado,
        "Delaunay: c · n log n",
        "força bruta: c · n²",
        "pontos: medições · linhas: curvas ajustadas aos pontos",
    )


if __name__ == "__main__":
    triangulacao()
    triangulacao_curvas()
    kruskal()
    kruskal_linear()
    par_mais_proximo()
    par_mais_proximo_linear()
