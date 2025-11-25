import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import beta, gamma, t, norm
from scipy.optimize import fsolve


# IAA ou IAP
IAA = True
IAP = False

# Parâmetros desejados
if IAA:
    media_desejada = 5.477
    desvio_desejado = 2.4943
    limite_inferior = 0
    limite_superior = 10
    x_mark = 7.51  # valor demarcado
if IAP:
    media_desejada = 6.862
    desvio_desejado = 2.3265
    limite_inferior = 0
    limite_superior = 10
    x_mark = 7.71  # valor demarcado
    
# -----------------------------
# 1️⃣ Beta ajustada
def equations_beta(p):
    a, b = p
    mean = a / (a + b) * (limite_superior - limite_inferior) + limite_inferior
    var = (a * b) / ((a + b)**2 * (a + b + 1)) * (limite_superior - limite_inferior)**2
    return (mean - media_desejada, np.sqrt(var) - desvio_desejado)

a_initial, b_initial = 2, 2
a_beta, b_beta = fsolve(equations_beta, (a_initial, b_initial))

x = np.linspace(limite_inferior, limite_superior, 1000)
y_beta = beta.pdf((x - limite_inferior)/(limite_superior - limite_inferior), a_beta, b_beta) / (limite_superior - limite_inferior)
cdf_beta = beta.cdf((x_mark - limite_inferior)/(limite_superior - limite_inferior), a_beta, b_beta)

# -----------------------------
# 2️⃣ Gamma truncada
def equations_gamma(p):
    k, theta = p
    return (k*theta - media_desejada, np.sqrt(k)*theta - desvio_desejado)

k_initial, theta_initial = 5, 1
k_gamma, theta_gamma = fsolve(equations_gamma, (k_initial, theta_initial))

y_gamma_raw = gamma.pdf(x, a=k_gamma, scale=theta_gamma)
y_gamma = y_gamma_raw / np.trapz(y_gamma_raw, x)  # normaliza para 0-10
cdf_gamma_raw = gamma.cdf(x_mark, a=k_gamma, scale=theta_gamma)
cdf_gamma_total = gamma.cdf(limite_superior, a=k_gamma, scale=theta_gamma)
cdf_gamma = cdf_gamma_raw / cdf_gamma_total

# -----------------------------
# 3️⃣ t-Student truncada
df = 5
loc = media_desejada
scale = desvio_desejado/np.sqrt(df/(df-2))
y_t_raw = t.pdf(x, df, loc=loc, scale=scale)
y_t = y_t_raw / np.trapz(y_t_raw, x)
cdf_t_raw = t.cdf(x_mark, df, loc=loc, scale=scale)
cdf_t_total = t.cdf(limite_superior, df, loc=loc, scale=scale)
cdf_t = (cdf_t_raw - t.cdf(limite_inferior, df, loc=loc, scale=scale)) / (cdf_t_total - t.cdf(limite_inferior, df, loc=loc, scale=scale))

# -----------------------------
# 4️⃣ Normal truncada
y_norm_raw = norm.pdf(x, loc=media_desejada, scale=desvio_desejado)
y_norm = y_norm_raw / np.trapz(y_norm_raw, x)
cdf_norm_raw = norm.cdf(x_mark, loc=media_desejada, scale=desvio_desejado)
cdf_norm_total = norm.cdf(limite_superior, loc=media_desejada, scale=desvio_desejado)
cdf_norm = (cdf_norm_raw - norm.cdf(limite_inferior, loc=media_desejada, scale=desvio_desejado)) / (cdf_norm_total - norm.cdf(limite_inferior, loc=media_desejada, scale=desvio_desejado))

# -----------------------------
# Plot comparativo
plt.figure(figsize=(10,6))
plt.plot(x, y_beta, 'r-', lw=2, label='Beta ajustada')
plt.plot(x, y_gamma, 'g-', lw=2, label='Gamma truncada')
plt.plot(x, y_t, 'b-', lw=2, label='t-Student truncada')
plt.plot(x, y_norm, 'y-', lw=2, label='Normal truncada')
plt.axvline(x=x_mark, color='k', linestyle='--', lw=2, label=f'x = {x_mark}')
if IAA:
    plt.title('Comparação de distribuições para IAA (0 a 10)')
if IAP:
    plt.title('Comparação de distribuições para IAP (0 a 10)')
plt.xlabel('Nota')
plt.ylabel('Densidade de probabilidade')
plt.grid(alpha=0.3)
plt.legend()
plt.show()

# -----------------------------
# Print dos percentuais acumulados
print(f"Percentual acumulado até {x_mark} (Beta ajustada): {cdf_beta*100:.2f}%")
print(f"Percentual acumulado até {x_mark} (Gamma truncada): {cdf_gamma*100:.2f}%")
print(f"Percentual acumulado até {x_mark} (t-Student truncada): {cdf_t*100:.2f}%")
print(f"Percentual acumulado até {x_mark} (Normal truncada): {cdf_norm*100:.2f}%")
