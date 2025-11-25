import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import beta

# Parâmetros desejados
media_desejada = 5.824
desvio_desejado = 2.2902
lower, upper = 0, 10

# Escala para o intervalo [0, 1]
media_esc = (media_desejada - lower) / (upper - lower)
var_esc = (desvio_desejado / (upper - lower)) ** 2

# Calcula parâmetros a e b da Beta
# (usando fórmulas invertidas de média e variância)
temp = media_esc * (1 - media_esc) / var_esc - 1
a = media_esc * temp
b = (1 - media_esc) * temp

print(f"Parâmetros Beta ajustados: a={a:.4f}, b={b:.4f}")

# Cria distribuição Beta escalada para [0,10]
x = np.linspace(lower, upper, 1000)
y = beta.pdf((x - lower) / (upper - lower), a, b) / (upper - lower)

# Gera amostras simuladas
samples = beta.rvs(a, b, size=100000) * (upper - lower) + lower

# Estatísticas observadas
media_obs = np.mean(samples)
desvio_obs = np.std(samples)
print(f"Média observada: {media_obs:.4f}")
print(f"Desvio padrão observado: {desvio_obs:.4f}")

# Plot
plt.figure(figsize=(8,5))
plt.hist(samples, bins=50, density=True, alpha=0.6, color='skyblue', label='Simulação Beta ajustada')
plt.plot(x, y, 'r-', lw=2, label='PDF Beta ajustada')
plt.title('Distribuição de Notas (Beta ajustada entre 0 e 10)')
plt.xlabel('Nota')
plt.ylabel('Densidade de probabilidade')
plt.legend()
plt.grid(alpha=0.3)
plt.show()
