import math

def Force(theta, x):
    # recieves theta (degrees) and x (meters) and gives out Fx (Newtons)
    m = 0.115
    g = 9.8
    l = 0.18
    l0_prime = 0.04
    Fx = m*g*(x*(1/math.tan(theta*math.pi/180))+l0_prime)/l
    return Fx



def Place(theta, force):
    # receives theta (degrees) and force (grm) and gives out x (meters)
    force = force * 0.00981
    m = 0.115
    g = 9.8
    l = 0.18
    l0_prime = 0.04
    x = ((l*force / m*g) - l0_prime)*math.tan(theta*math.pi/180)
    return x
