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


def x_distance(theta, force):
    # receives theta (degrees) and force (gram Force) and gives out x (millimeters)
    a = 64.37
    b = 58.89
    c = 17.73
    d = 92.65
    x = (((force * 150) / (a * 9.8)) - d) * math.tan((92 - theta + c) * math.pi / 180) + b
    