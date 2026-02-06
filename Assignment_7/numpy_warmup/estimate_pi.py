import numpy as np


def estimate_pi(N):
    pi_estimate = None
    # --- Your code here 
    points=np.random.uniform(-1,1,(N,2))
    distance = np.sum(points**2, axis=1)
    N_circle= np.sum(distance <= 1)
    pi_estimate=4*N_circle/N
    # ---

    return pi_estimate


if __name__ == "__main__":
    N = 1000
    approx_pi = estimate_pi(N)
    print(f'Estimate of pi is {approx_pi}')