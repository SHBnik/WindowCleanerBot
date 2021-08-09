import math

def Force(theta, x):
    # recieves theta (degrees) and x (meters) and gives out Fx (Newtons)
    m = 0.115
    g = 9.8
    l = 0.18
    l0_prime = 0.04
    Fx = m*g*(x*(1/math.tan(theta*math.pi/180))+l0_prime)/l
    return Fx

