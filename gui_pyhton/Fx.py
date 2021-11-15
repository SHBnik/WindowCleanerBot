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
    x = (((force * 150) / (a * 9.8)) - d) * math.tan((theta - c) * math.pi / 180) + b
    return x

def x_d(theta, force):
    p00 = -10770
    p10 = 340.4
    p01 = 517.9
    p11 = -24.91
    p02 = -1.028
    p12 = 0.6461
    p03 = -0.2879
    p13 = -0.005718
    p04 = 0.00384
    x = (force - p00 - p01 * theta - p02 * theta**2 - p03 * theta**3 - p04 * theta**4)/(p10 + p11 * theta + p12 * theta**2 + p13 * theta**3)
    return x


def x_dis(tehta, force):
    p1 = -0.0599
    p2 = 22.4
    p3 = -721.1
    x = (-p2 + math.sqrt(p2**2 - 4 * p1 * (p3-force))) / (2 * p1)
    return x

print(x_d(33, 200))


    